/*
 * avbox.h
 *
 *  Created on: 30.6.2012
 *      Author: martint
 */

#ifndef AVBOX_H_
#define AVBOX_H_

#include <string>
#include <map>
#include "container.h"

namespace AVBox {

class AVBox {
public:
	AVBox();
	virtual ~AVBox();
	std::list<Container> getContainers() const;
	Container getContainerByName(const std::string& name) const;
private:
	std::map<std::string, Container> containers;
};

} /* namespace AVBox */
#endif /* AVBOX_H_ */
