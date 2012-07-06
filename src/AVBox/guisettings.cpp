/*
 * guisettings.cpp
 *
 *  Created on: 4.7.2012
 *      Author: martint
 */

#include "guisettings.h"
#include "../regextools.h"
#include "../helper.h"

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
} /* namespace AVBox */
