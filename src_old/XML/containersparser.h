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
#include <map>
#include "../AVBox/container.h"
#include "../AVBox/avbox.h"

namespace XML {

class ContainersParser : public xmlpp::SaxParser{
public:
	ContainersParser(const std::list<AVBox::AVFormat>& formats);
	virtual ~ContainersParser();
	std::map<std::string, AVBox::Container> getContainersWithNames() const;
	bool parse(AVBox::AVBox* box);
protected:
	virtual void on_start_element(const Glib::ustring& name, const AttributeList& attributes);
	virtual void on_end_element(const Glib::ustring& name);
	virtual void on_characters(const Glib::ustring& characters);
private:
	std::list<AVBox::Container> containers;
	std::map<std::string, AVBox::AVFormat> formats;
	bool setFormat;
};

} /* namespace XML */
#endif /* CONTAINERSPARSER_H_ */
