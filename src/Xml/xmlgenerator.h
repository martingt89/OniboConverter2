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
#include <memory>
#include <libxml++/libxml++.h>

namespace Xml {

class PathNode{
public:
	PathNode(const std::string& name);
	PathNode(const std::string& name, const std::string& text);
	bool operator < (const PathNode& second) const;
	bool operator == (const PathNode& second) const;

	std::string name;
	bool haveText;
	std::string text;
};

class Node{
public:
	Node(const std::string& name);
	virtual ~Node();
	void addArguments(const std::string& name, const std::string& value);
	Node* addSubNode(Node* xml);
	void setParent(Node* parent);
	Node* getParent();
	void setText(const std::string& text);
	void write(std::ostream& output, const int depth = 0);
private:
	std::string name;
	std::string text;
	std::list<std::pair<std::string, std::string> > arguments;
	std::list<Node*> subNode;
	Node* parent;

	void intend(const int depth, std::ostream& output);
};

class Document{
public:
	Document();
	virtual ~Document();
	Node* setSubNode(Node* xml);
	void write(std::ostream& output);
	Node* getNode();
private:
	Node* subNode;
};

class XmlGenerator {
public:
	XmlGenerator(const std::string& rootName);
	virtual ~XmlGenerator();
	void addPath(const std::vector<PathNode>& path);
	std::unique_ptr<Document> generateFromPath() ;
private:
	void generate(Xml::Node* node, unsigned int depth,
				std::list<std::vector<Xml::PathNode> >::iterator actualLine,
				std::list<std::vector<Xml::PathNode> >::iterator lastLine,
				std::vector<std::string> path, bool change);
	const std::string rootName;
	std::list<std::vector<Xml::PathNode> > pathData;
};

} /* namespace Xml */
#endif /* XMLGENERATOR_H_ */
