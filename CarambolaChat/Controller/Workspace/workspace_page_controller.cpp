
#include "precomp.h"
#include "workspace_page_controller.h"
#include "workspace_controller.h"

using namespace clan;

WorkspacePageController::WorkspacePageController()
{
	controller_view->style()->set("flex: auto");
}

void WorkspacePageController::set_page_view(const std::shared_ptr<clan::View> &new_page_view)
{
	controller_view = new_page_view;
	controller_view->style()->set("flex: auto");
}

void WorkspacePageController::close()
{
	if (workspace)
		workspace->remove_page(this);
}

void WorkspacePageController::set_tab_title(const std::string &text)
{
	if (workspace)
		workspace->set_label(page_id, text);
}

void WorkspacePageController::increment_message_count()
{
	if (workspace)
	{
		if (workspace->is_message_count_hidden(page_id))
			message_count = 0;
		message_count++;
		workspace->set_message_count(page_id, StringHelp::int_to_text(message_count));
	}
}

int WorkspacePageController::next_page_id = 0;
