/*
 * settingsgenerator.h
 *
 *  Created on: 30.8.2012
 *      Author: martint
 */

#ifndef SETTINGSGENERATOR_H_
#define SETTINGSGENERATOR_H_

#include "../CppExtension/path.h"
#include "xmlgenerator.h"

namespace Xml {

class SettingsGenerator {
public:
	SettingsGenerator(const Path& settingsFile, const Path& ffmpegPath, const Path& destination);
	virtual ~SettingsGenerator();
	void setFFpath(const Path& ffmpegPath);
	void setDestination(const Path& destination);
	void save();
private:
	Path settingsFile;
	Path ffmpegPath;
	Path destination;
};

} /* namespace Xml */
#endif /* SETTINGSGENERATOR_H_ */
