/*
 * suportedencoders.h
 *
 *  Created on: 28.6.2012
 *      Author: martint
 */

#ifndef SUPORTEDENCODERS_H_
#define SUPORTEDENCODERS_H_

#include <string>
#include <map>
#include "../regextools.h"

namespace FFTools {

class SuportedEncoders {
public:
	enum EncoderType{
		VIDEO, AUDIO, SUBTITLE
	};
	struct Encoder{
		std::string encoder;
		std::string description;
		EncoderType type;
	};
public:
	SuportedEncoders();
	virtual ~SuportedEncoders();
	void rescan();
	bool isSuported(const std::string& name, std::string& description) const;
private:
	void parseLine(const std::string& line);
	std::map<std::string, Encoder> suportedEndcoders;
	RegexTools::Regex encoderDetector;
};

} /* namespace FFTools */
#endif /* SUPORTEDENCODERS_H_ */
