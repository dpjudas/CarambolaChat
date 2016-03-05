
#pragma once

#include "network_list_view.h"

class ConnectionsView : public uicore::View
{
public:
	ConnectionsView()
	{
		style()->set("flex: auto");
		style()->set("flex-direction: column");
		style()->set("margin: 11px");

		auto title = add_child<uicore::LabelBaseView>();
		title->style()->set("font: bold 16px/20px 'Source Sans Pro'");
		title->set_text("Chat Networks");

		networks = add_child<NetworkListView>();

		about_button = add_child<uicore::ButtonBaseView>();
		about_button->label()->set_text("About Carambola Chat..");
		about_button->label()->style()->set("font: 13px/16px 'Source Sans Pro'");
		about_button->label()->style()->set("color: rgb(0,0,128)");
		about_button->label()->style()->set("margin: 15px 0");
	}

	std::shared_ptr<NetworkListView> networks;
	std::shared_ptr<uicore::ButtonBaseView> about_button;
};
