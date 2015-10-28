
#include "precomp.h"
#include "xml_settings.h"
#include "xml_settings_list.h"
#include "xml_settings_map.h"

XMLSettings::XMLSettings()
{
	*this = document.get_root();
}

XMLSettings::XMLSettings(const XMLSettingsAppModel &document, const uicore::XmlNodePtr &node)
: document(document), node(node)
{
}

XMLSettingsAppModel XMLSettings::get_document()
{
	return document;
}

bool XMLSettings::get_bool(const std::string &key, bool default_value) const
{
	auto child = node->named_item(key);
	if (child)
		return child->text() == "true";
	else
		return default_value;
}

int XMLSettings::get_int(const std::string &key, int default_value) const
{
	auto child = node->named_item(key);
	if (child)
		return uicore::Text::parse_int32(child->text());
	else
		return default_value;
}

std::string XMLSettings::get_string(const std::string &key, const std::string &default_value) const
{
	auto child = node->named_item(key);
	if (child)
		return child->text();
	else
		return default_value;
}

void XMLSettings::set_bool(const std::string &key, bool value)
{
	auto child = node->named_item(key);
	if (!child)
		child = node->append_child(node->owner_document()->create_element(key));
	child->set_text(value ? "true" : "false");
}

void XMLSettings::set_int(const std::string &key, int value)
{
	auto child = node->named_item(key);
	if (!child)
		child = node->append_child(node->owner_document()->create_element(key));
	child->set_text(uicore::Text::to_string(value));
}

void XMLSettings::set_string(const std::string &key, const std::string &value)
{
	auto child = node->named_item(key);
	if (!child)
		child = node->append_child(node->owner_document()->create_element(key));
	child->set_text(value);
}

XMLSettingsList XMLSettings::get_list(const std::string &key)
{
	auto child = node->named_item(key);
	if (!child)
		child = node->append_child(node->owner_document()->create_element(key));
	return XMLSettingsList(document, child);
}

XMLSettingsMap XMLSettings::get_map(const std::string &key)
{
	auto child = node->named_item(key);
	if (!child)
		child = node->append_child(node->owner_document()->create_element(key));
	return XMLSettingsMap(document, child);
}

XMLSettings XMLSettings::get_section(const std::string &key)
{
	auto child = node->named_item(key);
	if (!child)
		child = node->append_child(node->owner_document()->create_element(key));
	return XMLSettings(document, child);
}
