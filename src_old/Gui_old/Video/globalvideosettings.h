/*
 *
 *
 *  Created on: 29.7.2012
 *      Author: martint
 */

#ifndef GLOBALVIDEOSETTINGS_H_
#define GLOBALVIDEOSETTINGS_H_

#include "../basiccontrols.h"
#include "../comboboxext.h"
#include <sigc++/sigc++.h>
#include <gtkmm/builder.h>
#include <gtkmm/button.h>
#include <gtkmm/window.h>
#include "../../ConverterOptions/optionsdatabase.h"
#include "../settingsdialog.h"
#include "encodersettings.h"
#include "../../CppExtension/path.h"

namespace Gui {

class GlobalVideoSettings: public Gui::BasicControls {
public:
	GlobalVideoSettings(ConverterOptions::OptionsDatabase &database,
			const Glib::RefPtr<Gtk::Builder>& refGlade,
			SettingsDialog& settingsDialog);
	virtual ~GlobalVideoSettings();
	virtual void setActiveProfile(Profile activeProfile);
	virtual sigc::signal<void>& signalUserInput();
	virtual void setActiveContainer(ConverterOptions::Container container);
private:
	void showVideoSettingsClicked();
	void okButtonClicked();
	void cancelButtonClicked();
	void videoModeChanged();
	void videoFormatChanged();
	void videoEncoderChanged();
	void videoBitrateChanged();
	bool isLockSignal;
	//==============================================================
	void saveActualSettings();
	void restorActualSettings();
	void setUnsesitiveVideoDialog();
	bool isVideoModeEditable();
	void setUnsensitiveVideoSettings();
	ConverterOptions::Container getActiveContainer();
	//==============================================================
	void loadComboBoxes(const Glib::RefPtr<Gtk::Builder>& refGlade);
	void initVideoMode(ComboBoxExt<int>& videoMode);
	void initResolution(ComboBoxExt<std::string>& videoResolution, ConverterOptions::OptionsDatabase &database);
	void initFramerate(ComboBoxExt<int>& videoFramerate, ConverterOptions::OptionsDatabase &database);
	sigc::signal<void> userInput;
	ConverterOptions::OptionsDatabase &database;
	EncoderSettings* encoderSettings;

	std::string activeContainerName;

	SettingsDialog& settingsDialog;
	ComboBoxExt<int> videoMode;
	ComboBoxExt<ConverterOptions::Format> videoFormat;
	ComboBoxExt<ConverterOptions::Encoder> videoEncoder;
	ComboBoxExt<int> videoFramerate;
	ComboBoxExt<ConverterOptions::Bitrate> videoBitrate;
	ComboBoxExt<std::string> videoResolution;
	ComboBoxExt<Path> videoFFpreset;
	Gtk::Button* showVideoSettings;
	Gtk::Button* okVideoButton;
	Gtk::Button* cancelVideoButton;
	Gtk::Label* videoErrorMessage;
};

} /* namespace Gui */
#endif /* GLOBALVIDEOSETTINGS_H_ */
