/* ---------------------------------------------------------------------------
** Author: Martin Geier
** systemsettings.h is part of OniboConverter2.
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

#ifndef SYSTEMSETTINGS_H_
#define SYSTEMSETTINGS_H_

#include "CppExtension/path.h"
#include "Xml/settingsgenerator.h"

class SystemSettings {
public:
	static SystemSettings* getInstance();
	virtual ~SystemSettings();
	Path getFFpresetFolder();
	Path getXmlConfigFilePath();
	Path getDefaultProfilesPath();
	Path getUserProfilesPath();
	Path getUserSettingsFile();
	Path getGladeFilesFolder();
private:
	SystemSettings();
	static SystemSettings* instance;
	Path ffpresetFolder;
	Path xmlConfigFilePath;
	Path defaultProfilesPath;
	Path userProfilesPath;
	Path userConfigDir;
	Path userSettingsFile;
	Path gladeFilesFolder;
};

#endif /* SYSTEMSETTINGS_H_ */
