/*
 * path.h
 *
 *  Created on: 26.7.2012
 *      Author: martint
 */

#ifndef PATH_H_
#define PATH_H_

#include <string>

class Path {
public:
	Path(){};
	Path(std::string path);
	virtual ~Path();
	std::string getPath() const;
private:
	std::string path;
};

#endif /* PATH_H_ */
