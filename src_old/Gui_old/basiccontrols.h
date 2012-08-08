/*
 * basiccontrols.h
 *
 *  Created on: 29.7.2012
 *      Author: martint
 */

#ifndef BASICCONTROLS_H_
#define BASICCONTROLS_H_

#include "../profil.h"
#include <string>
#include <sigc++/sigc++.h>
#include "../ConverterOptions/container.h"

namespace Gui {

class BasicControls {
public:
	BasicControls(){};
	virtual ~BasicControls(){};
	virtual void setActiveProfile(Profile activeProfile) = 0;
	virtual sigc::signal<void>& signalUserInput() = 0;
	virtual void setActiveContainer(ConverterOptions::Container container) = 0;
};


} /* namespace Gui */
#endif /* BASICCONTROLS_H_ */
