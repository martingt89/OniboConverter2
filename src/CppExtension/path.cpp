/*
 * path.cpp
 *
 *  Created on: 26.7.2012
 *      Author: martint
 */

#include "path.h"

Path::Path(std::string path) : path(path) {
	//test if path exist
}

Path::~Path() {

}

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


