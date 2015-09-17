
#pragma once

#include "Controller/Workspace/workspace_page_controller.h"
#include "Model/IRCSession/irc_session.h"
#include "View/Connections/connections_view.h"

class XMLSettings;

class ConnectionsController : public WorkspacePageController
{
public:
	ConnectionsController();

private:
	void add_clicked();
	void connect_clicked(XMLSettings connection);
	void edit_clicked(XMLSettings connection);
	void remove_clicked(XMLSettings connection);

	void on_irc_session_created(IRCSession *session);
	void on_irc_session_destroyed(IRCSession *session);
#if defined(XMPP_SUPPORT)
	void on_xmpp_session_created(XMPPSession *session);
	void on_xmpp_session_destroyed(XMPPSession *session);
	void on_xmpp_session_error_text(const CL_String &text, XMPPSession *session);
	void on_xmpp_session_roster_updated(XMPPSession *session);
#endif
	void on_session_connect_status_changed(IRCSession::ConnectStatus status, IRCSession *session);

	std::shared_ptr<ConnectionsView> view = std::make_shared<ConnectionsView>();
	uicore::SlotContainer slots;
};
