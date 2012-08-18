/*
 * optionsxmlparser.cpp
 *
 *  Created on: 25.7.2012
 *      Author: martint
 */

//TODO Refactor - switch to 2 class, a xml parser and a Options structure creator

#include "optionsloaderxml.h"
#include <libxml++/libxml++.h>
#include "../helper.h"
#include "ffpreset.h"
#include "../CppExtension/path.h"
#include "supportedencoders.h"
#include <iostream> //todo remove

namespace ConverterOptions {

OptionsLoaderXml::OptionsLoaderXml(
		const Path& xmlFilePath,
		const SupportedEncoders& supportedEncoders,
		const Path& ffpresetPath) : ffpresetPath(ffpresetPath){
	domParser = NULL;
	this->supprotedEncoders = supportedEncoders;
	try{
		domParser = new xmlpp::DomParser(xmlFilePath.getPath());
	}
	catch(const std::exception& exception){
		//todo return status
	}
}

OptionsLoaderXml::~OptionsLoaderXml() {
	if(domParser != NULL){
		delete domParser;
	}
}

Containers OptionsLoaderXml::loadContainers(){
	xmlpp::Element *root = domParser->get_document()->get_root_node();

	std::map<std::string, Bitrates> nameToBitrates;
	extractBitrates(root, nameToBitrates);

	std::map<std::string, Encoder> nameToEncoder;
	extractEncoders(root, nameToBitrates, nameToEncoder);

	std::map<std::string, Format> nameToFormat;
	extractFormats(root, nameToEncoder, nameToFormat);

	Containers containers;
	extractContainers(root, nameToFormat, containers);

	return containers;
}
Framerates OptionsLoaderXml::loadFramerates(){
	xmlpp::Element* root = domParser->get_document()->get_root_node();
	xmlpp::NodeSet nodeSet = root->find("/audio_video_parameters/framerates");
	Framerates framerates;
	for(auto iter = nodeSet.begin(); iter != nodeSet.end(); ++iter){
		xmlpp::Node* xmlNode = *iter;
		extractFrameratesFromNode(xmlNode, framerates);
	}
	return framerates;
}
Samplerates OptionsLoaderXml::loadSamplerates(){
	xmlpp::Element *root = domParser->get_document()->get_root_node();
	xmlpp::NodeSet nodeSet = root->find("/audio_video_parameters/samplerates");
	Samplerates samplerates;
	for(auto iter = nodeSet.begin(); iter != nodeSet.end(); ++iter){
		xmlpp::Node *xmlNode = *iter;
		extractSampleratesFromNode(xmlNode, samplerates);
	}
	return samplerates;
}
Resolutions OptionsLoaderXml::loadResolutions(){
	xmlpp::Element *root = domParser->get_document()->get_root_node();
	xmlpp::NodeSet nodeSet = root->find("/audio_video_parameters/video_resolutions/resolutions");
	Resolutions resolutions;
	for(auto iter = nodeSet.begin(); iter != nodeSet.end(); ++iter){
		xmlpp::Node *xmlNode = *iter;
		extractResolutionsFromNode(xmlNode, resolutions);
	}
	return resolutions;
}
Channels OptionsLoaderXml::loadChannels(){
	xmlpp::Element *root = domParser->get_document()->get_root_node();
	xmlpp::NodeSet nodeSet = root->find("/audio_video_parameters/channels");
	Channels channels;
	for(auto iter = nodeSet.begin(); iter != nodeSet.end(); ++iter){
		xmlpp::Node *xmlNode = *iter;
		extractChannelsFromNode(xmlNode, channels);
	}
	return channels;
}
void OptionsLoaderXml::extractChannelsFromNode(xmlpp::Node *xmlNode, Channels& channels){
	xmlpp::NodeSet nodeSet = xmlNode->find("./item/child::text()");
	for(auto iter = nodeSet.begin(); iter != nodeSet.end(); ++iter){
		xmlpp::Node *xmlNode = *iter;
		const xmlpp::TextNode* textNode = dynamic_cast<const xmlpp::TextNode*>(xmlNode);
		if(textNode != NULL){
			std::string name = getAttributValueFromNode(xmlNode->get_parent(), "name");
			Channel channel(name, toN(textNode->get_content(), int()));
			channels.push_back(channel);
		}
	}
}
void OptionsLoaderXml::extractSampleratesFromNode(xmlpp::Node *xmlNode, Samplerates& samplerates){
	xmlpp::NodeSet nodeSet = xmlNode->find("./item/child::text()");
	for(auto iter = nodeSet.begin(); iter != nodeSet.end(); ++iter){
		xmlpp::Node *xmlNode = *iter;
		const xmlpp::TextNode* textNode = dynamic_cast<const xmlpp::TextNode*>(xmlNode);
		if(textNode != NULL){
			Samplerate samplerate( toN(textNode->get_content(), double()) );
			samplerates.addSamplerate(samplerate);
		}
	}
}
void OptionsLoaderXml::extractFrameratesFromNode(xmlpp::Node *xmlNode, Framerates& framerates){
	xmlpp::NodeSet nodeSet = xmlNode->find("./item/child::text()");
	for(auto iter = nodeSet.begin(); iter != nodeSet.end(); ++iter){
		xmlpp::Node *xmlNode = *iter;
		const xmlpp::TextNode* textNode = dynamic_cast<const xmlpp::TextNode*>(xmlNode);
		if(textNode != NULL){
			Framerate framerate( toN(textNode->get_content(), double()) );
			framerates.addFramerate(framerate);
		}
	}
}
void OptionsLoaderXml::extractResolutionsFromNode(xmlpp::Node *xmlNode, Resolutions& resolutions){
	std::string aspectRatio = getAttributValueFromNode(xmlNode, "ratio");

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
				Resolution resolutio(resolutionName, aspectRatio, x, y, isBasic);
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
void OptionsLoaderXml::extractBitrates(
		xmlpp::Element* root,
		std::map<std::string, Bitrates>& nameToBitrates) {
	xmlpp::NodeSet bitrateSet = root->find("/audio_video_parameters/bitrates/bitrate");
	for (auto iter = bitrateSet.begin(); iter != bitrateSet.end(); ++iter) {
		xmlpp::Node *bitratesNode = *iter;
		std::string bitratesName = getAttributValueFromNode(bitratesNode, "name");
		Bitrates bitrates;
		xmlpp::NodeSet textSet = bitratesNode->find("./item/child::text()");
		for (auto textSetIter = textSet.begin(); textSetIter != textSet.end(); ++textSetIter) {
			const xmlpp::TextNode* textNode = dynamic_cast<const xmlpp::TextNode*>(*textSetIter);
			if (textNode != NULL) {
				bitrates.push_back( Bitrate(toN(textNode->get_content(), int())));
			}
		}
		nameToBitrates[bitratesName] = bitrates;
	}
}
void OptionsLoaderXml::extractEncoders(
		xmlpp::Element* root, std::map<std::string, Bitrates>& nameToBitrates,
		std::map<std::string, Encoder>& nameToEncoder) {
	xmlpp::NodeSet encoderSet = root->find("/audio_video_parameters/encoders/encoder");
	for (auto encoderIter = encoderSet.begin(); encoderIter != encoderSet.end(); ++encoderIter) {
		xmlpp::Node *encoderNode = *encoderIter;
		std::string bitrateName = getAttributValueFromNode(encoderNode, "bitrate");
		std::string ffpresetPrefix = getAttributValueFromNode(encoderNode, "ffpreset");
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
			Bitrates bitrates = nameToBitrates[bitrateName];
			Encoder encoder(encoderName, encoderDescription, bitrates);
			if(ffpresetPrefix.size() > 0){
				if(!prefixToFFpresets.isExistKey(ffpresetPrefix)){
					prefixToFFpresets.set(ffpresetPrefix, FFpresets(ffpresetPrefix, ffpresetPath));
		//			std::cout<<"prefix doesnt exist"<<std::endl;
				}
				encoder.setFFpresets(prefixToFFpresets.get(ffpresetPrefix), ffpresetPrefix);
		//		std::cout<<"add ffpresets"<<std::endl;
			}
			nameToEncoder[encoderName] = encoder;
		}
	}
}
void OptionsLoaderXml::extractFormats(
		xmlpp::Element* root,
		const std::map<std::string, Encoder>& nameToEncoder,
		std::map<std::string, Format>& nameToFormat) {
	xmlpp::NodeSet formatSet = root->find(
			"/audio_video_parameters/formats/format");
	for (auto formatIter = formatSet.begin(); formatIter != formatSet.end(); ++formatIter) {
		xmlpp::Node* formatNode = *formatIter;
		std::string formatName = getAttributValueFromNode(formatNode, "id");
		std::string formatType = getAttributValueFromNode(formatNode, "type");
		Format::FormatType type;
		if (formatType == "video") {
			type = Format::FORMAT_TYPE_VIDEO;
		} else {
			type = Format::FORMAT_TYPE_AUDIO;
		}
		Encoders encoders;
		xmlpp::NodeSet encoderSet = formatNode->find("./encoder/child::text()");
		for (auto encoderIter = encoderSet.begin(); encoderIter != encoderSet.end(); ++encoderIter) {
			const xmlpp::TextNode* encoderNode = dynamic_cast<const xmlpp::TextNode*>(*encoderIter);
			if (encoderNode == NULL) {
				continue;
			}
			std::string encoderName = encoderNode->get_content();
			auto findIter = nameToEncoder.find(encoderName);
			if (findIter != nameToEncoder.end()) {
				encoders.addEncoder(findIter->second);
			}
		}
		Format format(formatName, type, encoders);
		nameToFormat[formatName] = format;
	}
}
void OptionsLoaderXml::extractContainers(xmlpp::Element* root, std::map<std::string, Format> nameToFormat,
		Containers& containers) {
	xmlpp::NodeSet containerSet = root->find("/audio_video_parameters/containers/container");
	for (auto containerIter = containerSet.begin(); containerIter != containerSet.end(); ++containerIter) {
		xmlpp::Node* containerNode = *containerIter;
		std::string containerName = getAttributValueFromNode(containerNode, "name");
		xmlpp::NodeSet formatSet = containerNode->find("./format/child::text()");
		Formats formats;
		for (auto formatIter = formatSet.begin(); formatIter != formatSet.end(); ++formatIter) {
			const xmlpp::TextNode* formatNode = dynamic_cast<const xmlpp::TextNode*>(*formatIter);
			if (formatNode == NULL) {
				continue;
			}

			std::string formatName = formatNode->get_content();
			auto nameToFormatIter = nameToFormat.find(formatName);
			if (nameToFormatIter != nameToFormat.end()) {
				formats.addFormat(nameToFormatIter->second);
			}
		}
		Container::ContainerType containerType = Container::CONTAINER_TYPE_AUDIO_VIDEO;
		if (formats.isAudioOnly()) {
			containerType = Container::CONTAINER_TYPE_AUDIO;
		}
		Container container(containerName, containerType, formats);
		containers.addContainer(container);
	}
}
} /* namespace ConverterOptions */
