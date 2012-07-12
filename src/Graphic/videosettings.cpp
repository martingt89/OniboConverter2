/*
 * videosettings.cpp
 *
 *  Created on: 5.7.2012
 *      Author: martint
 */

#include "videosettings.h"
#include "../Tools/helper.h"
#include <gtkmm/liststore.h>
#include <gtkmm/stock.h>
#include <iostream> //todo reomve
#include <giomm/file.h>
namespace GUI {

VideoSettings::VideoSettings(const Glib::RefPtr<Gtk::Builder>& refGlade) :
		refGlade(refGlade), audioVideoData(NULL), guiData(NULL),
		suportedEncoders(NULL), convert(NULL),
		fileChooserDialog("Please choose a file", Gtk::FILE_CHOOSER_ACTION_OPEN){

	fileChooserDialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
	fileChooserDialog.add_button(Gtk::Stock::OPEN, Gtk::RESPONSE_OK);

	Glib::RefPtr<Gtk::FileFilter> filterFFpresets = Gtk::FileFilter::create();
	filterFFpresets->set_name("ffpreset");
	filterFFpresets->add_pattern("*.ffpreset");
	fileChooserDialog.add_filter(filterFFpresets);

	Glib::RefPtr<Gtk::FileFilter> filterAny = Gtk::FileFilter::create();
	filterAny->set_name("Any files");
	filterAny->add_pattern("*");
	fileChooserDialog.add_filter(filterAny);

	activeContainer = "";
	lastFormat = "";
	lastEncoder = "";
	refGlade->get_widget("v_mode",vMode);
	refGlade->get_widget("v_bitrate",vBitrate);
	refGlade->get_widget("v_framerate",vFramerate);

	refGlade->get_widget("v_format",vFormat);
	refGlade->get_widget("v_encoder",vEncoder);
	refGlade->get_widget("v_extra",vExtra);

	refGlade->get_widget("v_resolution",vResolution);
	refGlade->get_widget("v_res_label",vResolutionLabel);

	refGlade->get_widget_derived("resolution_dialog",resolutionDialog);
	refGlade->get_widget_derived("encoders_dialog",encodersDialog);

	mainResolution.first = -1;
	mainResolution.second = -1;
	vResolutionLabel->set_text("Copy");

	vFramerate->append("original");
	vFramerate->set_active(0);

	vMode->append("Copy");
	vMode->append("Custom");
	vMode->append("Disable");
	vMode->set_active(1);

	vMode->signal_changed().connect(sigc::mem_fun(*this, &VideoSettings::rescanVideoMode));
	vFormat->signal_changed().connect(sigc::mem_fun(*this, &VideoSettings::rescanVideoFormat));
	vEncoder->signal_changed().connect(sigc::mem_fun(*this, &VideoSettings::rescanVideoEncoder));
	vResolution->signal_clicked().connect(sigc::mem_fun(*this, &VideoSettings::manageVideoResolution));
	vExtra->signal_changed().connect(sigc::mem_fun(*this, &VideoSettings::manageVideoExtra));

	this->setAllInsensitive();
}

VideoSettings::~VideoSettings() {
	delete vMode;
	delete vMode;
	delete vBitrate;
	delete vFramerate;
	delete vEncoder;
	delete vFormat;
	delete vExtra;
	delete vResolution;
	delete resolutionDialog;
	delete encodersDialog;
}

void VideoSettings::enableVMode() {
	if(vFormatCount)
		vMode->set_sensitive(true);
}

void VideoSettings::reload(const std::string& container){
	std::string vFormatOld = "";
	activeContainer = container;
	if(audioVideoData){
		vFormat->set_sensitive(true);
		if(vFormat->get_active_row_number() != -1){
			vFormatOld = vFormat->get_active_text();
		}
		vFormat->remove_all ();
		vFormatCount = 0;
		std::list<std::string> forms = audioVideoData->getContainer(container).getVideoFormats();
		std::list<std::string>::iterator it;

		for(it = forms.begin(); it != forms.end(); ++it){
			vFormat->append(*it);
			vFormatCount++;
		}
		if(vFormatCount == 0){
			vFormat->append("None format");
			vFormat->set_active(0);
		}else{
			vFormat->set_active_text(vFormatOld);
		}
	}

	this->setAllInsensitive();
	enableVMode();
	rescanVideoMode();
}

void VideoSettings::rescanVideoMode(){
	int row = vMode->get_active_row_number();
	if(row == 0 || row == 2 || row == -1 || vFormatCount == 0){
		setAllInsensitive();
		enableVMode();
	}else{
		enableVideoSettings();
		rescanVideoFormat();
	}
}

std::list<AVBox::Encoder> VideoSettings::getAvailableEncoders() {
	std::string format = vFormat->get_active_text();
	AVBox::VideoFormat videof =
			audioVideoData->getContainer(activeContainer).getVideoFormat(
					format);
	std::list<AVBox::Encoder> encoders = videof.getAvailableEncoders(
			*suportedEncoders, *convert);
	return encoders;
}

void VideoSettings::rescanVideoFormat() {
	int row = vFormat->get_active_row_number();
	if(row != -1){
		vEncoder->set_sensitive(true);
		if(lastFormat != vFormat->get_active_text()){
			lastFormat = vFormat->get_active_text();
			vEncoder->remove_all();
			setEncoders.clear();
			numberOfEncoderItems = 0;

			std::list<AVBox::Encoder> encoders = getAvailableEncoders();

			std::list<AVBox::Encoder>::iterator it;

			for(it = encoders.begin(); it != encoders.end(); ++it){
				vEncoder->append(it->getEncoder());
				numberOfEncoderItems++;
				setEncoders[it->getEncoder()] = *it;
			}
			switch(numberOfEncoderItems){
			case 1:
				vEncoder->set_active(0);
				vEncoder->append("---details---"); break;
			case 0:
				vEncoder->append("None encoder");
				vEncoder->set_active(0);
				vEncoder->set_sensitive(false);
				break;
			default:
				vEncoder->append("---details---"); break;
			}
		}else{
			rescanVideoEncoder();
		}
	}
}
void VideoSettings::rescanVideoEncoder(){
	int row = vEncoder->get_active_row_number();
	if(row >= 0 && lastEncoder == vEncoder->get_active_text()
			&& vMode->get_sensitive()){
		vExtra->set_sensitive(true);
		return;
	}
	lastEncoder = vEncoder->get_active_text();
	vExtra->set_sensitive(true);
	vExtra->remove_all();
	activePrefix = "";
	vExtra->set_sensitive(false);
	if(row < 0 || numberOfEncoderItems == 0) return;

	if(row == numberOfEncoderItems){	//was selected "---details---"
		std::list<AVBox::Encoder> encoders = getAvailableEncoders();
		std::list<AVBox::Encoder>::iterator it;
		std::list<std::pair<std::string, std::string> > encoderWithDescription;

		for(it = encoders.begin(); it != encoders.end(); ++it){
			std::pair<std::string, std::string> tmpPair(it->getEncoder(), it->getDescription());
			encoderWithDescription.push_back(tmpPair);
		}
		std::string selectedEncoder;
		bool ret = encodersDialog->start(encoderWithDescription, selectedEncoder);
		if(ret){
			vEncoder->set_active_text(selectedEncoder);
		}else{
			vEncoder->unset_active();
		}
	}else{
		std::string encoder = vEncoder->get_active_text();
		std::map<std::string, AVBox::Encoder>::iterator it;
		it = setEncoders.find(encoder);
		if(it != setEncoders.end()){
			std::map<std::string, std::string> options = it->second.getOptions();
			if(options.find("ffprefix") != options.end()){	//encoder support config files
				vExtra->set_sensitive(true);
				vExtra->append("---choose file---");
				activePrefix = options["ffprefix"];
				std::list<std::pair<std::string, std::string> >
						list = ffpresets.getShortNamesWithPaths(options["ffprefix"]);
				std::list<std::pair<std::string, std::string> >::iterator iter;
				for(iter = list.begin(); iter != list.end(); ++iter){
					vExtra->append(iter->first);
				}
			}
		}
	}
}
void VideoSettings::manageVideoResolution(){
	bool copy;
	int x;
	int y;
	if(resolutionDialog->start(copy, x, y)){
		if(copy) {
			x = -1;
			y = -1;
			vResolutionLabel->set_text("Copy");
		}else{
			mainResolution.first = x;
			mainResolution.second = y;
			vResolutionLabel->set_text(toS(x) << "x" << y);
		}
	}
}
void VideoSettings::manageVideoExtra(){
	if(activePrefix.size() > 0 && vExtra->get_active_row_number() == 0 && vExtra->get_sensitive()){
		int stat = fileChooserDialog.run();
		fileChooserDialog.hide();
		if(stat == Gtk::RESPONSE_OK){
			//std::cout<<"OK: "<<fileChooserDialog.get_filename();
			Glib::RefPtr< Gio::File > file = fileChooserDialog.get_file ();
			vExtra->append(file->get_basename());			//todo make save struct???
			vExtra->set_active_text(file->get_basename());
			ffpresets.addUserDefinedFile(activePrefix, file);
		}
	}
}
void VideoSettings::setAllInsensitive(){
	vMode->set_sensitive(false);
	vBitrate->set_sensitive(false);
	vFramerate->set_sensitive(false);
	vFormat->set_sensitive(false);
	vEncoder->set_sensitive(false);
	vResolution->set_sensitive(false);
	vExtra->set_sensitive(false);
}
void VideoSettings::enableVideoSettings(){
	vBitrate->set_sensitive(true);
	vFramerate->set_sensitive(true);
	vFormat->set_sensitive(true);
	vResolution->set_sensitive(true);
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
	resolutionDialog->setGuiSettings(guiData);
}

} /* namespace GUI */
