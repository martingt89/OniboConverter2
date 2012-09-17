/* ---------------------------------------------------------------------------
** Author: Martin Geier
** supportedencodersloader.h is part of OniboConverter2.
**
** OniboConverter2 is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program.  If not, see <http://www.gnu.org/licenses/>.
** -------------------------------------------------------------------------*/

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
	void parseLine(const std::string& line, ConverterOptions::SupportedEncoders& encoders, bool& findMatch);
	std::string getCodecType(const RegexTools::Matcher& mat);
	std::string getEncoderName(const RegexTools::Matcher& mat);
	std::string getCodecDescription(const RegexTools::Matcher& mat);
	std::string getExecutorError(ProcessExecutor::Process& ffmpeg);

	RegexTools::Regex encoderDetector;
};

} /* namespace ExternalTools */
#endif /* SUPPORTEDENCODERS_H_ */
