/*
 * avformat.h
 *
 *  Created on: 14.7.2012
 *      Author: martint
 */

#ifndef AVFORMAT_H_
#define AVFORMAT_H_

#include "encoder.h"
#include <list>

namespace AVBox {

class AVFormat {
public:
	AVFormat(const std::string &name);
	AVFormat();
	virtual ~AVFormat();
	void addEncoder(Encoder encoder);
	std::string getName() const;
private:
	std::list<Encoder> encoders;
	std::string name;
};

} /* namespace AVBox */
#endif /* AVFORMAT_H_ */
