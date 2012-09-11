/*
 * elementsrelations.h
 *
 *  Created on: 9.9.2012
 *      Author: martin
 */

#ifndef ELEMENTSRELATIONS_H_
#define ELEMENTSRELATIONS_H_

#include "mediaelements.h"
#include "../CppExtension/hashmap.h"

namespace MediaElement {

class ElementsRelations {
public:
	std::list<std::string> getFormatsByContainer(const Container& container);
	std::list<std::string> getAudioEncodersByFormat(const Format& format);
	std::list<std::string> getVideoEncodersByFormat(const Format& format);
	std::string getBitratesByEncoder(const Encoder& encoder);
	std::string getAudioGradesByEncoder(const Encoder& encoder);
	bool getFFprefixByEncoder(const Encoder& encoder, std::string& ffprefix);

	void setContainerToFormats(const Container& container, const std::list<std::string>& formatsNames);
	void setFormatToEncoder(const Format& format, const std::list<std::string>& encodersNames);
	void setEncoderToBitrates(const Encoder& encoder, const std::string& bitratesName);
	void setEncoderToAudioGrade(const Encoder& encoder, const std::string& audioGradeName);
	void setEncoderToFFpreset(const Encoder& encoder, const std::string& ffpresetName);
private:
	CppExtension::HashMap<Container, std::list<std::string> > containerToFormats;
	CppExtension::HashMap<Format, std::list<std::string> > formatToEncoders;
	CppExtension::HashMap<Encoder, std::string > encoderToBitrates;
	CppExtension::HashMap<Encoder, std::string > encoderToFFpreset;
	CppExtension::HashMap<Encoder, std::string > encoderToAudioGrade;
};

} /* namespace MediaElement */
#endif /* ELEMENTSRELATIONS_H_ */
