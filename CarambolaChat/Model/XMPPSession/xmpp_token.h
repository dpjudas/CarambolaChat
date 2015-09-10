
#pragma once

class XMPPAttribute
{
public:
	XMPPAttribute(const std::string &name, const std::string &value) : name(name), value(value) { }
	std::string name;
	std::string value;
};

class XMPPToken
{
public:
	XMPPToken() : type(type_null) { }

	enum Type
	{
		type_null,
		type_begin,
		type_end,
		type_single,
		type_text
	};
	Type type;
	std::string name;
	std::vector<XMPPAttribute> attributes;
	std::string value;
};
