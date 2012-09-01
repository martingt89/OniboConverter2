/*
 * convertergui.h
 *
 *  Created on: 7.8.2012
 *      Author: martint
 */

#ifndef CONVERTERGUI_H_
#define CONVERTERGUI_H_

#include <gtkmm/window.h>
#include <gtkmm/entry.h>
#include <gtkmm/button.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/builder.h>
#include <gtkmm/notebook.h>
#include <gtkmm/messagedialog.h>
#include "../Profile/profile.h"
#include "../ConverterOptions/optionsdatabase.h"
#include "avcontrol.h"
#include "destinationcontrol.h"
#include "filecontrol.h"
#include "convertwindow.h"
#include "infocontrol.h"
#include "overwritedialog.h"
#include "mainwindow.h"
#include "../MediaFile/mediafile.h"

namespace Gui {

class ConverterGui {
public:
	ConverterGui(ConverterOptions::OptionsDatabase &database,
			const Glib::RefPtr<Gtk::Builder>& refGlade,
			const Profile::Profiles& profiles,
			Gui::MainWindow* mainWindow);
	void setAvailableProfiles(const std::list<Profile::Profile>& availableProfiles);
	sigc::signal<void, std::list<MediaFile::MediaFile*> >& signalConvert();
	virtual ~ConverterGui();
private:
	void closeMainWindow();
	void settingsButtonClicked();
	void okSettingsButtonClicked();
	void cancelSettingsButtonClicked();
	void convertButtonClicked();
	void returnToMainPage();
	bool onKeyRelease(GdkEventKey* event);
	void fileInfoEvent(const Gui::FileControl::PathWithFileId file);
	void fileDeleteEvent(const Gui::FileControl::PathWithFileId& file);
	void showWarningDialog(const std::string& title, const std::string& message);
	bool convertTimer();

	ConverterOptions::OptionsDatabase &database;
	AVControl avControl;
	DestinationControl destinationControl;
	FileControl fileControl;
	InfoControl infoControl;
	OverwriteDialog overwrite;
	ConvertWindow convertWindow;
	Gui::MainWindow* mainWindow;
	Gtk::MessageDialog warningDialog;
//	Gtk::Window* mainWindow;

	Gtk::Button* settingsButton;
	Gtk::Button* okSettingsButton;
	Gtk::Button* cancelSettingsButton;
	Gtk::Button* convertButton;
	Gtk::Button* fileInfoButton;
	Gtk::Button* returnFromInfo;
	Gtk::Notebook* mainNotebook;

	Gtk::Entry* entry;
	sigc::signal<void, std::list<MediaFile::MediaFile*> > convertEvent;
	CppExtension::HashMap<int, MediaFile::MediaFile*> idToMediaFile;
	std::list<MediaFile::MediaFile*> convertFilesList;
};

} /* namespace Gui */
#endif /* CONVERTERGUI_H_ */
