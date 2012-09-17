/* ---------------------------------------------------------------------------
** Author: Martin Geier
** container.cpp is part of OniboConverter2.
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
