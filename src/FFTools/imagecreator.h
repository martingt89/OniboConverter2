/*
 * imagecreator.h
 *
 *  Created on: 28.6.2012
 *      Author: martint
 */

#ifndef IMAGECREATOR_H_
#define IMAGECREATOR_H_

#include <string>
#include "../MediaInfo/mediafile.h"

namespace FFTools {

class ImageCreator {
public:
	static std::string createImage(MediaInfo::MediaFile file, double time = 10);
};

} /* namespace FFTools */
#endif /* IMAGECREATOR_H_ */
