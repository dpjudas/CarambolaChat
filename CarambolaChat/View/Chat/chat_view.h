
#pragma once

#include <list>

class IRCSession;
class ChatLine;
class ChatTextView;

class ChatView : public uicore::View
{
public:
	ChatView();
	~ChatView();

	struct TextPosition
	{
		TextPosition() : line(-1), column(0), offset(0), id(-1) { }
		bool operator ==(const TextPosition &other) const { return line == other.line && column == other.column && offset == other.offset; }
		bool operator !=(const TextPosition &other) const { return line != other.line || column != other.column || offset != other.offset; }
		int line, column, offset, id;
	};

	struct Selection
	{
		TextPosition start, end;
	};

	void add_line(ChatLine text);

	TextPosition hit_test(const uicore::Pointf &pos);
	void set_selection(const TextPosition &start, const TextPosition &end);
	void copy_to_clipboard();

	uicore::Colorf get_color_text();
	uicore::Colorf get_color_channel();
	uicore::Colorf get_color_system();
	uicore::Colorf get_color_nick_others();
	uicore::Colorf get_color_nick();
	uicore::Colorf get_color_timestamp();
	uicore::Colorf get_color_url();

	void scroll_page_up();
	void scroll_page_down();

	uicore::FontPtr font, font_url, font_fixed;

	uicore::Signal<void(int/* object_id*/)> cb_url_clicked;

	void layout_children(const uicore::CanvasPtr &canvas) override;

private:
	void render_text_content(ChatTextView *text_view, const uicore::CanvasPtr &canvas);

	void on_scroll();
	void on_pointer_press(uicore::PointerEvent &e);
	void on_pointer_release(uicore::PointerEvent &e);
	void on_pointer_move(uicore::PointerEvent &e);

	TextPosition hit_test_line_column(const uicore::CanvasPtr &canvas, int line, int column, const uicore::TextBlockPtr &span_layout, const uicore::Pointf &pos);
	static int offset_for_line_column(int line_index, int column, const TextPosition &pos);

	void append_column_text(int line, int column, ChatLine &chatline, std::string prefix, std::string postfix, std::string &out_text);

	std::string create_timestamp();
	void layout_line(const uicore::CanvasPtr &canvas, ChatLine &line, uicore::Rectf &client_area, int line_index);
	std::pair<int,int> get_selection_for_line(int line_index, int column);
	float get_prefix_width() const;
	void invalidate_lines(int start, int end);

	std::shared_ptr<ChatTextView> text_view;
	std::shared_ptr<uicore::ScrollBarBaseView> scroll;
	std::list<ChatLine> lines;
	uicore::SlotContainer slots;
	Selection selection;

	float prefix_width = 60;
	float column1_width = 0;
	float baseline_offset1 = 0;

	bool mouse_down = false;
	TextPosition mouse_down_text_position;

	friend class ChatTextView;
};

class ChatTextView : public uicore::View
{
public:
	ChatTextView(ChatView *chat_view) : chat_view(chat_view) { }
	void render_content(const uicore::CanvasPtr &canvas) override { chat_view->render_text_content(this, canvas); }

private:
	ChatView *chat_view;
};
