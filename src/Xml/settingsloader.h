/*
 * settingsloader.h
 *
 *  Created on: 30.8.2012
 *      Author: martint
 */

#ifndef SETTINGSLOADER_H_
#define SETTINGSLOADER_H_

#include "../CppExtension/path.h"
#include "../CppExtension/hashmap.h"
#include <libxml++/libxml++.h>

namespace Xml {

class SettingsLoader : public xmlpp::SaxParser {
private:
	enum SettingsProperty{
		FFMPEG_PATH_PROPERTY, DESTINATION_PATH_PROPERTY
	};
public:
	SettingsLoader(const Path& settingsFilePath);
	virtual ~SettingsLoader();
	Path getFFConverterPath();
	Path getDestinationPath();
	bool load();
protected:
	virtual void on_start_element(const Glib::ustring& name, const AttributeList& attributes);
	virtual void on_end_element(const Glib::ustring& name);
	virtual void on_characters(const Glib::ustring& characters);
private:
	Path settingsFilePath;
	std::list<std::string> path;
	CppExtension::HashMap<std::list<std::string>, SettingsProperty> pathToProperty;
	CppExtension::HashMap<SettingsProperty, std::string> propertyToValue;
};

} /* namespace Xml */
#endif /* SETTINGSLOADER_H_ */
