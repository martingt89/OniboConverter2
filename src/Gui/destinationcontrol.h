/*
 * destinationcontrol.h
 *
 *  Created on: 17.8.2012
 *      Author: martint
 */

#ifndef DESTINATIONCONTROL_H_
#define DESTINATIONCONTROL_H_

#include <gtkmm/builder.h>
#include <gtkmm/entry.h>
#include <gtkmm/button.h>
#include <gtkmm/filechooserdialog.h>
#include "../CppExtension/path.h"

namespace Gui {

class DestinationControl {
public:
	DestinationControl(const Glib::RefPtr<Gtk::Builder>& refGlade);
	virtual ~DestinationControl();
	Path getDestinationPath() const;
private:
	void searchForFolderClicked();
	Gtk::Entry* outputFolder;
	Gtk::Button* searchForFolder;
	Gtk::FileChooserDialog folderChooser;
};

} /* namespace Gui */
#endif /* DESTINATIONCONTROL_H_ */
