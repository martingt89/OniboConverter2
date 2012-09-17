/* ---------------------------------------------------------------------------
** Author: Martin Geier
** general.cpp is part of OniboConverter2.
**
** OniboConverter2 is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program.  If not, see <http://www.gnu.org/licenses/>.
** -------------------------------------------------------------------------*/

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
