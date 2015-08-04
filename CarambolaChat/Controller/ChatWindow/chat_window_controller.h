
#pragma once

class WorkspaceController;
class IRCSession;
class IRCEntity;
class DCCChatConnection;

class ChatWindowViewController
{
public:
	ChatWindowViewController();

	std::shared_ptr<clan::View> view = std::make_shared<clan::View>();
	std::shared_ptr<WorkspaceController> workspace;

private:
	void irc_session_created(IRCSession *session);
	void irc_channel_joined(IRCSession *session, const IRCEntity &channel);

	clan::SlotContainer slots;
};
