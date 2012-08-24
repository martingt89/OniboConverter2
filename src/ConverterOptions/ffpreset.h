/*
 * ffpreset.h
 *
 *  Created on: 25.7.2012
 *      Author: martint
 */

#ifndef FFPRESET_H_
#define FFPRESET_H_

#include <set>
#include <map>
#include <list>
#include <string>
#include "../CppExtension/path.h"
#include "../CppExtension/hashmap.h"
#include "../Converter/convertsettings.h"
namespace ConverterOptions {

class FFpreset {
public:
	FFpreset();
	FFpreset(const Path& path, const std::string& prefix, const bool& buildin);
	std::string getPrefix() const;
	virtual ~FFpreset();
	std::string toStr() const;
	Converter::ConvertSettingsList getConvertArguments() const;
	std::string getName() const;
	Path getPath() const;
	bool isBuildIn() const;
private:
	std::string cropName(const std::string& name, const std::string& prefix);
	std::string name;
	std::string prefix;
	Path ffpresetFilePath;
	bool buildin;
};

class FFpresets{
public:
	FFpresets();
	FFpresets(const std::string& prefix);
	FFpresets(const std::string& prefix, const Path& ffpresetsDirectory, const bool& buildin);
	void addFFpreset(const FFpreset& ffpreset);
	bool loadFromFolder(const Path& path, const bool& buildin);
	std::list<FFpreset> getFFpresetList();
private:
	std::list<FFpreset> ffpresets;
	std::string prefix;
};

} /* namespace ConverterOptions */
#endif /* FFPRESET_H_ */
