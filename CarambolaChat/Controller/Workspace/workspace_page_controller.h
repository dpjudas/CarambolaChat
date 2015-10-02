
#pragma once

class WorkspaceController;

class WorkspacePageController
{
public:
	WorkspacePageController();

	const std::shared_ptr<uicore::View> &page_view() const { return controller_view; }
	void set_page_view(const std::shared_ptr<uicore::View> &new_page_view);

	const std::string &get_page_id() const { return page_id; }

	void set_tab_title(const std::string &text);
	void increment_message_count();

	void close();

protected:
	virtual void close_clicked() { }

private:
	static std::string generate_page_id() { int id = next_page_id++; return uicore::Text::to_string(id); }
	static int next_page_id;

	std::shared_ptr<uicore::View> controller_view = std::make_shared<uicore::View>();

	WorkspaceController *workspace = nullptr;
	std::string page_id = generate_page_id();

	int message_count = 0;

	friend class WorkspaceController;
};
