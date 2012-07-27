/*
 * optionsxmlparser.h
 *
 *  Created on: 25.7.2012
 *      Author: martint
 */

#ifndef OPTIONSLOADERXML_H_
#define OPTIONSLOADERXML_H_

#include "optionsloader.h"
#include "supportedencoders.h"
#include "../CppExtension/hashmap.h"

class Path;

namespace xmlpp{
	class DomParser;
	class Node;
	class Element;
}
namespace ConverterOptions {
	class FFpreset;


class OptionsLoaderXml: public OptionsLoader {
public:
	OptionsLoaderXml(const Path& xmlFilePath,
			const SupportedEncoders& supportedEncoders,
			FFpreset* const ffpreset);
	virtual ~OptionsLoaderXml();
	virtual Containers loadContainers();
	virtual Framerates loadFramerates();
	virtual Samplerates loadSamplerates();
	virtual Resolutions loadResolutions();
private:
	void extractResolutionsFromNode(xmlpp::Node *xmlNode, Resolutions& resolutions);
	void extractFrameratesFromNode(xmlpp::Node *xmlNode, Framerates& framerates);
	void extractSampleratesFromNode(xmlpp::Node *xmlNode, Samplerates& samplerates);
	std::string getAttributValueFromNode(const xmlpp::Node *xmlNode, const std::string& attributName);
	void convertTextResolutionToInts(const std::string& textResolution, int& x, int& y);
	void extractBitrates(xmlpp::Element* root, std::map<std::string, Bitrates>& nameToBitrates);
	void extractEncoders(xmlpp::Element* root, std::map<std::string, Bitrates>& nameToBitrates,
			std::map<std::string, Encoder>& nameToEncoder);
	void extractFormats(xmlpp::Element* root,
			const std::map<std::string, Encoder>& nameToEncoder,
			std::map<std::string, Format>& nameToFormat);
	void extractContainers(xmlpp::Element* root, std::map<std::string, Format> nameToFormat,
			Containers& containers);

	xmlpp::DomParser* domParser;
	SupportedEncoders supprotedEncoders;
	FFpreset* const ffpreset;
};

} /* namespace ConverterOptions */
#endif /* OPTIONSLOADERXML_H_ */
