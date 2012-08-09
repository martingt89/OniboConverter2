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
#include <map>

namespace ConverterOptions {

class AspectRatio{
public:
	AspectRatio();
	AspectRatio(const std::string& aspect);
	operator std::string();
	int convertXtoY(int x);
	int convertYtoX(int y);
private:
	std::string aspectRatio;
	int aspectX;
	int aspectY;
};

class Resolution {
public:
	Resolution(){basic = false;};
	Resolution(std::string name, std::string aspectRatio, int x, int y, bool isBasic);
	std::pair<int, int> getValue() const;
	std::string getName() const;
	AspectRatio getAspectRatio() const;
	bool isBasic() const;
	bool operator<(const Resolution& res2);
private:
	std::pair<int, int> resolution;
	AspectRatio aspectRatio;
	std::string name;
	bool basic;
};

class Resolutions{
public:
	void addResolution(const Resolution& resolution);
	std::list<Resolution> getResolutionsByAspectRatio(const std::string& aspectRatio) const;
	std::list<AspectRatio> getAspectRatios() const;
	std::list<Resolution> getResolutions() const;
	std::string getNameByResolution(const int& x, const int& y) const;
private:
	std::map<std::string, std::list<Resolution> > resolutions; //todo
};

} /* namespace ConverterOptions */
#endif /* RESOLUTION_H_ */
