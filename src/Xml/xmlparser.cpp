/* ---------------------------------------------------------------------------
** Author: Martin Geier
** xmlparser.cpp is part of OniboConverter2.
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

#include "xmlparser.h"
#include "../helper.h"
#include <iostream>	//todo replace with logging

namespace Xml {

XmlParser::XmlParser() {
	data = NULL;
}

XmlParser::~XmlParser() {}

bool XmlParser::parseFile(const Path& filePath, XmlParserData* data){
	this->data = data;
	try{
		this->parse_file(filePath.getPath());
	}catch(std::exception& exception){
		std::cerr<<"Error: 'xmlparser.cpp' "<<exception.what()<<std::endl;
		data = NULL;
		return false;
	}
	data = NULL;
	return true;
}

void XmlParser::on_start_element(const Glib::ustring& name, const AttributeList&){
	path.push_back(name);
}
void XmlParser::on_end_element(const Glib::ustring&){
	path.pop_back();
}
void XmlParser::on_characters(const Glib::ustring& characters){
		if(data){
			std::string value = clearString(characters);
			if(value.size() > 0){
				std::pair<std::list<std::string>, std::string> pair;
				pair.first = path;
				pair.second = value;
				data->push_back(pair);
			}
		}
}

} /* namespace Xml */
