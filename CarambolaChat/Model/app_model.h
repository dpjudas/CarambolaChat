
#pragma once

#include "Model/XMLSettings/xml_settings.h"
#include "Model/IRCSession/irc_session.h"
#include "Model/IdentServer/ident_server.h"
#include "Model/DCCChat/dcc_chat_connection.h"
#include "settings.h"
#include <vector>

class IRCSession;
class IdentServer;
#if defined(XMPP_SUPPORT)
class XMPPSession;
#endif

class AppModel
{
public:
	AppModel();
	~AppModel();

	static AppModel *instance();

	Settings settings;

	uicore::Signal<void(XMLSettings connection)> sig_connection_added;
	uicore::Signal<void(XMLSettings connection)> sig_connection_edited;
	uicore::Signal<void(const std::string &name)> sig_connection_removed;

	void auto_connect_to_servers();
	void connect_to_server(XMLSettings &connection);

	IRCSession *create_irc_session(const std::string &connection_name);
	void destroy_irc_session(IRCSession *session);

#if defined(XMPP_SUPPORT)
	XMPPSession *create_xmpp_session(const std::string &connection_name);
	void destroy_xmpp_session(XMPPSession *session);
#endif

	DCCChatConnection *create_dcc_chat_connection(const std::string &local_nick, const std::string &remote_nick, uicore::SocketName socket_name, bool is_server);
	void destroy_dcc_chat_connection(DCCChatConnection *connection);

	uicore::Signal<void(IRCSession *)> cb_irc_session_created;
	uicore::Signal<void(IRCSession *)> cb_irc_session_destroyed;
#if defined(XMPP_SUPPORT)
	uicore::Signal<void(XMPPSession *)> cb_xmpp_session_created;
	uicore::Signal<void(XMPPSession *)> cb_xmpp_session_destroyed;
#endif
	uicore::Signal<void(DCCChatConnection *)> cb_dcc_chat_connection_created;
	uicore::Signal<void(DCCChatConnection *)> cb_dcc_chat_connection_destroyed;

private:
	std::vector<IRCSession *> irc_sessions;
	std::auto_ptr<IdentServer> ident_server;
#if defined(XMPP_SUPPORT)
	std::vector<XMPPSession *> xmpp_sessions;
#endif
	std::vector<DCCChatConnection *> dcc_chat_connections;

	static AppModel *instance_ptr;
};
