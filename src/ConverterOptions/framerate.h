/*
 * framerate.h
 *
 *  Created on: 24.7.2012
 *      Author: martint
 */

#ifndef FRAMERATE_H_
#define FRAMERATE_H_

#include <list>
#include "../Converter/convertsettings.h"

namespace ConverterOptions {

class Framerate {
public:
	Framerate(){framerate = 0;};
	Framerate(double framerate);
	double getValue() const;
	std::string toStr() const;
	Converter::ConvertSettingsList getConvertArguments() const;
private:
	double framerate;
};

class Framerates{
public:
	void addFramerate(const Framerate& framerate);
	std::list<Framerate> getFramerats() const;
private:
	std::list<Framerate> framerates;
};

} /* namespace ConverterOptions */
#endif /* FRAMERATE_H_ */
