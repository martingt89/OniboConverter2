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
#include "../Xml/xmlprofileparser.h"
#include "../ConverterOptions/ffpreset.h"
namespace Profile {

class ProfileLoader {
public:
	ProfileLoader();
	virtual ~ProfileLoader();
	bool load(const Path& profilesFolder, Profiles& profiles);
private:
	bool parseProfileFromFile(const Path& file, Profile& profile);
	bool getRegularFilesFromFolder(const Path& profilesFolder, std::list<Path>& profileFiles);
	Xml::XmlProfileParser parser;
};

} /* namespace Profile */
#endif /* PROFILELOADER_H_ */
