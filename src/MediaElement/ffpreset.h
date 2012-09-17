/* ---------------------------------------------------------------------------
** Author: Martin Geier
** ffpreset.h is part of OniboConverter2.
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

#ifndef FFPRESET_H_
#define FFPRESET_H_

#include <set>
#include <list>
#include <string>
#include "../CppExtension/path.h"
#include "../CppExtension/hashmap.h"

namespace MediaElement {

class FFpreset {
public:
	enum FFType{
		BUILDIN_FFTYPE = 0, USERDEFINED_FFTYPE = 1, DISABLE_FFTYPE = 2
	};
	FFpreset();
	FFpreset(const Path& path, const std::string& prefix, const FFType& type);
	std::string getPrefix() const;
	virtual ~FFpreset();
//	std::string toStr() const;
	std::string readableForm() const;
//	Converter::ConvertSettingsList getConvertArguments() const;
	std::string getName() const;
	Path getPath() const;
	FFType getType() const;
private:
	std::string cropName(const std::string& name, const std::string& prefix);
	std::string name;
	std::string prefix;
	Path ffpresetFilePath;
	FFType type;
};

class FFpresets{
public:
	FFpresets();
	void addFFpreset(const FFpreset& ffpreset);
	void loadFromFolder(const Path& path, const bool& buildin);
	std::list<FFpreset> getFFpresetList(const std::string& prefix) const;
private:
	//std::list<FFpreset> ffpresets;
	CppExtension::MultiHashMap<std::string, FFpreset> prefixToFFpreset;
};

} /* namespace MediaElement */
#endif /* FFPRESET_H_ */
