
#include "precomp.h"
#include "workspace_controller.h"
#include "workspace_page_controller.h"
#include "View/Workspace/workspace_view.h"

using namespace clan;

WorkspaceController::WorkspaceController()
{
	taskbar = clan::make_unique<TaskbarNotification>(view);
}

void WorkspaceController::add_page(const std::string &label_text, std::shared_ptr<WorkspacePageController> controller, bool app_page)
{
	controller->workspace = this;
	WorkspacePageController *controller_ptr = controller.get();
	view->add_page(controller->get_page_id(), label_text, controller->page_view(), app_page, [=]() { controller_ptr->close_clicked(); });
	pages.push_back(controller);
}

std::shared_ptr<WorkspacePageController> WorkspaceController::find_page(const std::string &label)
{
	for (auto &page : pages)
	{
		if (view->label(page->get_page_id()) == label)
			return page;
	}
	return std::shared_ptr<WorkspacePageController>();
}

void WorkspaceController::remove_page(WorkspacePageController *controller)
{
	controller->workspace = nullptr;
	view->remove_page(controller->page_view());
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

	if (!text.empty())
		taskbar->notify();
}
