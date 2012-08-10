/*
 * bitratecontrol.h
 *
 *  Created on: 10.8.2012
 *      Author: martint
 */

#ifndef BITRATEDIALOG_H_
#define BITRATEDIALOG_H_

#include <gtkmm/builder.h>
#include <gtkmm/dialog.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/checkbutton.h>
#include <gtkmm/label.h>
#include "../WidgetAdapter/comboboxext.h"
#include "../../ConverterOptions/optionsdatabase.h"

namespace Gui {
namespace Video{

class BitrateDialog {
public:
	BitrateDialog(ConverterOptions::OptionsDatabase &database,
			const Glib::RefPtr<Gtk::Builder>& refGlade);
	virtual ~BitrateDialog();
	bool start(const ConverterOptions::Encoder& encoder, ConverterOptions::Bitrate &bitrate);
private:
	void bitrateChanged();
	void bitrateMinChanged();
	void bitrateMaxChanged();
	void dispersionChanged();
	void bitrateMinActivate();
	void bitrateMaxActivate();
	void dispersionActivate();
	ConverterOptions::Bitrate createBitrate();
	ConverterOptions::OptionsDatabase &database;
	Gtk::Dialog* videoBitrateDialog;
	ComboBoxExt<ConverterOptions::Bitrate> vbdBitrate;
	Gtk::SpinButton* vbdMinBitrate;
	Gtk::SpinButton* vbdMaxBitrate;
	Gtk::SpinButton* vbdDispersion;
	Gtk::CheckButton* vbdMinEnable;
	Gtk::CheckButton* vbdMaxEnable;
	Gtk::CheckButton* vbdDisperEnable;
	Gtk::Label* vbdError;
	bool isEnableSignal;
};

}
} /* namespace Gui */
#endif /* BITRATEDIALOG_H_ */
