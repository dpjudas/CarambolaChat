
#pragma once

#include "xmpp_token.h"

class XMPPStanza
{
public:
	XMPPToken stream_token;
	std::vector<XMPPToken> tokens;

	bool empty() const;

	bool is_element(int index, const std::string &local_name, const std::string &namespace_uri) const;
	bool is_text(int index) const;

	std::string get_attribute(int index, const std::string &local_name, const std::string &namespace_uri) const;
	std::string get_text(int index) const;

	int find_child(int index, const std::string &local_name, const std::string &namespace_uri) const;
	int find_parent(int index) const;
	int find_next_sibling(int index) const;

	std::string to_string(int level = 0) const;

private:
	std::string token_to_string(int index) const;
	std::string get_namespace_uri(const std::string &xmlns, int index) const;
	static std::string get_prefix(const std::string &tag);
	static std::string get_local_name(const std::string &tag);
};
