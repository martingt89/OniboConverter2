/*
 * argument.cpp
 *
 *  Created on: 18.8.2012
 *      Author: martint
 */

#include "argument.h"
#include <iostream> //todo remove iostream
namespace Converter {

Argument::Argument(std::string command) {
	this->command = command;
}

Argument::~Argument() {}

void Argument::addValue(std::string value){
	valuesList.push_back(value);
}
Arguments::Arguments(){

}
Arguments::Arguments(const Arguments& arguments){
	std::copy(arguments.arguments.begin(), arguments.arguments.end(), std::back_inserter(this->arguments));
}
void Arguments::push_back(const Argument& argument){
	arguments.push_back(argument);
}
void Arguments::push_back(const Arguments& arguments){
	std::copy(arguments.arguments.begin(), arguments.arguments.end(), std::back_inserter(this->arguments));
}
void Arguments::print(){
	for(auto x : arguments){
		std::cout<<" "<<x.command;
		for(auto v : x.valuesList){
			std::cout<<" "<<v;
		}
	}
	std::cout<<std::endl;
}
} /* namespace Converter */
