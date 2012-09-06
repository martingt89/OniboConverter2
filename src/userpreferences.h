/*
 * userpreferences.h
 *
 *  Created on: 6.9.2012
 *      Author: martin
 */

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
		END = 5
	};
public:
	static UserPreferences* getInstance();
	virtual ~UserPreferences();

	void setConvertDestinationPath(const Path& destination);
	void setExtConverterPath(const Path& path);
	void setNumberOfCPU(const int& number, bool automatic = false);
	void setMultithreadingForEncoders(const bool& support);
	//
	Path getConvertDestinationPath() const;
	Path getExtConverterPath() const;
	int getNumerOfCPU() const;
	bool isAutomaticNumberOfCPU() const;
	bool isMultithreadinForEncoders() const;
	//
	void save();
private:
	static UserPreferences* instance;
	UserPreferences();
	UserPreferences(const UserPreferences&);
	CppExtension::HashMap<UserPreferencesOpt, std::string> optToValue;
};

#endif /* USERPREFERENCES_H_ */
