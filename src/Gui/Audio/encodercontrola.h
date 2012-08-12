/*
 * encodercontrol.h
 *
 *  Created on: 11.8.2012
 *      Author: martint
 */

#ifndef ENCODERCONTROLA_H_
#define ENCODERCONTROLA_H_

#include "../WidgetAdapter/comboboxext.h"
#include "../../ConverterOptions/optionsdatabase.h"
#include <sigc++/signal.h>
#include <gtkmm/builder.h>

namespace Gui {
namespace Audio {
class EncoderControlA {
public:
	EncoderControlA(ConverterOptions::OptionsDatabase &database,
			const Glib::RefPtr<Gtk::Builder>& refGlade);
	virtual ~EncoderControlA();
	void aktualizeSettings(const bool& isAudioActive, const ConverterOptions::Container& container);
	void disableSettings();
	void saveSettingsState();
	void restoreSettingsState();
	sigc::signal<void>& signalUserInput();
	bool checkSettingsComplete(std::string& message);
private:
	void audioFormatChanged();
	void audioEncoderChanged();
	void audioBitrateChanged();

	void setFormatsFromContainer(const ConverterOptions::Container& container);
	void aktualizeEncoder();
	void aktualizeBitrate();
	void sendUserInputSignal();

	ConverterOptions::OptionsDatabase &database;
	ComboBoxExt<ConverterOptions::Format> audioFormat;
	ComboBoxExt<ConverterOptions::Encoder> audioEncoder;
	ComboBoxExt<ConverterOptions::Bitrate> audioBitrate;

	sigc::signal<void> userEvent;
	bool isEnableSignals;
	bool isUserInput;
};

}
} /* namespace Gui */
#endif /* ENCODERCONTROLA_H_ */
