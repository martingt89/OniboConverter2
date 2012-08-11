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

namespace Gui {

class AVControl {
public:
	AVControl(ConverterOptions::OptionsDatabase &database, const Glib::RefPtr<Gtk::Builder>& refGlade);
	virtual ~AVControl();
	bool checkSettingsComplete(std::string& message);
	void saveSettingsState();
	void restoreSettingsState();
private:
	void userInput();
	void containerChanged();
	void initContainers(ConverterOptions::OptionsDatabase &database,
			ComboBoxExt<ConverterOptions::Container> &containers);

	ConverterOptions::OptionsDatabase &database;
	Video::VideoControl videoControlGui;
	Audio::AudioControl audioControlGui;
	ComboBoxExt<ConverterOptions::Container> containers;
	bool multiPassState;
	bool isEnabledSignal;
	bool isUserInput;
};

} /* namespace Gui */
#endif /* AVCONTROL_H_ */
