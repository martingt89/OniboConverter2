/*
 * onibowindow.h
 *
 *  Created on: 5.7.2012
 *      Author: martint
 */

#ifndef ONIBOWINDOW_H_
#define ONIBOWINDOW_H_

#include <gtkmm/window.h>
#include <gtkmm/builder.h>

#include "containercombobox.h"
#include "../AVBox/avbox.h"
#include "../AVBox/supportedencoders.h"
#include "../AVBox/formattoencoders.h"
#include "../AVBox/guisettings.h"

namespace GUI {

class OniboWindow : public Gtk::Window{
public:
	OniboWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);
	virtual ~OniboWindow();

private:
	const Glib::RefPtr<Gtk::Builder>& refGlade;
	ContainerComboBox *container;

	AVBox::SupportedEncoders suportedEncoders;
	AVBox::AVBox audioVideoData;
	AVBox::GuiSettings guiData;
	AVBox::FormatToEncoders convert;
};

} /* namespace GUI */
#endif /* ONIBOWINDOW_H_ */
