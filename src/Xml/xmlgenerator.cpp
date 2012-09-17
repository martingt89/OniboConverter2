/* ---------------------------------------------------------------------------
** Author: Martin Geier
** xmlgenerator.cpp is part of OniboConverter2.
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

#include "xmlgenerator.h"
#include "../helper.h"

namespace Xml {

struct VectorCompare{
	bool operator()(const std::vector<PathNode>& first, const std::vector<PathNode>& sec) const{
		for (unsigned int i = 0; i < first.size(); ++i){
			if(sec.size() > i){
				if(first[i] == sec[i]){
					continue;
				}
				return (bool) (first[i] < sec[i]);
			}
			return true;
		}
		return false;
	}
};

//===================================================================

XmlGenerator::XmlGenerator(const std::string& rootName) : rootName(rootName){}

XmlGenerator::~XmlGenerator(){}

void XmlGenerator::addPath(const std::vector<PathNode>& path){
	if(path.size() > 0 && path[0].name == rootName){
		pathData.push_back(path);
	}
}

std::unique_ptr<Document> XmlGenerator::generateFromPath() {
	VectorCompare cmp;
	pathData.sort(cmp);

	std::unique_ptr<Document> document(new Document);
	Xml::Node* node = new Xml::Node(rootName);
	(*document).setSubNode(node);
	std::vector<std::string> path;
	path.push_back(rootName);
	generate(node, 0, pathData.begin(), pathData.end(), path, false);
	return document;
}

void XmlGenerator::generate(Xml::Node* node, unsigned int depth,
				std::list<std::vector<Xml::PathNode> >::iterator actualLine,
				std::list<std::vector<Xml::PathNode> >::iterator lastLine,
				std::vector<std::string> path, bool change)
	{
	if(actualLine == lastLine){
		return;
	}
	if(change){
		unsigned int counter = 0;
		for(auto x : path){
			if(((*actualLine).size() <= counter) || (*actualLine)[counter].name != x){
				break;
			}
			++counter;
		}
		assert(counter > 0, "Counter is not great then 0");

		--counter;
		int diff = depth - counter;
		for (int i = 0; i < diff; ++i){
			node = node->getParent();
		}
		depth = counter;
		path.resize(depth+1);
	}
	if((*actualLine)[depth].haveText){
		node->setText((*actualLine)[depth].text);
	}
	if((*actualLine).size() > depth+1){
		Xml::Node* tmp = new Xml::Node((*actualLine)[depth+1].name);
		node->addSubNode(tmp);
		tmp->setParent(node);
		path.push_back((*actualLine)[depth+1].name);
		generate(tmp, depth+1, actualLine, lastLine, path, false);
	}else{
		generate(node, depth, ++actualLine, lastLine, path, true);
	}
}
//===================================================================

Node::Node(const std::string& name){
	this->name = name;
	parent = NULL;
}
Node::~Node(){
	for(auto iter = subNode.begin(); iter != subNode.end(); ++iter){
		delete *iter;
	}
}
void Node::addArguments(const std::string& name, const std::string& value){
	arguments.push_back(std::make_pair(name, value));
}
void Node::setText(const std::string& text){
	this->text = text;
}
Node* Node::addSubNode(Node* xml){
	subNode.push_back(xml);
	return xml;
}
void Node::setParent(Node* parent){
	this->parent = parent;
}
Node* Node::getParent(){
	return parent;
}

void Node::intend(const int depth, std::ostream& output) {
	for (int i = 0; i < depth; i++) {
		output << "\t";
	}
}

void Node::write(std::ostream& output, const int depth) {
	intend(depth, output);
	output<<"<"<<name;
	for(auto pair : arguments){
		output<<" "<<pair.first<<"=\""<<pair.second<<"\"";
	}
	output<<">";
	output<<text;
	if(!subNode.empty()){
		output<<std::endl;
	}
	for(auto node : subNode){
		node->write(output, depth + 1);
	}
	if(!subNode.empty()){
		intend(depth, output);
	}
	output<<"</"<<name<<">"<<std::endl;
}

//===================================================================

Document::Document(){
	subNode = NULL;
}
Document::~Document(){
	if(subNode != NULL){
		delete subNode;
	}
}
Node* Document::setSubNode(Node* xml){
	subNode = xml;
	return xml;
}
void Document::write(std::ostream& output){
	output<<"<?xml version=\"1.0\" encoding=\"UTF-8\"?>"<<std::endl;
	subNode->write(output);
}
Node* Document::getNode(){
	return subNode;
}
//===================================================================

PathNode::PathNode(const std::string& name){
	this->name = name;
	this->haveText = false;
}
PathNode::PathNode(const std::string& name, const std::string& text){
	this->name = name;
	this->haveText = true;
	this->text = text;
}
bool PathNode::operator < (const PathNode& second) const{
	return this->name < second.name;
}
bool PathNode::operator == (const PathNode& second) const{
	return this->name == second.name;
}

} /* namespace Xml */
