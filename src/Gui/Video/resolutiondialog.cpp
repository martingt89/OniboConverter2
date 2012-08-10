/*
 * videoresolutiongui.cpp
 *
 *  Created on: 9.8.2012
 *      Author: martint
 */

#include "resolutiondialog.h"

#include <gtkmm/stock.h>
#include "../../helper.h"
#include <vector>

namespace Gui {
namespace Video {
static const std::string INVALID_RESOLUTION = "Invalid final resolution";
static const std::string CUSTOM_MODE = "--- custom ---";

ResolutionControl::ResolutionControl(ConverterOptions::OptionsDatabase &database,
		const Glib::RefPtr<Gtk::Builder>& refGlade) : database(database),
				aspectRatio(refGlade, "aspectRatio"){

	refGlade->get_widget("resolutionDialog", resolutionDialog);
	refGlade->get_widget("resolutionEntryX", resolutionEntryX);
	refGlade->get_widget("resolutionEntryY", resolutionEntryY);
	refGlade->get_widget("resolutionCanavas", resolutionCanavas);
	refGlade->get_widget("resolutionError", resolutionError);

	isEnableSignal = true;

	resolutionDialog->add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
	resolutionDialog->add_button(Gtk::Stock::OK, Gtk::RESPONSE_OK);

	treeModel = Gtk::ListStore::create(model);
	resolutionCanavas->set_model(treeModel);

	treeSelection = resolutionCanavas->get_selection();

	initAspectRatio(aspectRatio);
	fillCanavas(treeModel);

	resolutionCanavas->append_column("Aspect ratio", model.colAspect);
	resolutionCanavas->append_column("Resolution name", model.colResolName);
	resolutionCanavas->append_column("Resolution", model.colResolution);

	Gtk::TreeView::Column* pColumn;
	pColumn = resolutionCanavas->get_column(0);
	if(pColumn)
	  pColumn->set_sort_column(model.colAspect);
	pColumn = resolutionCanavas->get_column(1);
	if(pColumn)
	  pColumn->set_sort_column(model.colResolName);
	pColumn = resolutionCanavas->get_column(2);
	if(pColumn)
	  pColumn->set_sort_column(model.colResolution);

	resolutionCanavas->signal_row_activated().connect(
			sigc::mem_fun(this, &ResolutionControl::doubleClickOnBoard));
	treeSelection->signal_changed().connect(
		    sigc::mem_fun(*this, &ResolutionControl::clickOnBoard));
	resolutionEntryX->signal_changed().connect(
		    sigc::mem_fun(*this, &ResolutionControl::changedX));
	resolutionEntryY->signal_changed().connect(
		    sigc::mem_fun(*this, &ResolutionControl::changedY));
	aspectRatio.signal_changed().connect(
		    sigc::mem_fun(*this, &ResolutionControl::aspectChanged));
}

ResolutionControl::~ResolutionControl() {
	delete resolutionDialog;
	delete resolutionEntryX;
	delete resolutionEntryY;
	delete resolutionCanavas;
	delete resolutionError;
}

bool ResolutionControl::start(ConverterOptions::Resolution& resolution){
	resolutionError->set_text("");
	while(1){
		int res = resolutionDialog->run();

		if(res == Gtk::RESPONSE_OK){
			int x = toN(resolutionEntryX->get_text(), int());
			int y = toN(resolutionEntryY->get_text(), int());
			if(x == 0 || y == 0){
				resolutionError->set_markup("<span color='red'>"+INVALID_RESOLUTION+"</span>");
				continue;
			}
			std::string aspect = calcAspect(x, y);
			std::string name = "";
			bool found = false;
			ConverterOptions::Resolution res = database.getResolutions().getResolutionBySize(x, y, found);
			if(found){
				aspect = res.getAspectRatio();
				name = res.getName();
			}
			resolution = ConverterOptions::Resolution(name, aspect, x, y, false);
			resolutionDialog->hide();
			return true;
		}
		break;
	}
	resolutionDialog->hide();
	return false;
}
void ResolutionControl::initAspectRatio(ComboBoxExt<ConverterOptions::AspectRatio>& aspectRatio){
	aspectRatio.append(CUSTOM_MODE);
	aspectRatio.set_active_row_number(0);

	auto aspectRatioList = database.getResolutions().getAspectRatios();
	for(auto aspectIter = aspectRatioList.begin(); aspectIter!= aspectRatioList.end(); ++aspectIter){
		aspectRatio.append((std::string)*aspectIter, *aspectIter);
	}
}
void ResolutionControl::fillCanavas(Glib::RefPtr<Gtk::ListStore>& treeModel){
	treeModel->clear();
	if(aspectRatio.is_set_first()){	//custom mode
		auto resolutionList = database.getResolutions().getResolutions();
		std::for_each(resolutionList.begin(), resolutionList.end(),
				[&](const ConverterOptions::Resolution& resolution){

			Gtk::TreeModel::Row row = *(treeModel->append());
			row[model.colAspect] = resolution.getAspectRatio();
			std::string resol = toS(resolution.getValue().first) + "x" + toS(resolution.getValue().second);
			row[model.colResolution] = resol;
			row[model.colResolName] = resolution.getName();
			row[model.resolution] = resolution;
		});
	}else{
		auto resol = database.getResolutions().getResolutionsByAspectRatio(aspectRatio.get_active_row_item());
		std::for_each(resol.begin(), resol.end(),
						[&](const ConverterOptions::Resolution& resolution){

			Gtk::TreeModel::Row row = *(treeModel->append());
			row[model.colAspect] = resolution.getAspectRatio();
			std::string resol = toS(resolution.getValue().first) + "x" + toS(resolution.getValue().second);
			row[model.colResolution] = resol;
			row[model.colResolName] = resolution.getName();
			row[model.resolution] = resolution;
		});
	}
}
void ResolutionControl::changedX(){
	if(isEnableSignal){
		isEnableSignal = false;
		if(!aspectRatio.is_set_first()){
			int x = toN(resolutionEntryX->get_text(), int());
			int y = aspectRatio.get_active_row_item().convertXtoY(x);
			resolutionEntryY->set_text(toS(y));
		}
		isEnableSignal = true;
	}
}
void ResolutionControl::changedY(){
	if(isEnableSignal){
		isEnableSignal = false;
		if(!aspectRatio.is_set_first()){
			int y = toN(resolutionEntryY->get_text(), int());
			int x = aspectRatio.get_active_row_item().convertYtoX(y);
			resolutionEntryX->set_text(toS(x));
		}
		isEnableSignal = true;
	}
}
void ResolutionControl::doubleClickOnBoard(const Gtk::TreeModel::Path& path, Gtk::TreeViewColumn*){
	Gtk::TreeModel::Row row = *(treeModel->get_iter(path));
	if(row){
		ConverterOptions::Resolution resol = row[model.resolution];
		setResolutiontoEntry(resol);
		resolutionDialog->response(Gtk::RESPONSE_OK);
	}
}
void ResolutionControl::clickOnBoard(){
	std::vector<Gtk::TreeModel::Path> rows = treeSelection->get_selected_rows();
	if(rows.size() > 0){
		Gtk::TreeModel::Row row = *(treeModel->get_iter(rows[0]));
		ConverterOptions::Resolution resol = row[model.resolution];
		setResolutiontoEntry(resol);
	}
}
void ResolutionControl::aspectChanged(){
	fillCanavas(treeModel);
}
void ResolutionControl::setResolutiontoEntry(const ConverterOptions::Resolution& resolution){
	isEnableSignal = false;
	resolutionEntryX->set_text(toS(resolution.getValue().first));
	resolutionEntryY->set_text(toS(resolution.getValue().second));
	isEnableSignal = true;
}
std::string ResolutionControl::calcAspect(const int& x, const int& y){
	int nsd = NSD(x, y);
	int tx = x / nsd;
	int ty = y / nsd;
	return toS(tx)+":"+toS(ty);
}

}
} /* namespace Gui */
