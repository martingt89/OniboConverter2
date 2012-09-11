/*
 * audiograde.h
 *
 *  Created on: 11.9.2012
 *      Author: martin
 */

#ifndef AUDIOGRADE_H_
#define AUDIOGRADE_H_

#include <list>
#include <string>

namespace MediaElement {

class AudioGrade {
public:
	enum Type{
		BITRATE_TYPE, QUALITY_TYPE
	};
	AudioGrade();
	virtual ~AudioGrade();

	AudioGrade(int value, Type type);
	int getValue() const;
	bool operator== (const AudioGrade& second) const;
	std::string readableForm() const;
	Type getType() const;
	bool isDefault() const;
private:
	int value;
	Type type;
};

typedef std::list<AudioGrade> AudioGrades;

} /* namespace MediaElement */
#endif /* AUDIOGRADE_H_ */
