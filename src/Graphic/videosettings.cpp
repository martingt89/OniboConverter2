/*
 * videosettings.cpp
 *
 *  Created on: 5.7.2012
 *      Author: martint
 */

#include "videosettings.h"
#include "../helper.h"
#include <iostream> //todo remove
#include <gtkmm/liststore.h>

namespace GUI {

VideoSettings::VideoSettings(const Glib::RefPtr<Gtk::Builder>& refGlade) :
		refGlade(refGlade), audioVideoData(NULL), guiData(NULL), convert(NULL),
		suportedEncoders(NULL){

	activeContainer = "";
	refGlade->get_widget("v_mode",vMode);
	refGlade->get_widget("v_bitrate",vBitrate);
	refGlade->get_widget("v_framerate",vFramerate);

	refGlade->get_widget("v_format",vFormat);
	refGlade->get_widget("v_encoder",vEncoder);
	//todo load conponents

	vFramerate->append("original");
	vFramerate->set_active(0);

	vMode->append("Copy");
	vMode->append("Custom");
	vMode->append("Disable");
	vMode->set_active(1);

	vMode->signal_changed().connect(sigc::mem_fun(*this, &VideoSettings::rescanVideoMode));
	vFormat->signal_changed().connect(sigc::mem_fun(*this, &VideoSettings::rescanVideoFormat));
	this->setAllInsensitive();
}

VideoSettings::~VideoSettings() {
	// TODO Auto-generated destructor stub
}

void VideoSettings::reload(const std::string& container){
	std::cout<<container<<std::endl;
	activeContainer = container;
	if(audioVideoData){
		vFormat->set_sensitive(true);		//todo save old format
		vFormat->remove_all ();
		std::list<std::string> forms = audioVideoData->getContainer(container).getVideoFormats();
		std::list<std::string>::iterator it;

		for(it = forms.begin(); it != forms.end(); ++it){
			vFormat->append(*it);
			std::cout<<"adding: "<<*it<<std::endl;
		}
	}

	this->setAllInsensitive();
	vMode->set_sensitive(true);
	rescanVideoMode();
}

void VideoSettings::rescanVideoMode(){
	int row = vMode->get_active_row_number();
	std::cout<<"row: "<<row<<std::endl;
	if(row == 0 || row == 2 || row == -1){
		setAllInsensitive();
		vMode->set_sensitive(true);
	}
	if(row == 1){
		enableVideoSettings();
		rescanVideoFormat();
	}
}
void VideoSettings::rescanVideoFormat(){
	int row = vFormat->get_active_row_number();
	if(row != -1){
		vEncoder->set_sensitive(true);
		vEncoder->remove_all();
		numberOfEncoderItems = 0;

		std::string format = vFormat->get_active_text();
		AVBox::VideoFormat videof = audioVideoData->getContainer(activeContainer).getVideoFormat(format);
		std::list<AVBox::Encoder> encoders = videof.getAvailableEncoders(*suportedEncoders, *convert);
		std::list<AVBox::Encoder>::iterator it;

		for(it = encoders.begin(); it != encoders.end(); ++it){
			vEncoder->append(it->getEncoder());
			numberOfEncoderItems++;
		}

		if(encoders.size() == 0){
			vEncoder->append("None encoder");
			vEncoder->set_active(0);
			vEncoder->set_sensitive(false);
		}else{
			vEncoder->append("---details---");
		}
		std::cout<<"Details: "<<numberOfEncoderItems<<std::endl;
		//todo test for special (h264, vpx)
	}
}
void VideoSettings::setAllInsensitive(){
	vMode->set_sensitive(false);
	vBitrate->set_sensitive(false);
	vFramerate->set_sensitive(false);
	vFormat->set_sensitive(false);
	vEncoder->set_sensitive(false);
}
void VideoSettings::enableVideoSettings(){
	vBitrate->set_sensitive(true);
	vFramerate->set_sensitive(true);
	vFormat->set_sensitive(true);
}

void VideoSettings::initGuiData(AVBox::GuiSettings* guiData) {
	std::list<int> bitrs = guiData->getVideoBitrates();
	std::list<int>::iterator it;
	int counter = 0;
	for (it = bitrs.begin(); it != bitrs.end(); ++it) {
		vBitrate->append(toS(*it));
		counter++;
	}
	if (counter != 0) {
		vBitrate->set_active(counter / 2);
	}
	std::list<double> framerts = guiData->getVideoFramerates();
	std::list<double>::iterator it2;
	for (it2 = framerts.begin(); it2 != framerts.end(); ++it2) {
		vFramerate->append(toS(*it2));
	}
}

void VideoSettings::setNeedsData(AVBox::SupportedEncoders *suportedEncoders,
					AVBox::AVBox *audioVideoData,
					AVBox::GuiSettings *guiData,
					AVBox::FormatToEncoders *convert){
	this->suportedEncoders = suportedEncoders;
	this->audioVideoData = audioVideoData;
	this->guiData = guiData;
	this->convert = convert;

	initGuiData(guiData);
}

} /* namespace GUI */
