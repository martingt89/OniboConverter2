/* ---------------------------------------------------------------------------
** Author: Martin Geier
** importexport.cpp is part of OniboConverter2.
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

#include "importexport.h"
#include <gtkmm/stock.h>
#include "../systemsettings.h"
#include "../Xml/profilegenerator.h"
#include "../Profile/configuration.h"

namespace Gui {

ImportExport::ImportExport(const Glib::RefPtr<Gtk::Builder>& refGlade, MediaElement::ElementsDB& elementsDB) :
		elementsDB(elementsDB), fileSaveDialog("Select output file", Gtk::FILE_CHOOSER_ACTION_SAVE),
		fileLoadDialog("Select profile files", Gtk::FILE_CHOOSER_ACTION_OPEN),
		avcontrol (0), profiles(0){
	refGlade->get_widget("importItem", importProfile);
	refGlade->get_widget("exportItem", exportProfile);
	fileLoadDialog.set_select_multiple(true);
	fileLoadDialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
	fileLoadDialog.add_button(Gtk::Stock::OK, Gtk::RESPONSE_OK);

	fileSaveDialog.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
	fileSaveDialog.add_button(Gtk::Stock::OK, Gtk::RESPONSE_OK);

	importProfile->signal_activate().connect(sigc::mem_fun(*this, &ImportExport::importProfileClicked));
	exportProfile->signal_activate().connect(sigc::mem_fun(*this, &ImportExport::exportProfileClicked));
}

ImportExport::~ImportExport() {}

void ImportExport::setAVControl(AVControl* avcontrol){
	this->avcontrol = avcontrol;
}
void ImportExport::setProfiles(Profile::Profiles* profiles){
	this->profiles = profiles;
}
void ImportExport::importProfileClicked(){
	assert(profiles != 0, toS(__FILE__) + toS(__LINE__) + toS("profiles != 0"));
	int res = fileLoadDialog.run();
	fileLoadDialog.hide();
	if(res == Gtk::RESPONSE_OK && profiles != 0){
		std::vector<std::string> files = fileLoadDialog.get_filenames();
		Xml::ProfileLoader loader;
		for (std::string file : files) {
			Path path(file);
			Profile::Profile prof;
			profiles->loadFromFile(path, prof);
			Profile::Configuration conf(prof, elementsDB);
			Path output = SystemSettings::getInstance()->getUserProfilesPath();
			Xml::ProfileGenerator generator(output);
			generator.generateFile(conf);
		}
		avcontrol->rescanProfiles();
	}
}

void ImportExport::exportProfileClicked(){
	if(avcontrol != 0){
		int res = fileSaveDialog.run();
		fileSaveDialog.hide();
		if(res == Gtk::RESPONSE_OK){
			Glib::RefPtr<Gio::File> file = fileSaveDialog.get_file();
			std::string path = file->get_path();
			std::string name = path;
			std::string::size_type pos = path.find_last_of('/');
			if(pos != std::string::npos){
				name = path.substr(pos+1);
				path = path.substr(0, pos);
			}
			Profile::Profile profile = avcontrol->getTmpProfile(name);
			Path pp(path);
			Xml::ProfileGenerator generator(pp);
			Profile::Configuration conf(profile, elementsDB);

			generator.generateFile(conf, name);
		}
	}
}
} /* namespace Gui */
