/* ---------------------------------------------------------------------------
** Author: Martin Geier
** elementsrelations.h is part of OniboConverter2.
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
