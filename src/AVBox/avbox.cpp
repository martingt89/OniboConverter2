/*
 * avbox.cpp
 *
 *  Created on: 30.6.2012
 *      Author: martint
 */

#include "avbox.h"

namespace AVBox {

AVBox::AVBox() {}

AVBox::~AVBox() {}

void AVBox::addContainer(const Container& container){
	containers[container.getName()] = container;
}

Container AVBox::getContainer(const std::string& name){
	return containers[name];
}

std::list<std::string> AVBox::getContainerList() const{
	std::map<std::string, Container>::const_iterator it;
	std::list<std::string> list;
	for(it = containers.begin(); it != containers.end(); ++it){
		list.push_back(it->first);
	}
	return list;
}

} /* namespace AVBox */
