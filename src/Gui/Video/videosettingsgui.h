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
#include "videoencodergui.h"
#include "videoresolutiongui.h"

namespace Gui {

class VideoSettingsGui {
public:
	VideoSettingsGui(ConverterOptions::OptionsDatabase &database, const Glib::RefPtr<Gtk::Builder>& refGlade);
	virtual ~VideoSettingsGui();
	void videoContainerChanged(const ConverterOptions::Container& container);
	void saveSettingsState();
	void restoreSettingsState();
	bool checkSettingsComplete(std::string& message);
	void disableSettings();
	sigc::signal<void>& signalUserInput();
private:
	void encoderUserInput();
	void videoModeChanged();
	void videoFramerateChanged();
	void videoResolutinChanged();
	void initVideoMode(ComboBoxExt<int> &videoMode);
	void initVideoFramerate(ComboBoxExt<ConverterOptions::Framerate> &videoFramerate);
	void initVideoResolution(ComboBoxExt<ConverterOptions::Resolution> &videoResolution);
	void sendUserInputSignal();
	ConverterOptions::OptionsDatabase &database;

	sigc::signal<void> userEvent;
	VideoEncoderGui encoder;
	ConverterOptions::Container actualContainer;
	bool isEnabledSignals;

	ComboBoxExt<int> videoMode;
	ComboBoxExt<ConverterOptions::Framerate> videoFramerate;
	ComboBoxExt<ConverterOptions::Resolution> videoResolution;
	VideoResolutionGui resolutionDialog;
};

} /* namespace Gui */
#endif /* VIDEOSETTINGSGUI_H_ */
