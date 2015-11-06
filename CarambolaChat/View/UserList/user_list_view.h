
#pragma once

class UserListView;

class UserListRowView : public uicore::RowView
{
public:
	UserListRowView(UserListView *init_user_list, const std::string &id);

	UserListView *user_list = nullptr;
	std::string id;
	int sort_priority = 0;
	std::shared_ptr<uicore::ImageView> icon;
	std::shared_ptr<uicore::LabelView> label;
};

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

	uicore::Signal<void(std::shared_ptr<UserListRowView> view, uicore::PointerEvent &e)> &sig_context_menu() { return context_menu; }

private:
	std::map<std::string, std::shared_ptr<UserListRowView>> users;
	uicore::Signal<void(std::shared_ptr<UserListRowView> view, uicore::PointerEvent &e)> context_menu;
};

inline UserListRowView::UserListRowView(UserListView *init_user_list, const std::string &id) : user_list(init_user_list), id(id)
{
	style()->set("flex: none");
	style()->set("padding: 5px");
	style()->set("flex-direction: row");

	icon = std::make_shared<uicore::ImageView>();
	icon->style()->set("flex: none");
	add_subview(icon);

	label = std::make_shared<uicore::LabelView>();
	label->style()->set("color: black");
	label->style()->set("font: 12px/15px 'Source Sans Pro'");
	label->style()->set("margin: 0 0 0 5px");
	add_subview(label);

	slots.connect(sig_pointer_release(), [this](uicore::PointerEvent &e)
	{
		if (e.button() == uicore::PointerButton::right)
			user_list->sig_context_menu()(std::dynamic_pointer_cast<UserListRowView>(shared_from_this()), e);
	});
}
