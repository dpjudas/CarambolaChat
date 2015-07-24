
#pragma once

class WorkspaceViewController;
class IRCSession;
class IRCEntity;
class DCCChatConnection;

class ChatWindowViewController : public clan::ViewController
{
public:
	ChatWindowViewController();

	std::shared_ptr<WorkspaceViewController> workspace;

private:
	void irc_session_created(IRCSession *session);
	void irc_channel_joined(IRCSession *session, const IRCEntity &channel);
};
