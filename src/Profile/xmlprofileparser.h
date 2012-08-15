/*
 * xmlprofileparser.h
 *
 *  Created on: 12.8.2012
 *      Author: martint
 */

#ifndef XMLPROFILEPARSER_H_
#define XMLPROFILEPARSER_H_

#include "../CppExtension/path.h"
#include "profile.h"
#include <libxml++/libxml++.h>
#include <initializer_list>
#include "../CppExtension/hashmap.h"
namespace Profile {

class XmlProfileParser : public xmlpp::SaxParser {
public:
	XmlProfileParser();
	virtual ~XmlProfileParser();
	bool parseFile(const Path& filePath, Profile& profile);
protected:
	virtual void on_start_element(const Glib::ustring& name, const AttributeList& attributes);
	virtual void on_end_element(const Glib::ustring& name);
	virtual void on_characters(const Glib::ustring& characters);
	bool toOptions(const std::list<std::string>& path, Profile::Options& options);
	std::string toPath(const std::initializer_list<std::string>& path);
	std::string toPath(const std::list<std::string>& path);
	std::list<std::string> path;
	Profile* actualProfile;

	CppExtension::HashMap<std::string, Profile::Options> pathToOptions;
};

} /* namespace Profile */
#endif /* XMLPROFILEPARSER_H_ */
