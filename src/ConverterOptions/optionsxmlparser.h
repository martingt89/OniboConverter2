/*
 * optionsxmlparser.h
 *
 *  Created on: 25.7.2012
 *      Author: martint
 */

#ifndef OPTIONSXMLPARSER_H_
#define OPTIONSXMLPARSER_H_

#include "optionsloader.h"
#include <set>

namespace xmlpp{
	class DomParser;
	class Node;
	class Element;
}
namespace ConverterOptions {

class OptionsXmlParser: public OptionsLoader {
public:
	OptionsXmlParser(const std::string& filePath,
			const std::map<std::string, std::string>& suportedEncodersWithDescription);
	virtual ~OptionsXmlParser();
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
	std::map<std::string, std::string> encodersWithDescr;
};

} /* namespace ConverterOptions */
#endif /* OPTIONSXMLPARSER_H_ */
