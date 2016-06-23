
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
	uicore::Colorf nick_color = uicore::StandardColorf::black();
	uicore::TextBlockPtr column1 = uicore::TextBlock::create();
	uicore::TextBlockPtr column2 = uicore::TextBlock::create();
	uicore::TextBlockPtr column3 = uicore::TextBlock::create();
	bool column3_rendered = false;
	float layout_width = 0;
	float prefix_width = 0;

	friend class ChatView;
};
