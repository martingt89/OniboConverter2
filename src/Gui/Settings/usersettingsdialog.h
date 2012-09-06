/*
 * usersettingsdialog.h
 *
 *  Created on: 5.9.2012
 *      Author: martin
 */

#ifndef USERSETTINGSDIALOG_H_
#define USERSETTINGSDIALOG_H_

#include <list>
#include <gtkmm/builder.h>
#include <gtkmm/dialog.h>
#include "subsettings.h"

namespace Gui {
namespace Settings {

class UserSettingsDialog {
public:
	UserSettingsDialog(const Glib::RefPtr<Gtk::Builder>& refGlade);
	virtual ~UserSettingsDialog();
	void start();
private:
	void aktualizeGlobalSettings();
	void initGraphicElements();
	Gtk::Dialog* userSettingsDialog;
	std::list<SubSetting*> subSettings;
};

} /* namespace Settings */
} /* namespace Gui */
#endif /* USERSETTINGSDIALOG_H_ */
