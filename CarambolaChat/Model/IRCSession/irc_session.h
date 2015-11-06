
#pragma once

#include "irc_connection.h"
#include "irc_text.h"
#include "irc_message.h"

class IRCJoinedChannel
{
public:
	IRCJoinedChannel() : topic_time(0) { }

	IRCChannel name;
	std::vector<IRCNick> users;
	IRCText topic;
	IRCNick topic_author;
	unsigned int topic_time;
};

class IRCFileOffer
{
public:
	IRCFileOffer() : size(0), size_provided(false) { }

	IRCNick sender;
	std::string filename;
	unsigned int size;
	bool size_provided;
	uicore::SocketName host;
};

class IRCSession
{
public:
	IRCSession();
	~IRCSession();

	void set_perform_list(const std::vector<std::string> &perform_list);

	void connect(const std::string &server, const std::string &port, const std::string &nick, const std::string &alt_nick, const std::string &username, const std::string &full_name);
	void disconnect_graceful(const std::string &quit_message);
	void disconnect_abortive();

	enum ConnectStatus
	{
		status_connecting,
		status_connected,
		status_disconnected
	};

	ConnectStatus get_connect_status() const { return connect_status; }

	void set_connection_name(const std::string &connection_name);
	std::string get_connection_name() const { return connection_name; }

	void set_nick(const std::string &nick);
	IRCNick get_nick() const;

	std::string get_our_hostname() const;

	void join(const IRCChannel &channel);
	void part(const IRCChannel &channel);

	IRCJoinedChannel get_channel_status(const IRCChannel &channel);

	void send_text(const IRCEntity &target, const IRCText &text);
	void send_notice(const IRCEntity &target, const IRCText &text);

	void set_topic(const IRCChannel &channel, const IRCText &text);

	void execute_command(const IRCEntity &filter, std::string command_line);

	uicore::Signal<void(const IRCNick &, const IRCNick &)> cb_nick_changed;
	uicore::Signal<void(const IRCChannel &)> cb_joined;
	uicore::Signal<void(const IRCChannel &)> cb_parted;
	uicore::Signal<void(const IRCChannel &, const IRCNick &)> cb_user_joined;
	uicore::Signal<void(const IRCChannel &, const IRCNick &, const IRCText &)> cb_user_parted;
	uicore::Signal<void(const IRCNick &, const IRCChannel &, const IRCNick &, const IRCText &)> cb_user_kicked;
	uicore::Signal<void(const IRCNick &, const IRCText &)> cb_user_quit;

	uicore::Signal<void(const IRCEntity &, const IRCNick &, const IRCText &)> cb_text;
	uicore::Signal<void(const IRCEntity &, const IRCNick &, const IRCText &)> cb_notice;
	uicore::Signal<void(const IRCEntity &, const IRCNick &, const IRCText &)> cb_action;
	uicore::Signal<void(const IRCText &)> cb_error_text;
	uicore::Signal<void(const IRCText &)> cb_system_text;

	uicore::Signal<void(const IRCNick &, const IRCChannel &, const std::vector<IRCRawString> &)> cb_channel_mode_change;
	uicore::Signal<void(const IRCNick &, const IRCNick &, const std::vector<IRCRawString> &)> cb_nick_mode_change;

	uicore::Signal<void(const IRCChannel &)> cb_channel_topic_updated;
	uicore::Signal<void(const IRCChannel &)> cb_channel_names_updated;

	uicore::Signal<void(ConnectStatus)> cb_connect_status_changed;

	uicore::Signal<void(const IRCFileOffer &)> cb_dcc_file_offer;
	uicore::Signal<void(const IRCNick &, const uicore::SocketName &)> cb_dcc_chat_offer;

private:
	void calculate_ping_interval();
	void set_connect_status(ConnectStatus new_status);

	void set_channel_status(const IRCJoinedChannel &status);

	void on_message_received(const IRCMessage &message);
	void on_disconnected(const std::string &reason);
	void on_numeric_reply(const IRCNumericReply &message);
	void on_rpl_welcome(const IRCNumericReply &message);
	void on_rpl_userhost(const IRCNumericReply &message);
	void on_rpl_namereply(const IRCNumericReply &message);
	void on_rpl_endofnames(const IRCNumericReply &message);
	void on_rpl_topic(const IRCNumericReply &message);
	void on_rpl_topicwhotime(const IRCNumericReply &message);
	void on_rpl_notopic(const IRCNumericReply &message);
	void on_err_nicknameinuse(const IRCNumericReply &message);
	void on_nick(const IRCNickMessage &message);
	void on_join(const IRCJoinMessage &message);
	void on_part(const IRCPartMessage &message);
	void on_kick(const IRCKickMessage &message);
	void on_quit(const IRCQuitMessage &message);
	void on_channel_mode(const IRCChannelModeMessage &message);
	void on_nick_mode(const IRCNickModeMessage &message);
	void on_topic(const IRCTopicMessage &message);
	void on_privmsg(const IRCPrivateMessage &message);
	void on_notice(const IRCNoticeMessage &message);
	void on_ping(const IRCPingMessage &message);
	void on_unknown_message(const IRCMessage &message);

	void extract_ctcp_command(const IRCText &ctcp_data, IRCRawString &command, IRCRawString &data);
	void on_ctcp_privmsg(const IRCRawString &command, const IRCText &data, const IRCPrivateMessage &message);
	void on_ctcp_notice(const IRCRawString &command, const IRCText &data, const IRCNoticeMessage &message);

	void on_ctcp_privmsg_action(const IRCText &data, const IRCPrivateMessage &message);
	void on_ctcp_privmsg_dcc(const IRCText &data, const IRCPrivateMessage &message);
	void on_ctcp_privmsg_finger(const IRCText &data, const IRCPrivateMessage &message);
	void on_ctcp_privmsg_version(const IRCText &data, const IRCPrivateMessage &message);
	void on_ctcp_privmsg_userinfo(const IRCText &data, const IRCPrivateMessage &message);
	void on_ctcp_privmsg_clientinfo(const IRCText &data, const IRCPrivateMessage &message);
	void on_ctcp_privmsg_ping(const IRCText &data, const IRCPrivateMessage &message);
	void on_ctcp_privmsg_time(const IRCText &data, const IRCPrivateMessage &message);

	void on_ctcp_notice_finger(const IRCText &data, const IRCNoticeMessage &message);
	void on_ctcp_notice_version(const IRCText &data, const IRCNoticeMessage &message);
	void on_ctcp_notice_userinfo(const IRCText &data, const IRCNoticeMessage &message);
	void on_ctcp_notice_clientinfo(const IRCText &data, const IRCNoticeMessage &message);
	void on_ctcp_notice_ping(const IRCText &data, const IRCNoticeMessage &message);
	void on_ctcp_notice_time(const IRCText &data, const IRCNoticeMessage &message);

	void on_reconnect_timer_expired();

	std::vector<std::string> split_command_line(std::string command_line);

	IRCNick our_nickname;
	std::string our_hostname;
	std::vector<IRCJoinedChannel> channels;
	IRCConnection connection;
	ConnectStatus connect_status;
	std::vector<std::string> perform_list;

	uicore::TimerPtr reconnect_timer = uicore::Timer::create();
	int reconnect_timeout;
	bool user_requested_disconnect;

	uicore::TimerPtr ping_timeout_timer = uicore::Timer::create();
	int ping_timeout_time = 10 * 1000 * 60;	// 10 minutes

	const int ping_timeout_max_samples = 4;		// We sample 4 times before be are certain about the interval time
	const int ping_timeout_grace_period = 1000*30;
	int ping_timeout_num_samples = 0;
	int ping_timeout_samples_total = 0;
	uint64_t ping_timeout_last_sample_time = 0;

	std::string connection_name;

	std::string connect_nick, alt_connect_nick;
	std::string connect_server, connect_port, connect_username, connect_full_name;

	friend class Command;
};
