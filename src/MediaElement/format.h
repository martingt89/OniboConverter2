/*
 * format.h
 *
 *  Created on: 24.7.2012
 *      Author: martint
 */

#ifndef FORMAT_H_
#define FORMAT_H_

#include "encoder.h"
#include "../CppExtension/hashmap.h"

namespace MediaElement {

class Format {
public:
	enum FormatType{
		FORMAT_TYPE_AUDIO, FORMAT_TYPE_VIDEO
	};
public:
	Format();
	Format(std::string name, FormatType formatType);
	std::string getName() const;
	std::string readableForm() const;
	FormatType getFormatType() const;
	bool operator<(const Format& second) const;
	bool operator==(const Format& second) const;
private:
	std::string name;
	FormatType formatType;
};

class Formats{
public:
	void addFormat(const Format& format);
	std::list<Format> getVideoFormatsList() const;
	std::list<Format> getAudioFormatsList() const;
	std::list<Format> getFormatsList() const;
	Format getFormatByName(std::string formatName) const;
	bool getFormatByName(std::string formatName, const Format::FormatType& type, Format& format) const;
	bool isAudioOnly() const;

private:
	CppExtension::HashMap<std::string, Format> videoFormats;
	CppExtension::HashMap<std::string, Format> audioFormats;
};

} /* namespace MediaElement */
#endif /* FORMAT_H_ */
