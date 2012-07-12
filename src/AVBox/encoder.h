/*
 * encoder.h
 *
 *  Created on: 28.6.2012
 *      Author: martint
 */

#ifndef ENCODER_H_
#define ENCODER_H_

#include <string>
//#include <list>
#include <map>

namespace AVBox {

class Encoder {
public:
	Encoder(const std::string& encoder, const std::string& description);
	Encoder(const Encoder& old, const std::string& description);
	Encoder(const std::string& encoder);
	Encoder();
	virtual ~Encoder();
	operator std::string() const{
		return encoder+"->"+description;
	}
	void addOptions(std::string name, std::string value);
	std::string getEncoder() const;
	std::string getDescription() const;
	std::map<std::string, std::string> getOptions() const;
private:
	std::string encoder;
	std::string description;
	std::map<std::string, std::string> options;
};

} /* namespace AVBox */
#endif /* ENCODER_H_ */
