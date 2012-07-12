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
#include "../AVBox/avbox.h"
#include "../AVBox/guisettings.h"
#include "encodersdialog.h"
#include "resolutiondialog.h"
namespace GUI {

class VideoSettings {
public:
	VideoSettings(const Glib::RefPtr<Gtk::Builder>& refGlade);
	virtual ~VideoSettings();
	void reload(const std::string& container);
	void setAllInsensitive();
	void rescanVideoMode();
	void enableVideoSettings();
	void rescanVideoFormat();
	void rescanVideoEncoder();
	void manageVideoResolution();
	void setNeedsData(AVBox::SupportedEncoders *suportedEncoders,
						AVBox::AVBox *audioVideoData,
						AVBox::GuiSettings *guiData,
						AVBox::FormatToEncoders *convert);
private:
	std::string activeContainer;
	const Glib::RefPtr<Gtk::Builder>& refGlade;
	int numberOfEncoderItems;
	std::map<std::string, AVBox::Encoder> setEncoders;
	int vFormatCount;
	std::pair<int, int> mainResolution;
	std::string lastFormat;
	//
	AVBox::SupportedEncoders *suportedEncoders;
	AVBox::AVBox *audioVideoData;
	AVBox::GuiSettings *guiData;
	AVBox::FormatToEncoders *convert;
	//
	Gtk::ComboBoxText *vMode;
	Gtk::ComboBoxText *vBitrate;
	Gtk::ComboBoxText *vFramerate;
	Gtk::ComboBoxText *vEncoder;
	Gtk::ComboBoxText *vFormat;
	Gtk::ComboBoxText *vExtra;
	Gtk::Button *vResolution;
	Gtk::Label *vResolutionLabel;
	ResolutionDialog *resolutionDialog;
	EncodersDialog *encodersDialog;

	void initGuiData(AVBox::GuiSettings* guiData);
	std::list<AVBox::Encoder> getAvailableEncoders();
	void enableVMode();
};

} /* namespace GUI */
#endif /* VIDEOSETTINGS_H_ */
