/*
 * mainsettings.h
 *
 *  Created on: 7.8.2012
 *      Author: martint
 */

#ifndef AVCONTROL_H_
#define AVCONTROL_H_

#include <gtkmm/builder.h>
#include "manualsettingscontrol.h"
#include "profilenamedialog.h"
#include "WidgetAdapter/comboboxext.h"
#include "Video/videocontrol.h"
#include "Audio/audiocontrol.h"
#include "../Profile/profiles.h"
#include "../MediaElement/elementsdb.h"

namespace Gui {

class AVControl {
public:
	AVControl(MediaElement::ElementsDB& elementsDB,
			const Glib::RefPtr<Gtk::Builder>& refGlade,
			const Profile::Profiles& profiles);
	virtual ~AVControl();
	bool checkSettingsComplete(std::string& message);
	void saveSettingsState();
	void restoreSettingsState();
	std::string getContainerName();
	Profile::Profile getTmpProfile();
private:
	void getNewProfile(const std::string& name);
	void userInput();
	void containerChanged();
	void profileChanged();
	void manualSettingsClicked();
	void saveProfileClicked();
	void initContainers(MediaElement::ElementsDB& elementsDB,
			ComboBoxExt<MediaElement::Container> &containers);
	void initProfiles(const Profile::Profiles& profiles,
			ComboBoxExt<Profile::Profile> &profilesComboBox);
	MediaElement::ElementsDB& elementsDB;
	const Profile::Profiles& profiles;
	Video::VideoControl videoControlGui;
	Audio::AudioControl audioControlGui;
	ComboBoxExt<MediaElement::Container> containers;
	ComboBoxExt<Profile::Profile> profilesComboBox;
	ManualSettingsControl settingsDialog;
	ProfileNameDialog profileNameDialog;
	Gtk::Button* manualSettingsButton;
	Gtk::Button* saveProfileAsButton;
	bool multiPassState;
	bool isEnabledSignal;
	bool isUserInput;
};

} /* namespace Gui */
#endif /* AVCONTROL_H_ */
