
#pragma once

#include "Views/Workspace/workspace_view.h"

class WorkspacePageViewController;

class WorkspaceViewController
{
public:
	WorkspaceViewController();

	std::shared_ptr<WorkspaceView> view = std::make_shared<WorkspaceView>();

	void add_page(const std::string &label, std::shared_ptr<WorkspacePageViewController> controller, bool app_page);

private:
	void set_label(const std::string &id, const std::string &text);
	bool is_message_count_hidden(const std::string &id) const;
	void set_message_count(const std::string &id, const std::string &text);

	std::vector<std::shared_ptr<WorkspacePageViewController>> pages;

	friend class WorkspacePageViewController;
};
