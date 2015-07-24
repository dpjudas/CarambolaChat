
#pragma once

class EditConnectionCheckView : public clan::RowView
{
public:
	EditConnectionCheckView(const std::string &label_text = std::string())
	{
		value = add_subview<clan::CheckBoxView>();
		label = add_subview<clan::LabelView>();

		label->set_text(label_text);

		style()->set("margin-bottom: 5px");
		label->style()->set("font: 13px/22px 'Source Sans Pro'");
		value->style()->set("font: 13px/22px 'Source Sans Pro'");
		value->style()->set("background: white");
		value->style()->set("width: 16px; height: 16px; margin: auto 0");
		value->style()->set("border: 1px solid #ccc");
		value->style("checked")->set("background: yellow");
	}

	std::shared_ptr<clan::LabelView> label;
	std::shared_ptr<clan::CheckBoxView> value;
};

class EditConnectionTextView : public clan::RowView
{
public:
	EditConnectionTextView(const std::string &label_text = std::string(), const std::string &placeholder = std::string(), int size = 0)
	{
		label = add_subview<clan::LabelView>();
		value = add_subview<clan::TextFieldView>();

		label->set_text(label_text);

		style()->set("margin-bottom: 5px");
		label->style()->set("width: 150px");
		label->style()->set("font: 13px/22px 'Source Sans Pro'");
		value->style()->set("font: 13px/16px 'Source Sans Pro'");
		value->style()->set("background: white");
		value->style()->set("padding: 2px 5px");
		value->style()->set("border: 1px solid #ccc");

		value->set_placeholder(placeholder);
		
		if (size != 0)
			value->set_preferred_size(size);
		else
			value->style()->set("flex: auto");
	}

	std::shared_ptr<clan::LabelView> label;
	std::shared_ptr<clan::TextFieldView> value;
};

class EditConnectionButtonView : public clan::ButtonView
{
public:
	EditConnectionButtonView(const std::string &text)
	{
		label()->set_text(text);
		label()->set_text_alignment(clan::TextAlignment::center);
		label()->style()->set("font: 13px/16px 'Source Sans Pro'");
		style()->set("background: rgb(245,245,245)");
		style("hot")->set("background: rgb(255,255,255)");
		style()->set("padding: 7px 0; margin-left: 5px");
		style()->set("border: 1px solid #ccc");
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
