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

class Resolution {
public:
	Resolution(std::string name, std::string aspectRatio, int x, int y, bool isBasic);
	std::pair<int, int> getValue() const;
	std::string getName() const;
	std::string getAspectRatio() const;
	bool isBasic() const;
	bool operator<(const Resolution& res2);
private:
	std::string name;
	std::string aspectRatio;
	std::pair<int, int> resolution;
	bool basic;
};

class Resolutions{
public:
	void addResolution(const Resolution& resolution);
	std::list<Resolution> getResolutionsByAspectRatio(const std::string& aspectRatio) const;
	std::list<std::string> getAspectRatios() const;
	std::list<Resolution> getResolutions() const;
private:
	std::map<std::string, std::list<Resolution> > resolutions; //todo
};

} /* namespace ConverterOptions */
#endif /* RESOLUTION_H_ */
