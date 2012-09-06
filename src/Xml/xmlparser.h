/*
 * xmlparser.h
 *
 *  Created on: 7.9.2012
 *      Author: martin
 */

#ifndef XMLPARSER_H_
#define XMLPARSER_H_

#include <libxml++/libxml++.h>
#include "../CppExtension/path.h"

namespace Xml {

typedef std::list<std::pair<std::list<std::string>, std::string> > XmlParserData;

class XmlParser : public xmlpp::SaxParser  {
public:
	XmlParser();
	virtual ~XmlParser();
	bool parseFile(const Path& filePath, XmlParserData* data);
protected:
	virtual void on_start_element(const Glib::ustring& name, const AttributeList& attributes);
	virtual void on_end_element(const Glib::ustring& name);
	virtual void on_characters(const Glib::ustring& characters);
	std::list<std::string> path;
	XmlParserData *data;
};

} /* namespace Xml */
#endif /* XMLPARSER_H_ */
