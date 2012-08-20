/*
 * stream.h
 *
 *  Created on: 20.8.2012
 *      Author: martint
 */

#ifndef STREAM_H_
#define STREAM_H_

#include <utility>

namespace MediaFile {

class Stream {
public:
	Stream(int firstNumber, int secondNumebr);
	virtual ~Stream();
	std::pair<int, int> getStreamNumber() const;
private:
	std::pair<int, int> streamNumber;
};

} /* namespace MediaFile */
#endif /* STREAM_H_ */
