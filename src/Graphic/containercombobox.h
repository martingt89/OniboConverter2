/*
 * containercombobox.h
 *
 *  Created on: 5.7.2012
 *      Author: martint
 */

#ifndef CONTAINERCOMBOBOX_H_
#define CONTAINERCOMBOBOX_H_

#include <gtkmm/comboboxtext.h>
#include <gtkmm/builder.h>
#include "videosettings.h"
//#include "audiosettings.h" //todo implement

#include "../AVBox/avbox.h"
#include "../AVBox/supportedencoders.h"
#include "../AVBox/formattoencoders.h"
#include "../AVBox/guisettings.h"

namespace GUI {

class ContainerComboBox : public Gtk::ComboBoxText{
public:
	ContainerComboBox(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);
	virtual ~ContainerComboBox();
	void setNeedsData(AVBox::SupportedEncoders *suportedEncoders,
						AVBox::AVBox *audioVideoData,
						AVBox::GuiSettings *guiData,
						AVBox::FormatToEncoders *convert);
protected:
	virtual void on_changed ();
	void changeContent();
private:
	const Glib::RefPtr<Gtk::Builder>& refGlade;
	VideoSettings videoSettings;

	AVBox::SupportedEncoders *suportedEncoders;
	AVBox::AVBox *audioVideoData;
	AVBox::GuiSettings *guiData;
	AVBox::FormatToEncoders *convert;
};

} /* namespace GUI */
#endif /* CONTAINERCOMBOBOX_H_ */
