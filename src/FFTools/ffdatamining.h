/*
 * ffdatamining.h
 *
 *  Created on: 28.6.2012
 *      Author: martint
 */

#ifndef FFDATAMINING_H_
#define FFDATAMINING_H_

#include <string>
#include <map>
#include "../regextools.h"
#include "../AVBox/encoder.h"
#include "../AVBox/supportedencoders.h"

namespace FFTools {

class FFDataMining {
public:
	FFDataMining();
	virtual ~FFDataMining();
	bool scan(AVBox::SupportedEncoders *encoders);
private:
	void parseLine(const std::string& line);
	RegexTools::Regex encoderDetector;
	AVBox::SupportedEncoders *suportEncoders;
};

} /* namespace FFTools */
#endif /* FFDATAMINING_H_ */
