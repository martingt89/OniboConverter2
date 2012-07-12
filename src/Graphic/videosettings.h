/*
 * videosettings.h
 *
 *  Created on: 5.7.2012
 *      Author: martint
 */

#ifndef VIDEOSETTINGS_H_
#define VIDEOSETTINGS_H_

#include <gtkmm/builder.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/filechooserdialog.h>
#include "../AVBox/avbox.h"
#include "../AVBox/guisettings.h"
#include "encodersdialog.h"
#include "resolutiondialog.h"
#include "../FFTools/ffpresets.h"
#include "Widgets/comboboxtextwraper.h"

namespace GUI {

class VideoSettings {
public:
	VideoSettings(const Glib::RefPtr<Gtk::Builder>& refGlade);
	virtual ~VideoSettings();
	void setActualContainer(const std::string& container);

	void setNeedsData(AVBox::SupportedEncoders *suportedEncoders,
						AVBox::AVBox *audioVideoData,
						AVBox::GuiSettings *guiData,
						AVBox::FormatToEncoders *convert);
private:
	FFTools::FFpresets ffpresets;
	std::string activeContainer;
	const Glib::RefPtr<Gtk::Builder>& refGlade;
	std::pair<int, int> mainResolution;
	std::string activePrefix;
	//
	AVBox::SupportedEncoders *suportedEncoders;
	AVBox::AVBox *audioVideoData;
	AVBox::GuiSettings *guiData;
	AVBox::FormatToEncoders *convert;
	//
	Gtk::ComboBoxText *vMode;
	Gtk::ComboBoxText *vBitrate;
	Gtk::ComboBoxText *vFramerate;
	ComboBoxTextWraper<AVBox::Encoder> vEncoder;
	ComboBoxTextWraper<bool> vFormat;
	ComboBoxTextWraper<std::string> vExtra;

	Gtk::Button *vResolution;
	Gtk::Label *vResolutionLabel;
	Gtk::FileChooserDialog fileChooserDialog;
	ResolutionDialog *resolutionDialog;
	EncodersDialog *encodersDialog;

	void initGuiData(AVBox::GuiSettings* guiData);
	std::list<AVBox::Encoder> getAvailableEncoders();
	void enableVMode();
	void setAllInsensitive();
	void rescanVideoMode();
	void enableVideoSettings();
	void rescanVideoFormat();
	void rescanVideoEncoder();
	void manageVideoResolution();
	void manageVideoExtra();
	void initFileChooserDialog(Gtk::FileChooserDialog &fileChooserDialog);
};

} /* namespace GUI */
#endif /* VIDEOSETTINGS_H_ */
