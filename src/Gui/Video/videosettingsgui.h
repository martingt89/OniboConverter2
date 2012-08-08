/*
 * videosettingsgui.h
 *
 *  Created on: 8.8.2012
 *      Author: martint
 */

#ifndef VIDEOSETTINGSGUI_H_
#define VIDEOSETTINGSGUI_H_

#include <gtkmm/builder.h>
#include "../../ConverterOptions/optionsdatabase.h"
#include "../comboboxext.h"

namespace Gui {

class VideoSettingsGui {
public:
	VideoSettingsGui(ConverterOptions::OptionsDatabase &database, const Glib::RefPtr<Gtk::Builder>& refGlade);
	virtual ~VideoSettingsGui();
	void saveSettingsState();
	void restoreSettingsState();
	bool checkSettingsComplete(std::string& message);
private:
	void initVideoMode(ComboBoxExt<int> &videoMode);
	void initVideoFramerate(ComboBoxExt<ConverterOptions::Framerate> &videoFramerate);
	void initVideoResolution(ComboBoxExt<ConverterOptions::Resolution> &videoResolution);
	ConverterOptions::OptionsDatabase &database;

	ComboBoxExt<int> videoMode;
	ComboBoxExt<ConverterOptions::Framerate> videoFramerate;
	ComboBoxExt<ConverterOptions::Resolution> videoResolution;
};

} /* namespace Gui */
#endif /* VIDEOSETTINGSGUI_H_ */
