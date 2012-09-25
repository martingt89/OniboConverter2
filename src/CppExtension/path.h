/* ---------------------------------------------------------------------------
** Author: Martin Geier
** path.h is part of OniboConverter2.
**
** OniboConverter2 is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program.  If not, see <http://www.gnu.org/licenses/>.
** -------------------------------------------------------------------------*/

#ifndef PATH_H_
#define PATH_H_

#include <string>
#include <list>

class Path {
public:
	enum PathType{
		FILE, FOLDER, NOSET
	};
public:
	Path(){path = "", type = NOSET;};
	Path(std::string path, PathType type = NOSET);
	Path(std::string first, std::string second, PathType type = NOSET);
	virtual ~Path();
	bool create() const;
	std::string getPath() const;
	std::string getLastPathPart() const;
	bool exist() const;
	bool getSubfiles(std::list<Path>& fileList, bool sort = false) const;
	bool operator==(const Path& path) const;
	bool operator<(const Path& path) const;
private:
	std::string path;
	PathType type;
};

#endif /* PATH_H_ */
