/* ---------------------------------------------------------------------------
** Author: Martin Geier
** xmlparser.h is part of OniboConverter2.
**
** OniboConverter2 is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program.  If not, see <http://www.gnu.org/licenses/>.
** -------------------------------------------------------------------------*/

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
