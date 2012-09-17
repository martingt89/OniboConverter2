/* ---------------------------------------------------------------------------
** Author: Martin Geier
** settingsgenerator.h is part of OniboConverter2.
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

#ifndef SETTINGSGENERATOR_H_
#define SETTINGSGENERATOR_H_

#include "xmlgenerator.h"
#include "../CppExtension/path.h"
#include "../CppExtension/hashmap.h"
#include "../userpreferences.h"

namespace Xml {

class SettingsGenerator {
public:
	SettingsGenerator(const Path& destination);
	virtual ~SettingsGenerator();
	void setFFpath(const Path& ffmpegPath);
	void setDestination(const Path& destination);
	void save(CppExtension::HashMap<UserPreferences::UserPreferencesOpt, std::string> optToValue);
private:
	std::vector<PathNode> toPathVector(std::list<std::string> list, std::string value);
	Path settingsFile;
};

} /* namespace Xml */
#endif /* SETTINGSGENERATOR_H_ */
