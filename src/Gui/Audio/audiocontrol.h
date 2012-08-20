/*
 * audiocontrol.h
 *
 *  Created on: 11.8.2012
 *      Author: martint
 */

#ifndef AUDIOCONTROL_H_
#define AUDIOCONTROL_H_

#include <gtkmm/builder.h>
#include <sigc++/sigc++.h>
#include "../WidgetAdapter/comboboxext.h"
#include "../../ConverterOptions/optionsdatabase.h"
#include "encodercontrola.h"
#include "../../Profile/profile.h"

namespace Gui {

namespace Audio{

class AudioControl {
public:
	AudioControl(ConverterOptions::OptionsDatabase &database, const Glib::RefPtr<Gtk::Builder>& refGlade);
	virtual ~AudioControl();
	void containerChanged(const ConverterOptions::Container& container);
	void saveSettingsState();
	void restoreSettingsState();
	bool checkSettingsComplete(std::string& message);
	void disableSettings();
	void setActiveProfile(const Profile::Profile& activeProfile);
	sigc::signal<void>& signalUserInput();
	Converter::ConvertSettingsList getConvertArguments() const;
private:
	void initAudioMode(ComboBoxExt<int>& audioMode);
	void initSamplerate(ComboBoxExt<ConverterOptions::Samplerate>& audioSamplerate);
	void initChannels(ComboBoxExt<ConverterOptions::Channel>& audioChannels);
	void audioModeChanged();
	void audioSamplerateChanged();
	void audioChannelsChanged();
	void sendUserInputSignal();
	ConverterOptions::OptionsDatabase &database;
	EncoderControlA encoderControl;
	ComboBoxExt<int> audioMode;
	ComboBoxExt<ConverterOptions::Samplerate> audioSamplerate;
	ComboBoxExt<ConverterOptions::Channel> audioChannels;
	bool isEnabledSignals;
	ConverterOptions::Container actualContainer;
	sigc::signal<void> userEvent;
};

} /* namespace Audio */
} /* namespace Gui */
#endif /* AUDIOCONTROL_H_ */
