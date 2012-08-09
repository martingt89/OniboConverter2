/*
 * mainsettings.h
 *
 *  Created on: 7.8.2012
 *      Author: martint
 */

#ifndef MAINSETTINGS_H_
#define MAINSETTINGS_H_

#include <gtkmm/builder.h>
#include "../ConverterOptions/optionsdatabase.h"
#include "comboboxext.h"
#include "Video/videosettingsgui.h"

namespace Gui {

class MainSettings {
public:
	MainSettings(ConverterOptions::OptionsDatabase &database, const Glib::RefPtr<Gtk::Builder>& refGlade);
	virtual ~MainSettings();
	bool checkSettingsComplete(std::string& message);
	void saveSettingsState();
	void restoreSettingsState();
private:
	void userInput();
	void containerChanged();
	void initContainers(ConverterOptions::OptionsDatabase &database,
			ComboBoxExt<ConverterOptions::Container> &containers);

	ConverterOptions::OptionsDatabase &database;
	VideoSettingsGui videoSettingsGui;
	ComboBoxExt<ConverterOptions::Container> containers;
	bool multiPassState;
	bool isEnabledSignal;
};

} /* namespace Gui */
#endif /* MAINSETTINGS_H_ */
