/*
 * guisettings.cpp
 *
 *  Created on: 4.7.2012
 *      Author: martint
 */

#include "guisettings.h"
#include "../Tools/regextools.h"
#include "../Tools/helper.h"
#include <algorithm>
#include <iostream> //todo remove
namespace AVBox {

GuiSettings::GuiSettings() {

}

GuiSettings::~GuiSettings() {

}

void GuiSettings::addVideoResolution(const std::string& ratio, const std::string& resolution, const std::string& name){
	RegexTools::Regex reg("([[:digit:]]+)x([[:digit:]]+)");
	RegexTools::Matcher match = reg.getMatcher(resolution);
	if(match.find()){
		ResolutionStruct res;
		res.x = toN(match.getGroup(1), int());
		res.y = toN(match.getGroup(2), int());
		res.name = name;
		res.ratio = ratio;
		res.resolution = resolution;
		ratioToResolution[ratio].push_back(res);
	}
}
void GuiSettings::addVideoBitrate(const std::string& bitrate){
	int bitr = toN(bitrate, int());
	this->vbitrate.push_back(bitr);
}
void GuiSettings::addVideoFramerate(const std::string& framerate){
	double frame = toN(framerate, double());
	this->vframerate.push_back(frame);
}
void GuiSettings::addAudioBitrate(const std::string& bitrate){
	int bitr = toN(bitrate, int());
	this->abitrate.push_back(bitr);
}
void GuiSettings::addAudioSamplerate(const std::string& samplerate){
	int samp = toN(samplerate, int());
	this->abitrate.push_back(samp);
}
std::list<int> GuiSettings::getVideoBitrates() const{
	return vbitrate;
}
std::list<double> GuiSettings::getVideoFramerates() const{
	return vframerate;
}
std::list<std::string> GuiSettings::getVideoRatios() const{
	std::list<std::string> ratios;
	std::map<std::string, std::list<ResolutionStruct> >::const_iterator it;
	for(it = ratioToResolution.begin(); it != ratioToResolution.end(); ++it){
		ratios.push_back(it->first);
	}
	return ratios;
}
std::list<GuiSettings::ResolutionStruct> GuiSettings::getVideoResolution() const{
	std::list<GuiSettings::ResolutionStruct> resol;
	std::map<std::string, std::list<ResolutionStruct> >::const_iterator it;
	for(it = ratioToResolution.begin(); it != ratioToResolution.end(); ++it){
		std::copy(it->second.begin(), it->second.end(),  std::front_inserter(resol));
	}
	return resol;
}
std::list<GuiSettings::ResolutionStruct> GuiSettings::getVideoResolution(const std::string &ratio) const{
	std::list<GuiSettings::ResolutionStruct> resol;
	std::map<std::string, std::list<ResolutionStruct> >::const_iterator it;
	it = ratioToResolution.find(ratio);
	if(it != ratioToResolution.end()){
		std::copy(it->second.begin(), it->second.end(),  std::front_inserter(resol));
	}
	return resol;
}
} /* namespace AVBox */
