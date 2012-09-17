/* ---------------------------------------------------------------------------
** Author: Martin Geier
** audiocontrol.h is part of OniboConverter2.
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

#ifndef AUDIOCONTROL_H_
#define AUDIOCONTROL_H_

#include <gtkmm/builder.h>
#include <sigc++/sigc++.h>
#include "../WidgetAdapter/comboboxext.h"
#include "encodercontrola.h"
#include "../../Profile/profile.h"

namespace Gui {

namespace Audio{

class AudioControl {
public:
	AudioControl(MediaElement::ElementsDB& elementsDB, const Glib::RefPtr<Gtk::Builder>& refGlade);
	virtual ~AudioControl();
//	Converter::ConvertSettingsList getConvertArguments() const;
	void containerChanged(const MediaElement::Container& container);
	void saveSettingsState();
	void restoreSettingsState();
	bool checkSettingsComplete(std::string& message);
	void disableSettings();
	void setActiveProfile(const Profile::Profile& activeProfile);
	sigc::signal<void>& signalUserInput();
	void getNewProfile(Profile::Profile& newProfile);
private:
	void initAudioMode(ComboBoxExt<int>& audioMode);
	void initSamplerate(ComboBoxExt<MediaElement::Samplerate>& audioSamplerate);
	void initChannels(ComboBoxExt<MediaElement::Channel>& audioChannels);
	void audioModeChanged();
	void audioSamplerateChanged();
	void audioChannelsChanged();
	void sendUserInputSignal();
	MediaElement::ElementsDB& elementsDB;
//	ConverterOptions::OptionsDatabase &database;
	EncoderControlA encoderControl;
	ComboBoxExt<int> audioMode;
	ComboBoxExt<MediaElement::Samplerate> audioSamplerate;
	ComboBoxExt<MediaElement::Channel> audioChannels;
	bool isEnabledSignals;
	MediaElement::Container actualContainer;
	sigc::signal<void> userEvent;
};

} /* namespace Audio */
} /* namespace Gui */
#endif /* AUDIOCONTROL_H_ */
