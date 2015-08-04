
#include "precomp.h"
#include "workspace_controller.h"
#include "workspace_page_controller.h"
#include "Views/Workspace/workspace_view.h"

using namespace clan;

WorkspaceController::WorkspaceController()
{
}

void WorkspaceController::add_page(const std::string &label_text, std::shared_ptr<WorkspacePageController> controller, bool app_page)
{
	controller->workspace = this;
	view->add_page(controller->get_page_id(), label_text, controller->view, app_page);
	pages.push_back(controller);
}

void WorkspaceController::set_label(const std::string &id, const std::string &text)
{
	view->set_label(id, text);
}

bool WorkspaceController::is_message_count_hidden(const std::string &id) const
{
	return view->is_message_count_hidden(id);
}

void WorkspaceController::set_message_count(const std::string &id, const std::string &text)
{
	view->set_message_count(id, text);
}
