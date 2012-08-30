/*
 * convertparser.h
 *
 *  Created on: 30.8.2012
 *      Author: martint
 */

#ifndef CONVERTPARSER_H_
#define CONVERTPARSER_H_

#include <string>
#include "../RegexTools/regextools.h"

namespace Converter {

class ConvertParser {
public:
	ConvertParser(const double& duration);
	virtual ~ConvertParser();
	void processLine(const std::string& line, double& fraction, int& remainingTime);
private:
	double aktualTime;
	double duration;
	RegexTools::Regex lineRegex;
};

} /* namespace Converter */
#endif /* CONVERTPARSER_H_ */
