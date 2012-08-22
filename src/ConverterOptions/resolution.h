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
#include "../Converter/convertsettings.h"

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
	Resolution(){basic = false; isset = false;};
	Resolution(std::string name, std::string aspectRatio, int x, int y, bool isBasic = false);
	bool isSet();
	std::pair<int, int> getValue() const;
	std::string getName() const;
	AspectRatio getAspectRatio() const;
	bool isBasic() const;
	bool operator<(const Resolution& res2);
	std::string toStr() const;
	Converter::ConvertSettingsList getConvertArguments() const;
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
	std::list<Resolution> getResolutionsByAspectRatio(const std::string& aspectRatio) const;
	std::list<AspectRatio> getAspectRatios() const;
	std::list<Resolution> getResolutions() const;
	Resolution getResolutionBySize(const int& x, const int& y, bool& found) const;
private:
	std::map<std::string, std::list<Resolution> > resolutions;
};

} /* namespace ConverterOptions */
#endif /* RESOLUTION_H_ */
