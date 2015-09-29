
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

	WindowManager::present_main<ChatWindowViewController>();
}
