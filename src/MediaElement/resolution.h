/* ---------------------------------------------------------------------------
** Author: Martin Geier
** resolution.h is part of OniboConverter2.
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

#ifndef RESOLUTION_H_
#define RESOLUTION_H_

#include <string>
#include <list>
#include "../CppExtension/hashmap.h"

namespace MediaElement {

class AspectRatio{
public:
	AspectRatio();
	AspectRatio(const int& x, const int& y);
	static AspectRatio createFromString(const std::string& XcolomnY);
	std::string readableForm() const;
	std::string getXcolonY() const;
	int convertXtoY(int x);
	int convertYtoX(int y);
	bool operator<(const AspectRatio& second) const;
	bool operator==(const AspectRatio& second) const;
private:
	int aspectX;
	int aspectY;
};

class Resolution {
public:
	Resolution(){basic = false; isset = false;};
	Resolution(std::string name, AspectRatio aspectRatio, int x, int y, bool isBasic = false);
	bool isSet();
	void setBasic();
	std::pair<int, int> getValue() const;
	std::string getName() const;
	AspectRatio getAspectRatio() const;
	bool isBasic() const;
	bool operator<(const Resolution& second) const;
	bool operator==(const Resolution& second) const;
	std::string readableForm() const;
	bool isOriginal() const;
private:
	std::pair<int, int> resolution;
	AspectRatio aspectRatio;
	std::string name;
	bool basic;
	bool isset;
};

class Resolutions{
public:
	void addResolution(const Resolution& resolution);
	std::list<Resolution> getResolutionsByAspectRatio(const AspectRatio& aspectRatio) const;
	std::list<AspectRatio> getAspectRatios() const;
	std::list<Resolution> getResolutions() const;
	Resolution getResolutionBySize(const int& x, const int& y, bool& found) const;
private:
	CppExtension::MultiHashMap<AspectRatio, Resolution> aspectToResolution;
};

} /* namespace MediaElement */
#endif /* RESOLUTION_H_ */
