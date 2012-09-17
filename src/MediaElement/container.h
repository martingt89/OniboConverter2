/* ---------------------------------------------------------------------------
** Author: Martin Geier
** container.h is part of OniboConverter2.
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

#ifndef CONTAINER_H_
#define CONTAINER_H_

#include <string>
#include "format.h"
#include "../CppExtension/hashmap.h"


namespace MediaElement {

class Container {
public:
	enum ContainerType{
		CONTAINER_TYPE_AUDIO,
		CONTAINER_TYPE_AUDIO_VIDEO
	};
public:
	Container();
	//Container(std::string containerName, ContainerType containerType, Formats formats);
	Container(std::string containerName, ContainerType containerType);
	std::string getName() const;
	std::string readableForm() const;
	//Formats getFormats() const;
	ContainerType getContainerType() const;
	//Converter::ConvertSettingsList getConvertArguments() const;
	bool operator<(const Container& second) const;
	bool operator==(const Container& second) const;
private:
	std::string name;
	ContainerType containerType;
	Formats formats;
};

class Containers {
public:
	void addContainer(const Container& container);
	std::list<Container> getContainers() const;
	Container getContainerByName(const std::string& containerName) const;
	bool getContainerByName(const std::string& containerName, Container& container) const;
private:
	//std::map<std::string, Container> containers;
	CppExtension::HashMap<std::string, Container> containers;
};

} /* namespace MediaElement */
#endif /* CONTAINER_H_ */
