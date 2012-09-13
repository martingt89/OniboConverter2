/*
 * infocontrol.cpp
 *
 *  Created on: 25.8.2012
 *      Author: martint
 */

#include "infocontrol.h"
namespace Gui {

void operator<<(Gtk::Label*& label, const std::string& text){
	label->set_text(toS(text));
}

InfoControl::InfoControl(const Glib::RefPtr<Gtk::Builder>& refGlade) :
		videoStream(refGlade, "videoStreamInfo"), audioStream(refGlade, "audioStreamInfo"){
	actualMediaFile = 0;
	refGlade->get_widget("filePathInfo", filePath);
	refGlade->get_widget("durationInfo", duration);
	refGlade->get_widget("startTimeInfo", startTime);
	refGlade->get_widget("bitrateInfo", bitrate);

	refGlade->get_widget("videoCodecInfo", videoCodec);
	refGlade->get_widget("colorSpaceInfo", colorSpace);
	refGlade->get_widget("resolutionInfo", resolution);
	refGlade->get_widget("fpsInfo", fps);
	refGlade->get_widget("tbrInfo", tbr);
	refGlade->get_widget("tbnInfo", tbn);
	refGlade->get_widget("tbcInfo", tbc);

	refGlade->get_widget("audioCodecInfo", audioCodec);
	refGlade->get_widget("audioBitrateInfo", audioBitrate);
	refGlade->get_widget("samplerateInfo", samplerate);
	refGlade->get_widget("channelsInfo", channels);

	videoStream.signal_changed().connect(sigc::mem_fun(*this, &InfoControl::videoStreamChanged));
	audioStream.signal_changed().connect(sigc::mem_fun(*this, &InfoControl::audioStreamChanged));
}

InfoControl::~InfoControl() {}

void InfoControl::show(MediaFile::MediaFile*& mediaFile){
	actualMediaFile = mediaFile;
	MediaFile::MediaInfo info = mediaFile->getMediaInfo();
	videoStream.remove_all();
	audioStream.remove_all();
	filePath->set_text(actualMediaFile->getPath().getPath());
	if(info.getDuration() >= 0){
		duration << (toS(info.getDuration()) + " sec");
	}else{
		duration << std::string("N/A");
	}
	startTime << (toS(info.getStartTime()) + " sec");
	bitrate << info.getBitrate();

	int counter = 0;
	auto videos = info.getVideoStreams();
	for(auto stream : videos){
		auto pair = stream.getStreamNumber();
		videoStream.append(toS(pair.first) +"."+ toS(pair.second), counter++);
	}
	if(videoStream.count_of_rows() > 0){
		videoStream.set_sensitive(true);
	}
	counter = 0;
	auto audios = info.getAudioStreams();
	for(auto stream : audios){
		auto pair = stream.getStreamNumber();
		audioStream.append(toS(pair.first) +"."+ toS(pair.second), counter++);
	}
	if(audioStream.count_of_rows() > 0){
		audioStream.set_sensitive(true);
	}

	videoCodec << std::string();
	colorSpace << std::string();
	resolution << std::string();
	fps << std::string();
	tbr << std::string();
	tbn << std::string();
	tbc << std::string();

	audioCodec << std::string();
	audioBitrate << std::string();
	samplerate << std::string();
	channels << std::string();

	if(audioStream.count_of_rows() == 0){
		audioStream.set_sensitive(false);
	}else{
		audioStream.set_active_row_number(0);
	}
	if(videoStream.count_of_rows() == 0){
		videoStream.set_sensitive(false);
	}else{
		videoStream.set_active_row_number(0);
	}
}
std::string getAsString(const MediaFile::VideoStream& stream,
		const std::string& nullString,
		const MediaFile::VideoStream::Video& name){
	std::string val = nullString;
	if(stream.getValue(name, val)){
		return val;
	}
	return nullString;

}
std::string getAsString(const MediaFile::AudioStream& stream,
		const std::string& nullString,
		const MediaFile::AudioStream::Audio& name){
	std::string val = nullString;
	if(stream.getValue(name, val)){
		return val;
	}
	return nullString;

}
void InfoControl::videoStreamChanged(){
	bool exist = false;
	int row = videoStream.get_active_row_item(exist);
	if(exist){
		auto stream = actualMediaFile->getMediaInfo().getVideoStreams()[row];
		videoCodec << getAsString(stream, "", MediaFile::VideoStream::CODEC);
		colorSpace << getAsString(stream, "", MediaFile::VideoStream::COLORSPACE);
		resolution << (getAsString(stream, "", MediaFile::VideoStream::RESX) + "x" +
				getAsString(stream, "", MediaFile::VideoStream::RESY));
		fps << getAsString(stream, "", MediaFile::VideoStream::FPS);
		tbr << getAsString(stream, "", MediaFile::VideoStream::TBR);
		tbn << getAsString(stream, "", MediaFile::VideoStream::TBN);
		tbc << getAsString(stream, "", MediaFile::VideoStream::TBC);
	}
}
void InfoControl::audioStreamChanged(){
	bool exist = false;
	int row = audioStream.get_active_row_item(exist);
	if(exist){
		auto stream = actualMediaFile->getMediaInfo().getAudioStreams()[row];
		audioCodec << getAsString(stream, "", MediaFile::AudioStream::CODEC);
		audioBitrate << getAsString(stream, "", MediaFile::AudioStream::BITRATE);
		samplerate << getAsString(stream, "", MediaFile::AudioStream::SAMPLERATE);
		channels << getAsString(stream, "", MediaFile::AudioStream::CHANNELS);
	}
}
} /* namespace Gui */
