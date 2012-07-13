/*
 * simplememorymanager.h
 *
 *  Created on: 13.7.2012
 *      Author: martint
 */

#ifndef SIMPLEMEMORYMANAGER_H_
#define SIMPLEMEMORYMANAGER_H_

#include <list>

template<class T>
class SimpleMemoryManager{
public:
	void addObject(T* object){
		objects.push_back(object);
	}

	void free(){
		typename std::list<T*>::iterator it;
		for(it = objects.begin(); it != objects.end(); ++it){
			if(*it != 0)
				delete *it;
		}
		objects.clear();
	}

	~SimpleMemoryManager(){
		free();
	}
private:
	std::list<T*> objects;
};


#endif /* SIMPLEMEMORYMANAGER_H_ */
