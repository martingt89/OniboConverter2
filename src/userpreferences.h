/* ---------------------------------------------------------------------------
** Author: Martin Geier
** userpreferences.h is part of OniboConverter2.
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

#ifndef USERPREFERENCES_H_
#define USERPREFERENCES_H_

#include "CppExtension/path.h"
#include "CppExtension/hashmap.h"

class UserPreferences {
public:
	enum UserPreferencesOpt{
		BEGIN = 0,
		DESTINATION_PATH = 1,
		EXT_CONVERTER_PATH = 2,
		NUM_OF_CPU = 3,
		ENABLE_MULTITHREAD_FOR_ENC = 4,
		DISABLE_SHOW_UNENCODER = 5,
		END = 6
	};
public:
	static UserPreferences* getInstance();
	virtual ~UserPreferences();

	void setConvertDestinationPath(const Path& destination);
	void setExtConverterPath(const Path& path);
	void setNumberOfCPU(const int& number, bool automatic = false);
	void setMultithreadingForEncoders(const bool& support);
	void setDisableShowUnEncoders(const bool& disable);
	//
	Path getConvertDestinationPath() const;
	Path getExtConverterPath() const;
	int getNumerOfCPU() const;
	bool isAutomaticNumberOfCPU() const;
	bool isMultithreadinForEncoders() const;
	bool isDisableShowUnEncoders() const;
	//
	void save();
private:
	static UserPreferences* instance;
	UserPreferences();
	UserPreferences(const UserPreferences&);
	CppExtension::HashMap<UserPreferencesOpt, std::string> optToValue;
};

#endif /* USERPREFERENCES_H_ */
