/*
 * resolutiondialog.cpp
 *
 *  Created on: 7.7.2012
 *      Author: martint
 */

#include "resolutiondialog.h"
#include <gtkmm/stock.h>
#include "../Tools/helper.h"
#include "../Tools/regextools.h"

ResolutionDialog::ResolutionDialog(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade):
	Gtk::Dialog(cobject), settings(NULL), disableEntryInterupt(false){
	aspectCount = 0;
	lastSetRatio = "";

	this->add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
	this->add_button(Gtk::Stock::OK, Gtk::RESPONSE_OK);

	refGlade->get_widget("res_copy", copyMode);
	refGlade->get_widget("res_aspect", aspectRatio);
	refGlade->get_widget("res_preddef_res", resolutions);
	refGlade->get_widget("res_manually_x", editableResolutionX);
	refGlade->get_widget("res_manually_y", editableResolutionY);
	refGlade->get_widget("res_error", errorMessage);

	changeCopyMode();
	setCopyButtonLabel();

	copyMode->signal_clicked().connect(sigc::mem_fun(*this, &ResolutionDialog::setCopyButtonLabel));
	copyMode->signal_clicked().connect(sigc::mem_fun(*this, &ResolutionDialog::changeCopyMode));
	aspectRatio->signal_changed().connect(sigc::mem_fun(*this, &ResolutionDialog::rescanApectRatio));
	resolutions->signal_changed().connect(sigc::mem_fun(*this, &ResolutionDialog::rescanResolution));
	editableResolutionX->signal_changed().connect(sigc::mem_fun(*this, &ResolutionDialog::recalculeResolutionXtoY));
	editableResolutionY->signal_changed().connect(sigc::mem_fun(*this, &ResolutionDialog::recalculeResolutionYtoX));

}
ResolutionDialog::~ResolutionDialog() {
	delete copyMode;
	delete aspectRatio;
	delete resolutions;
	delete editableResolutionX;
	delete editableResolutionY;
	delete errorMessage;
}

void ResolutionDialog::changeCopyMode(){
	setSensitivity(copyMode->get_active());
	rescanApectRatio();
}
void ResolutionDialog::recalculeResolutionXtoY(){
	if(disableEntryInterupt) return;
	disableEntryInterupt = true;
	std::string width = editableResolutionX->get_text();
	if(toS(toN(width, int())) != width){
		errorMessage->set_text("invalid number");
		disableEntryInterupt = false;
		return;
	}
	errorMessage->set_text("");
	int row = aspectRatio->get_active_row_number();
	if(row >= 0 && row != aspectCount){
		int x, y;
		getRatioNumbers(aspectRatio->get_active_text(), x, y);
		int w = toN(width, int());
		setResolution(w, (w/(double)x*y));
	}
	disableEntryInterupt = false;
}
void ResolutionDialog::recalculeResolutionYtoX(){
	if(disableEntryInterupt) return;

	std::string height = editableResolutionY->get_text();
	if(toS(toN(height, int())) != height){
		errorMessage->set_text("invalid number");
		disableEntryInterupt = false;
		return;
	}
	errorMessage->set_text("");
	int row = aspectRatio->get_active_row_number();
	if(row >= 0 && row != aspectCount){
		int x, y;
		getRatioNumbers(aspectRatio->get_active_text(), x, y);
		int h = toN(height, int());
		setResolution((h/(double)y*x), h);
	}
}
void ResolutionDialog::rescanApectRatio(){
	int row = aspectRatio->get_active_row_number();
	if(row < 0 || aspectRatio->get_sensitive() == false){
		resolutions->set_sensitive(false);
		editableResolutionX->set_sensitive(false);
		editableResolutionY->set_sensitive(false);
		return;
	}

	if(lastSetRatio == aspectRatio->get_active_text())return;

	lastSetRatio = aspectRatio->get_active_text();

	std::list<AVBox::GuiSettings::ResolutionStruct> resol;
	if(row != aspectCount){
		resol = settings->getVideoResolution(aspectRatio->get_active_text());
	}else{
		resol = settings->getVideoResolution();
	}
	std::list<AVBox::GuiSettings::ResolutionStruct>::iterator it;

	resolutions->set_sensitive(true);
	resolutions->remove_all();
	resolutions->set_sensitive(false);
	resolutionCeeper.clear();
	resolutionCeeper.resize(0);
	for(it = resol.begin(); it != resol.end(); ++it){
		if(it->name.size() > 0)
			resolutions->append(it->resolution + " == " +it->name);
		else
			resolutions->append(it->resolution);
		resolutionCeeper.push_back(*it);
	}
	if(resol.size() != 0){
		resolutions->set_sensitive(true);
		editableResolutionX->set_sensitive(true);
		editableResolutionY->set_sensitive(true);
	}
}

void ResolutionDialog::setResolution(int x, int y){
	errorMessage->set_text("");
	disableEntryInterupt = true;
	editableResolutionX->set_text(toS(x));
	editableResolutionY->set_text(toS(y));
	disableEntryInterupt = false;
}

void ResolutionDialog::rescanResolution(){
	int row = resolutions->get_active_row_number();
	if(row >= 0){
		AVBox::GuiSettings::ResolutionStruct res = resolutionCeeper[row];
		setResolution(res.x, res.y);
	}
}

void ResolutionDialog::setCopyButtonLabel(){
	if(copyMode->get_active()){
		copyMode->set_label("false");
	}else{
		copyMode->set_label("true");
	}
}

void ResolutionDialog::setSensitivity(bool sensitiv){
	aspectRatio->set_sensitive(sensitiv);
	resolutions->set_sensitive(sensitiv);
	editableResolutionX->set_sensitive(sensitiv);
	editableResolutionY->set_sensitive(sensitiv);
}

void ResolutionDialog::setGuiSettings(AVBox::GuiSettings *settings){
	this->settings = settings;
	std::list<std::string> ratios = settings->getVideoRatios();

	std::list<std::string>::iterator it;
	for(it = ratios.begin(); it != ratios.end(); ++it){
		aspectRatio->append(*it);
		aspectCount++;
	}
	aspectRatio->append("custom");
}
void ResolutionDialog::getRatioNumbers(const std::string& ratio, int &x, int &y){
	x = 1; y = 1;
	RegexTools::Regex reg("([[:digit:]]+)\\:([[:digit:]]+)");
	RegexTools::Matcher mat = reg.getMatcher(ratio);
	if(mat.find()){
		x = toN(mat.getGroup(1), int());
		y = toN(mat.getGroup(2), int());
	}
}
bool ResolutionDialog::start(bool& copy, int& xRes, int& yRes){
	errorMessage->set_label("");
	bool ok = false;
	while(this->run() == 1){
		if(!copyMode->get_active() ||
				(isN(editableResolutionX->get_text(), unsigned()) &&
				isN(editableResolutionY->get_text(), unsigned()))){

			copy = !copyMode->get_active();
			xRes = toN(editableResolutionX->get_text(), int());
			yRes = toN(editableResolutionY->get_text(), int());
			ok = true;
			break;
		}else{
			errorMessage->set_label("Invalid resolution");
		}
	}
	this->hide();
	return ok;
}
