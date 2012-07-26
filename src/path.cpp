/*
 * path.cpp
 *
 *  Created on: 26.7.2012
 *      Author: martint
 */

#include "path.h"

Path::Path(std::string path) : path(path) {

}

Path::~Path() {

}

std::string Path::getPath() const{
	return path;
}
