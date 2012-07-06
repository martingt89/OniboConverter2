/*
 * guisettings.h
 *
 *  Created on: 4.7.2012
 *      Author: martint
 */

#ifndef GUISETTINGS_H_
#define GUISETTINGS_H_

#include <string>
#include <map>
#include <list>

namespace AVBox {

class GuiSettings {
public:
	struct ResolutionStruct{
		std::string ratio;
		std::string resolution;
		std::string name;
		int x;
		int y;
	};
	GuiSettings();
	virtual ~GuiSettings();

	void addVideoResolution(const std::string& ratio, const std::string& resolution, const std::string& name);
	void addVideoBitrate(const std::string& bitrate);
	void addVideoFramerate(const std::string& framerate);
	void addAudioBitrate(const std::string& bitrate);
	void addAudioSamplerate(const std::string& samplerate);

	std::list<int> getVideoBitrates() const;
	std::list<double> getVideoFramerates() const;
private:
	std::map<std::string, std::list<ResolutionStruct>> ratioToResolution;
	std::list<int> vbitrate;
	std::list<double> vframerate;
	//
	std::list<int> abitrate;
	std::list<int> asamplerate;
};

} /* namespace AVBox */
#endif /* GUISETTINGS_H_ */
