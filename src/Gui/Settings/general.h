/*
 * general.h
 *
 *  Created on: 5.9.2012
 *      Author: martin
 */

#ifndef GENERAL_H_
#define GENERAL_H_

#include "subsettings.h"
#include <gtkmm/builder.h>
#include <gtkmm/entry.h>
#include <gtkmm/button.h>
#include <gtkmm/filechooserdialog.h>
#include <list>

namespace Gui{
namespace Settings {

class General : public SubSetting {
public:
	General(const Glib::RefPtr<Gtk::Builder>& refGlade);
	virtual ~General();
	virtual void initGraphicElements(UserPreferences* preferences);
	virtual void aktualizeGlobalSettings(UserPreferences* preferences);
private:
	void binFilePathClicked();
	void desFilePathClicked();
	Gtk::Entry* binFilePathEntry;
	Gtk::Button* binFilePathButton;
	Gtk::Entry* destFilePathEntry;
	Gtk::Button* destFilePathButton;
	Gtk::FileChooserDialog fileSelector;
	Gtk::FileChooserDialog dirSelector;
};

} /* namespace Settings */
} /* namespace Gui */
#endif /* GENERAL_H_ */
