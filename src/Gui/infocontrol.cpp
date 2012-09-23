/* ---------------------------------------------------------------------------
** Author: Martin Geier
** infocontrol.cpp is part of OniboConverter2.
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

#include "infocontrol.h"

namespace Gui {

static const std::string DEFAULT_STREAM = "default";
static const std::string CONVERT_STREAM = "convert";

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
	refGlade->get_widget("extraInfo", extra);

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
		duration << secTimeToReadableTime(info.getDuration());
	}else{
		duration << std::string("N/A");
	}
	startTime << (toS(info.getStartTime()) + " sec");
	bitrate << info.getBitrate();

	int counter = 0;
	auto videos = info.getVideoStreams();
	int videoConvertStream = 0;
	for(auto stream : videos){
		auto pair = stream.getStreamNumber();
		if(stream.isCenvertable()){
			videoStream.append(toS(pair.first) +"."+ toS(pair.second) +" "+
					stream.getStreamLanguage() + " " + CONVERT_STREAM, counter++);
			videoConvertStream = videoStream.number_of_rows() -1;
		}else{
			videoStream.append(toS(pair.first) +"."+ toS(pair.second) +" "+ stream.getStreamLanguage(), counter++);
		}
	}
	if(videoStream.number_of_rows() > 0){
		videoStream.set_sensitive(true);
	}

	counter = 0;
	auto audios = info.getAudioStreams();
	int audioConvertStream = 0;
	for(auto stream : audios){
		auto pair = stream.getStreamNumber();
		if(stream.isCenvertable()){
			audioStream.append(toS(pair.first) +"."+ toS(pair.second) +" "+
					stream.getStreamLanguage() + " " + CONVERT_STREAM, counter++);
			audioConvertStream = audioStream.number_of_rows() -1;
		}else{
			audioStream.append(toS(pair.first) +"."+ toS(pair.second) +" "+ stream.getStreamLanguage() , counter++);
		}
	}
	if(audioStream.number_of_rows() > 0){
		audioStream.set_sensitive(true);
	}

	videoCodec << std::string();
	colorSpace << std::string();
	resolution << std::string();
	fps << std::string();
	tbr << std::string();
	tbn << std::string();
	tbc << std::string();
	extra << std::string();

	audioCodec << std::string();
	audioBitrate << std::string();
	samplerate << std::string();
	channels << std::string();

	if(audioStream.number_of_rows() == 0){
		audioStream.set_sensitive(false);
	}else{
		audioStream.set_active_row_number(audioConvertStream);
	}
	if(videoStream.number_of_rows() == 0){
		videoStream.set_sensitive(false);
	}else{
		videoStream.set_active_row_number(videoConvertStream);
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
	int row = videoStream.getActiveItem(exist);
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
		if(stream.isDefault()){
			extra << DEFAULT_STREAM;
		}else{
			extra << std::string();
		}
	}
}
void InfoControl::audioStreamChanged(){
	bool exist = false;
	int row = audioStream.getActiveItem(exist);
	if(exist){
		auto stream = actualMediaFile->getMediaInfo().getAudioStreams()[row];
		audioCodec << getAsString(stream, "", MediaFile::AudioStream::CODEC);
		audioBitrate << getAsString(stream, "", MediaFile::AudioStream::BITRATE);
		samplerate << getAsString(stream, "", MediaFile::AudioStream::SAMPLERATE);
		channels << getAsString(stream, "", MediaFile::AudioStream::CHANNELS);
	}
}
} /* namespace Gui */
