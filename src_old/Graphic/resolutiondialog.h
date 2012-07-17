/*
 * resolutiondialog.h
 *
 *  Created on: 7.7.2012
 *      Author: martint
 */

#ifndef RESOLUTIONDIALOG_H_
#define RESOLUTIONDIALOG_H_

#include <gtkmm/dialog.h>
#include <gtkmm/builder.h>
#include <gtkmm/togglebutton.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/entry.h>
#include "../AVBox/guisettings.h"
#include "Widgets/comboboxtextwraper.h"

class ResolutionDialog : public Gtk::Dialog {
public:
	ResolutionDialog(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);
	virtual ~ResolutionDialog();
	void setGuiSettings(AVBox::GuiSettings *settings);
	bool start(bool &copy, int &xRes, int &yRes);
	void setSensitivity(bool sensitiv);
private:
	void setCopyButtonLabel();
	void changeCopyMode();
	void rescanApectRatio();
	void rescanResolution();
	void setResolution(int x, int y);
	void getRatioNumbers(const std::string& ratio, int &x, int &y);
	void recalculeResolutionXtoY();
	void recalculeResolutionYtoX();
	bool disableEntryInterupt;
	Gtk::ToggleButton *copyMode;
	ComboBoxTextWraper<bool> aspectRatio;

	Gtk::ComboBoxText *resolutions;
	Gtk::Entry *editableResolutionX;
	Gtk::Entry *editableResolutionY;
	Gtk::Label *errorMessage;

	AVBox::GuiSettings *settings;
	std::vector<AVBox::GuiSettings::ResolutionStruct> resolutionCeeper;
};

#endif /* RESOLUTIONDIALOG_H_ */
