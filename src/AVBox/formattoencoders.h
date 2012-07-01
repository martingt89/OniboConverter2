/*
 * formattoencoders.h
 *
 *  Created on: 30.6.2012
 *      Author: martint
 */

#ifndef FORMATTOENCODERS_H_
#define FORMATTOENCODERS_H_

#include <string>
#include <map>
#include <list>

namespace AVBox {

class FormatToEncoders {
public:
	FormatToEncoders();
	virtual ~FormatToEncoders();
	void addFormatEncoder(const std::string& format, const std::string& encoder);
	std::list<std::string> getEncoders(const std::string& format) const;
private:
	std::map<std::string, std::list<std::string> > convertTable;
};

} /* namespace AVBox */

#endif /* FORMATTOENCODERS_H_ */
