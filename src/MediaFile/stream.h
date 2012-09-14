/*
 * stream.h
 *
 *  Created on: 20.8.2012
 *      Author: martint
 */

#ifndef STREAM_H_
#define STREAM_H_

#include <utility>
#include <string>

namespace MediaFile {

class Stream {
public:
	Stream(int firstNumber, int secondNumebr, std::string name);
	virtual ~Stream();
	std::pair<int, int> getStreamNumber() const;
	std::string getStreamName() const;
private:
	std::pair<int, int> streamNumber;
	std::string name;
};

} /* namespace MediaFile */
#endif /* STREAM_H_ */
