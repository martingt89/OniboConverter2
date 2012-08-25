/*
 * infocontrol.h
 *
 *  Created on: 25.8.2012
 *      Author: martint
 */

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
