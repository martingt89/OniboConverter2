/*
 * encodercontrol.h
 *
 *  Created on: 11.8.2012
 *      Author: martint
 */

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
