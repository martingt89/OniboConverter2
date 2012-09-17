/* ---------------------------------------------------------------------------
** Author: Martin Geier
** path.cpp is part of OniboConverter2.
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

#include "path.h"
#include <error.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <glibmm/miscutils.h>
#include <iostream>
#include <giomm/file.h>

Path::Path(std::string path,  PathType type) : path(path), type(type) {}

Path::Path(std::string first, std::string second, PathType type) : type(type){
	path = Glib::build_filename(first, second);
}

Path::~Path() {}

std::string Path::getPath() const{
	return path;
}

std::string Path::getLastPathPart() const{
	std::string tmpPath = path;
	std::string::size_type position = tmpPath.find_last_of('/');
	if(position == path.size() -1){
		tmpPath = tmpPath.substr(0, path.size() -1);
		position = tmpPath.find_last_of('/');
	}
	if(position != std::string::npos){
		tmpPath = tmpPath.substr(position+1);
	}
	return tmpPath;
}

bool Path::getSubfiles(std::list<Path>& fileList) const{
	try {
		Glib::RefPtr<Gio::File> directory = Gio::File::create_for_path(path);
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
				fileList.push_back(Path(directory->get_path(), file_info->get_name()));
			}
			file_info = enumerator->next_file();
		}
	} catch (const Glib::Exception& ex) {
		std::cerr <<"Error: 'path.cpp' path: "<<path<< std::endl;
		std::cerr <<"Error: 'path.cpp' "<<ex.what() << std::endl;
	}
	return true;
}

bool Path::create() const{
	int res = mkdir(path.c_str(), 0777);
	if (res == 0){
		return true;
	}
	if(res == -1 && errno == EEXIST){
		return true;
	}
	return false;
}

bool Path::exist() const{
	struct stat buffer ;
	if ( stat( path.c_str(), &buffer ) == 0 ){
		return true;
	}
	return false;
}

bool Path::operator==(const Path& path) const{
	return (this->path == path.path) && (this->type == path.type);
}
