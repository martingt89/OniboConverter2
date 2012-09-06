/*
 * subsettings.h
 *
 *  Created on: 5.9.2012
 *      Author: martin
 */

#ifndef SUBSETTINGS_H_
#define SUBSETTINGS_H_

#include "../../userpreferences.h"

namespace Gui {
namespace Settings {

class SubSetting {
public:
	virtual ~SubSetting(){};
	virtual void initGraphicElements(UserPreferences* preferences) = 0;
	virtual void aktualizeGlobalSettings(UserPreferences* preferences) = 0;
};

} /* namespace Settings */
} /* namespace Gui */


#endif /* SUBSETTINGS_H_ */
