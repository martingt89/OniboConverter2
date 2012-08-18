/*
 * argument.h
 *
 *  Created on: 18.8.2012
 *      Author: martint
 */

#ifndef ARGUMENT_H_
#define ARGUMENT_H_

#include <list>
#include <string>

namespace Converter {

class Argument {
public:
	Argument(std::string command);
	void addValue(std::string value);
	virtual ~Argument();
//private: todo
	std::string command;
	std::list<std::string> valuesList;
};

class Arguments{
public:
	Arguments();
	Arguments(const Arguments& arguments);
	void push_back(const Argument& argument);
	void push_back(const Arguments& argument);
	void print();
private:
	std::list<Argument> arguments;
};


} /* namespace Converter */
#endif /* ARGUMENT_H_ */
