/* ---------------------------------------------------------------------------
** Author: Martin Geier
** regextools.h is part of RegexTools.
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

#ifndef REGEXTOOLS_H_
#define REGEXTOOLS_H_

#include <regex.h>
#include <string>
#include <exception>

namespace RegexTools{

class RegexException : std::exception{
public:
	RegexException(const std::string& message);
	virtual ~RegexException() throw ();
	virtual const char* what() const throw ();
private:
	std::string message;
};

class Matcher{
public:
	Matcher (const std::string& text, const regex_t& regex);	//Don't use constructor manualy -> call RegexTools::getMatcher
	~Matcher();
	bool find();
	std::string getGroup(const unsigned int& number) const;
private:
	regex_t regex;
	regmatch_t *groups;
	std::string text;
	unsigned int numberOfGroups;
	unsigned long int lastPosition;
	unsigned long int backPosition;
};

class Regex {
public:
	Regex(const std::string& expression, const bool& caseIgnor = false)
			throw (RegexException);
	virtual ~Regex();
	bool search(const std::string& text, std::string::size_type &start,
			std::string::size_type &end) const throw (RegexException);
	bool search(const std::string& text) const throw (RegexException);
	Matcher getMatcher(const std::string& text) const;
private:
	regex_t regex;
	std::string text;

	void addIgnorCaseFlag(int& flags);
	void addExtendedRegexFlag(int& flags);
};

}

#endif /* REGEXTOOLS_H_ */
