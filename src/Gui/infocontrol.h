/* ---------------------------------------------------------------------------
** Author: Martin Geier
** infocontrol.h is part of OniboConverter2.
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

#ifndef INFOCONTROL_H_
#define INFOCONTROL_H_

#include <gtkmm/builder.h>
#include <gtkmm/label.h>
#include <gtkmm/entry.h>
#include "WidgetAdapter/comboboxext.h"
#include "../MediaFile/mediafile.h"

namespace Gui {

class InfoControl {
public:
	InfoControl(const Glib::RefPtr<Gtk::Builder>& refGlade);
	virtual ~InfoControl();
	void show(MediaFile::MediaFile*& mediaFile);
private:
	void videoStreamChanged();
	void audioStreamChanged();
	Gtk::Entry* filePath; Gtk::Label* duration; Gtk::Label* startTime; Gtk::Label* bitrate;

	Gtk::Label* videoCodec; Gtk::Label* colorSpace; Gtk::Label* resolution; Gtk::Label* fps;
	Gtk::Label* tbr; Gtk::Label* tbn; Gtk::Label* tbc;

	Gtk::Label* audioCodec; Gtk::Label* audioBitrate; Gtk::Label* samplerate; Gtk::Label* channels;
	//
	ComboBoxExt<int> videoStream;
	ComboBoxExt<int> audioStream;
	//
	MediaFile::MediaFile* actualMediaFile;
};

} /* namespace Gui */
#endif /* INFOCONTROL_H_ */
