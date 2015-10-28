
#include "precomp.h"
#include "xml_settings_list.h"
#include "xml_settings.h"

XMLSettingsList::XMLSettingsList()
{
}

XMLSettingsList::XMLSettingsList(const XMLSettingsAppModel &document, const uicore::XmlNodePtr &node)
: document(document), node(node)
{
}

XMLSettingsAppModel XMLSettingsList::get_document()
{
	return document;
}

XMLSettings XMLSettingsList::add()
{
	auto element = node->owner_document()->create_element("item");
	node->append_child(element);
	return XMLSettings(document, element);
}

XMLSettings XMLSettingsList::get(int index)
{
	int count = 0;
	for (auto cur = node->first_child(); cur; cur = cur->next_sibling())
	{
		if (!cur->is_element())
			continue;

		if (count == index)
			return XMLSettings(document, cur);

		count++;
	}
	return XMLSettings();
}

void XMLSettingsList::remove(int index)
{
	int count = 0;
	for (auto cur = node->first_child(); cur; cur = cur->next_sibling())
	{
		if (!cur->is_element())
			continue;

		if (count == index)
		{
			node->remove_child(cur);
			break;
		}

		count++;
	}
}

int XMLSettingsList::get_count() const
{
	int count = 0;
	for (auto cur = node->first_child(); cur; cur = cur->next_sibling())
	{
		if (!cur->is_element())
			continue;

		count++;
	}
	return count;
}
