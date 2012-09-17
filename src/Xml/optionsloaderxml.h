/* ---------------------------------------------------------------------------
** Author: Martin Geier
** optionsloaderxml.h is part of OniboConverter2.
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

#ifndef OPTIONSLOADERXML_H_
#define OPTIONSLOADERXML_H_

#include "../ConverterOptions/supportedencoders.h"
#include "../CppExtension/hashmap.h"
#include "../MediaElement/elementsrelations.h"
#include "../Converter/unsupportedencoders.h"
class Path;

namespace xmlpp{
	class DomParser;
	class Node;
	class Element;
}
namespace Xml {

class OptionsLoaderXml{
public:
	OptionsLoaderXml(const Path& xmlFilePath,
			const ConverterOptions::SupportedEncoders& supportedEncoders,
			const Path& ffpresetPath);
	virtual ~OptionsLoaderXml();
	MediaElement::Containers loadContainers(MediaElement::ElementsRelations& relations);
	MediaElement::Formats loadFormats(MediaElement::ElementsRelations& relations);
	MediaElement::Encoders loadAudioEncoders(MediaElement::ElementsRelations& relations,
			Converter::UnsupportedEncoders& unsuportedEncoders);
	MediaElement::Encoders loadVideoEncoders(MediaElement::ElementsRelations& relations,
			Converter::UnsupportedEncoders& unsuportedEncoders);
	CppExtension::HashMap<std::string, MediaElement::Bitrates> loadBitrates();
	CppExtension::HashMap<std::string, MediaElement::AudioGrades> loadAudioGrade();
	MediaElement::Framerates loadFramerates();
	MediaElement::Samplerates loadSamplerates();
	MediaElement::Resolutions loadResolutions();
	MediaElement::Channels loadChannels();
private:
	void extractResolutionsFromNode(xmlpp::Node *xmlNode, MediaElement::Resolutions& resolutions);
	void extractFrameratesFromNode(xmlpp::Node *xmlNode, MediaElement::Framerates& framerates);
	void extractSampleratesFromNode(xmlpp::Node *xmlNode, MediaElement::Samplerates& samplerates);
	void extractChannelsFromNode(xmlpp::Node *xmlNode, MediaElement::Channels& channels);
	//
	void extractAudioGrade(xmlpp::Element* root,
			CppExtension::HashMap<std::string, MediaElement::AudioGrades>& nameToAudioGrades);
	void extractBitrates(	xmlpp::Element* root,
			CppExtension::HashMap<std::string, MediaElement::Bitrates>& nameToBitrates);
	void extractAudioEncoders(xmlpp::Element* root, MediaElement::Encoders& encoders,
			MediaElement::ElementsRelations& relations, Converter::UnsupportedEncoders& unsuportedEncoders);
	void extractVideoEncoders(xmlpp::Element* root, MediaElement::Encoders& encoders,
			MediaElement::ElementsRelations& relations, Converter::UnsupportedEncoders& unsuportedEncoders);
	void extractFormats(xmlpp::Element* root,
			MediaElement::Formats& formats, MediaElement::ElementsRelations& relations);
	void extractContainers(xmlpp::Element* root,
			MediaElement::Containers& containers, MediaElement::ElementsRelations& relations);
	//
	std::string getAttributValueFromNode(const xmlpp::Node *xmlNode, const std::string& attributName);
	void convertTextResolutionToInts(const std::string& textResolution, int& x, int& y);
	void getAudioGrade(xmlpp::Element* root, std::string path, MediaElement::AudioGrade::Type audioGradeType,
			CppExtension::HashMap<std::string, MediaElement::AudioGrades>& nameToAudioGrades);

	xmlpp::DomParser* domParser;
	ConverterOptions::SupportedEncoders supprotedEncoders;
	CppExtension::HashMap<std::string, MediaElement::FFpresets> prefixToFFpresets;
	Path ffpresetPath;
};

} /* namespace Xml */
#endif /* OPTIONSLOADERXML_H_ */
