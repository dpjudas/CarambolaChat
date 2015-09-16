
#include "precomp.h"
#include "xml_settings_document.h"
#include "xml_settings.h"

XMLSettingsAppModel::XMLSettingsAppModel()
{
}

void XMLSettingsAppModel::load(const std::string &filename)
{
	uicore::File file(filename, uicore::File::open_existing, uicore::File::access_read, uicore::File::share_read);
	load(file);
}

void XMLSettingsAppModel::load(uicore::IODevice device)
{
	document.load(device, false);
}

void XMLSettingsAppModel::save(const std::string &filename)
{
	uicore::File file(filename, uicore::File::create_always, uicore::File::access_write, 0);
	save(file);
}

void XMLSettingsAppModel::save(uicore::IODevice device)
{
	document.save(device, false);
}

XMLSettings XMLSettingsAppModel::get_root()
{
	DomElement element = document.get_document_element();
	if (element.is_null())
	{
		element = document.create_element("settings");
		document.append_child(element);
	}
	return XMLSettings(*this, element);
}
