/* ---------------------------------------------------------------------------
** Author: Martin Geier
** optionsloaderxml.cpp is part of OniboConverter2.
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
//TODO Refactor - switch to 2 class, a xml parser and a Options structure creator

#include "optionsloaderxml.h"
#include <libxml++/libxml++.h>
#include "../MediaElement/ffpreset.h"
#include "../helper.h"
#include "../CppExtension/path.h"
#include "iostream"

namespace Xml {

OptionsLoaderXml::OptionsLoaderXml(
		const Path& xmlFilePath,
		const ConverterOptions::SupportedEncoders& supportedEncoders,
		const Path& ffpresetPath) :
				ffpresetPath(ffpresetPath){
	domParser = NULL;
	this->supprotedEncoders = supportedEncoders;
	try{
		domParser = new xmlpp::DomParser(xmlFilePath.getPath());
	}
	catch(const std::exception& exception){
		std::cerr<<"Error: 'optionsloaderxml.cpp' "<<exception.what()<<std::endl;
	}
}

OptionsLoaderXml::~OptionsLoaderXml() {
	if(domParser != NULL){
		delete domParser;
	}
}

MediaElement::Containers OptionsLoaderXml::loadContainers(MediaElement::ElementsRelations& relations){
	xmlpp::Element *root = domParser->get_document()->get_root_node();

	MediaElement::Containers containers;
	extractContainers(root, containers, relations);

	return containers;
}
MediaElement::Formats OptionsLoaderXml::loadFormats(MediaElement::ElementsRelations& relations){
	xmlpp::Element *root = domParser->get_document()->get_root_node();
	MediaElement::Formats formats;
	extractFormats(root, formats, relations);
	return formats;
}
MediaElement::Encoders OptionsLoaderXml::loadAudioEncoders(MediaElement::ElementsRelations& relations,
		Converter::UnsupportedEncoders& unsuportedEncoders){
	xmlpp::Element *root = domParser->get_document()->get_root_node();
	MediaElement::Encoders encoders;
	extractAudioEncoders(root, encoders, relations, unsuportedEncoders);
	return encoders;
}
MediaElement::Encoders OptionsLoaderXml::loadVideoEncoders(MediaElement::ElementsRelations& relations,
		Converter::UnsupportedEncoders& unsuportedEncoders){
	xmlpp::Element *root = domParser->get_document()->get_root_node();
	MediaElement::Encoders encoders;
	extractVideoEncoders(root, encoders, relations, unsuportedEncoders);
	return encoders;
}
CppExtension::HashMap<std::string, MediaElement::Bitrates> OptionsLoaderXml::loadBitrates(){
	xmlpp::Element *root = domParser->get_document()->get_root_node();
	CppExtension::HashMap<std::string, MediaElement::Bitrates> bitrs;
	extractBitrates(root, bitrs);
	return bitrs;
}
CppExtension::HashMap<std::string, MediaElement::AudioGrades> OptionsLoaderXml::loadAudioGrade(){
	xmlpp::Element *root = domParser->get_document()->get_root_node();
	CppExtension::HashMap<std::string, MediaElement::AudioGrades> audioGrades;
	extractAudioGrade(root, audioGrades);
	return audioGrades;
}

MediaElement::Framerates OptionsLoaderXml::loadFramerates(){
	xmlpp::Element* root = domParser->get_document()->get_root_node();
	xmlpp::NodeSet nodeSet = root->find("/audio_video_parameters/framerates");
	MediaElement::Framerates framerates;
	for(auto iter = nodeSet.begin(); iter != nodeSet.end(); ++iter){
		xmlpp::Node* xmlNode = *iter;
		extractFrameratesFromNode(xmlNode, framerates);
	}
	return framerates;
}
MediaElement::Samplerates OptionsLoaderXml::loadSamplerates(){
	xmlpp::Element *root = domParser->get_document()->get_root_node();
	xmlpp::NodeSet nodeSet = root->find("/audio_video_parameters/samplerates");
	MediaElement::Samplerates samplerates;
	for(auto iter = nodeSet.begin(); iter != nodeSet.end(); ++iter){
		xmlpp::Node *xmlNode = *iter;
		extractSampleratesFromNode(xmlNode, samplerates);
	}
	return samplerates;
}
MediaElement::Resolutions OptionsLoaderXml::loadResolutions(){
	xmlpp::Element *root = domParser->get_document()->get_root_node();
	xmlpp::NodeSet nodeSet = root->find("/audio_video_parameters/video_resolutions/resolutions");
	MediaElement::Resolutions resolutions;
	for(auto iter = nodeSet.begin(); iter != nodeSet.end(); ++iter){
		xmlpp::Node *xmlNode = *iter;
		extractResolutionsFromNode(xmlNode, resolutions);
	}
	return resolutions;
}
MediaElement::Channels OptionsLoaderXml::loadChannels(){
	xmlpp::Element *root = domParser->get_document()->get_root_node();
	xmlpp::NodeSet nodeSet = root->find("/audio_video_parameters/channels");
	MediaElement::Channels channels;
	for(auto iter = nodeSet.begin(); iter != nodeSet.end(); ++iter){
		xmlpp::Node *xmlNode = *iter;
		extractChannelsFromNode(xmlNode, channels);
	}
	return channels;
}
void OptionsLoaderXml::extractChannelsFromNode(xmlpp::Node *xmlNode, MediaElement::Channels& channels){
	xmlpp::NodeSet nodeSet = xmlNode->find("./item/child::text()");
	for(auto iter = nodeSet.begin(); iter != nodeSet.end(); ++iter){
		xmlpp::Node *xmlNode = *iter;
		const xmlpp::TextNode* textNode = dynamic_cast<const xmlpp::TextNode*>(xmlNode);
		if(textNode != NULL){
			std::string name = getAttributValueFromNode(xmlNode->get_parent(), "name");
			MediaElement::Channel channel(name, toN(textNode->get_content(), int()));
			channels.push_back(channel);
		}
	}
}
void OptionsLoaderXml::extractSampleratesFromNode(xmlpp::Node *xmlNode, MediaElement::Samplerates& samplerates){
	xmlpp::NodeSet nodeSet = xmlNode->find("./item/child::text()");
	for(auto iter = nodeSet.begin(); iter != nodeSet.end(); ++iter){
		xmlpp::Node *xmlNode = *iter;
		const xmlpp::TextNode* textNode = dynamic_cast<const xmlpp::TextNode*>(xmlNode);
		if(textNode != NULL){
			MediaElement::Samplerate samplerate( toN(textNode->get_content(), double()) );
			samplerates.addSamplerate(samplerate);
		}
	}
}
void OptionsLoaderXml::extractFrameratesFromNode(xmlpp::Node *xmlNode, MediaElement::Framerates& framerates){
	xmlpp::NodeSet nodeSet = xmlNode->find("./item/child::text()");
	for(auto iter = nodeSet.begin(); iter != nodeSet.end(); ++iter){
		xmlpp::Node *xmlNode = *iter;
		const xmlpp::TextNode* textNode = dynamic_cast<const xmlpp::TextNode*>(xmlNode);
		if(textNode != NULL){
			MediaElement::Framerate framerate( toN(textNode->get_content(), double()) );
			framerates.addFramerate(framerate);
		}
	}
}
void OptionsLoaderXml::extractResolutionsFromNode(xmlpp::Node *xmlNode, MediaElement::Resolutions& resolutions){
	std::string aspectRatio = getAttributValueFromNode(xmlNode, "ratio");
	MediaElement::AspectRatio aspect = MediaElement::AspectRatio::createFromString(aspectRatio);
	xmlpp::NodeSet resolutionSet = xmlNode->find("./resolution");

	for(auto iter = resolutionSet.begin(); iter != resolutionSet.end(); ++iter){
		const xmlpp::Element* nodeElement = dynamic_cast<const xmlpp::Element*>(*iter);
		if(nodeElement != NULL){
			std::string resolutionName = getAttributValueFromNode(*iter, "name");
			bool isBasic = getAttributValueFromNode(*iter, "basic").size() > 0;
			const xmlpp::TextNode* textNode = nodeElement->get_child_text();
			if(textNode != NULL){
				std::string xyresolution = textNode->get_content();
				int x = 0, y = 0;
				convertTextResolutionToInts(xyresolution, x, y);
				MediaElement::Resolution resolutio(resolutionName, aspect, x, y, isBasic);
				resolutions.addResolution(resolutio);
			}
		}
	}
}

std::string OptionsLoaderXml::getAttributValueFromNode(
		const xmlpp::Node *xmlNode,
		const std::string& attributName){
	const xmlpp::Element* nodeElement = dynamic_cast<const xmlpp::Element*>(xmlNode);
	if(nodeElement){
		xmlpp::Attribute* attribute = nodeElement->get_attribute(attributName);
		if(attribute){
			return attribute->get_value();
		}
	}
	return std::string();
}

void OptionsLoaderXml::convertTextResolutionToInts(const std::string& textResolution, int& x, int& y){
	std::string::size_type position = textResolution.find("x");
	x = 0;
	y = 0;
	if(position != std::string::npos){
		std::string stringX = textResolution.substr(0, position);
		std::string stringY = textResolution.substr(position+1);
		x = toN(stringX, int());
		y = toN(stringY, int());
	}
}

void OptionsLoaderXml::getAudioGrade(xmlpp::Element* root, std::string path, MediaElement::AudioGrade::Type audioGradeType,
		CppExtension::HashMap<std::string, MediaElement::AudioGrades>& nameToAudioGrades) {
	xmlpp::NodeSet gradeSet = root->find(path);
	for (auto iter = gradeSet.begin(); iter != gradeSet.end(); ++iter) {
		xmlpp::Node *gradeNode = *iter;
		std::string gradeName = getAttributValueFromNode(gradeNode, "name");
		MediaElement::AudioGrades audioGrades;
		xmlpp::NodeSet textSet = gradeNode->find("./item/child::text()");
		for (auto textSetIter = textSet.begin(); textSetIter != textSet.end();
				++textSetIter) {
			const xmlpp::TextNode* textNode =
					dynamic_cast<const xmlpp::TextNode*>(*textSetIter);
			if (textNode != NULL) {

				audioGrades.push_back(MediaElement::AudioGrade(toN(textNode->get_content(), int()), audioGradeType));
			}
		}
		nameToAudioGrades.set(gradeName, audioGrades);
	}
}

void OptionsLoaderXml::extractAudioGrade(xmlpp::Element* root,
		CppExtension::HashMap<std::string, MediaElement::AudioGrades>& nameToAudioGrades) {
	getAudioGrade(root, "/audio_video_parameters/audiogrades/bitrate",
			 MediaElement::AudioGrade::BITRATE_TYPE, nameToAudioGrades);
	getAudioGrade(root, "/audio_video_parameters/audiogrades/quality",
			MediaElement::AudioGrade::QUALITY_TYPE, nameToAudioGrades);
}
void OptionsLoaderXml::extractBitrates(xmlpp::Element* root,
		CppExtension::HashMap<std::string, MediaElement::Bitrates>& nameToBitrates) {
	xmlpp::NodeSet bitrateSet = root->find("/audio_video_parameters/videogrades/bitrate");
	for (auto iter = bitrateSet.begin(); iter != bitrateSet.end(); ++iter) {
		xmlpp::Node *bitratesNode = *iter;
		std::string bitratesName = getAttributValueFromNode(bitratesNode, "name");
		MediaElement::Bitrates bitrates;
		xmlpp::NodeSet textSet = bitratesNode->find("./item/child::text()");
		for (auto textSetIter = textSet.begin(); textSetIter != textSet.end(); ++textSetIter) {
			const xmlpp::TextNode* textNode = dynamic_cast<const xmlpp::TextNode*>(*textSetIter);
			if (textNode != NULL) {
				bitrates.push_back( MediaElement::Bitrate(toN(textNode->get_content(), int())));
			}
		}
		nameToBitrates.set(bitratesName, bitrates);
	}
}
void OptionsLoaderXml::extractAudioEncoders(xmlpp::Element* root, MediaElement::Encoders& encoders,
		MediaElement::ElementsRelations& relations, Converter::UnsupportedEncoders& unsuportedEncoders) {
	xmlpp::NodeSet encoderSet = root->find("/audio_video_parameters/encoders/encoder");
	for (auto encoderIter = encoderSet.begin(); encoderIter != encoderSet.end(); ++encoderIter) {
		xmlpp::Node *encoderNode = *encoderIter;
		std::string gradeName = getAttributValueFromNode(encoderNode, "grade_name");
		std::string encoderType = getAttributValueFromNode(encoderNode, "type");
		std::string level = getAttributValueFromNode(encoderNode, "level");
		if(encoderType != "audio"){
			continue;
		}
		const xmlpp::Element* nodeElement = dynamic_cast<const xmlpp::Element*>(encoderNode);
		if (nodeElement == NULL) {
			continue;
		}
		const xmlpp::TextNode* textNode = nodeElement->get_child_text();
		if (textNode == NULL) {
			continue;
		}
		std::string encoderName = textNode->get_content();
		if(supprotedEncoders.isSupported(encoderName)){
			std::string encoderDescription = supprotedEncoders.getEncoderDescription(encoderName);
			MediaElement::Encoder encoder(encoderName, encoderDescription, false);
			encoders.addEncoder(encoder);
			relations.setEncoderToAudioGrade(encoder, gradeName);
		}else{
			int numLevel = toN(level, int());
			Converter::UnsupportedEncoders::PriorityLevel priority = Converter::UnsupportedEncoders::MEDIUM;
			if(numLevel >= Converter::UnsupportedEncoders::BEGIN && numLevel < Converter::UnsupportedEncoders::END){
				priority = (Converter::UnsupportedEncoders::PriorityLevel)numLevel;
			}
			unsuportedEncoders.addUnsupportedEncoder(encoderName, "", priority);
		}
	}
}
void OptionsLoaderXml::extractVideoEncoders(xmlpp::Element* root, MediaElement::Encoders& encoders,
		MediaElement::ElementsRelations& relations, Converter::UnsupportedEncoders& unsuportedEncoders) {
	xmlpp::NodeSet encoderSet = root->find("/audio_video_parameters/encoders/encoder");
	for (auto encoderIter = encoderSet.begin(); encoderIter != encoderSet.end(); ++encoderIter) {
		xmlpp::Node *encoderNode = *encoderIter;
		std::string bitrateName = getAttributValueFromNode(encoderNode, "grade_name");
		std::string ffpresetPrefix = getAttributValueFromNode(encoderNode, "ffpreset");
		std::string encoderType = getAttributValueFromNode(encoderNode, "type");
		std::string multithread = getAttributValueFromNode(encoderNode, "multithread");
		std::string level = getAttributValueFromNode(encoderNode, "level");
		if(encoderType != "video"){
			continue;
		}
		const xmlpp::Element* nodeElement = dynamic_cast<const xmlpp::Element*>(encoderNode);
		if (nodeElement == NULL) {
			continue;
		}
		const xmlpp::TextNode* textNode = nodeElement->get_child_text();
		if (textNode == NULL) {
			continue;
		}
		std::string encoderName = textNode->get_content();
		if(supprotedEncoders.isSupported(encoderName)){
			std::string encoderDescription = supprotedEncoders.getEncoderDescription(encoderName);
			MediaElement::Encoder encoder(encoderName, encoderDescription, (bool)toN(multithread, int()));
			encoders.addEncoder(encoder);
			relations.setEncoderToBitrates(encoder, bitrateName);
			if(ffpresetPrefix.size() > 0){
				relations.setEncoderToFFpreset(encoder, ffpresetPrefix);
			}
		}else{
			int numLevel = toN(level, int());
			Converter::UnsupportedEncoders::PriorityLevel priority = Converter::UnsupportedEncoders::MEDIUM;
			if(numLevel >= Converter::UnsupportedEncoders::BEGIN && numLevel < Converter::UnsupportedEncoders::END){
				priority = (Converter::UnsupportedEncoders::PriorityLevel)numLevel;
			}
			unsuportedEncoders.addUnsupportedEncoder(encoderName, "", priority);
		}
	}
}
void OptionsLoaderXml::extractFormats(xmlpp::Element* root, MediaElement::Formats& formats,
		MediaElement::ElementsRelations& relations) {
	xmlpp::NodeSet formatSet = root->find("/audio_video_parameters/formats/format");
	for (auto formatIter = formatSet.begin(); formatIter != formatSet.end(); ++formatIter) {
		xmlpp::Node* formatNode = *formatIter;
		std::string formatName = getAttributValueFromNode(formatNode, "id");
		std::string formatType = getAttributValueFromNode(formatNode, "type");
		MediaElement::Format::FormatType type;
		if (formatType == "video") {
			type = MediaElement::Format::FORMAT_TYPE_VIDEO;
		} else {
			type = MediaElement::Format::FORMAT_TYPE_AUDIO;
		}
		MediaElement::Format format(formatName, type);
		formats.addFormat(format);

		xmlpp::NodeSet encoderSet = formatNode->find("./encoder/child::text()");
		std::list<std::string> encodersNames;
		for (auto encoderIter = encoderSet.begin(); encoderIter != encoderSet.end(); ++encoderIter) {
			const xmlpp::TextNode* encoderNode = dynamic_cast<const xmlpp::TextNode*>(*encoderIter);
			if (encoderNode == NULL) {
				continue;
			}
			encodersNames.push_back(encoderNode->get_content());
		}
		relations.setFormatToEncoder(format, encodersNames);
	}
}
void OptionsLoaderXml::extractContainers(xmlpp::Element* root, MediaElement::Containers& containers,
		MediaElement::ElementsRelations& relations) {
	xmlpp::NodeSet containerSet = root->find("/audio_video_parameters/containers/container");
	for (auto containerIter = containerSet.begin(); containerIter != containerSet.end(); ++containerIter) {
		xmlpp::Node* containerNode = *containerIter;
		std::string containerName = getAttributValueFromNode(containerNode, "name");
		std::string cType = getAttributValueFromNode(containerNode, "type");

		MediaElement::Container::ContainerType containerType;
		if(cType == "audio"){
			containerType = MediaElement::Container::CONTAINER_TYPE_AUDIO;
		}else{
			containerType = MediaElement::Container::CONTAINER_TYPE_AUDIO_VIDEO;
		}
		MediaElement::Container container(containerName, containerType);

		std::list<std::string> formatsNames;
		xmlpp::NodeSet formatSet = containerNode->find("./format/child::text()");
		for (auto formatIter = formatSet.begin(); formatIter != formatSet.end(); ++formatIter) {
			const xmlpp::TextNode* formatNode = dynamic_cast<const xmlpp::TextNode*>(*formatIter);
			if (formatNode == NULL) {
				continue;
			}

			formatsNames.push_back(formatNode->get_content());
		}
		containers.addContainer(container);
		relations.setContainerToFormats(container, formatsNames);
	}
}
} /* namespace ConverterOptions */
