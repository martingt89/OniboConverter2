/*
 * samplerate.h
 *
 *  Created on: 24.7.2012
 *      Author: martint
 */

#ifndef SAMPLERATE_H_
#define SAMPLERATE_H_

#include <list>
#include <string>
#include "../Converter/convertsettings.h"

namespace ConverterOptions {

class Samplerate {
public:
	Samplerate();
	Samplerate(int samplerate);
	int getValue() const;
	std::string toStr() const;
	Converter::ConvertSettingsList getConvertArguments() const;
private:
	int samplerate;
};

class Samplerates{
public:
	void addSamplerate(const Samplerate& samplerate);
	std::list<Samplerate> getSamplerates() const;
private:
	std::list<Samplerate> samplerates;
};

} /* namespace ConverterOptions */
#endif /* SAMPLERATE_H_ */
