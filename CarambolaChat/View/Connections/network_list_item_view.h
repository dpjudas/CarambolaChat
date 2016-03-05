
#pragma once

class NetworkListItemView : public uicore::View
{
public:
	NetworkListItemView();

	void set_name(const std::string &value) { name->set_text(value); }
	void set_status_online(const std::string &status_text);
	void set_status_offline(const std::string &status_text);

	std::shared_ptr<uicore::ButtonBaseView> connect_button;
	std::shared_ptr<uicore::ButtonBaseView> edit_button;
	std::shared_ptr<uicore::ButtonBaseView> remove_button;

private:
	std::shared_ptr<uicore::LabelBaseView> name;
	std::shared_ptr<uicore::ImageBaseView> status_icon;
	std::shared_ptr<uicore::LabelBaseView> status_text;
};
