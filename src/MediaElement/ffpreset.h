/*
 * ffpreset.h
 *
 *  Created on: 25.7.2012
 *      Author: martint
 */

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
