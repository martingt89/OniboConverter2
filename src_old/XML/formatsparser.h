/*
 * formatsparser.h
 *
 *  Created on: 14.7.2012
 *      Author: martint
 */

#ifndef FORMATSPARSER_H_
#define FORMATSPARSER_H_

#include <libxml++/libxml++.h>
#include <glibmm/ustring.h>
#include <string>
#include "../AVBox/encoder.h"
#include "../AVBox/avformat.h"
#include <map>
#include <list>

namespace XML {

class FormatsParser : public xmlpp::SaxParser{
public:
	FormatsParser(const std::list<AVBox::Encoder> supportedEncoders);
	virtual ~FormatsParser();
	std::list<AVBox::AVFormat> getFormats() const;
protected:
	virtual void on_start_element(const Glib::ustring& name, const AttributeList& attributes);
	virtual void on_end_element(const Glib::ustring& name);
	virtual void on_characters(const Glib::ustring& characters);
private:
	std::string actualFormat;
	std::string presentsPrefix;
	bool inEnc;

	std::map<std::string, AVBox::Encoder> supportedEncoders;
	std::list<AVBox::AVFormat> formats;

	bool getEncoder(const std::string& encoderName, AVBox::Encoder &encoder);
	void addEncoderToFormat(std::list<AVBox::AVFormat> &formats, const AVBox::Encoder& encoder);
};

} /* namespace XML */
#endif /* FORMATSPARSER_H_ */
