/*
 * profileloader.h
 *
 *  Created on: 12.8.2012
 *      Author: martint
 */

#ifndef PROFILELOADER_H_
#define PROFILELOADER_H_

#include "../CppExtension/path.h"
#include "profile.h"
#include "xmlprofileparser.h"
#include "../ConverterOptions/ffpreset.h"
namespace Profile {

class ProfileLoader {
public:
	ProfileLoader();
	virtual ~ProfileLoader();
	bool load(const Path& profilesFolder,
			const CppExtension::HashMap<std::string, ConverterOptions::FFpresets>& buildInFFpresets,
			Profiles& profiles);
private:
	bool parseProfileFromFile(const Path& file, Profile& profile);
	bool getRegularFilesFromFolder(const Path& profilesFolder, std::list<Path>& profileFiles);
	XmlProfileParser parser;
};

} /* namespace Profile */
#endif /* PROFILELOADER_H_ */
