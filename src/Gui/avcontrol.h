/*
 * mainsettings.h
 *
 *  Created on: 7.8.2012
 *      Author: martint
 */

#ifndef AVCONTROL_H_
#define AVCONTROL_H_

#include <gtkmm/builder.h>
#include "../ConverterOptions/optionsdatabase.h"
#include "WidgetAdapter/comboboxext.h"
#include "Video/videocontrol.h"
#include "Audio/audiocontrol.h"
#include "../Profile/profile.h"
#include "manualsettingscontrol.h"
#include "../Converter/convertsettings.h"

namespace Gui {

class AVControl {
public:
	AVControl(ConverterOptions::OptionsDatabase &database,
			const Glib::RefPtr<Gtk::Builder>& refGlade,
			const Profile::Profiles& profiles);
	virtual ~AVControl();
	bool checkSettingsComplete(std::string& message);
	void saveSettingsState();
	void restoreSettingsState();
	Converter::ConvertSettingsList getConvertArguments() const;
private:
	void getNewProfile();
	void userInput();
	void containerChanged();
	void profileChanged();
	void manualSettingsClicked();
	void initContainers(ConverterOptions::OptionsDatabase &database,
			ComboBoxExt<ConverterOptions::Container> &containers);
	void initProfiles(const Profile::Profiles& profiles,
			ComboBoxExt<Profile::Profile> &profilesComboBox);
	ConverterOptions::OptionsDatabase &database;
	const Profile::Profiles& profiles;
	Video::VideoControl videoControlGui;
	Audio::AudioControl audioControlGui;
	ComboBoxExt<ConverterOptions::Container> containers;
	ComboBoxExt<Profile::Profile> profilesComboBox;
	ManualSettingsControl settingsDialog;
	Gtk::Button* manualSettingsButton;
	Gtk::Button* saveProfileAsButton;
	bool multiPassState;
	bool isEnabledSignal;
	bool isUserInput;
};

} /* namespace Gui */
#endif /* AVCONTROL_H_ */
