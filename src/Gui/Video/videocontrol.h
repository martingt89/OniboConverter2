/*
 * videosettingsgui.h
 *
 *  Created on: 8.8.2012
 *      Author: martint
 */

#ifndef VIDEOCONTROL_H_
#define VIDEOCONTROL_H_

#include <gtkmm/builder.h>
#include "../../ConverterOptions/optionsdatabase.h"
#include "../WidgetAdapter/comboboxext.h"
#include "encodercontrol.h"
#include "resolutioncontrol.h"

namespace Gui {
namespace Video {

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
	std::string createResolutionText(const ConverterOptions::Resolution& resolution);
	ConverterOptions::OptionsDatabase &database;

	sigc::signal<void> userEvent;
	EncoderControl encoder;
	ConverterOptions::Container actualContainer;
	bool isEnabledSignals;

	ComboBoxExt<int> videoMode;
	ComboBoxExt<ConverterOptions::Framerate> videoFramerate;
	ComboBoxExt<ConverterOptions::Resolution> videoResolution;
	ResolutionControl resolutionDialog;
};

}
} /* namespace Gui */
#endif /* VIDEOCONTROL_H_ */
