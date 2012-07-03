/*
 * audioformat.h
 *
 *  Created on: 28.6.2012
 *      Author: martint
 */

#ifndef AUDIOFORMAT_H_
#define AUDIOFORMAT_H_

#include <string>
#include <list>
#include "../FFTools/suportedencoders.h"
//#include "encoder.h"
#include "formattoencoders.h"

namespace AVBox {

class AudioFormat {
public:
	AudioFormat(const std::string& formatName);
	AudioFormat();
	virtual ~AudioFormat();
	bool operator==(const AudioFormat& enc) const;

	std::string getFormat() const;
	std::list<Encoder> getAvailableEncoders(const FFTools::SuportedEncoders& suport,
			const AVBox::FormatToEncoders& encoder) const;
private:
	std::string format;						//MP3, MP2 ...
};

class AudioFormatCmp{
	bool operator()(const AudioFormat &first, const AudioFormat &second) const;
};

} /* namespace AVBox */
#endif /* AUDIOFORMAT_H_ */
