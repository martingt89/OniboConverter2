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
	enum PathType{
		FILE, FOLDER, NOSET
	};
public:
	Path(){type = NOSET;};
	Path(std::string path, PathType type = NOSET);
	Path(std::string first, std::string second, PathType type = NOSET);
	virtual ~Path();
	bool create() const;
	std::string getPath() const;
	std::string getLastPathPart() const;
	bool exist() const;
private:
	std::string path;
	PathType type;
};

#endif /* PATH_H_ */
