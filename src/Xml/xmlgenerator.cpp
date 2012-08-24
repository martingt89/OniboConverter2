/*
 * xmlgenerator.cpp
 *
 *  Created on: 23.8.2012
 *      Author: martint
 */

#include "xmlgenerator.h"
#include <iostream>

namespace Xml {

XmlGenerator::XmlGenerator(){

}
XmlGenerator::~XmlGenerator(){

}
XmlDocument* XmlGenerator::createDocument(const std::string& name) const{
	return new XmlDocument(name);
}

XmlNode* XmlGenerator::createNode(const std::string& name) const{
	return new XmlNode(name);
}

XmlNode::XmlNode(const std::string& name){
	this->name = name;
}
XmlNode::~XmlNode(){
	for(auto iter = subNode.begin(); iter != subNode.end(); ++iter){
		delete *iter;
	}
}
void XmlNode::addArguments(const std::string& name, const std::string& value){
	arguments.push_back(std::make_pair(name, value));
}
void XmlNode::addText(const std::string& text){
	this->text = text;
}
XmlNode* XmlNode::addSubNode(XmlNode* xml){
	subNode.push_back(xml);
	return xml;
}
void XmlNode::write(std::stringstream& output){
	output<<"<"<<name<<" ";
	for(auto pair : arguments){
		output<<pair.first<<"=\""<<pair.second<<"\" ";
	}
	output<<">";
	output<<text;
	for(auto node : subNode){
		node->write(output);
	}
	output<<"</"<<name<<">";
}

XmlDocument::XmlDocument(const std::string& name){
	this->name = name;
}
XmlDocument::~XmlDocument(){
	for(auto iter = subNode.begin(); iter != subNode.end(); ++iter){
		delete *iter;
	}
}
XmlNode* XmlDocument::addSubNode(XmlNode* xml){
	subNode.push_back(xml);
	return xml;
}
void XmlDocument::write(std::stringstream& output){
	output<<"<?xml version=\"1.0\" encoding=\"UTF-8\"?>"<<std::endl;

	output<<"<"<<name<<">";
	for(auto node : subNode){
		node->write(output);
	}
	output<<"</"<<name<<">";
}

} /* namespace Xml */
