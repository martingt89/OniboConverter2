/*
 * xmlgenerator.h
 *
 *  Created on: 23.8.2012
 *      Author: martint
 */

#ifndef XMLGENERATOR_H_
#define XMLGENERATOR_H_

#include <list>
#include <string>
#include <sstream>

namespace Xml {

class XmlNode{
public:
	XmlNode(const std::string& name);
	virtual ~XmlNode();
	void addArguments(const std::string& name, const std::string& value);
	XmlNode* addSubNode(XmlNode* xml);
	void addText(const std::string& text);
	void write(std::stringstream& output);
private:
	std::string name;
	std::string text;
	std::list<std::pair<std::string, std::string> > arguments;
	std::list<XmlNode*> subNode;
};

class XmlDocument{
public:
	XmlDocument(const std::string& name);
	virtual ~XmlDocument();
	XmlNode* addSubNode(XmlNode* xml);
	void write(std::stringstream& output);
private:
	std::list<XmlNode*> subNode;
	std::string name;
};

class XmlGenerator {
public:
	XmlGenerator();
	virtual ~XmlGenerator();
	XmlDocument* createDocument(const std::string& name) const;
	XmlNode* createNode(const std::string& name) const;
};

} /* namespace Xml */
#endif /* XMLGENERATOR_H_ */
