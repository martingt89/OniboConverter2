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
	refGlade->get_widget("vbdBuffSize", vbdBuffer);
	refGlade->get_widget("vbdMinEnable", vbdMinEnable);
	refGlade->get_widget("vbdMaxEnable", vbdMaxEnable);
	refGlade->get_widget("vbdDisperEnable", vbdDisperEnable);
	refGlade->get_widget("vbdBufferEnable", vbdBufferEnable);
	refGlade->get_widget("vbdError", vbdError);

	videoBitrateDialog->add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
	videoBitrateDialog->add_button(Gtk::Stock::OK, Gtk::RESPONSE_OK);

	vbdMinEnable->set_active(false);
	vbdMaxEnable->set_active(false);
	vbdDisperEnable->set_active(false);
	vbdBufferEnable->set_active(false);

	vbdBitrate.signal_changed().connect(sigc::mem_fun(*this, &BitrateDialog::bitrateChanged));
	vbdMinBitrate->signal_value_changed().connect(sigc::mem_fun(*this, &BitrateDialog::bitrateMinChanged));
	vbdBuffer->signal_value_changed().connect(sigc::mem_fun(*this, &BitrateDialog::bufferChanged));
	vbdMaxBitrate->signal_value_changed ().connect(sigc::mem_fun(*this, &BitrateDialog::bitrateMaxChanged));
	vbdDispersion->signal_value_changed ().connect(sigc::mem_fun(*this, &BitrateDialog::dispersionChanged));

	vbdMinBitrate->signal_key_release_event().connect(sigc::mem_fun(*this, &BitrateDialog::bitrateMinKeyRelease), false);
	vbdMaxBitrate->signal_key_release_event().connect(sigc::mem_fun(*this, &BitrateDialog::bitrateMaxKeyRelease), false);
	vbdDispersion->signal_key_release_event().connect(sigc::mem_fun(*this, &BitrateDialog::dispersionKeyRelease), false);
	vbdBuffer->signal_key_release_event().connect(sigc::mem_fun(*this, &BitrateDialog::bufferKeyRelease), false);

	vbdMinEnable->signal_clicked().connect(sigc::mem_fun(*this, &BitrateDialog::bitrateMinActivate));
	vbdMaxEnable->signal_clicked().connect(sigc::mem_fun(*this, &BitrateDialog::bitrateMaxActivate));
	vbdDisperEnable->signal_clicked().connect(sigc::mem_fun(*this, &BitrateDialog::dispersionActivate));
	vbdBufferEnable->signal_clicked().connect(sigc::mem_fun(*this, &BitrateDialog::bufferActivate));
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

	vbdBitrate.setActiveText(toS(bitrate.getValue()));
	isEnableSignal = false;

	vbdMinBitrate->set_value(bitrate.getMinBitrate());
	vbdMaxBitrate->set_value(bitrate.getMaxBitrate());
	vbdBuffer->set_value(bitrate.getBufferSize());

	vbdMinEnable->set_active(bitrate.getMinBitrate() >= 0);
	vbdMaxEnable->set_active(bitrate.getMaxBitrate() >= 0);

	if(bitrate.getBufferSize() < 0){
		vbdBufferEnable->set_active(false);
		vbdBuffer->set_value(bitrate.getValue());
	}else{
		vbdBufferEnable->set_active(true);
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

		vbdMinBitrate->get_adjustment()->set_upper(bitrate);
		vbdMinBitrate->update();
		vbdMaxBitrate->get_adjustment()->set_lower(bitrate);
		vbdMaxBitrate->update();
		vbdDispersion->get_adjustment()->set_upper(bitrate);
		vbdDispersion->update();
		vbdBuffer->get_adjustment()->set_value(bitrate);
		vbdBuffer->update();
		isEnableSignal = true;
	}
}

void BitrateDialog::bitrateMinChanged(){
	if(isEnableSignal){
		isEnableSignal = false;
		vbdMinEnable->set_active(true);
		vbdDisperEnable->set_active(false);
		vbdBufferEnable->set_active(true);
		isEnableSignal = true;
	}
}
void BitrateDialog::bufferChanged(){
	if(isEnableSignal){
		isEnableSignal = false;
		vbdBufferEnable->set_active(true);

		isEnableSignal = true;
	}
}
void BitrateDialog::bitrateMaxChanged(){
	if(isEnableSignal){
		isEnableSignal = false;
		vbdMaxEnable->set_active(true);
		vbdBufferEnable->set_active(true);
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
		vbdBufferEnable->set_active(true);
		isEnableSignal = true;
	}
}

void BitrateDialog::bitrateMinActivate(){
	if(isEnableSignal){
		isEnableSignal = false;
		if(vbdMinEnable->get_active()){
			vbdDisperEnable->set_active(false);
			vbdBufferEnable->set_active(true);
		}
		isEnableSignal = true;
	}
}
void BitrateDialog::bitrateMaxActivate(){
	if(isEnableSignal){
		isEnableSignal = false;
		if(vbdMaxEnable->get_active()){
			vbdDisperEnable->set_active(false);
			vbdBufferEnable->set_active(true);
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
			vbdBufferEnable->set_active(true);
		}
		isEnableSignal = true;
	}
}
void BitrateDialog::bufferActivate(){
	if(isEnableSignal){
		isEnableSignal = false;
		if(!vbdBufferEnable->get_active()){
			vbdMinEnable->set_active(false);
			vbdMaxEnable->set_active(false);
			vbdDisperEnable->set_active(false);
		}
		isEnableSignal = true;
	}
}

/////////////
bool BitrateDialog::bitrateMinKeyRelease(GdkEventKey* event){
	if(isNumber(event->keyval)){
		bitrateMinChanged();
	}
	return false;
}
bool BitrateDialog::bitrateMaxKeyRelease(GdkEventKey* event){
	if(isNumber(event->keyval)){
		bitrateMaxChanged();
	}
	return false;
}
bool BitrateDialog::dispersionKeyRelease(GdkEventKey* event){
	if(isNumber(event->keyval)){
		dispersionChanged();
	}
	return false;
}
bool BitrateDialog::bufferKeyRelease(GdkEventKey* event){
	if(isNumber(event->keyval)){
		bufferChanged();
	}
	return false;
}

bool BitrateDialog::isNumber(guint keyval){
	return (keyval >= GDK_KEY_0 && keyval <= GDK_KEY_9) ||
			(keyval >= GDK_KEY_KP_0 && keyval <= GDK_KEY_KP_9);
}
/////////////

MediaElement::Bitrate BitrateDialog::createBitrate(){
	int bitrate = toN(vbdBitrate.getTextInEntry(), int());

	int min = -1;
	int max = -1;
	int buff = -1;
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
	if(vbdBufferEnable->get_active()){
		buff = vbdBuffer->get_value_as_int();
	}
	return MediaElement::Bitrate(bitrate, buff, min, max);
}
}
} /* namespace Gui */
