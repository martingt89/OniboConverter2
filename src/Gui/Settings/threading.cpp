/* ---------------------------------------------------------------------------
** Author: Martin Geier
** threading.cpp is part of OniboConverter2.
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

#include "threading.h"

namespace Gui {
namespace Settings {

Threading::Threading(const Glib::RefPtr<Gtk::Builder>& refGlade) {
	refGlade->get_widget("numberOfThreads",numberOfThreads);
	refGlade->get_widget("autoNumberOfThreads",autoNumberOfThreads);
	refGlade->get_widget("enableMultForEncoders",enableMultForEncoders);

	autoNumberOfThreads->signal_clicked().connect(sigc::mem_fun(*this, &Threading::autoNumberOfThreadsClicked));
	autoNumberOfThreads->set_active(true);
}

Threading::~Threading() {}

void Threading::aktualizeGlobalSettings(UserPreferences* preferences){
	preferences->setNumberOfCPU(numberOfThreads->get_value_as_int(), autoNumberOfThreads->get_active());
	preferences->setMultithreadingForEncoders(enableMultForEncoders->get_active());
}

void Threading::initGraphicElements(UserPreferences* preferences){
	numberOfThreads->set_value(preferences->getNumerOfCPU());
	autoNumberOfThreads->set_active(preferences->isAutomaticNumberOfCPU());
	enableMultForEncoders->set_active(preferences->isMultithreadinForEncoders());
}

void Threading::autoNumberOfThreadsClicked(){
	if(autoNumberOfThreads->get_active()){
		numberOfThreads->set_sensitive(false);
	}else{
		numberOfThreads->set_sensitive(true);
	}
}

} /* namespace Settings */
} /* namespace Gui */
