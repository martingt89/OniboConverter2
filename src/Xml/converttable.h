/* ---------------------------------------------------------------------------
** Author: Martin Geier
** converttable.h is part of OniboConverter2.
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
