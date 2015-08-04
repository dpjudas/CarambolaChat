
#include "precomp.h"
#include "workspace_view_controller.h"
#include "workspace_page_view_controller.h"
#include "Views/Workspace/workspace_view.h"

using namespace clan;

WorkspaceViewController::WorkspaceViewController()
{
}

void WorkspaceViewController::add_page(const std::string &label_text, std::shared_ptr<WorkspacePageViewController> controller, bool app_page)
{
	controller->workspace = this;
	view->add_page(controller->get_page_id(), label_text, controller->view, app_page);
	pages.push_back(controller);
}

void WorkspaceViewController::set_label(const std::string &id, const std::string &text)
{
	view->set_label(id, text);
}

bool WorkspaceViewController::is_message_count_hidden(const std::string &id) const
{
	return view->is_message_count_hidden(id);
}

void WorkspaceViewController::set_message_count(const std::string &id, const std::string &text)
{
	view->set_message_count(id, text);
}
