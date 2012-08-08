/*
 * settingsdialog.h
 *
 *  Created on: 30.7.2012
 *      Author: martint
 */

#ifndef SETTINGSDIALOG_H_
#define SETTINGSDIALOG_H_

#include <gtkmm/builder.h>
#include <gtkmm/window.h>
#include <gtkmm/notebook.h>
#include <sigc++/sigc++.h>

namespace Gui {

class SettingsDialog {
public:
	SettingsDialog(const Glib::RefPtr<Gtk::Builder>& refGlade);
	virtual ~SettingsDialog();
	void showVideoSettings();
	void showAudioSettings();
	void showResolutionSettings();
	void showEncoderSettings();
	sigc::signal<void>& signalClose();
	void close();
private:
	void signalHide();
	Gtk::Window* settingsDialog;
	Gtk::Notebook* settingsPages;
	sigc::signal<void> closeWindow;
	bool closeCommand;
};

} /* namespace Gui */
#endif /* SETTINGSDIALOG_H_ */
