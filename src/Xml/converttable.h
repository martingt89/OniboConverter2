/*
 * converttable.h
 *
 *  Created on: 6.9.2012
 *      Author: martin
 */

#ifndef CONVERTTABLE_H_
#define CONVERTTABLE_H_

#include <list>
#include <string>
#include "../CppExtension/hashmap.h"

namespace Xml {

template<class Options>
class ConvertTable {
public:
	ConvertTable(){};
	virtual ~ConvertTable(){};
	bool getOptionsFromList(const std::list<std::string>& list, Options& opt){
		bool exist = false;
		opt = listToOptions.get(list, exist);
		return exist;
	}
	std::list<std::string> getListFromOptions(const Options& options){
		return optionsToList.get(options);
	}

	void add(const std::list<std::string>& list, const Options& options){
		listToOptions.set(list, options);
		optionsToList.set(options, list);
	}

private:
	CppExtension::HashMap<Options, std::list<std::string> > optionsToList;
	CppExtension::HashMap<std::list<std::string>, Options> listToOptions;
};


} /* namespace Xml */
#endif /* CONVERTTABLE_H_ */
