/*
 * onibowindow.cpp
 *
 *  Created on: 5.7.2012
 *      Author: martint
 */

#include "onibowindow.h"
#include "gtkmm/main.h"

//#include "../FFTools/imagecreator.h"
#include "../FFTools/ffdatamining.h"

#include "../XML/containersparser.h"
#include "../XML/encodersparser.h"
#include "../XML/guisettingsparser.h"

#include <iostream>	//todo remove

namespace GUI {

OniboWindow::OniboWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade) :
		Gtk::Window(cobject), refGlade(refGlade){

	refGlade->get_widget_derived("container_combo_box", container);

	XML::ContainersParser parser;
	parser.parse(audioVideoData);

	XML::GuiSettingsParser guiParser;
	guiParser.parse(guiData);

	XML::EncodersParser encodersParser;
	encodersParser.parse(convert);

	FFTools::FFDataMining dataMining;
	dataMining.scan(&suportedEncoders);

	container->setNeedsData(&suportedEncoders, &audioVideoData, &guiData, &convert);
}

OniboWindow::~OniboWindow() {
	// TODO Auto-generated destructor stub
}

} /* namespace GUI */
