/*
 * optionsxmlparser.cpp
 *
 *  Created on: 25.7.2012
 *      Author: martint
 */

#include "optionsxmlparser.h"
#include <libxml++/libxml++.h>
#include "../helper.h"

namespace ConverterOptions {

OptionsXmlParser::OptionsXmlParser(
		const std::string& filePath,
		const std::map<std::string, std::string>& encodersWithDescr) {
	domParser = NULL;
	this->encodersWithDescr = encodersWithDescr;
	try{
		domParser = new xmlpp::DomParser(filePath);
	}
	catch(const std::exception& exception){
		//todo return status
	}
}

OptionsXmlParser::~OptionsXmlParser() {
	if(domParser != NULL){
		delete domParser;
	}
}

Containers OptionsXmlParser::loadContainers(){
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
Framerates OptionsXmlParser::loadFramerates(){	//todo exception -> framerates not available...
	xmlpp::Element* root = domParser->get_document()->get_root_node();
	xmlpp::NodeSet nodeSet = root->find("/audio_video_parameters/framerates");
	Framerates framerates;
	for(auto iter = nodeSet.begin(); iter != nodeSet.end(); ++iter){
		xmlpp::Node* xmlNode = *iter;
		extractFrameratesFromNode(xmlNode, framerates);
	}
	return framerates;
}
Samplerates OptionsXmlParser::loadSamplerates(){
	xmlpp::Element *root = domParser->get_document()->get_root_node();
	xmlpp::NodeSet nodeSet = root->find("/audio_video_parameters/samplerates");
	Samplerates samplerates;
	for(auto iter = nodeSet.begin(); iter != nodeSet.end(); ++iter){
		xmlpp::Node *xmlNode = *iter;
		extractSampleratesFromNode(xmlNode, samplerates);
	}
	return samplerates;
}
Resolutions OptionsXmlParser::loadResolutions(){
	xmlpp::Element *root = domParser->get_document()->get_root_node();
	xmlpp::NodeSet nodeSet = root->find("/audio_video_parameters/video_resolutions/resolutions");
	Resolutions resolutions;
	for(auto iter = nodeSet.begin(); iter != nodeSet.end(); ++iter){
		xmlpp::Node *xmlNode = *iter;
		extractResolutionsFromNode(xmlNode, resolutions);
	}
	return resolutions;
}

void OptionsXmlParser::extractSampleratesFromNode(xmlpp::Node *xmlNode, Samplerates& samplerates){
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
void OptionsXmlParser::extractFrameratesFromNode(xmlpp::Node *xmlNode, Framerates& framerates){
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
void OptionsXmlParser::extractResolutionsFromNode(xmlpp::Node *xmlNode, Resolutions& resolutions){
	std::string aspectRatio = getAttributValueFromNode(xmlNode, "ratio");

	xmlpp::NodeSet resolutionSet = xmlNode->find("./resolution");

	for(auto iter = resolutionSet.begin(); iter != resolutionSet.end(); ++iter){
		const xmlpp::Element* nodeElement = dynamic_cast<const xmlpp::Element*>(*iter);
		if(nodeElement != NULL){
			std::string resolutionName = getAttributValueFromNode(*iter, "name");
			const xmlpp::TextNode* textNode = nodeElement->get_child_text();
			if(textNode != NULL){
				std::string xyresolution = textNode->get_content();
				int x = 0, y = 0;
				convertTextResolutionToInts(xyresolution, x, y);
				Resolution resolutio(resolutionName, aspectRatio, x, y);
				resolutions.addResolution(resolutio);
			}
		}
	}
}

std::string OptionsXmlParser::getAttributValueFromNode(
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

void OptionsXmlParser::convertTextResolutionToInts(const std::string& textResolution, int& x, int& y){
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
void OptionsXmlParser::extractBitrates(
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
void OptionsXmlParser::extractEncoders(
		xmlpp::Element* root, std::map<std::string, Bitrates>& nameToBitrates,
		std::map<std::string, Encoder>& nameToEncoder) {
	xmlpp::NodeSet encoderSet = root->find("/audio_video_parameters/encoders/encoder");
	for (auto encoderIter = encoderSet.begin(); encoderIter != encoderSet.end(); ++encoderIter) {
		xmlpp::Node *encoderNode = *encoderIter;
		std::string bitrateName = getAttributValueFromNode(encoderNode, "bitrate");
		std::string ffpreset = getAttributValueFromNode(encoderNode, "ffpreset");
		const xmlpp::Element* nodeElement = dynamic_cast<const xmlpp::Element*>(encoderNode);
		if (nodeElement == NULL) {
			continue;
		}
		const xmlpp::TextNode* textNode = nodeElement->get_child_text();
		if (textNode == NULL) {
			continue;
		}
		std::string encoderName = textNode->get_content();
		auto encodersIter = encodersWithDescr.find(encoderName);
		if (encodersIter != encodersWithDescr.end()) {
			Bitrates bitrates = nameToBitrates[bitrateName];
			Encoder encoder(encoderName, encodersIter->second, bitrates);
			if(ffpreset.size() > 0){
				encoder.setFFreset(ffpreset);
			}
			nameToEncoder[encoderName] = encoder;
		}
	}
}
void OptionsXmlParser::extractFormats(
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
void OptionsXmlParser::extractContainers(xmlpp::Element* root, std::map<std::string, Format> nameToFormat,
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
