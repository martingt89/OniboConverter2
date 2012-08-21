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
#include "../MediaFile/mediafile.h"

namespace Gui {

class ConverterGui {
public:
	ConverterGui(ConverterOptions::OptionsDatabase &database,
			const Glib::RefPtr<Gtk::Builder>& refGlade,
			const Profile::Profiles& profiles);
	void setAvailableProfiles(const std::list<Profile::Profile>& availableProfiles);
	Gtk::Window& getWindow();
	sigc::signal<void, std::list<MediaFile::MediaFile*> >& signalConvert();
	virtual ~ConverterGui();
private:
	void settingsButtonClicked();
	void okSettingsButtonClicked();
	void cancelSettingsButtonClicked();
	void convertButtonClicked();
	void showWarningDialog(const std::string& title, const std::string& message);

	ConverterOptions::OptionsDatabase &database;
	AVControl mainSettings;
	DestinationControl destinationControl;
	FileControl fileControl;
	Gtk::Window* mainWindow;
	Gtk::Button* settingsButton;
	Gtk::Button* okSettingsButton;
	Gtk::Button* cancelSettingsButton;
	Gtk::Button* convertButton;
	Gtk::Notebook* mainNotebook;
	Gtk::MessageDialog warningDialog;

	Gtk::Entry* entry;
	sigc::signal<void, std::list<MediaFile::MediaFile*> > convertEvent;
	CppExtension::HashMap<int, MediaFile::MediaFile> idToMediaFile;
	std::list<MediaFile::MediaFile*> convertFilesList;
};

} /* namespace Gui */
#endif /* CONVERTERGUI_H_ */
