/*
 * resolution.cpp
 *
 *  Created on: 24.7.2012
 *      Author: martint
 */

#include "resolution.h"
#include <algorithm>

namespace ConverterOptions {

Resolution::Resolution(std::string name, std::string aspectRatio, int x, int y): resolution(x,y) {
	this->name = name;
	this->aspectRatio = aspectRatio;

}

std::pair<int, int> Resolution::getValue() const{
	return resolution;
}
std::string Resolution::getName() const{
	return name;
}
std::string Resolution::getAspectRatio() const{
	return aspectRatio;
}

bool Resolution::operator<(const Resolution& res2){
	return this->resolution.first < res2.getValue().first;
}
void Resolutions::addResolution(const Resolution& resolution){
	resolutions[resolution.getAspectRatio()].push_back(resolution);
}
std::list<Resolution> Resolutions::getResolutionsByAspectRatio(const std::string& aspectRatio) const{
	auto iterator = resolutions.find(aspectRatio);
	if(iterator == resolutions.end()){
		return std::list<Resolution>();
	}
	return std::list<Resolution>(iterator->second);
}
std::list<std::string> Resolutions::getAspectRatios() const{
	std::list<std::string> aspectRatious;
	for(auto iterator = resolutions.begin(); iterator != resolutions.end(); ++iterator){
		aspectRatious.push_back(iterator->first);
	}
	return aspectRatious;
}

std::list<Resolution> Resolutions::getResolutions() const{
	std::list<Resolution> resolution;
	std::map<std::string, std::list<Resolution> >::const_iterator iterator;
	for(iterator = resolutions.begin(); iterator != resolutions.end(); ++iterator){
		std::copy(iterator->second.begin(), iterator->second.end(), back_inserter(resolution));
	}
	resolution.sort();
	return resolution;
}

} /* namespace ConverterOptions */
