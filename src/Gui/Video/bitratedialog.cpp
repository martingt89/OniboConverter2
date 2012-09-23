/* ---------------------------------------------------------------------------
** Author: Martin Geier
** bitratedialog.cpp is part of OniboConverter2.
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

	vbdMinEnable->set_active(false);
	vbdMaxEnable->set_active(false);
	vbdDisperEnable->set_active(false);

	vbdBitrate.signal_changed().connect(sigc::mem_fun(*this, &BitrateDialog::bitrateChanged));
	vbdMinBitrate->signal_value_changed ().connect(sigc::mem_fun(*this, &BitrateDialog::bitrateMinChanged));
	vbdMaxBitrate->signal_value_changed ().connect(sigc::mem_fun(*this, &BitrateDialog::bitrateMaxChanged));
	vbdDispersion->signal_value_changed ().connect(sigc::mem_fun(*this, &BitrateDialog::dispersionChanged));

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
			vbdBitrate.uniqueAppend(toS(bitrate.getValue()), bitrate);
		}
	}

	vbdBitrate.set_active_text(toS(bitrate.getValue()));
	vbdMinBitrate->set_value(bitrate.getMinBitrate());
	vbdMaxBitrate->set_value(bitrate.getMaxBitrate());

	isEnableSignal = false;
	if(bitrate.getMinBitrate() < 0){
		vbdMinEnable->set_active(false);
	}
	if(bitrate.getMaxBitrate() < 0){
		vbdMaxEnable->set_active(false);
	}
	vbdDispersion->set_value(0);
	vbdDisperEnable->set_active(false);
	isEnableSignal = true;


	while(1){
		int res = videoBitrateDialog->run();
		if(res == Gtk::RESPONSE_OK){
			if(toN(vbdBitrate.getTextInEntry(), int()) != 0){
				bitrate = createBitrate();
				videoBitrateDialog->hide();
				return true;
			}else{
				vbdError->set_visible(true);
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
		int bitrate = toN(vbdBitrate.getTextInEntry(), int());
//		if(bitrate == 0){
//			vbdError->set_visible(true);
//		}else{
//			vbdError->set_visible(false);
//		}
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
	int bitrate = toN(vbdBitrate.getTextInEntry(), int());

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
