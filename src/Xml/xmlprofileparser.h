/*
 * xmlprofileparser.h
 *
 *  Created on: 12.8.2012
 *      Author: martint
 */

#ifndef XMLPROFILEPARSER_H_
#define XMLPROFILEPARSER_H_

#include <libxml++/libxml++.h>
#include "../xmlfilesdefinitions.h"
#include "../CppExtension/path.h"
#include "../CppExtension/hashmap.h"
#include "../Profile/profile.h"

namespace Xml {

class XmlProfileParser : public xmlpp::SaxParser {
public:
	XmlProfileParser();
	virtual ~XmlProfileParser();
	bool parseFile(const Path& filePath, Profile::Profile& profile);
protected:
	virtual void on_start_element(const Glib::ustring& name, const AttributeList& attributes);
	virtual void on_end_element(const Glib::ustring& name);
	virtual void on_characters(const Glib::ustring& characters);
	std::list<std::string> path;
	Profile::Profile* actualProfile;
};

} /* namespace Xml */
#endif /* XMLPROFILEPARSER_H_ */
