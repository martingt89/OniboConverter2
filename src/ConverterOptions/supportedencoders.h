/*
 * supportedencoders.h
 *
 *  Created on: 27.7.2012
 *      Author: martint
 */

#ifndef SUPPORTEDENCODERS_H_
#define SUPPORTEDENCODERS_H_

#include "../CppExtension/hashmap.h"
#include <string>

namespace ConverterOptions {

class SupportedEncoders {
public:
	void addEncoder(const std::string& encoderName, const std::string& description);
	bool isSupported(const std::string& encoderName) const;
	std::string getEncoderDescription(const std::string& encoderName) const;
private:
	CppExtension::HashMap<std::string, std::string> encoderNameToDescr;
};

} /* namespace ConverterOptions */
#endif /* SUPPORTEDENCODERS_H_ */
