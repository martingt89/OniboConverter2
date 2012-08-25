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
	auto info = mediaFile->getFileInfo();
	videoStream.remove_all();
	audioStream.remove_all();
	filePath->set_text(actualMediaFile->getPath().getPath());
	duration << (toS(info.duration) + " sec");
	startTime << (toS(info.startTime) + " sec");
	bitrate << info.bitrate;

	auto videos = info.videos;
	for(auto stream : videos){
		auto pair = stream.getStreamNumber();
		videoStream.append(toS(pair.first) +"."+ toS(pair.second));
	}
	if(videoStream.count_of_rows() > 0){
		videoStream.set_sensitive(true);
	}
	auto audios = info.audios;
	for(auto stream : audios){
		auto pair = stream.getStreamNumber();
		audioStream.append(toS(pair.first) +"."+ toS(pair.second));
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
void InfoControl::videoStreamChanged(){
	bool exist = false;
	int row = videoStream.get_active_row_item(exist);
	if(exist){
		auto stream = actualMediaFile->getFileInfo().videos[row];
		videoCodec << stream.getValue(MediaFile::VideoStream::CODEC);
		colorSpace << stream.getValue(MediaFile::VideoStream::COLORSPACE);
		resolution << (stream.getValue(MediaFile::VideoStream::RESX) + "x" +
				stream.getValue(MediaFile::VideoStream::RESY));
		fps << stream.getValue(MediaFile::VideoStream::FPS);
		tbr << stream.getValue(MediaFile::VideoStream::TBR);
		tbn << stream.getValue(MediaFile::VideoStream::TBN);
		tbc << stream.getValue(MediaFile::VideoStream::TBC);
	}
}
void InfoControl::audioStreamChanged(){
	bool exist = false;
	int row = audioStream.get_active_row_item(exist);
	if(exist){
		auto stream = actualMediaFile->getFileInfo().audios[row];
		audioCodec << stream.getValue(MediaFile::AudioStream::CODEC);
		audioBitrate << stream.getValue(MediaFile::AudioStream::BITRATE);
		samplerate << stream.getValue(MediaFile::AudioStream::SAMPLERATE);
		channels << stream.getValue(MediaFile::AudioStream::CHANNELS);
	}
}
} /* namespace Gui */
