
#include "precomp.h"
#include "program.h"
#include "Controller/ChatWindow/chat_window_controller.h"

using namespace uicore;

ApplicationInstance<Program> app;

Program::Program()
{
	UIThread::add_font_face("font-family: 'Source Sans Pro'", "SourceSansPro/SourceSansPro-Regular.ttf");
	UIThread::add_font_face("font-family: 'Source Sans Pro'; font-weight: bold", "SourceSansPro/SourceSansPro-Bold.ttf");
	UIThread::add_font_face("font-family: 'Source Sans Pro'; font-style: italic", "SourceSansPro/SourceSansPro-Italic.ttf");
	UIThread::add_font_face("font-family: 'Source Sans Pro'; font-weight: bold; font-style: italic", "SourceSansPro/SourceSansPro-BoldItalic.ttf");
	UIThread::add_font_face("font-family: 'Noto Sans'", "NotoSans/NotoSans-Regular.ttf");
	UIThread::add_font_face("font-family: 'Noto Sans'; font-weight: bold", "NotoSans/NotoSans-Bold.ttf");
	UIThread::add_font_face("font-family: 'Noto Sans'; font-style: italic", "NotoSans/NotoSans-Italic.ttf");
	UIThread::add_font_face("font-family: 'Noto Sans'; font-weight: bold; font-style: italic", "NotoSans/NotoSans-BoldItalic.ttf");

	WindowManager::present_main<ChatWindowViewController>();
}
