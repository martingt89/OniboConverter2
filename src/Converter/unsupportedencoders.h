/*
 * unsupportedencoders.h
 *
 *  Created on: 11.9.2012
 *      Author: martin
 */

#ifndef UNSUPPORTEDENCODERS_H_
#define UNSUPPORTEDENCODERS_H_

#include <string>
#include <list>
namespace Converter {

class UnsupportedEncoders {
public:
	enum PriorityLevel{
		BEGIN = 1, MEDIUM = 1, HIGHT = 2, END = 3
	};
	void addUnsupportedEncoder(const std::string &name, const std::string &description, PriorityLevel level);
	bool isEmpty();
	std::list<std::pair<std::string, UnsupportedEncoders::PriorityLevel> > getEncoders() const;
private:
	std::list<std::pair<std::string, PriorityLevel> > encoders;
};

} /* namespace Converter */
#endif /* UNSUPPORTEDENCODERS_H_ */
