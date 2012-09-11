/*
 * elementsdb.h
 *
 *  Created on: 9.9.2012
 *      Author: martin
 */

#ifndef ELEMENTSDB_H_
#define ELEMENTSDB_H_

#include "mediaelements.h"
#include "elementsrelations.h"
#include "../ConverterOptions/supportedencoders.h"
#include "../Converter/unsupportedencoders.h"
namespace MediaElement {

class ElementsDB {
public:
	void load(const Path& configFile, const Path& ffpresetFolder,
			const ConverterOptions::SupportedEncoders& supportedEncoders);

	Containers getContainers() const;

	bool getBitratesByName(const std::string& name, Bitrates& bitrates) const;
	bool getAudioGradesByName(const std::string& name, AudioGrades& audioGrades) const;
	void getFFpresetsByPrefix(const std::string& prefix, std::list<FFpreset>& ffpresets) const;

	Encoders getVideoEncoders() const;
	Encoders getAudioEncoders() const;

	Formats getFormats() const;

	Framerates getFramerates() const;
	Channels getChannels() const;
	Resolutions getResolutions() const;
	Samplerates getSamplerates() const;

	Converter::UnsupportedEncoders getUnsuprtedEncoders() const;


	void addUserVideoBitrate(const Bitrate& bitrate);
	void addUserResolution(const Resolution& resolution);
	void addUserFFpreset(const std::string& prefix, const FFpreset& ffpreset);

	ElementsRelations elementsRelations;
private:
	Containers containers;
	Encoders videoEncoders;
	Encoders audioEncoders;
	Formats formats;
	Framerates framerates;
	Channels channels;
	Resolutions resolutions;
	Samplerates samplerates;
	FFpresets ffpresets;
	std::list<Bitrate> userBitrates;
	std::list<Resolution> userResolutions;
	CppExtension::HashMap<std::string, Bitrates> nameToBitrates;
	CppExtension::HashMap<std::string, AudioGrades> nameToAudioGrade;
	CppExtension::MultiHashMap<std::string, FFpreset> prefixToFFpresets;
	Converter::UnsupportedEncoders unsuportedEncoders;
};

} /* namespace MediaElement */
#endif /* ELEMENTSDB_H_ */
