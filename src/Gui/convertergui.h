/* ---------------------------------------------------------------------------
** Author: Martin Geier
** convertergui.h is part of OniboConverter2.
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

#ifndef CONVERTERGUI_H_
#define CONVERTERGUI_H_

#include <gtkmm/window.h>
#include <gtkmm/entry.h>
#include <gtkmm/button.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/builder.h>
#include <gtkmm/notebook.h>
#include <gtkmm/messagedialog.h>
#include <gtkmm/imagemenuitem.h>
#include <gtkmm/aboutdialog.h>
#include "avcontrol.h"
#include "destinationcontrol.h"
#include "filecontrol.h"
#include "convertwindow.h"
#include "infocontrol.h"
#include "overwritedialog.h"
#include "mainwindow.h"
#include "unencodersdialog.h"
#include "importexport.h"
#include "Settings/usersettingsdialog.h"
#include "../Profile/profile.h"
#include "../MediaFile/mediafile.h"

namespace Gui {

class ConverterGui {
public:
	ConverterGui(MediaElement::ElementsDB& elementsDB,
			const Glib::RefPtr<Gtk::Builder>& refGlade,
			Profile::Profiles& profiles,
			Gui::MainWindow* mainWindow);
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
	void showAboutDialog();

	AVControl avControl;
	DestinationControl destinationControl;
	FileControl fileControl;
	InfoControl infoControl;
	OverwriteDialog overwrite;
	ConvertWindow convertWindow;

	Settings::UserSettingsDialog settingsDialog;

	Gui::MainWindow* mainWindow;
	Gtk::MessageDialog warningDialog;
	UnEncodersDialog unsuportedEncoders;
	ImportExport inportExport;

	Gtk::Button* settingsButton;
	Gtk::Button* okSettingsButton;
	Gtk::Button* cancelSettingsButton;
	Gtk::Button* convertButton;
	Gtk::Button* fileInfoButton;
	Gtk::Button* returnFromInfo;
	Gtk::Notebook* mainNotebook;

	Gtk::MenuItem* settingsMenuItem;
	Gtk::ImageMenuItem* preferenceMenuItem;
	Gtk::ImageMenuItem* quitMenuItem;
	Gtk::ImageMenuItem* aboutMenuItem;

	Gtk::AboutDialog* aboutDialog;

	Gtk::Entry* entry;
	sigc::signal<void, std::list<MediaFile::MediaFile*> > convertEvent;
	CppExtension::HashMap<int, MediaFile::MediaFile*> idToMediaFile;
	std::list<MediaFile::MediaFile*> convertFilesList;
};

} /* namespace Gui */
#endif /* CONVERTERGUI_H_ */
