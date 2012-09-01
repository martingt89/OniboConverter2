/*
 * videoencodergui.h
 *
 *  Created on: 8.8.2012
 *      Author: martint
 */

#ifndef ENCODERCONTROL_H_
#define ENCODERCONTROL_H_

#include <sigc++/signal.h>
#include <gtkmm/builder.h>
#include <gtkmm/filechooserdialog.h>
#include "resolutiondialog.h"
#include "bitratedialog.h"
#include "../WidgetAdapter/comboboxext.h"
#include "../../ConverterOptions/optionsdatabase.h"
#include "../../Profile/profile.h"
namespace Gui {
namespace Video {

class EncoderControl {
public:
	EncoderControl(ConverterOptions::OptionsDatabase &database,
			const Glib::RefPtr<Gtk::Builder>& refGlade);
	virtual ~EncoderControl();
	void aktualizeSettings(const bool& isVideoActive, const ConverterOptions::Container& container);
	void disableSettings();
	void saveSettingsState();
	void restoreSettingsState();
	sigc::signal<void>& signalUserInput();
	bool checkSettingsComplete(std::string& message);
	void setActiveProfile(const Profile::Profile& activeProfile);
	Converter::ConvertSettingsList getConvertArguments() const;
	void getNewProfile(Profile::Profile& newProfile);
private:
	void videoFormatChanged();
	void videoEncoderChanged();
	void videoBitrateChanged();
	void videoFFpresetChanged();

	void setFormatsFromContainer(const ConverterOptions::Container& container);
	void aktualizeEncoder();
	void aktualizeBitrate();
	void aktualizeFFpreset(const std::string name = "");

	void sendUserInputSignal();
	void initFileChooserDialog(Gtk::FileChooserDialog &fileChooserDialog);

	sigc::signal<void> userEvent;
	bool isEnableSignals;
	bool isUserInput;
	ConverterOptions::OptionsDatabase &database;

	ComboBoxExt<ConverterOptions::Format> videoFormat;
	ComboBoxExt<ConverterOptions::Encoder> videoEncoder;
	ComboBoxExt<ConverterOptions::Bitrate> videoBitrate;
	ComboBoxExt<ConverterOptions::FFpreset> videoFFpreset;
	Gtk::FileChooserDialog ffpresetChooser;
	BitrateDialog bitrateDialog;

	ConverterOptions::Bitrate lastSetBitrate;
};

}
} /* namespace Gui */
#endif /* ENCODERCONTROL_H_ */
