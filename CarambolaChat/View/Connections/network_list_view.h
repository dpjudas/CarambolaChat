
#pragma once

class NetworkListItemView;

class NetworkListView : public uicore::View
{
public:
	NetworkListView();

	std::shared_ptr<NetworkListItemView> add_item(const std::string &name);
	std::shared_ptr<NetworkListItemView> get_item(const std::string &name);

	std::shared_ptr<uicore::ButtonView> add_button;

private:
	std::shared_ptr<uicore::View> items_view;
	std::map<std::string, std::shared_ptr<NetworkListItemView>> items;
};
