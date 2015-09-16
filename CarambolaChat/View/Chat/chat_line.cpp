
#include "precomp.h"
#include "chat_line.h"

using namespace uicore;

ChatLine::ChatLine()
{
}

ChatLine::ChatLine(const std::string &nick, const uicore::Colorf &nick_color) : nick(nick), nick_color(nick_color)
{
}

void ChatLine::add_text(const std::shared_ptr<uicore::Style> &style, const std::string &text, int id)
{
	inlines.push_back(InlineText(style, text, id));
}
