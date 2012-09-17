/* ---------------------------------------------------------------------------
** Author: Martin Geier
** profile.cpp is part of OniboConverter2.
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

#include "profile.h"

namespace Profile {

Profile::Profile(){
	videoMode = 0;
	audioMode = 0;
	isContainer = false;
	isVideoMode = false;
	isVideoFormat = false;
	isVideoEncoder = false;
	isVideoBitrate = false;
	isResolution = false;
	isFFPreset = false;
	isFramerate = false;
	isAudioMode = false;
	isAudioFormat = false;
	isAudioEncoder = false;
	isAudioGrade = false;
	isSamplerate = false;
	isChannel = false;
}

Profile::Profile(const std::string& name){
	profileName = name;
	videoMode = 0;
	audioMode = 0;
	isContainer = false;
	isVideoMode = false;
	isVideoFormat = false;
	isVideoEncoder = false;
	isVideoBitrate = false;
	isResolution = false;
	isFFPreset = false;
	isFramerate = false;
	isAudioMode = false;
	isAudioFormat = false;
	isAudioEncoder = false;
	isAudioGrade = false;
	isSamplerate = false;
	isChannel = false;
}

std::string Profile::getName() const{
	return profileName;
}
bool Profile::getContainer(MediaElement::Container& container) const{
	container = this->container;
	return isContainer;
}
bool Profile::getVideoMode(int& row) const{		//todo object
	row = this->videoMode;
	return isVideoMode;
}
bool Profile::getVideoFormat(MediaElement::Format& videoFormat) const{
	videoFormat = this->videoFormat;
	return isVideoFormat;
}
bool Profile::getVideoEncoder(MediaElement::Encoder& videoEncoder) const{
	videoEncoder = this->videoEncoder;
	return isVideoEncoder;
}
bool Profile::getVideoBitrate(MediaElement::Bitrate& videoBitrate) const{
	videoBitrate = this->videoBitrate;
	return isVideoBitrate;
}
bool Profile::getVideoResolution(MediaElement::Resolution& resolution) const{
	resolution = this->resolution;
	return isResolution;
}
bool Profile::getVideoFFpreset(MediaElement::FFpreset& ffpreset) const{
	ffpreset = this->ffpreset;
	return isFFPreset;
}
bool Profile::getVideoFramerate(MediaElement::Framerate& framerate) const{
	framerate = this->framerate;
	return isFramerate;
}
//
bool Profile::getAudioMode(int& row) const{
	row = audioMode;
	return isAudioMode;
}
bool Profile::getAudioFormat(MediaElement::Format& audioFormat) const{
	audioFormat = this->audioFormat;
	return isAudioFormat;
}
bool Profile::getAudioEncoder(MediaElement::Encoder& audioEncoder) const{
	audioEncoder = this->audioEncoder;
	return isAudioEncoder;
}
bool Profile::getAudioGrade(MediaElement::AudioGrade& audioGrade) const{
	audioGrade = this->audioGrade;
	return isAudioGrade;
}
bool Profile::getAudioSamplerate(MediaElement::Samplerate& audioSamplerate) const{
	audioSamplerate = this->samplerate;
	return isSamplerate;
}
bool Profile::getAudioChannel(MediaElement::Channel& audioChannel) const{
	audioChannel = this->channel;
	return isChannel;
}
void Profile::getManualSettings(std::list<ManualSettings>& manualSettings) const{
	manualSettings = this->settings;
}
//***********************************************************************************************************
void Profile::setContainer(const MediaElement::Container& container){
	this->container = container;
	isContainer = true;
}
void Profile::setVideoMode(const int& row){
	this->videoMode = row;
	isVideoMode = true;
}
void Profile::setVideoFormat(const MediaElement::Format& videoFormat){
	this->videoFormat = videoFormat;
	isVideoFormat = true;
}
void Profile::setVideoEncoder(const MediaElement::Encoder& videoEncoder){
	this->videoEncoder = videoEncoder;
	isVideoEncoder = true;
}
void Profile::setVideoBitrate(const MediaElement::Bitrate& videoBitrate){
	this->videoBitrate = videoBitrate;
	isVideoBitrate = true;
}
void Profile::setVideoResolution(const MediaElement::Resolution& resolution){
	this->resolution = resolution;
	isResolution = true;
}
void Profile::setVideoFFpreset(const MediaElement::FFpreset& ffpreset){
	this->ffpreset = ffpreset;
	isFFPreset = true;
}
void Profile::setVideoFramerate(const MediaElement::Framerate& framerate){
	this->framerate = framerate;
	isFramerate = true;
}
//
void Profile::setAudioMode(const int& row){
	this->audioMode = row;
	isAudioMode = true;
}
void Profile::setAudioFormat(const MediaElement::Format& audioFormat){
	this->audioFormat = audioFormat;
	isAudioFormat = true;
}
void Profile::setAudioEncoder(const MediaElement::Encoder& audioEncoder){
	this->audioEncoder = audioEncoder;
	isAudioEncoder = true;
}
void Profile::setAudioGrade(const MediaElement::AudioGrade& audioGrade){
	this->audioGrade = audioGrade;
	isAudioGrade = true;
}
void Profile::setAudioSamplerate(const MediaElement::Samplerate& audioSamplerate){
	this->samplerate = audioSamplerate;
	isSamplerate = true;
}
void Profile::setAudioChannel(const MediaElement::Channel& audioChannel){
	this->channel = audioChannel;
	isChannel = true;
}
//
void Profile::setManualSettings(const std::list<ManualSettings>& manualSettings){
	this->settings = manualSettings;
}
void Profile::addManualSettings(const ManualSettings& manualSettings){
	this->settings.push_back(manualSettings);
}
} /* namespace Profile */
