/*
 * stream.cpp
 *
 *  Created on: 26.6.2012
 *      Author: martint
 */

#include "stream.h"

namespace MediaInfo {

Stream::Stream(int f, int r): streamNuber(f, r) {
}

Stream::~Stream() {

}
std::pair<int, int> Stream::getStreamNumber(){
	return streamNuber;
}
} /* namespace MediaInfo */
