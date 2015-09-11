
#pragma once

#include "Model/IRCSession/irc_entity.h"

class WorkspaceController;
class IRCSession;
class IRCEntity;
class IRCText;
class IRCFileOffer;
class DCCChatConnection;

class ChatWindowViewController
{
public:
	ChatWindowViewController();

	std::shared_ptr<clan::ColumnView> view = std::make_shared<clan::ColumnView>();
	std::shared_ptr<WorkspaceController> workspace;

private:
	void irc_session_created(IRCSession *session);
	void irc_channel_joined(IRCSession *session, const IRCEntity &channel);
	void irc_connection_text(IRCSession *session, const IRCEntity &room, const IRCNick &nick, const IRCText &text);
	void irc_connection_dcc_file_offer(IRCSession *session, const IRCFileOffer &offer);
	void irc_connection_dcc_chat_offer(IRCSession *session, const IRCNick &nick, const clan::SocketName &host);

	clan::SlotContainer slots;
};
