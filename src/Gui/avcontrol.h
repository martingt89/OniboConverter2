/* ---------------------------------------------------------------------------
** Author: Martin Geier
** avcontrol.h is part of OniboConverter2.
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
	Profile::Profile getTmpProfile(const std::string name = "tmp");
	void rescanProfiles();
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
