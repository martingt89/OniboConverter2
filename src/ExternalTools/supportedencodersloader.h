/*
 * encodersparser.h
 *
 *  Created on: 14.7.2012
 *      Author: martint
 */

#ifndef SUPPORTEDENCODERSLOADER_H_
#define SUPPORTEDENCODERSLOADER_H_

#include "../ConverterOptions/supportedencoders.h"
#include "../RegexTools/regextools.h"
#include "../CppExtension/path.h"
#include "../ProcessExecutor/process.h"

namespace ExternalTools {

class SupportedEncodersLoader {
public:
	SupportedEncodersLoader();
	virtual ~SupportedEncodersLoader();
	bool scan(ConverterOptions::SupportedEncoders& encoders, const Path& ffmpegPath);
private:
	void parseLine(const std::string& line, ConverterOptions::SupportedEncoders& encoders);
	std::string getCodecType(const RegexTools::Matcher& mat);
	std::string getEncoderName(const RegexTools::Matcher& mat);
	std::string getCodecDescription(const RegexTools::Matcher& mat);
	std::string getExecutorError(ProcessExecutor::Process& ffmpeg);

	RegexTools::Regex encoderDetector;
};

} /* namespace ExternalTools */
#endif /* SUPPORTEDENCODERS_H_ */
