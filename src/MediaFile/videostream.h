/*
 * videostream.h
 *
 *  Created on: 20.8.2012
 *      Author: martint
 */

#ifndef VIDEOSTREAM_H_
#define VIDEOSTREAM_H_

#include <string>
#include "stream.h"
#include "../CppExtension/hashmap.h"

namespace MediaFile {

class VideoStream : public Stream {
public:
	VideoStream(int firstNumber, int secondNumber);
	enum Video{
			CODEC, COLORSPACE, RESX, RESY, TBR, TBN, TBC, FPS
	};
public:
	void setValue(Video name, std::string value);
	std::string getValue(Video name);
	void setStream(int f, int r);
private:
	CppExtension::HashMap<Video, std::string> content;
};

} /* namespace MediaFile */
#endif /* VIDEOSTREAM_H_ */