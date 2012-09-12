/*
 * convertparser.h
 *
 *  Created on: 30.8.2012
 *      Author: martint
 */

#ifndef CONVERTPARSER_H_
#define CONVERTPARSER_H_

#include <string>
#include <list>
#include "../RegexTools/regextools.h"

namespace Converter {

class ConvertParser {
public:
	ConvertParser(const double& duration);
	virtual ~ConvertParser();
	bool processLine(const std::string& line, double& fraction, int& remainingTime);
private:
	void addRecord(double diff, double elapsed);
	double getNumSecPerSec();
	double toSecondTime(const std::string& time);
	double aktualTime;
	double duration;
	RegexTools::Regex colonTimeFormat;
	long lastWorldTime;
	std::list<std::pair<double, double> > diffAndTime;
};

} /* namespace Converter */
#endif /* CONVERTPARSER_H_ */
