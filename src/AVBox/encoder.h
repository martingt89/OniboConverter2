/*
 * encoder.h
 *
 *  Created on: 28.6.2012
 *      Author: martint
 */

#ifndef ENCODER_H_
#define ENCODER_H_

#include <string>

namespace AVBox {

class Encoder {
public:
	Encoder(const std::string& encoder, const std::string& description);
	virtual ~Encoder();
	operator std::string() const{
		return encoder+"->"+description;
	}
private:
	std::string encoder;
	std::string description;
};

} /* namespace AVBox */
#endif /* ENCODER_H_ */
