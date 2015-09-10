
#pragma once

#include "xmpp_stanza.h"

class XMPPConnectionQueues
{
public:
	void reset();
	void push_send(const XMPPStanza &stanza);
	XMPPStanza pop_send();
	void push_received(const XMPPStanza &stanza);
	XMPPStanza pop_received();
	void set_disconnected(const std::string &reason);
	bool pop_disconnected(std::string &out_reason);

	CL_Event send_event;

private:
	CL_Mutex mutex;
	std::vector<XMPPStanza> send_queue;
	std::vector<XMPPStanza> receive_queue;
	CL_InterlockedVariable disconnected;
	std::string disconnected_reason;
};
