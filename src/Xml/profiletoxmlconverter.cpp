/*
 * profiletoxmlconverter.cpp
 *
 *  Created on: 24.8.2012
 *      Author: martint
 */

#include "profiletoxmlconverter.h"
#include "../helper.h"
#include "../globalsettings.h"
#include <fstream>
#include <iostream>

namespace Xml {

ProfileToXmlConverter::ProfileToXmlConverter() {}

ProfileToXmlConverter::~ProfileToXmlConverter() {}

bool ProfileToXmlConverter::convertToFile(const Profile::Profile& profile){
	std::string xml = generateProfileXml(profile);
	Path userProfilesPath = GlobalSettings::getInstance()->getUserProfilesPath();
	std::string name = getActualTimeMiliSec()+".xml";
	Path profilePath = GlobalSettings::buildPath(userProfilesPath, Path(name));
	//std::cout<<"path: "<<profilePath.getPath()<<std::endl;
	std::ofstream file(profilePath.getPath());
	if(file.good()){
		//todo log
		file << xml;
		file.close();
		return true;
	}
	return false;
}
//todo rewrite to automatic version
std::string ProfileToXmlConverter::generateProfileXml(const Profile::Profile& profile) {
	XmlGenerator generator;
	XmlDocument* doc = generator.createDocument("profile");
	std::string name = profile.getName();
	doc->addSubNode(generator.createNode("name"))->addText(name);
	std::string containerName;
	if (!profile.getContainerName(containerName)) {
		return std::string();
	}
	doc->addSubNode(generator.createNode("container"))->addText(containerName);
	getVideoXml(generator, profile, doc);
	getAudioXml(generator, profile, doc);
	getManualXml(generator, profile, doc);
	std::stringstream ss;
	doc->write(ss);
	return ss.str();
}
void ProfileToXmlConverter::getManualXml(const XmlGenerator& generator, const Profile::Profile& profile,
		XmlDocument* doc) {
	std::list<Profile::Profile::ManualSettings> manualSettings;
	profile.getManualSettings(manualSettings);

	XmlNode* manualNod = doc->addSubNode(generator.createNode("manualsettings"));

	for(auto manual : manualSettings){
		XmlNode* settingNod = manualNod->addSubNode(generator.createNode("setting"));
		settingNod->addSubNode(generator.createNode("command"))->addText(manual.command);
		for(auto arg : manual.args){
			settingNod->addSubNode(generator.createNode("arg"))->addText(arg);
		}
	}
}
void ProfileToXmlConverter::getAudioXml(const XmlGenerator& generator, const Profile::Profile& profile,
		XmlDocument* doc) {
	XmlNode* audio = doc->addSubNode(generator.createNode("audio"));
	int audioRow;
	if (profile.getVideoMode(audioRow)) {
		audio->addSubNode(generator.createNode("mode"))->addText(toS(audioRow));
		bool original;
		ConverterOptions::Samplerate samplerate;
		if(profile.getAudioSamplerate(samplerate, original)){
			audio->addSubNode(generator.createNode("samplerate"))->addText(toS(samplerate.getValue()));
		}
		ConverterOptions::Channel channel;
		if(profile.getAudioChannel(channel, original)){
			XmlNode* channelNod = audio->addSubNode(generator.createNode("channel"));
			channelNod->addSubNode(generator.createNode("value"))->addText(toS(channel.getValue()));
			channelNod->addSubNode(generator.createNode("name"))->addText(channel.getName());
		}
		std::string audioFormatName;
		bool format = false;
		if (profile.getAudioFormatName(audioFormatName)) {
			format = true;
			audio->addSubNode(generator.createNode("format"))->addText(audioFormatName);
		}
		std::string audioEncoderName;
		bool encoder = false;
		if (format && profile.getAudioEncoderName(audioEncoderName)) {
			encoder = true;
			audio->addSubNode(generator.createNode("encoder"))->addText(audioEncoderName);
		}
		ConverterOptions::Bitrate bitrate;
		if (encoder && profile.getAudioBitrate(bitrate)) {
			audio->addSubNode(generator.createNode("bitrate"))->addText(toS(bitrate.getValue()));
		}
	}
}


void ProfileToXmlConverter::getVideoXml(const XmlGenerator& generator, const Profile::Profile& profile,
		XmlDocument* doc) {
	XmlNode* video = doc->addSubNode(generator.createNode("video"));
	int videoRow;
	if (profile.getVideoMode(videoRow)) {
		video->addSubNode(generator.createNode("mode"))->addText(toS(videoRow));
		bool original;
		ConverterOptions::Framerate framerate;
		if(profile.getVideoFramerate(framerate, original)){
			video->addSubNode(generator.createNode("framerate"))->addText(toS(framerate.getValue()));
		}
		ConverterOptions::Resolution resolution;
		if(profile.getVideoResolution(resolution, original)){
			XmlNode* resolNod = video->addSubNode(generator.createNode("resolution"));
			resolNod->addSubNode(generator.createNode("x"))->addText(toS(resolution.getValue().first));
			resolNod->addSubNode(generator.createNode("y"))->addText(toS(resolution.getValue().second));
			resolNod->addSubNode(generator.createNode("aspect"))->addText(resolution.getAspectRatio());
			resolNod->addSubNode(generator.createNode("name"))->addText(resolution.getName());
		}
		std::string videoFormatName;
		bool format = false;
		if (profile.getVideoFormatName(videoFormatName)) {
			format = true;
			video->addSubNode(generator.createNode("format"))->addText(videoFormatName);
		}
		std::string videoEncoderName;
		bool encoder = false;
		if (format && profile.getVideoEncoderName(videoEncoderName)) {
			encoder = true;
			video->addSubNode(generator.createNode("encoder"))->addText(videoEncoderName);
		}
		ConverterOptions::Bitrate bitrate;
		if (encoder && profile.getVideoBitrate(bitrate)) {
			XmlNode* bitrateNod = video->addSubNode(generator.createNode("bitrate"));
			bitrateNod->addSubNode(generator.createNode("value"))->addText(toS(bitrate.getValue()));
			bitrateNod->addSubNode(generator.createNode("min"))->addText(toS(bitrate.getMinBitrate()));
			bitrateNod->addSubNode(generator.createNode("max"))->addText(toS(bitrate.getMaxBitrate()));
		}
		ConverterOptions::FFpreset ffpreset;
		if (encoder && profile.getVideoFFpreset(ffpreset)) {
			XmlNode* ffpresetNod = video->addSubNode(generator.createNode("ffpreset"));
			ffpresetNod->addSubNode(generator.createNode("prefix"))->addText(ffpreset.getPrefix());
			if (ffpreset.isBuildIn()) {
				ffpresetNod->addSubNode(generator.createNode("path"))->addText(ffpreset.getName());
				ffpresetNod->addSubNode(generator.createNode("buildin"))->addText("y");
			} else {
				ffpresetNod->addSubNode(generator.createNode("path"))->addText(ffpreset.getPath().getPath());
			}
		}
	}
}

} /* namespace Xml */
