/*
 * encoder.h
 *
 *  Created on: 28.6.2012
 *      Author: martint
 */

#ifndef ENCODER_H_
#define ENCODER_H_

#include <string>
#include <map>

namespace AVBox {

class Encoder {
public:
	enum Type{
		VIDEO, AUDIO, SUBTITLES, UNKNOWN
	};
	Encoder(const std::string& encoder, const std::string& description, const Type& type);
	Encoder();
	virtual ~Encoder();


	operator std::string() const{
		return encoder+"->"+description;
	}
	void addOptions(std::string name, std::string value);
	std::string getName() const;
	std::string getDescription() const;
	std::map<std::string, std::string> getOptions() const;
	bool getOptions(const std::string& name, std::string& returnValue) const;
private:
	std::string encoder;
	std::string description;
	Type type;
	std::map<std::string, std::string> options;
};

} /* namespace AVBox */
#endif /* ENCODER_H_ */
