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
#include <giomm/file.h>

namespace GUI {


VideoSettings::VideoSettings(const Glib::RefPtr<Gtk::Builder>& refGlade, sigc::signal<void>& userEvent) :
		refGlade(refGlade), audioVideoData(NULL),
		suportedEncoders(NULL), convert(NULL),userEvent(userEvent),
		fileChooserDialog("Please choose a file", Gtk::FILE_CHOOSER_ACTION_OPEN){

	initFileChooserDialog(fileChooserDialog);

	activeContainer = "";
	Gtk::ComboBoxText *tmp;
	refGlade->get_widget("v_mode",vMode);
	refGlade->get_widget("v_bitrate",vBitrate);
	refGlade->get_widget("v_framerate",vFramerate);

	refGlade->get_widget("v_format",tmp);
	vFormat.set_widget(tmp);

	refGlade->get_widget("v_encoder",tmp);
	vEncoder.set_widget(tmp);

	refGlade->get_widget("v_extra",tmp);
	vExtra.set_widget(tmp);

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
	vFormat.signal_changed().connect(sigc::mem_fun(*this, &VideoSettings::rescanVideoFormat));
	vEncoder.signal_changed().connect(sigc::mem_fun(*this, &VideoSettings::rescanVideoEncoder));
	vResolution->signal_clicked().connect(sigc::mem_fun(*this, &VideoSettings::manageVideoResolution));
	vExtra.signal_changed().connect(sigc::mem_fun(*this, &VideoSettings::manageVideoExtra));

	vMode->signal_changed().connect(sigc::mem_fun(*this, &VideoSettings::event));
	vFormat.signal_changed().connect(sigc::mem_fun(*this, &VideoSettings::event));
	vEncoder.signal_changed().connect(sigc::mem_fun(*this, &VideoSettings::event));
	vExtra.signal_changed().connect(sigc::mem_fun(*this, &VideoSettings::event));
	vBitrate->signal_changed().connect(sigc::mem_fun(*this, &VideoSettings::event));
	vFramerate->signal_changed().connect(sigc::mem_fun(*this, &VideoSettings::event));
	this->setAllInsensitive();
}

VideoSettings::~VideoSettings() {
	delete vMode;
	delete vBitrate;
	delete vFramerate;
	delete vResolution;
	delete resolutionDialog;
	delete encodersDialog;
}

void VideoSettings::event(){
	userEvent();
}

void VideoSettings::enableVMode() {
	if(vFormat.count_of_elements() > 0 && vFormat.is_activable())
		vMode->set_sensitive(true);
}

void VideoSettings::setActualContainer(const std::string& container){
	std::string vFormatOld = "";
	activeContainer = container;
	if(audioVideoData){
		vFormat.set_sensitive(true);
		if(vFormat.is_selected()){
			vFormatOld = vFormat.get_active_text();
		}
		vFormat.remove_all ();
		std::list<std::string> forms = audioVideoData->getContainer(container).getVideoFormats();
		std::list<std::string>::iterator it;

		for(it = forms.begin(); it != forms.end(); ++it){
			vFormat.append(*it, true);
		}
		vFormat.set_activable(true);
		if(vFormat.count_of_elements() == 0){
			vFormat.append("None format", false);
			vFormat.set_active(0);
			vFormat.set_activable(false);
		}else{
			vFormat.set_active_text(vFormatOld);
		}
	}

	this->setAllInsensitive();
	enableVMode();
	rescanVideoMode();
}

void VideoSettings::rescanVideoMode(){
	int row = vMode->get_active_row_number();
	bool isSetSelectableItem = vFormat.get_active_row_data(true);
	if(row == 1 && isSetSelectableItem){
		enableVideoSettings();
		rescanVideoFormat();
	}else{
		setAllInsensitive();
		enableVMode();
	}
}

std::list<AVBox::Encoder> VideoSettings::getAvailableEncoders() {
	std::string format = vFormat.get_active_text();
	AVBox::VideoFormat videof =
			audioVideoData->getContainer(activeContainer).getVideoFormat(format);
	std::list<AVBox::Encoder> encoders = videof.getAvailableEncoders(
			*suportedEncoders, *convert);
	return encoders;
}

void VideoSettings::rescanVideoFormat() {
	if(vFormat.is_selected() && vFormat.is_sensitive()){
		if(!vFormat.is_same_row()){
			vFormat.checkpoint();

			vEncoder.remove_all();

			std::list<AVBox::Encoder> encoders = getAvailableEncoders();
			std::list<AVBox::Encoder>::iterator it;

			for(it = encoders.begin(); it != encoders.end(); ++it){
				vEncoder.append(it->getEncoder(), *it);
			}
			vEncoder.set_activable(true);
			vEncoder.set_sensitive(true);
			switch(vEncoder.count_of_elements()){
			case 1:
				vEncoder.append("---details---");
				vEncoder.set_active(0);
				break;
			case 0:
				vEncoder.append("None encoder");
				vEncoder.set_sensitive(false);
				vEncoder.set_activable(false);
				vEncoder.set_active(0);
				break;
			default:
				vEncoder.append("---details---");
				break;
			}
		}else{
			vEncoder.set_sensitive(true);
			rescanVideoEncoder();
		}
	}
}
void VideoSettings::rescanVideoEncoder(){
	if(vEncoder.is_selected() && vEncoder.is_same_row() && vMode->get_sensitive()){
		vExtra.set_sensitive(true);
		return;
	}

	vEncoder.checkpoint();
	vExtra.remove_all();
	activePrefix = "";

	if(!vEncoder.is_selected() || !vEncoder.is_sensitive()) return;

	if(vEncoder.is_set_last()){ //was selected "---details---"
		std::list<AVBox::Encoder> encoders = getAvailableEncoders();
		std::list<AVBox::Encoder>::iterator it;
		std::list<std::pair<std::string, std::string> > encoderWithDescription;

		for(it = encoders.begin(); it != encoders.end(); ++it){
			std::pair<std::string, std::string> tmpPair(it->getEncoder(), it->getDescription());
			encoderWithDescription.push_back(tmpPair);
		}
		std::string selectedEncoder;

		bool userSelected = encodersDialog->start(encoderWithDescription, selectedEncoder);
		if(userSelected){
			vEncoder.set_active_text(selectedEncoder);
		}else{
			vEncoder.unset_active();
		}
	}else{
		std::string prefix;
		if(vEncoder.get_active_row_data().getOptions("ffprefix", prefix)){
			vExtra.set_sensitive(true);
			vExtra.append("---choose file---", "");
			activePrefix = prefix;
			std::list<std::pair<std::string, std::string> >
					list = ffpresets.getShortnamesWithPaths(prefix);
			std::list<std::pair<std::string, std::string> >::iterator iter;
			for(iter = list.begin(); iter != list.end(); ++iter){
				vExtra.append(iter->first, iter->second);
			}
		}
	}
}
void VideoSettings::manageVideoResolution(){
	bool copy; int x; int y;
	std::string last = vResolutionLabel->get_text();
	std::string newone = "";
	if(resolutionDialog->start(copy, x, y)){
		if(copy) {
			x = -1;
			y = -1;
			newone = "Copy";
		}else{
			mainResolution.first = x;
			mainResolution.second = y;
			newone = toS(x) << "x" << y;
		}
		if(last != newone){
			vResolutionLabel->set_text(newone);
			event();
		}
	}
}
void VideoSettings::manageVideoExtra(){
	if(activePrefix.size() > 0 && vExtra.is_set_first() && vExtra.is_sensitive()){
		int stat = fileChooserDialog.run();
		fileChooserDialog.hide();
		if(stat == Gtk::RESPONSE_OK){
			Glib::RefPtr< Gio::File > file = fileChooserDialog.get_file ();
			vExtra.append(file->get_basename(), file->get_path());
			vExtra.set_active_text(file->get_basename());
			ffpresets.addUserDefinedFile(activePrefix, file);
		}else{
			vExtra.unset_active();
		}
	}
}
void VideoSettings::setAllInsensitive(){
	vMode->set_sensitive(false);
	vBitrate->set_sensitive(false);
	vFramerate->set_sensitive(false);
	vFormat.set_sensitive(false);
	vEncoder.set_sensitive(false);
	vResolution->set_sensitive(false);
	vExtra.set_sensitive(false);
}
void VideoSettings::enableVideoSettings(){
	vBitrate->set_sensitive(true);
	vFramerate->set_sensitive(true);
	vFormat.set_sensitive(true);
	vResolution->set_sensitive(true);
}
void VideoSettings::initFileChooserDialog(Gtk::FileChooserDialog &fileChooserDialog) {
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

void VideoSettings::setData(DataKeeper& keeper){
	this->convert = keeper.getFormatToEncoders();
	this->suportedEncoders = keeper.getSupportedEncoders();
	this->audioVideoData = keeper.getAVBox();
	initGuiData(keeper.getGuiSettings());
	resolutionDialog->setGuiSettings(keeper.getGuiSettings());
}
} /* namespace GUI */
