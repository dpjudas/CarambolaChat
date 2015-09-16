
#pragma once

#include "View/Chat/chat_view.h"
#include "View/UserList/user_list_view.h"

class ChatPageView : public uicore::ColumnView
{
public:
	ChatPageView()
	{
		auto chat_users_group = std::make_shared<uicore::View>();
		chat_users_group->style()->set("flex-direction: row");
		chat_users_group->style()->set("flex: auto");

		chat_log = std::make_shared<ChatView>();
		chat_log->style()->set("flex: auto");
		chat_users_group->add_subview(chat_log);

		user_list = std::make_shared<UserListView>();
		user_list->style()->set("width: 200px");
		user_list->style()->set("flex: none");
		chat_users_group->add_subview(user_list);

		auto input_bar = std::make_shared<uicore::View>();
		input_bar->style()->set("flex: none");
		input_bar->style()->set("background: linear-gradient(to bottom, rgb(235,243,252), rgb(219,234,249))");
		input_bar->style()->set("border-top: 1px solid rgb(153,153,153)");
		input_bar->style()->set("padding: 5px");
		input_bar->style()->set("flex-direction: row");

		input_text = std::make_shared<uicore::TextFieldView>();
		input_text->style()->set("flex: auto");
		input_text->style()->set("border: 1px solid rgb(153,153,153)");
		input_text->style()->set("border-radius: 2px");
		input_text->style()->set("background: white");
		input_text->style()->set("padding: 2px 5px");
		input_text->style()->set("font: 12px/20px 'Source Sans Pro'");
		input_text->set_select_all_on_focus_gain(false);
		input_bar->add_subview(input_text);

		add_subview(chat_users_group);
		add_subview(input_bar);
	}

	std::shared_ptr<ChatView> chat_log;
	std::shared_ptr<UserListView> user_list;
	std::shared_ptr<uicore::TextFieldView> input_text;
};
