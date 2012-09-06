/*
 * threading.cpp
 *
 *  Created on: 5.9.2012
 *      Author: martin
 */

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
