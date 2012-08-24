/*
 * profiletoxmlconverter.h
 *
 *  Created on: 24.8.2012
 *      Author: martint
 */

#ifndef PROFILETOXMLCONVERTER_H_
#define PROFILETOXMLCONVERTER_H_

#include "../Profile/profile.h"
#include "xmlgenerator.h"

namespace Xml {

class ProfileToXmlConverter {
public:
	ProfileToXmlConverter();
	virtual ~ProfileToXmlConverter();
	bool convertToFile(const Profile::Profile& profile, const Path& filePath);

private:
	void getManualXml(const XmlGenerator& generator, const Profile::Profile& profile, XmlDocument* doc);
	void getVideoXml(const XmlGenerator& generator, const Profile::Profile& profile, XmlDocument* doc);
	void getAudioXml(const XmlGenerator& generator, const Profile::Profile& profile, XmlDocument* doc);
};

} /* namespace Xml */
#endif /* PROFILETOXMLCONVERTER_H_ */
