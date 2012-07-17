/*
 * avbox.cpp
 *
 *  Created on: 30.6.2012
 *      Author: martint
 */

#include "avbox.h"
#include "../FFTools/encodersparser.h"
#include "../XML/formatsparser.h"
#include "../XML/containersparser.h"

namespace AVBox {

AVBox::AVBox() {

	FFTools::EncodersParser encodersLoader;

	XML::FormatsParser formatsLoader(encodersLoader.getEncoders());

	XML::ContainersParser containersLoader(formatsLoader.getFormats());

	containers = containersLoader.getContainersWithNames();

}

AVBox::~AVBox() {}

Container AVBox::getContainerByName(const std::string& name) const{	//todo declare excetion
	std::map<std::string, Container>::const_iterator position;
	position = containers.find(name);
	if(position == containers.end()){
		//todo throw excetion
	}
	return position->second;
}

std::list<Container> AVBox::getContainers() const{
	std::map<std::string, Container>::const_iterator it;
	std::list<Container> list;
	for(it = containers.begin(); it != containers.end(); ++it){
		list.push_back(it->second);
	}
	return list;
}

} /* namespace AVBox */
