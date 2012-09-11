/*
 * videocontrolv.h
 *
 *  Created on: 8.8.2012
 *      Author: martint
 */

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
