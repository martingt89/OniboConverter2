/*
 * videostream.h
 *
 *  Created on: 20.6.2012
 *      Author: Martin Geier
 *
 */

#ifndef VIDEOSTREAM_H_
#define VIDEOSTREAM_H_

#include <map>
#include <string>
#include "stream.h"

namespace MediaInfo{

class VideoStream : public Stream {
public:
	VideoStream(int f, int r);
	enum Video{
			CODEC, COLORSPACE, RESX, RESY, TBR, TBN, TBC, FPS
	};
public:
	void setValue(Video name, std::string value);
	std::string getValue(Video name);
	void setStream(int f, int r);
private:
	std::map<Video, std::string> content;
	std::pair<int, int> streamNumber;
};

} /* namespace MediaInfo */
#endif /* VIDEOSTREAM_H_ */
