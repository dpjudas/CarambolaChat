
#include "precomp.h"
#include "network_list_item_view.h"

using namespace uicore;

NetworkListItemView::NetworkListItemView()
{
	style()->set("flex-direction: row");
	style()->set("padding: 5px 0");
	style()->set("background: white"); // Bug: required to make the border work
	style()->set("border-top: 1px solid rgb(204,204,204)");

	status_icon = std::make_shared<ImageBaseView>();
	status_icon->style()->set("flex: none");
	status_icon->style()->set("width: 32px");
	status_icon->style()->set("margin: 0 7px");
	add_child(status_icon);

	auto name_status_block = std::make_shared<View>();
	name_status_block->style()->set("flex: none");
	name_status_block->style()->set("width: 220px");
	name_status_block->style()->set("flex-direction: column");

	name = std::make_shared<LabelBaseView>();
	name->style()->set("font: bold 13px/16px 'Source Sans Pro'");
	name_status_block->add_child(name);

	status_text = std::make_shared<LabelBaseView>();
	status_text->style()->set("font: 13px/16px 'Source Sans Pro'");
	name_status_block->add_child(status_text);

	add_child(name_status_block);

	connect_button = std::make_shared<ButtonBaseView>();
	connect_button->label()->style()->set("font: 13px/16px 'Source Sans Pro'");
	connect_button->label()->style()->set("color: rgb(0,0,128)");
	connect_button->style()->set("flex: none");
	connect_button->style()->set("margin: auto 15px auto 0");
	add_child(connect_button);

	edit_button = std::make_shared<ButtonBaseView>();
	edit_button->label()->set_text("Edit");
	edit_button->label()->style()->set("font: 13px/16px 'Source Sans Pro'");
	edit_button->label()->style()->set("color: rgb(0,0,128)");
	edit_button->style()->set("flex: none");
	edit_button->style()->set("margin: auto 15px auto 0");
	add_child(edit_button);

	remove_button = std::make_shared<ButtonBaseView>();
	remove_button->label()->set_text("Remove");
	remove_button->label()->style()->set("font: 13px/16px 'Source Sans Pro'");
	remove_button->label()->style()->set("color: rgb(0,0,128)");
	remove_button->style()->set("flex: none");
	remove_button->style()->set("margin: auto 0");
	add_child(remove_button);

	set_status_offline("Not Connected");
}

void NetworkListItemView::set_status_online(const std::string &text)
{
	status_icon->set_image(ImageSource::from_resource("Icons/status_online32.png"));
	status_text->set_text(text);
	connect_button->label()->set_text("Disconnect");
}

void NetworkListItemView::set_status_offline(const std::string &text)
{
	status_icon->set_image(ImageSource::from_resource("Icons/status_offline32.png"));
	status_text->set_text(text);
	connect_button->label()->set_text("Connect");
}
