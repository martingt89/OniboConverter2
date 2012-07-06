/*
 * videoformat.h
 *
 *  Created on: 28.6.2012
 *      Author: martint
 */

#ifndef VIDEOFORMAT_H_
#define VIDEOFORMAT_H_

#include <string>
#include <list>
#include "formattoencoders.h"
#include "supportedencoders.h"

namespace AVBox {

class VideoFormat {
public:
	VideoFormat(const std::string& formatName);
	VideoFormat();
	virtual ~VideoFormat();
	bool operator==(const VideoFormat& enc) const;
//
//	operator std::string() const{
//		return format;
//	};
//
	std::string getFormat() const;
	std::list<Encoder> getAvailableEncoders(const SupportedEncoders& support,
			const FormatToEncoders& encoder) const;
private:
	std::string format;						//X264, MPEG4, MPEG2, etc.
};

class VideoFormatCmp{
	bool operator()(const VideoFormat &first, const VideoFormat &second) const;
};

} /* namespace AVBox */

#endif /* VIDEOFORMAT_H_ */
