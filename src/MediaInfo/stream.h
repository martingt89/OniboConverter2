/*
 * stream.h
 *
 *  Created on: 26.6.2012
 *      Author: martint
 */

#ifndef STREAM_H_
#define STREAM_H_

#include <utility>

namespace MediaInfo {

class Stream {
public:
	Stream(int f, int r);
	virtual ~Stream();
	std::pair<int, int> getStreamNumber();
private:
	std::pair<int, int> streamNuber;
};

} /* namespace MediaInfo */
#endif /* STREAM_H_ */
