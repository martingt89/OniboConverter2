/*
 * xmlprofiletable.h
 *
 *  Created on: 24.8.2012
 *      Author: martint
 */

#ifndef XMLPROFILETABLE_H_
#define XMLPROFILETABLE_H_

#include <list>
#include <string>
#include <initializer_list>
#include "../Profile/profile.h"
#include "../CppExtension/hashmap.h"
namespace Xml {

class XmlProfileTable {
public:
	XmlProfileTable();
	virtual ~XmlProfileTable();
	Profile::Profile::Options getOptionsFromList(const std::list<std::string>& list);
	std::list<std::string> getListFromOptions(const Profile::Profile::Options& options);
private:
	void add(const std::list<std::string>& list, const Profile::Profile::Options& options);
	std::list<std::string> toList(const std::initializer_list<std::string>& path);
	CppExtension::HashMap<Profile::Profile::Options, std::list<std::string> > optionsToList;
	CppExtension::HashMap<std::list<std::string>, Profile::Profile::Options> listToOptions;
};

} /* namespace Xml */
#endif /* XMLPROFILETABLE_H_ */
