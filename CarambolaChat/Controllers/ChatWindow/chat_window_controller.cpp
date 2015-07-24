
#include "precomp.h"
#include "chat_window_controller.h"
#include "Controllers/Workspace/workspace_view_controller.h"
#include "Controllers/Chat/chat_view_controller.h"
#include "Controllers/Connections/connections_view_controller.h"
#include "Models/app_model.h"
#include "Models/IRCSession/irc_session.h"

using namespace clan;

ChatWindowViewController::ChatWindowViewController()
{
	view->style()->set("flex-direction: column");

	workspace = std::make_shared<WorkspaceViewController>();
	add_child_controller(workspace);

	slots.connect(AppModel::instance()->cb_irc_session_created, this, &ChatWindowViewController::irc_session_created);

	workspace->add_page("Connection", std::make_shared<ConnectionsViewController>(), true);
}

void ChatWindowViewController::irc_session_created(IRCSession *session)
{
	slots.connect(session->cb_joined, [=](const IRCChannel &channel) { irc_channel_joined(session, channel); });

	workspace->add_page(session->get_connection_name(), std::make_shared<ChatViewController>(session, IRCEntity()), false);
}

void ChatWindowViewController::irc_channel_joined(IRCSession *session, const IRCChannel &channel)
{
	workspace->add_page("#" + channel.get_name(), std::make_shared<ChatViewController>(session, channel), false);
}
