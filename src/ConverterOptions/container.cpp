/*
 * container.cpp
 *
 *  Created on: 24.7.2012
 *      Author: martint
 */

#include "container.h"

namespace ConverterOptions {

Container::Container(){
	name = "";
	containerType = Container::CONTAINER_TYPE_AUDIO_VIDEO;
	formats = Formats();
}
Container::Container(std::string containerName, ContainerType containerType, Formats formats) {
	this->name = containerName;
	this->containerType = containerType;
	this->formats = formats;
}

std::string Container::getName() const{
	return name;
}
Formats Container::getFormats() const{
	return formats;
}
Container::ContainerType Container::getContainerType() const{
	return containerType;
}

void Containers::addContainer(const Container& container){
	containers.set(container.getName(), container);
}
std::list<Container> Containers::getContainers() const{
	return containers.getListOfValues();
}
Container Containers::getContainerByName(std::string containerName) const{	//todo container not found
	return containers.get(containerName);
}

} /* namespace ConverterOptions */
