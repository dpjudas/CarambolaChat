
#include "precomp.h"
#include "chat_window_controller.h"
#include "Controller/Workspace/workspace_controller.h"
#include "Controller/Chat/chat_controller.h"
#include "Controller/Connections/connections_controller.h"
#include "Model/app_model.h"
#include "Model/IRCSession/irc_session.h"

using namespace uicore;

ChatWindowViewController::ChatWindowViewController()
{
	workspace = std::make_shared<WorkspaceController>();
	view->add_subview(workspace->view);

	slots.connect(AppModel::instance()->cb_irc_session_created, this, &ChatWindowViewController::irc_session_created);

	workspace->add_page("Connection", std::make_shared<ConnectionsController>(), true);
}

void ChatWindowViewController::irc_session_created(IRCSession *session)
{
	slots.connect(session->cb_joined, [=](const IRCChannel &channel) { irc_channel_joined(session, channel); });
	slots.connect(session->cb_text, [=](const IRCChannel &channel, const IRCNick &nick, const IRCText &text) { irc_connection_text(session, channel, nick, text); });
	slots.connect(session->cb_dcc_file_offer, [=](const IRCFileOffer &offer) { irc_connection_dcc_file_offer(session, offer); });
	slots.connect(session->cb_dcc_chat_offer, [=](const IRCNick &nick, const SocketName &host) { irc_connection_dcc_chat_offer(session, nick, host); });

	workspace->add_page(session->get_connection_name(), std::make_shared<ChatController>(session, IRCEntity()), false);
}

void ChatWindowViewController::irc_channel_joined(IRCSession *session, const IRCChannel &channel)
{
	workspace->add_page("#" + channel.get_name(), std::make_shared<ChatController>(session, channel), false);
}

void ChatWindowViewController::irc_connection_text(IRCSession *session, const IRCEntity &room, const IRCNick &nick, const IRCText &text)
{
	if (!room.is_channel() && workspace->find_page(nick.get_name()) == 0 && !text.is_ctcp())
	{
		auto chat = std::make_shared<ChatController>(session, nick);
		workspace->add_page(nick.get_name(), chat, false);

		chat->add_private_text(nick, text);
	}
}

void ChatWindowViewController::irc_connection_dcc_file_offer(IRCSession *session, const IRCFileOffer &offer)
{
	/*
	if (file_transfer_view == 0)
	{
		file_transfer_view = new FileTransferView(workspace, this);
		workspace->add_view(file_transfer_view);
		workspace->show_view(file_transfer_view);
	}
	file_transfer_view->file_offered(offer, session);
	*/
}

void ChatWindowViewController::irc_connection_dcc_chat_offer(IRCSession *session, const IRCNick &nick, const SocketName &host)
{
	/*
	DCCChatConnection *connection = AppModel::instance()->create_dcc_chat_connection(session->get_nick().get_name(), nick.get_name(), host, false);
	workspace->add_page(nick.get_name(), std::make_shared<ChatController>(connection), false);
	*/
}
