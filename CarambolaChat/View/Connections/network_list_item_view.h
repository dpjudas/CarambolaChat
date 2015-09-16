
#pragma once

class NetworkListItemView : public uicore::View
{
public:
	NetworkListItemView();

	void set_name(const std::string &value) { name->set_text(value); }
	void set_status_online(const std::string &status_text);
	void set_status_offline(const std::string &status_text);

	std::shared_ptr<uicore::ButtonView> connect_button;
	std::shared_ptr<uicore::ButtonView> edit_button;
	std::shared_ptr<uicore::ButtonView> remove_button;

private:
	std::shared_ptr<uicore::LabelView> name;
	std::shared_ptr<uicore::ImageView> status_icon;
	std::shared_ptr<uicore::LabelView> status_text;
};
