/*
 * channel.h
 *
 *  Created on: 11.8.2012
 *      Author: martint
 */

#ifndef CHANNEL_H_
#define CHANNEL_H_

#include <list>
#include <string>

namespace ConverterOptions {

class Channel {
public:
	Channel();
	Channel(const std::string& name, const int& value);
	virtual ~Channel();
	int getValue() const;
	operator std::string() const;

private:
	std::string name;
	int value;
};

typedef std::list<Channel> Channels;

} /* namespace ConverterOptions */
#endif /* CHANNEL_H_ */