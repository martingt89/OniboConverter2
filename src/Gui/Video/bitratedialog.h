/* ---------------------------------------------------------------------------
** Author: Martin Geier
** bitratedialog.h is part of OniboConverter2.
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

#ifndef BITRATEDIALOG_H_
#define BITRATEDIALOG_H_

#include <gtkmm/builder.h>
#include <gtkmm/dialog.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/checkbutton.h>
#include <gtkmm/label.h>
#include "../WidgetAdapter/comboboxext.h"
#include "../../MediaElement/elementsdb.h"

namespace Gui {
namespace Video{

class BitrateDialog {
public:
	BitrateDialog(MediaElement::ElementsDB& elementsDB,
			const Glib::RefPtr<Gtk::Builder>& refGlade);
	virtual ~BitrateDialog();
	bool start(const MediaElement::Encoder& encoder, MediaElement::Bitrate &bitrate);
private:
	void bitrateChanged();
	void bitrateMinChanged();
	void bitrateMaxChanged();
	void dispersionChanged();
	void bitrateMinActivate();
	void bitrateMaxActivate();
	void dispersionActivate();
	MediaElement::Bitrate createBitrate();
	MediaElement::ElementsDB& elementsDB;
	Gtk::Dialog* videoBitrateDialog;
	ComboBoxExt<MediaElement::Bitrate> vbdBitrate;
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
