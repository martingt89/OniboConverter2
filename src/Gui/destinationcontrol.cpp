/*
 * destinationcontrol.cpp
 *
 *  Created on: 17.8.2012
 *      Author: martint
 */

#include "destinationcontrol.h"
#include <gtkmm/stock.h>
#include <glibmm/miscutils.h>
#include "../userpreferences.h"

namespace Gui {

DestinationControl::DestinationControl(const Glib::RefPtr<Gtk::Builder>& refGlade) :
		folderChooser("Please choose a folder", Gtk::FILE_CHOOSER_ACTION_SELECT_FOLDER){

	refGlade->get_widget("outputFolder", outputFolder);
	refGlade->get_widget("searchFolder", searchForFolder);
	refGlade->get_widget("outputDestMenu", outputDestMenu);

	folderChooser.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
	folderChooser.add_button(Gtk::Stock::OK, Gtk::RESPONSE_OK);

	Path outputDestination = UserPreferences::getInstance()->getConvertDestinationPath();

	outputFolder->set_text(outputDestination.getPath());

	searchForFolder->signal_clicked().connect(	sigc::mem_fun(*this, &DestinationControl::searchForFolderClicked));
	outputDestMenu->signal_activate().connect(	sigc::mem_fun(*this, &DestinationControl::searchForFolderClicked));
}

DestinationControl::~DestinationControl() {
	delete outputFolder;
	delete searchForFolder;
}
Path DestinationControl::getDestinationPath() const{
	return Path(outputFolder->get_text());
}

void DestinationControl::searchForFolderClicked(){
	int res = folderChooser.run();
	folderChooser.hide();
	if(res == Gtk::RESPONSE_OK){
		Glib::RefPtr< Gio::File > file = folderChooser.get_file ();
		outputFolder->set_text(file->get_path());
	}
}

} /* namespace Gui */
