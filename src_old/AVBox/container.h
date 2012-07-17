/*
 * container.h
 *
 *  Created on: 28.6.2012
 *      Author: martint
 */

#ifndef CONTAINER_H_
#define CONTAINER_H_

#include <map>
#include <string>
#include <list>

#include "avformat.h"

namespace AVBox {

class Container {
public:
	Container(const std::string& name);
	Container();
	virtual ~Container();
//	std::list<std::string> getVideoFormats();
//	std::list<std::string> getAudioFormats(const VideoFormat& vEncoder);
//	VideoFormat getVideoFormat(const std::string& name);
//	AudioFormat getAudioFormat(const std::string& name);
	void addAVFormat(const AVFormat& format);

//	void addAudioFormat(const AudioFormat& audio);
//	void addVideoFormat(const VideoFormat& video);
	std::string getName() const;
private:
	std::string name;
	std::map<std::string, AVFormat> avformats;
//	std::map<std::string, VideoFormat> videoFormats;
//	std::map<std::string, AudioFormat> audioFormats;
//	std::map<VideoFormat, AudioFormat, VideoFormatCmp> blackList;
};

} /* namespace AVBox */
#endif /* CONTAINER_H_ */
