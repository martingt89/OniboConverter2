/*
 * resolution.cpp
 *
 *  Created on: 24.7.2012
 *      Author: martint
 */

#include "resolution.h"
#include <algorithm>
#include "../helper.h"

namespace MediaElement {

static const std::string ORIGINAL="--- original ---";

Resolution::Resolution(std::string name, AspectRatio aspectRatio, int x, int y, bool isBasic):
		resolution(x,y), aspectRatio(aspectRatio) {
	this->name = name;
	this->basic = isBasic;
	isset = true;
}
bool Resolution::isSet(){
	return isset;
}
void Resolution::setBasic(){
	basic = true;
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
bool Resolution::operator<(const Resolution& second) const{
	if(this->resolution.first == second.resolution.first){
		return this->resolution.second < second.resolution.second;
	}
	return this->resolution.first < second.resolution.first;
}
bool Resolution::operator==(const Resolution& second) const{
	return (this->resolution.first == second.resolution.first) && (this->resolution.second == second.resolution.second);
}
std::string Resolution::readableForm() const{
	if(resolution.first > 0 && resolution.second > 0){
		std::string resol = toS(resolution.first)+" x "+toS(resolution.second);
		return resol + "\t" + this->getAspectRatio().readableForm();
	}else{
		return ORIGINAL;
	}
}
bool Resolution::isOriginal() const{
	return (resolution.first <= 0 || resolution.second <= 0);
}
//==============================================================================================================
void Resolutions::addResolution(const Resolution& resolution){
	aspectToResolution.set(resolution.getAspectRatio(), resolution);
}
std::list<Resolution> Resolutions::getResolutionsByAspectRatio(const AspectRatio& aspectRatio) const{
	return aspectToResolution.get(aspectRatio);
}
std::list<AspectRatio> Resolutions::getAspectRatios() const{
	std::list<AspectRatio> aspectRatious;
	return aspectToResolution.getListOfKeys();
}

std::list<Resolution> Resolutions::getResolutions() const{
	std::list<Resolution> resolution = aspectToResolution.getListOfValues();
	std::map<std::string, std::list<Resolution> >::const_iterator iterator;
	resolution.sort();
	return resolution;
}

Resolution Resolutions::getResolutionBySize(const int& x, const int& y, bool& found) const{
	auto resol = getResolutions();
	auto find = std::find_if(resol.begin(), resol.end(), [&, x, y](const Resolution& resolution) -> bool{
		return (resolution.getValue().first == x) && (resolution.getValue().second == y);
	});
	if(find != resol.end()){
		found = true;
		return *find;
	}
	found = false;
	return Resolution();
}
//==============================================================================================================
AspectRatio::AspectRatio(){
//	this->aspectRatio = "";
	aspectX = 0;
	aspectY = 0;
}
AspectRatio AspectRatio::createFromString(const std::string& XcolomnY){
	std::string::size_type pos = XcolomnY.find(":");
	int x = 0;
	int y = 0;
	if(pos != std::string::npos){
		x = toN(XcolomnY.substr(0, pos), int());
		y = toN(XcolomnY.substr(pos+1), int());
	}
	return AspectRatio(x, y);
}
AspectRatio::AspectRatio(const int& x, const int& y){
	aspectX = x;
	aspectY = y;
}
std::string AspectRatio::readableForm() const{
	return toS(aspectX)+":"+toS(aspectY);
}
std::string AspectRatio::getXcolonY() const{
	return toS(aspectX) + ":" + toS(aspectY);
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
bool AspectRatio::operator<(const AspectRatio& second) const{
	if(this->aspectX == second.aspectX){
		return this->aspectY < second.aspectY;
	}
	return this->aspectX < second.aspectX;
}
bool AspectRatio::operator==(const AspectRatio& second) const{
	return (this->aspectX == second.aspectX) && (this->aspectY == second.aspectY);
}

} /* namespace MediaElement */
