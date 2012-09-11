/*
 * resolution.h
 *
 *  Created on: 24.7.2012
 *      Author: martint
 */

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
