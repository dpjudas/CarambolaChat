
#include "precomp.h"
#include "chat_window_controller.h"
#include "Controller/Workspace/workspace_controller.h"
#include "Controller/Chat/chat_controller.h"
#include "Controller/Connections/connections_controller.h"
#include "Model/app_model.h"
#include "Model/IRCSession/irc_session.h"

using namespace clan;

ChatWindowViewController::ChatWindowViewController()
{
	view->style()->set("flex-direction: column");

	workspace = std::make_shared<WorkspaceController>();
	view->add_subview(workspace->view);

	slots.connect(AppModel::instance()->cb_irc_session_created, this, &ChatWindowViewController::irc_session_created);

	workspace->add_page("Connection", std::make_shared<ConnectionsController>(), true);
}

void ChatWindowViewController::irc_session_created(IRCSession *session)
{
	slots.connect(session->cb_joined, [=](const IRCChannel &channel) { irc_channel_joined(session, channel); });

	workspace->add_page(session->get_connection_name(), std::make_shared<ChatController>(session, IRCEntity()), false);
}

void ChatWindowViewController::irc_channel_joined(IRCSession *session, const IRCChannel &channel)
{
	workspace->add_page("#" + channel.get_name(), std::make_shared<ChatController>(session, channel), false);
}
