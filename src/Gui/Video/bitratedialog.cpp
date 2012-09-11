/*
 * bitratecontrol.cpp
 *
 *  Created on: 10.8.2012
 *      Author: martint
 */

#include "bitratedialog.h"
#include <gtkmm/stock.h>
#include "../../helper.h"

namespace Gui {
namespace Video{

BitrateDialog::BitrateDialog(MediaElement::ElementsDB &elementsDB,
		const Glib::RefPtr<Gtk::Builder>& refGlade) : elementsDB(elementsDB),
				vbdBitrate(refGlade, "vbdBitrate"){
	isEnableSignal = true;
	refGlade->get_widget("videoBitrateDialog", videoBitrateDialog);
	refGlade->get_widget("vbdMinBitrate", vbdMinBitrate);
	refGlade->get_widget("vbdMaxBitrate", vbdMaxBitrate);
	refGlade->get_widget("vbdDispersion", vbdDispersion);
	refGlade->get_widget("vbdMinEnable", vbdMinEnable);
	refGlade->get_widget("vbdMaxEnable", vbdMaxEnable);
	refGlade->get_widget("vbdDisperEnable", vbdDisperEnable);
	refGlade->get_widget("vbdError", vbdError);

	videoBitrateDialog->add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
	videoBitrateDialog->add_button(Gtk::Stock::OK, Gtk::RESPONSE_OK);

	vbdBitrate.signal_changed().connect(sigc::mem_fun(*this, &BitrateDialog::bitrateChanged));
	vbdMinBitrate->signal_changed().connect(sigc::mem_fun(*this, &BitrateDialog::bitrateMinChanged));
	vbdMaxBitrate->signal_changed().connect(sigc::mem_fun(*this, &BitrateDialog::bitrateMaxChanged));
	vbdDispersion->signal_changed().connect(sigc::mem_fun(*this, &BitrateDialog::dispersionChanged));

	vbdMinEnable->signal_clicked().connect(sigc::mem_fun(*this, &BitrateDialog::bitrateMinActivate));
	vbdMaxEnable->signal_clicked().connect(sigc::mem_fun(*this, &BitrateDialog::bitrateMaxActivate));
	vbdDisperEnable->signal_clicked().connect(sigc::mem_fun(*this, &BitrateDialog::dispersionActivate));
}

BitrateDialog::~BitrateDialog() {
	delete videoBitrateDialog;
	delete vbdMinBitrate;
	delete vbdMaxBitrate;
	delete vbdDispersion;
	delete vbdMinEnable;
	delete vbdMaxEnable;
	delete vbdDisperEnable;
	delete vbdError;
}
bool BitrateDialog::start(const MediaElement::Encoder& encoder, MediaElement::Bitrate &bitrate){
	std::string bitratersName = elementsDB.elementsRelations.getBitratesByEncoder(encoder);
	MediaElement::Bitrates bitrates;

	vbdError->set_visible(false);
	vbdBitrate.remove_all();

	if(elementsDB.getBitratesByName(bitratersName, bitrates)){
		for(auto bitrate : bitrates){
			vbdBitrate.uniqueAppend(bitrate.readableForm(), bitrate);
		}
	}

	vbdBitrate.set_active_text(toS(bitrate.getValue()));
	vbdMinBitrate->set_value(bitrate.getMinBitrate());
	vbdMaxBitrate->set_value(bitrate.getMaxBitrate());
	while(1){
		int res = videoBitrateDialog->run();
		if(res == Gtk::RESPONSE_OK){
			if(toN(vbdBitrate.getValue(), int()) != 0){
				bitrate = createBitrate();
				videoBitrateDialog->hide();
				return true;
			}
		}else{
			videoBitrateDialog->hide();
			return false;
		}
	}
	return true;
}
void BitrateDialog::bitrateChanged(){
	if(isEnableSignal){
		isEnableSignal = false;
		int bitrate = toN(vbdBitrate.getValue(), int());
		if(bitrate == 0){
			vbdError->set_visible(true);
		}else{
			vbdError->set_visible(false);
		}
		vbdMinBitrate->get_adjustment()->set_upper(bitrate);
		vbdMinBitrate->update();
		vbdMaxBitrate->get_adjustment()->set_lower(bitrate);
		vbdMaxBitrate->update();
		vbdDispersion->get_adjustment()->set_upper(bitrate);
		vbdDispersion->update();
		isEnableSignal = true;
	}
}

void BitrateDialog::bitrateMinChanged(){
	if(isEnableSignal){
		isEnableSignal = false;
		vbdMinEnable->set_active(true);
		vbdDisperEnable->set_active(false);
		isEnableSignal = true;
	}
}
void BitrateDialog::bitrateMaxChanged(){
	if(isEnableSignal){
		isEnableSignal = false;
		vbdMaxEnable->set_active(true);
		vbdDisperEnable->set_active(false);
		isEnableSignal = true;
	}
}
void BitrateDialog::dispersionChanged(){
	if(isEnableSignal){
		isEnableSignal = false;
		vbdMinEnable->set_active(false);
		vbdMaxEnable->set_active(false);
		vbdDisperEnable->set_active(true);
		isEnableSignal = true;
	}
}

void BitrateDialog::bitrateMinActivate(){
	if(isEnableSignal){
		isEnableSignal = false;
		if(vbdMinEnable->get_active()){
			vbdDisperEnable->set_active(false);
		}
		isEnableSignal = true;
	}
}
void BitrateDialog::bitrateMaxActivate(){
	if(isEnableSignal){
		isEnableSignal = false;
		if(vbdMaxEnable->get_active()){
			vbdDisperEnable->set_active(false);
		}
		isEnableSignal = true;
	}
}
void BitrateDialog::dispersionActivate(){
	if(isEnableSignal){
		isEnableSignal = false;
		if(vbdDisperEnable->get_active()){
			vbdMinEnable->set_active(false);
			vbdMaxEnable->set_active(false);
		}
		isEnableSignal = true;
	}
}
MediaElement::Bitrate BitrateDialog::createBitrate(){
	int bitrate = toN(vbdBitrate.getValue(), int());

	int min = -1;
	int max = -1;
	if(vbdDisperEnable->get_active()){
		int dispersion = vbdDispersion->get_value();
		min = bitrate - dispersion;
		max = bitrate + dispersion;
	}else{
		if(vbdMaxEnable->get_active()){
			max = vbdMaxBitrate->get_value();
		}
		if(vbdMinEnable->get_active()){
			min = vbdMinBitrate->get_value();
		}
	}
	return MediaElement::Bitrate(bitrate, min, max);
}
}
} /* namespace Gui */
