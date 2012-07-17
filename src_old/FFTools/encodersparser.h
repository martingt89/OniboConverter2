/*
 * encodersparser.h
 *
 *  Created on: 14.7.2012
 *      Author: martint
 */

#ifndef ENCODERSPARSER_H_
#define ENCODERSPARSER_H_

#include <string>
#include <map>
#include <list>
#include "../AVBox/encoder.h"
#include "../Tools/regextools.h"
#include "../Process/processexecutor.h"

namespace FFTools {

class EncodersParser {
public:
	EncodersParser();
	virtual ~EncodersParser();
	std::list<AVBox::Encoder> getEncoders() const;

	//bool scan(AVBox::SupportedEncoders *encoders);
private:
	void parseLine(const std::string& line);
	std::string getCodecType(const RegexTools::Matcher& mat);
	std::string getEncoderName(const RegexTools::Matcher& mat);
	std::string getCodecDescription(const RegexTools::Matcher& mat);
	std::string getExecutorError(Process::Executor& ffmpeg);

	RegexTools::Regex* encoderDetector;
	std::list<AVBox::Encoder> encoders;
};

} /* namespace FFTools */
#endif /* ENCODERSPARSER_H_ */
