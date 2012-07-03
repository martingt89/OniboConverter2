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
#include "encoder.h"

namespace AVBox {

class FormatToEncoders {
public:
	FormatToEncoders();
	virtual ~FormatToEncoders();
	void addFormatEncoder(const std::string& format, const std::string& encoder, std::string ffprefix);
	std::list<Encoder> getEncoders(const std::string& format) const;
private:
	std::map<std::string, std::list<Encoder> > convertTable;
};

} /* namespace AVBox */

#endif /* FORMATTOENCODERS_H_ */
