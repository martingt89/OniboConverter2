/*
 * guisettingsparser.h
 *
 *  Created on: 4.7.2012
 *      Author: martint
 */

#ifndef GUISETTINGSPARSER_H_
#define GUISETTINGSPARSER_H_

#include "../AVBox/guisettings.h"
#include <libxml++/libxml++.h>
#include <glibmm/ustring.h>
#include <string>
#include <set>

namespace XML {

class GuiSettingsParser : public xmlpp::SaxParser{
public:
	GuiSettingsParser();
	virtual ~GuiSettingsParser();
	bool parse(AVBox::GuiSettings* gui);
protected:
	enum ParserState{
		DOCUMENT, AUDIO, VIDEO, RESOLUTIONS, RESOLUTION, BITRATES,
		BITRATE, FRAMERATES, FRAMERATE, SAMPLERATE, SAMPLERATES
	};
	virtual void on_start_document();
	virtual void on_end_document();
	virtual void on_start_element(const Glib::ustring& name, const AttributeList& attributes);
	virtual void on_end_element(const Glib::ustring& name);
	virtual void on_characters(const Glib::ustring& characters);
	virtual void on_comment(const Glib::ustring& text);
	virtual void on_warning(const Glib::ustring& text);
	virtual void on_error(const Glib::ustring& text);
	virtual void on_fatal_error(const Glib::ustring& text);
	virtual void on_cdata_block(const Glib::ustring& text);
private:
	std::set<ParserState> states;
	std::map<std::string, ParserState> convertTable;
	std::string resolutionRatio;
	std::string resolutionName;
	xmlpp::SaxParser::AttributeList::const_iterator iter;
	AVBox::GuiSettings* guiSettings;
	void initConvertTable();
};

} /* namespace XML */
#endif /* GUISETTINGSPARSER_H_ */
