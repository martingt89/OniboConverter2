/* ---------------------------------------------------------------------------
** Author: Martin Geier
** hashmap.h is part of OniboConverter2.
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

#ifndef HASHMAP_H_
#define HASHMAP_H_

#include <map>
#include <list>

namespace CppExtension{

template<class Key, class Value>

class HashMap{
public:
	void set(const Key& key, const Value& value){
		map[key] = value;
	}
	void operator=(const std::map<Key, Value> _map){
		map = _map;
	}
	Value get(const Key& key, bool& isExist) const{
		typename std::map<Key, Value>::const_iterator keyIter = map.find(key);
		if(keyIter == map.end()){
			isExist = false;
			return Value();
		}
		isExist = true;
		return keyIter->second;
	}
	Value get(const Key& key) const{
		typename std::map<Key, Value>::const_iterator keyIter = map.find(key);
		if(keyIter == map.end()){
			return Value();
		}
		return keyIter->second;
	}
	bool get(const Key& key, Value& value) const{
		typename std::map<Key, Value>::const_iterator keyIter = map.find(key);
		if(keyIter == map.end()){
			return false;
		}
		value = keyIter->second;
		return true;
	}
	bool isExistKey(const Key& key) const{
		return (map.find(key) != map.end());
	}
	std::list<Value> getListOfValues() const{
		std::list<Value> values;
		for(typename std::map<Key, Value>::const_iterator it = map.begin(); it != map.end(); ++it){
			values.push_back(it->second);
		}
		return values;
	}
	bool isEmpty() const{
		return map.size() == 0;
	}
	void remove(const Key& key) {
		map.erase(key);
	}
private:
	std::map<Key, Value> map;
};

template<class Key, class Value>
class MultiHashMap{
public:
	void set(const Key& key, const Value& value){
		multiMap[key].push_back(value);
	}
	std::list<Value> get(const Key& key, bool& isExist) const{
		typename std::map<Key, std::list<Value> >::const_iterator multiMapIter = multiMap.find(key);
		if(multiMapIter == multiMap.end()){
			isExist = false;
			return std::list<Value>();
		}
		isExist = true;
		return multiMapIter->second;
	}
	std::list<Value> get(const Key& key) const{
			typename std::map<Key, std::list<Value> >::const_iterator multiMapIter = multiMap.find(key);
			if(multiMapIter == multiMap.end()){
				return std::list<Value>();
			}
			return multiMapIter->second;
		}
	bool isExist(const Key& key) const{
		return (multiMap.find(key) != multiMap.end());
	}
	void remove(const Key& key) {
		multiMap.erase(key);
	}
	std::list<Value> getListOfValues() const{
		std::list<Value> values;
		for(typename std::map<Key,  std::list<Value> >::const_iterator it = multiMap.begin(); it != multiMap.end(); ++it){
			auto list = it->second;
			std::copy(list.begin(), list.end(), std::back_inserter(values));
		}
		return values;
	}
	std::list<Key> getListOfKeys() const{
		std::list<Key> keys;
		for(typename std::map<Key,  std::list<Value> >::const_iterator it = multiMap.begin(); it != multiMap.end(); ++it){
			keys.push_back(it->first);
		}
		return keys;
	}
private:
	std::map<Key, std::list<Value> > multiMap;
};

}


#endif /* HASHMAP_H_ */
