/*
 * general.cpp
 *
 *  Created on: 5.9.2012
 *      Author: martin
 */

#include "general.h"
#include <gtkmm/stock.h>
namespace Gui {
namespace Settings {

General::General(const Glib::RefPtr<Gtk::Builder>& refGlade) :
		fileSelector("Please choose a binary file", Gtk::FILE_CHOOSER_ACTION_OPEN),
		dirSelector("Please choose a destination", Gtk::FILE_CHOOSER_ACTION_SELECT_FOLDER)	{

	fileSelector.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
	fileSelector.add_button(Gtk::Stock::OK, Gtk::RESPONSE_OK);
	dirSelector.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
	dirSelector.add_button(Gtk::Stock::OK, Gtk::RESPONSE_OK);

	refGlade->get_widget("binFilePathEntry",binFilePathEntry);
	refGlade->get_widget("binFilePathButton",binFilePathButton);
	refGlade->get_widget("destFilePathEntry",destFilePathEntry);
	refGlade->get_widget("destFilePathButton",destFilePathButton);

	binFilePathButton->signal_clicked().connect(sigc::mem_fun(*this, &General::binFilePathClicked));
	destFilePathButton->signal_clicked().connect(sigc::mem_fun(*this, &General::desFilePathClicked));
}

General::~General() {}

void General::initGraphicElements(UserPreferences* preferences){
	binFilePathEntry->set_text(preferences->getExtConverterPath().getPath());
	destFilePathEntry->set_text(preferences->getConvertDestinationPath().getPath());
}

void General::aktualizeGlobalSettings(UserPreferences* preferences){
	preferences->setExtConverterPath(Path(binFilePathEntry->get_text()));
	preferences->setConvertDestinationPath(Path(destFilePathEntry->get_text()));
}
void General::binFilePathClicked(){
	int res = fileSelector.run();
	fileSelector.hide();
	if(res == Gtk::RESPONSE_OK){
		binFilePathEntry->set_text(fileSelector.get_file()->get_path());
	}
}
void General::desFilePathClicked(){
	int res = dirSelector.run();
	dirSelector.hide();
	if(res == Gtk::RESPONSE_OK){
		destFilePathEntry->set_text(dirSelector.get_file()->get_path());
	}
}
} /* namespace Settings */
} /* namespace Gui */
