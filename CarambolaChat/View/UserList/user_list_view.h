
#pragma once

class UserListView : public uicore::ScrollView
{
public:
	UserListView();

	void update_user(const std::string &id, const std::string &name, const std::string &icon, int sort_priority);
	void remove_user(const std::string &id);
	void rename_user(const std::string &old_id, const std::string &new_id, const std::string &name);
	bool has_user(const std::string &id) const { return users.find(id) != users.end(); }
	void sort();
	void clear();

private:
	struct User
	{
		int sort_priority = 0;
		std::shared_ptr<uicore::View> view;
		std::shared_ptr<uicore::ImageView> icon;
		std::shared_ptr<uicore::LabelView> label;
	};

	std::map<std::string, User> users;
};
