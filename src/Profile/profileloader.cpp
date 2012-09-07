/*
 * profileloader.cpp
 *
 *  Created on: 12.8.2012
 *      Author: martint
 */

#include "profileloader.h"
#include <giomm/file.h>
#include <iostream> //todo remove replace with log
#include <glibmm/miscutils.h>

namespace Profile {

ProfileLoader::ProfileLoader() {}

ProfileLoader::~ProfileLoader() {}

bool ProfileLoader::load(const Path& profilesFolder, Profiles& profiles){
	std::list<Path> profileFiles;
	bool res = getRegularFilesFromFolder(profilesFolder, profileFiles);
	if(!res){
		return false;
	}
	std::for_each(profileFiles.begin(), profileFiles.end(), [&](const Path& filePath){
		Profile profile;
		bool res = parseProfileFromFile(filePath, profile);
		if(res){
			profiles.push_back(profile);
		}
	});
	return true;
}

bool ProfileLoader::parseProfileFromFile(const Path& file, Profile& profile){
	return parser.load(file, profile);
}

bool ProfileLoader::getRegularFilesFromFolder(const Path& profilesFolder, std::list<Path>& profileFiles) {
	try {
		Glib::RefPtr<Gio::File> directory = Gio::File::create_for_path(profilesFolder.getPath());
		if (!directory) {
			std::cerr << "folder not found" << std::endl;
				return false;
		}
		Glib::RefPtr<Gio::FileEnumerator> enumerator = directory->enumerate_children();
		if (!enumerator) {
			std::cerr << "Gio::File::enumerate_children() returned an empty RefPtr." << std::endl;
				return false;
		}
		Glib::RefPtr<Gio::FileInfo> file_info = enumerator->next_file();
		while (file_info) {
			if (file_info->get_file_type() == Gio::FILE_TYPE_REGULAR) {
				profileFiles.push_back(Path(directory->get_path(), file_info->get_name()));
			}
			file_info = enumerator->next_file();
		}
	} catch (const Glib::Exception& ex) {
		std::cerr << ex.what() << std::endl;
	}
	return true;
}

} /* namespace Profile */
