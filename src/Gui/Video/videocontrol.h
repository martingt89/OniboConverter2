/* ---------------------------------------------------------------------------
** Author: Martin Geier
** videocontrol.h is part of OniboConverter2.
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

#ifndef VIDEOCONTROLV_H_
#define VIDEOCONTROLV_H_

#include <sigc++/sigc++.h>
#include <gtkmm/builder.h>
#include "encodercontrolv.h"
#include "resolutiondialog.h"
#include "../WidgetAdapter/comboboxext.h"
#include "../../Profile/profile.h"

namespace Gui {
namespace Video {

class VideoControl {
public:
	VideoControl(MediaElement::ElementsDB& elementsDB, const Glib::RefPtr<Gtk::Builder>& refGlade);
	virtual ~VideoControl();
	void containerChanged(const MediaElement::Container& container);
	void saveSettingsState();
	void restoreSettingsState();
	bool checkSettingsComplete(std::string& message);
	void disableSettings();
	void setActiveProfile(const Profile::Profile& activeProfile);
	sigc::signal<void>& signalUserInput();
	//Converter::ConvertSettingsList getConvertArguments() const;
	void getNewProfile(Profile::Profile& newProfile);
private:
	void encoderUserInput();
	void videoModeChanged();
	void videoFramerateChanged();
	void videoResolutinChanged();
	void initVideoMode(ComboBoxExt<int> &videoMode);
	void initVideoFramerate(ComboBoxExt<MediaElement::Framerate> &videoFramerate);
	void initVideoResolution(ComboBoxExt<MediaElement::Resolution> &videoResolution);
	void sendUserInputSignal();

	MediaElement::ElementsDB& elementsDB;

	sigc::signal<void> userEvent;
	EncoderControl encoder;
	MediaElement::Container actualContainer;
	bool isEnabledSignals;

	ComboBoxExt<int> videoMode;
	ComboBoxExt<MediaElement::Framerate> videoFramerate;
	ComboBoxExt<MediaElement::Resolution> videoResolution;
	ResolutionControl resolutionDialog;
	MediaElement::Resolution lastSetResolution;
};

}
} /* namespace Gui */
#endif /* VIDEOCONTROLV_H_ */
