/*
 * resolution.cpp
 *
 *  Created on: 24.7.2012
 *      Author: martint
 */

#include "resolution.h"
#include <algorithm>
#include "../helper.h"

namespace ConverterOptions {

Resolution::Resolution(std::string name, std::string aspectRatio, int x, int y, bool isBasic):
		resolution(x,y), aspectRatio(aspectRatio) {
	this->name = name;
	this->basic = isBasic;
}

std::pair<int, int> Resolution::getValue() const{
	return resolution;
}
std::string Resolution::getName() const{
	return name;
}
AspectRatio Resolution::getAspectRatio() const{
	return aspectRatio;
}
bool Resolution::isBasic() const{
	return basic;
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
std::list<AspectRatio> Resolutions::getAspectRatios() const{
	std::list<AspectRatio> aspectRatious;
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

std::string Resolutions::getNameByResolution(const int& x, const int& y) const{
	auto resol = getResolutions();
	auto find = std::find_if(resol.begin(), resol.end(), [&, x, y](const Resolution& resolution) -> bool{
		return (resolution.getValue().first == x) && (resolution.getValue().second == y);
	});
	if(find != resol.end()){
		return find->getName();
	}
	return "";
}

AspectRatio::AspectRatio(){
	this->aspectRatio = "";
	aspectX = 0;
	aspectY = 0;
}
AspectRatio::AspectRatio(const std::string& aspect){
	this->aspectRatio = aspect;
	std::string::size_type pos = aspect.find(":");
	if(pos != std::string::npos){
		aspectX = toN(aspect.substr(0, pos), int());
		aspectY = toN(aspect.substr(pos+1), int());
	}else{
		aspectX = 0;
		aspectY = 0;
	}
}
AspectRatio::operator std::string (){
	return aspectRatio;
}
int AspectRatio::convertXtoY(int x){
	if(aspectX > 0 && aspectY > 0){
		return (x/(double)aspectX)*aspectY;
	}
	return 0;
}
int AspectRatio::convertYtoX(int y){
	if(aspectX > 0 && aspectY > 0){
		return (y/(double)aspectY)*aspectX;
	}
	return 0;
}

} /* namespace ConverterOptions */
