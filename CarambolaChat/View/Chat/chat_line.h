
#pragma once

class ChatLine
{
public:
	ChatLine();
	ChatLine(const std::string &nick, const uicore::Colorf &nick_color);

	void add_text(const std::shared_ptr<uicore::Style> &style, const std::string &text, int id = -1);

private:
	struct InlineText
	{
		InlineText(const std::shared_ptr<uicore::Style> &style, const std::string &text, int id) : style(style), text(text), id(id) { }

		std::shared_ptr<uicore::Style> style;
		std::string text;
		int id;
	};

	std::vector<InlineText> inlines;

	bool bold = false;
	std::string timestamp;
	std::string nick;
	uicore::Colorf nick_color = uicore::Colorf::black;
	uicore::SpanLayout column1;
	uicore::SpanLayout column2;
	uicore::SpanLayout column3;
	bool column3_rendered = false;
	int layout_width = 0;
	int prefix_width = 0;

	friend class ChatView;
};
