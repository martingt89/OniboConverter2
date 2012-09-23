/* ---------------------------------------------------------------------------
** Author: Martin Geier
** supportedencodersloader.cpp is part of OniboConverter2.
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

#include "supportedencodersloader.h"
#include "../CppExtension/logger.h"
namespace ExternalTools {

SupportedEncodersLoader::SupportedEncodersLoader():
	encoderDetector("^ [ D]E([VAS])[ S][ D][ T][[:space:]]+([^[:space:]]+)[[:space:]]*(.+)$"){

}

SupportedEncodersLoader::~SupportedEncodersLoader() {}

bool SupportedEncodersLoader::scan(ConverterOptions::SupportedEncoders& encoders, const Path& ffmpegPath){
	std::list<std::string> args;
	args.push_back("-codecs");
	ProcessExecutor::Process ffmpeg(ffmpegPath.getPath(), args);

	if(ffmpeg.waitForProcessBegin()){
		std::string message = getExecutorError(ffmpeg);
		easylog(CppExtension::Logger::ERROR, message);
		return false;
	}

	std::string line;
	bool findMatch = false;
	while(ffmpeg.getStdOut() >> line){
		parseLine(line, encoders, findMatch);
	}
	return findMatch & (ffmpeg.waitForProcessEnd() == 0);
}


void SupportedEncodersLoader::parseLine(const std::string& line,
		ConverterOptions::SupportedEncoders& encoders, bool& findMatch){
	RegexTools::Matcher mat = encoderDetector.getMatcher(line);
	if(mat.find()){
		findMatch = true;
//		ConverterOptions::Encoder::Type type;
//		std::string codecType = getCodecType(mat);
//		if (codecType == "V") {
//			type = AVBox::Encoder::VIDEO;
//		}else
//		if(codecType == "A"){
//			type = AVBox::Encoder::AUDIO;
//		}else{
//			type = AVBox::Encoder::UNKNOWN;
//		}

		encoders.addEncoder(getEncoderName(mat), getCodecDescription(mat));
	}
}

std::string SupportedEncodersLoader::getCodecType(const RegexTools::Matcher& mat) {
	return mat.getGroup(1);
}

std::string SupportedEncodersLoader::getEncoderName(const RegexTools::Matcher& mat) {
	return mat.getGroup(2);
}

std::string SupportedEncodersLoader::getCodecDescription(const RegexTools::Matcher& mat) {
	return mat.getGroup(3);
}

std::string SupportedEncodersLoader::getExecutorError(ProcessExecutor::Process& ffmpeg) {
	std::string err;
	std::string errorMessage = "";
	while (ffmpeg.getLog() >> err){
		errorMessage += err;
	}
	return errorMessage;
}
} /* namespace ExternalTools */
