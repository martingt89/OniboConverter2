/*
 * threading.h
 *
 *  Created on: 5.9.2012
 *      Author: martin
 */

#ifndef THREADING_H_
#define THREADING_H_

#include "subsettings.h"
#include <gtkmm/builder.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/checkbutton.h>
#include <list>

namespace Gui {
namespace Settings {

class Threading : public SubSetting{
public:
	Threading(const Glib::RefPtr<Gtk::Builder>& refGlade);
	virtual ~Threading();
	virtual void initGraphicElements(UserPreferences* preferences);
	virtual void aktualizeGlobalSettings(UserPreferences* preferences);
private:
	void autoNumberOfThreadsClicked();
	Gtk::SpinButton* numberOfThreads;
	Gtk::CheckButton* autoNumberOfThreads;
	Gtk::CheckButton* enableMultForEncoders;
};

} /* namespace Settings */
} /* namespace Gui */
#endif /* THREADING_H_ */
