/*
 * containersparser.h
 *
 *  Created on: 30.6.2012
 *      Author: martint
 */

#ifndef CONTAINERSPARSER_H_
#define CONTAINERSPARSER_H_

#include <libxml++/libxml++.h>
#include <glibmm/ustring.h>
#include <string>
#include "../AVBox/container.h"
#include "../AVBox/avbox.h"

namespace XML {

class ContainersParser : public xmlpp::SaxParser{
public:
	ContainersParser();
	virtual ~ContainersParser();
	bool parse(AVBox::AVBox& box);
protected:
	virtual void on_start_document();
	virtual void on_end_document();
	virtual void on_start_element(const Glib::ustring& name, const AttributeList& attributes);
	virtual void on_end_element(const Glib::ustring& name);
	virtual void on_characters(const Glib::ustring& characters);
	virtual void on_comment(const Glib::ustring& text);
	virtual void on_warning(const Glib::ustring& text);
	virtual void on_error(const Glib::ustring& text);
	virtual void on_fatal_error(const Glib::ustring& text);
	virtual void on_cdata_block(const Glib::ustring& text);
private:
	enum FortmaType{
		NONE, AUDIO, VIDEO
	};
	AVBox::Container *tmpContainer;
	FortmaType formatType;
	AVBox::AVBox *avBox;
	bool setCodec;
};

} /* namespace XML */
#endif /* CONTAINERSPARSER_H_ */
