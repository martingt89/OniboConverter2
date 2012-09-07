/* ---------------------------------------------------------------------------
** Author: Martin Geier
** regextools.cpp is part of RegexTools.
**
** RegexTools is free software: you can redistribute it and/or modify
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

#include "regextools.h"
#include <cstdlib>

namespace RegexTools{

void Regex::addIgnorCaseFlag(int& flags) {
	flags |= REG_ICASE;
}
void Regex::addExtendedRegexFlag(int& flags) {
	flags |= REG_EXTENDED;
}

Regex::Regex(const std::string& expression, const bool& caseIgnore) throw (RegexException){
	int flags = 0;
	if(caseIgnore){
		addIgnorCaseFlag(flags);
	}
	addExtendedRegexFlag(flags);
	if (int st = regcomp(&regex, expression.c_str(), flags|REG_EXTENDED) != 0){
		char buffer[100];
		size_t len = regerror(st, &regex, buffer, 100);
		throw RegexException(std::string("Regcomp error: ")+std::string(buffer, len)+", regex: "+expression);
	}
}

Regex::~Regex() {
	regfree(&regex);
}
bool Regex::search(const std::string& text) const throw (RegexException){
	std::string::size_type x, y;
	try{
		return this->search(text, x, y);
	}catch(RegexException &ex){
		throw ex;
	}
	return false;
}
bool Regex::search(const std::string& text, std::string::size_type &start,
		std::string::size_type &end) const throw (RegexException){
	regmatch_t pmatch[1];
	int error= regexec(&regex, text.c_str(), 1, pmatch, 0);
	if(error){
		if(error == REG_NOMATCH) return false;
		char buffer[100];
		size_t len = regerror(error, &regex, buffer, 100);
		throw RegexException("Regexec error: "+std::string(buffer, len));
	}
	start = pmatch[0].rm_so;
	end = pmatch[0].rm_eo;
	return true;
}
Matcher Regex::getMatcher(const std::string& text) const{
	return Matcher(text, this->regex);
}

Matcher::Matcher (const std::string& text, const regex_t& regex){
	this->text = text;
	this->regex = regex;
	numberOfGroups = regex.re_nsub + 1;
	groups = (regmatch_t*)malloc(sizeof(regmatch_t)*numberOfGroups);
	lastPosition = 0;
	backPosition = 0;
}
Matcher::~Matcher (){
	if(groups)
		free(groups);
}
bool Matcher::find(){

	int status= regexec(&regex, text.c_str()+lastPosition, numberOfGroups, groups, 0);
	if(status == 0){
		backPosition = lastPosition;
		lastPosition = lastPosition + groups[0].rm_so+1;
		return true;
	}
	return false;
}
std::string Matcher::getGroup(const unsigned int& number) const{
	if(number >= numberOfGroups || groups[number].rm_eo == -1 || groups[number].rm_so == -1){
		return "";
	}
	int n = groups[number].rm_eo - groups[number].rm_so;
	return text.substr(backPosition + groups[number].rm_so, n);
}
bool Matcher::getGroup(const unsigned int& number, std::string& groupText) const{
	if(number >= numberOfGroups || groups[number].rm_eo == -1 || groups[number].rm_so == -1){
		return false;
	}

	int n = groups[number].rm_eo - groups[number].rm_so;

	try{
		groupText = text.substr(backPosition + groups[number].rm_so, n);
	}catch(const std::exception& ex){
		//todo log???
		return false;
	}
	return true;
}
RegexException::RegexException(const std::string& message){
	this->message = message;
}
RegexException::~RegexException() throw (){

}
const char* RegexException::what() const throw (){
	return message.c_str();
}

}
