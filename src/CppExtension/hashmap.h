/*
 * hashmap.h
 *
 *  Created on: 27.7.2012
 *      Author: martint
 */

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
private:
	std::map<Key, std::list<Value> > multiMap;
};

}


#endif /* HASHMAP_H_ */
