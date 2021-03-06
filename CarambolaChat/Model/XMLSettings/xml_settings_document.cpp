
#include "precomp.h"
#include "xml_settings_document.h"
#include "xml_settings.h"

XMLSettingsAppModel::XMLSettingsAppModel()
{
	document = uicore::XmlDocument::create();
}

void XMLSettingsAppModel::load(const std::string &filename)
{
	auto file = uicore::File::open_existing(filename);
	load(file);
}

void XMLSettingsAppModel::load(uicore::IODevicePtr device)
{
	document = uicore::XmlDocument::load(device, false);
}

void XMLSettingsAppModel::save(const std::string &filename)
{
	auto file = uicore::File::create_always(filename);
	save(file);
}

void XMLSettingsAppModel::save(uicore::IODevicePtr device)
{
	document->save(device, false);
}

XMLSettings XMLSettingsAppModel::get_root()
{
	auto element = document->document_element();
	if (!element)
	{
		element = document->create_element("settings");
		document->append_child(element);
	}
	return XMLSettings(*this, element);
}
