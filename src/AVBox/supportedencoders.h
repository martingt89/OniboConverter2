/*
 * supportedencoders.h
 *
 *  Created on: 6.7.2012
 *      Author: martint
 */

#ifndef SUPPORTEDENCODERS_H_
#define SUPPORTEDENCODERS_H_

#include "encoder.h"
#include <map>
#include <string>

namespace AVBox {

class SupportedEncoders {
public:
	enum EncoderType{
		VIDEO, AUDIO, SUBTITLE
	};
	struct EncoderFFData{
			std::string encoder;
			std::string description;
			EncoderType type;
		};
	SupportedEncoders();
	virtual ~SupportedEncoders();
	bool isSuported(const AVBox::Encoder& name, std::string& description) const;	//todo struct
	void addEncoder(const EncoderFFData& encoder);
private:
	std::map<std::string, EncoderFFData> suportedEndcoders;
};

} /* namespace AVBox */
#endif /* SUPPORTEDENCODERS_H_ */
