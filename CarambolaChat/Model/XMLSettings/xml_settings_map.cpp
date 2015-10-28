
#include "precomp.h"
#include "xml_settings_map.h"
#include "xml_settings.h"

XMLSettingsMap::XMLSettingsMap()
{
}

XMLSettingsMap::XMLSettingsMap(const XMLSettingsAppModel &document, const uicore::XmlNodePtr &node)
: document(document), node(node)
{
}

XMLSettingsAppModel XMLSettingsMap::get_document()
{
	return document;
}

XMLSettings XMLSettingsMap::get(const std::string &key)
{
	for (auto cur = node->first_child(); cur; cur = cur->next_sibling())
	{
		if (!cur->is_element())
			continue;
		
		if (cur->attribute("key") == key)
			return XMLSettings(document, cur);
	}

	auto cur = node->owner_document()->create_element("item");
	cur->set_attribute("key", key);
	node->append_child(cur);
	return XMLSettings(document, cur);
}

void XMLSettingsMap::remove(const std::string &key)
{
	for (auto cur = node->first_child(); cur; cur = cur->next_sibling())
	{
		if (!cur->is_element())
			continue;

		if (cur->attribute("key") == key)
		{
			node->remove_child(cur);
			break;
		}
	}
}
