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

namespace ConverterOptions {

class FFpreset {
public:
	struct FFfile{
		std::string path;
		std::string name;
	};
public:
	FFpreset(const Path& path);
	virtual ~FFpreset();
	void addUserDefineFile(const std::string& prefix, const std::string& path);
	bool getFFpresetsByPrefix(const std::string& prefix, std::list<std::pair<std::string, std::string> > &ffpresets);
private:
	std::string cropName(const std::string& name, const std::string& prefix);
	//std::map<std::string, std::list<FFfile> > ffpreset;
	CppExtension::MultiHashMap<std::string, FFfile> ffpreset;
	std::set<std::string> searchedPrefixes;
	Path ffpresetFolderPath;
};

} /* namespace ConverterOptions */
#endif /* FFPRESET_H_ */
