/* ---------------------------------------------------------------------------
** Author: Martin Geier
** encodercontrolv.h is part of OniboConverter2.
**
** OniboConverter2 is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program.  If not, see <http://www.gnu.org/licenses/>.
** -------------------------------------------------------------------------*/

#ifndef ENCODERCONTROL_H_
#define ENCODERCONTROL_H_

#include <sigc++/signal.h>
#include <gtkmm/builder.h>
#include <gtkmm/filechooserdialog.h>
#include "resolutiondialog.h"
#include "bitratedialog.h"
#include "../WidgetAdapter/comboboxext.h"
#include "../../Profile/profile.h"
namespace Gui {
namespace Video {

class EncoderControl {
public:
	EncoderControl(MediaElement::ElementsDB& elementsDB,
			const Glib::RefPtr<Gtk::Builder>& refGlade);
	virtual ~EncoderControl();
	void aktualizeSettings(const bool& isVideoActive, const MediaElement::Container& container);
	void disableSettings();
	void saveSettingsState();
	void restoreSettingsState();
	sigc::signal<void>& signalUserInput();
	bool checkSettingsComplete(std::string& message);
	void setActiveProfile(const Profile::Profile& activeProfile);
	//Converter::ConvertSettingsList getConvertArguments() const;
	void getNewProfile(Profile::Profile& newProfile);
private:
	void videoFormatChanged();
	void videoEncoderChanged();
	void videoBitrateChanged();
	void videoFFpresetChanged();

	void setFormatsFromContainer(const MediaElement::Container& container);
	void aktualizeEncoder();
	void aktualizeBitrate();
	void aktualizeFFpreset(const std::string name = "");

	void sendUserInputSignal();
	void initFileChooserDialog(Gtk::FileChooserDialog &fileChooserDialog);

	sigc::signal<void> userEvent;
	bool isEnableSignals;
	bool isUserInput;
	MediaElement::ElementsDB& elementsDB;

	ComboBoxExt<MediaElement::Format> videoFormat;
	ComboBoxExt<MediaElement::Encoder> videoEncoder;
	ComboBoxExt<MediaElement::Bitrate> videoBitrate;
	ComboBoxExt<MediaElement::FFpreset> videoFFpreset;
	Gtk::FileChooserDialog ffpresetChooser;
	BitrateDialog bitrateDialog;

	MediaElement::Bitrate lastSetBitrate;
};

}
} /* namespace Gui */
#endif /* ENCODERCONTROL_H_ */
