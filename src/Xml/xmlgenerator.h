/* ---------------------------------------------------------------------------
** Author: Martin Geier
** xmlgenerator.h is part of OniboConverter2.
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
