/* ---------------------------------------------------------------------------
** Author: Martin Geier
** encodercontrola.h is part of OniboConverter2.
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

#ifndef ENCODERCONTROLA_H_
#define ENCODERCONTROLA_H_

#include <sigc++/signal.h>
#include <gtkmm/builder.h>
#include "../WidgetAdapter/comboboxext.h"
#include "../../Profile/profile.h"
#include "../../MediaElement/elementsdb.h"

namespace Gui {
namespace Audio {
class EncoderControlA {
public:
	EncoderControlA(MediaElement::ElementsDB& elementsDB,
			const Glib::RefPtr<Gtk::Builder>& refGlade);
	virtual ~EncoderControlA();
	void aktualizeSettings(const bool& isAudioActive, const MediaElement::Container& container);
	void disableSettings();
	void saveSettingsState();
	void restoreSettingsState();
	sigc::signal<void>& signalUserInput();
	bool checkSettingsComplete(std::string& message);
	void setActiveProfile(const Profile::Profile& activeProfile);
	void getNewProfile(Profile::Profile& newProfile);
private:
	void audioFormatChanged();
	void audioEncoderChanged();
	void audioBitrateChanged();

	void setFormatsFromContainer(const MediaElement::Container& container);
	void aktualizeEncoder();
	void aktualizeBitrate();
	void sendUserInputSignal();

	MediaElement::ElementsDB &elementsDB;
	ComboBoxExt<MediaElement::Format> audioFormat;
	ComboBoxExt<MediaElement::Encoder> audioEncoder;
	ComboBoxExt<MediaElement::AudioGrade> audioGradeChooser;

	sigc::signal<void> userEvent;
	bool isEnableSignals;
	bool isUserInput;
};

}
} /* namespace Gui */
#endif /* ENCODERCONTROLA_H_ */
