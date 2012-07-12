/*
 * comboboxtextwraper.h
 *
 *  Created on: 12.7.2012
 *      Author: martint
 */

#ifndef COMBOBOXTEXTWRAPER_H_
#define COMBOBOXTEXTWRAPER_H_

#include "../../Tools/helper.h"
template <class T>
class ComboBoxTextWraper{
public:
	ComboBoxTextWraper(){
		widget = 0;
		old = "";
		activable = true;
	}

	~ComboBoxTextWraper(){
		if(widget != 0){
			delete widget;
			widget = 0;
		}
	}

	void set_widget(Gtk::ComboBoxText* widget){
		this->widget = widget;
	}

	void append(const std::string& text, const T &infoData = T()){
		bool sens = widget->get_sensitive();
		widget->set_sensitive(true);
		widget->append(text, toS(data.size()));
		data.push_back(infoData);
		if(!sens)
			widget->set_sensitive(sens);
	}

	void set_active(int index){
		widget->set_active(index);
	}

	void set_sensitive(bool sensitive){
		if(sensitive && activable){
			widget->set_sensitive(true);
		}else if(!sensitive){
			widget->set_sensitive(false);
		}
	}

	int get_active_row_number(){
		return widget->get_active_row_number();
	}
	std::string get_active_text(){
		return widget->get_active_text();
	}
	T get_active_row_data(T def = T()){
		if(widget->get_active_row_number() >= 0){
			return data[widget->get_active_row_number()];
		}
		return def;
	}
	void remove_all(){
		widget->remove_all();
		data.clear();
		data.resize(0);
	}

	void set_active_text(const std::string& text){
		widget->set_active_text(text);
	}

	bool is_sensitive(){
		return widget->get_sensitive();
	}

	bool is_selected(){
		return widget->get_active_row_number() >= 0;
	}
	Glib::SignalProxy0< void > signal_changed(){
		return widget->signal_changed();
	}
	void unset_active(){
		widget->unset_active();
	}
	int count_of_elements(){
		return data.size();
	}
	void checkpoint(){
		old = widget->get_active_id();
	}
	bool is_same_row(){
		return old == widget->get_active_id();
	}
	void set_activable(bool activable){
		this->activable = activable;
	}
	bool is_activable(){
		return activable;
	}
	bool is_set_last(){
		return widget->get_active_row_number() == (data.size()-1);
	}
	bool is_set_first(){
		return widget->get_active_row_number() == 0;
	}
private:
	Gtk::ComboBoxText *widget;
	std::vector<T> data;
	std::string old;
	bool activable;
};



#endif /* COMBOBOXTEXTWRAPER_H_ */
