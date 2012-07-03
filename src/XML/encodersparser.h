/*
 * encodersparser.h
 *
 *  Created on: 30.6.2012
 *      Author: martint
 */

#ifndef ENCODERSPARSER_H_
#define ENCODERSPARSER_H_

#include <libxml++/libxml++.h>
#include <glibmm/ustring.h>
#include <string>
#include "../AVBox/formattoencoders.h"

namespace XML {

class EncodersParser : public xmlpp::SaxParser{
public:
	EncodersParser();
	virtual ~EncodersParser();
	bool parse(AVBox::FormatToEncoders& box);
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
	AVBox::FormatToEncoders *encoders;
	std::string actualFormat;
	std::string presentsPrefix;
	bool inEnc;
};

} /* namespace XML */
#endif /* ENCODERSPARSER_H_ */
