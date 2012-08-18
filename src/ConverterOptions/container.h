/*
 * container.h
 *
 *  Created on: 24.7.2012
 *      Author: martint
 */

#ifndef CONTAINER_H_
#define CONTAINER_H_

#include <string>
#include "format.h"
#include "../CppExtension/hashmap.h"


namespace ConverterOptions {

class Container {
public:
	enum ContainerType{
		CONTAINER_TYPE_AUDIO,
		CONTAINER_TYPE_AUDIO_VIDEO
	};
public:
	Container();
	Container(std::string containerName, ContainerType containerType, Formats formats);
	std::string getName() const;
	Formats getFormats() const;
	ContainerType getContainerType() const;
	Converter::Arguments getConvertArguments() const;
private:
	std::string name;
	ContainerType containerType;
	Formats formats;
};

class Containers {
public:
	void addContainer(const Container& container);
	std::list<Container> getContainers() const;
	Container getContainerByName(std::string containerName) const;
private:
	//std::map<std::string, Container> containers;
	CppExtension::HashMap<std::string, Container> containers;
};

} /* namespace ConverterOptions */
#endif /* CONTAINER_H_ */
