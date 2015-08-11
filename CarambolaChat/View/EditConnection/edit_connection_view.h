
#pragma once

#include "View/Theme/theme_views.h"

class EditConnectionCheckView : public clan::RowView
{
public:
	EditConnectionCheckView(const std::string &label_text = std::string())
	{
		value = add_subview<ThemeCheckBoxView>();
		label = add_subview<ThemeLabelView>();

		label->set_text(label_text);

		style()->set("margin-bottom: 5px");
		value->style()->set("margin: auto 3px auto 0");
	}

	std::shared_ptr<ThemeLabelView> label;
	std::shared_ptr<ThemeCheckBoxView> value;
};

class EditConnectionTextView : public clan::RowView
{
public:
	EditConnectionTextView(const std::string &label_text = std::string(), const std::string &placeholder = std::string(), int size = 0)
	{
		label = add_subview<ThemeLabelView>();
		value = add_subview<ThemeTextFieldView>();

		label->set_text(label_text);

		style()->set("margin-bottom: 5px");
		label->style()->set("width: 150px");

		value->set_placeholder(placeholder);
		
		if (size != 0)
			value->set_preferred_size(size);
		else
			value->style()->set("flex: auto");
	}

	std::shared_ptr<ThemeLabelView> label;
	std::shared_ptr<ThemeTextFieldView> value;
};

class EditConnectionButtonView : public ThemeButtonView
{
public:
	EditConnectionButtonView(const std::string &text)
	{
		label()->set_text(text);
		style()->set("margin-left: 5px");
		style()->set("width: 75px");
	}
};

class EditConnectionButtonBarView : public clan::RowView
{
public:
	EditConnectionButtonBarView()
	{
		add_subview<clan::SpacerView>();
		ok_button = add_subview<EditConnectionButtonView>("OK");
		cancel_button = add_subview<EditConnectionButtonView>("Cancel");

		style()->set("margin-top: 30px");
	}

	std::shared_ptr<EditConnectionButtonView> ok_button;
	std::shared_ptr<EditConnectionButtonView> cancel_button;
};

class EditConnectionView : public clan::ColumnView
{
public:
	EditConnectionView()
	{
		connection_name = add_subview<EditConnectionTextView>("Connection name", "Some IRC Network");
		server = add_subview<EditConnectionTextView>("Server", "irc.server.net", 30);
		port = add_subview<EditConnectionTextView>("Port", "6667", 6);
		nick = add_subview<EditConnectionTextView>("Nick", "name", 20);
		alt_nick = add_subview<EditConnectionTextView>("Alternative nick", "alternative name", 20);
		auto_connect = add_subview<EditConnectionCheckView>("Auto connect on startup");
		add_subview<clan::SpacerView>();
		button_bar = add_subview<EditConnectionButtonBarView>();

		style()->set("margin: 11px");
	}

	std::shared_ptr<EditConnectionTextView> connection_name;
	std::shared_ptr<EditConnectionTextView> server;
	std::shared_ptr<EditConnectionTextView> port;
	std::shared_ptr<EditConnectionTextView> nick;
	std::shared_ptr<EditConnectionTextView> alt_nick;
	std::shared_ptr<EditConnectionCheckView> auto_connect;
	std::shared_ptr<EditConnectionButtonBarView> button_bar;
};
