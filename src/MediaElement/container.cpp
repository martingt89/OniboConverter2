/*
 * container.cpp
 *
 *  Created on: 24.7.2012
 *      Author: martint
 */

#include "container.h"
#include "../helper.h"

namespace MediaElement {

Container::Container(){
	name = "";
	containerType = Container::CONTAINER_TYPE_AUDIO_VIDEO;
	formats = Formats();
}
//Container::Container(std::string containerName, ContainerType containerType, Formats formats) {
//	this->name = containerName;
//	this->containerType = containerType;
//	this->formats = formats;
//}
Container::Container(std::string containerName, ContainerType containerType) {
	this->name = containerName;
	this->containerType = containerType;
}

std::string Container::getName() const{
	return name;
}
std::string Container::readableForm() const{
	return name;
}
//Formats Container::getFormats() const{
//	return formats;
//}
Container::ContainerType Container::getContainerType() const{
	return containerType;
}
bool Container::operator<(const Container& second) const{
	return this->name < second.name;
}
bool Container::operator==(const Container& second) const{
	return this->name == second.name;
}
//Converter::ConvertSettingsList Container::getConvertArguments() const{
//	return Converter::ConvertSettingsList();
//}
//==========================================================================
void Containers::addContainer(const Container& container){
	containers.set(container.getName(), container);
}
std::list<Container> Containers::getContainers() const{
	return containers.getListOfValues();
}
Container Containers::getContainerByName(const std::string& containerName) const{
	bool isExist = false;
	Container container = containers.get(containerName, isExist);
	assert(isExist, "Container name doesn't exist: "+containerName);
	return container;
}
bool Containers::getContainerByName(const std::string& containerName, Container& container) const{
	bool isExist = false;
	container = containers.get(containerName, isExist);
	return isExist;
}
} /* namespace MediaElement */
