/*
 * path.cpp
 *
 *  Created on: 26.7.2012
 *      Author: martint
 */

#include "path.h"
#include <error.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <glibmm/miscutils.h>
//#include <iostream>

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
//	std::cout<<"testujem: "<<path<<std::endl;
	struct stat buffer ;
	if ( stat( path.c_str(), &buffer ) == 0 ){
		return true;
	}
	return false;
}

bool Path::operator==(const Path& path) const{
	return (this->path == path.path) && (this->type == path.type);
}

