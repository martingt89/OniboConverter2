/*
 * videosettingsgui.h
 *
 *  Created on: 8.8.2012
 *      Author: martint
 */

#ifndef VIDEOCONTROL_H_
#define VIDEOCONTROL_H_

#include <sigc++/sigc++.h>
#include <gtkmm/builder.h>
#include "../../ConverterOptions/optionsdatabase.h"
#include "../WidgetAdapter/comboboxext.h"
#include "encodercontrol.h"
#include "resolutiondialog.h"
#include "../../Profile/profile.h"

namespace Gui {
namespace Video {

class VideoControl {
public:
	VideoControl(ConverterOptions::OptionsDatabase &database, const Glib::RefPtr<Gtk::Builder>& refGlade);
	virtual ~VideoControl();
	void containerChanged(const ConverterOptions::Container& container);
	void saveSettingsState();
	void restoreSettingsState();
	bool checkSettingsComplete(std::string& message);
	void disableSettings();
	void setActiveProfile(const Profile::Profile& activeProfile);
	sigc::signal<void>& signalUserInput();
	Converter::ConvertSettingsList getConvertArguments() const;
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
	EncoderControl encoder;
	ConverterOptions::Container actualContainer;
	bool isEnabledSignals;

	ComboBoxExt<int> videoMode;
	ComboBoxExt<ConverterOptions::Framerate> videoFramerate;
	ComboBoxExt<ConverterOptions::Resolution> videoResolution;
	ResolutionControl resolutionDialog;
	ConverterOptions::Resolution lastSetResolution;
};

}
} /* namespace Gui */
#endif /* VIDEOCONTROL_H_ */
