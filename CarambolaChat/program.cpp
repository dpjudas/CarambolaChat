
#include "precomp.h"
#include "program.h"
#include "Controller/ChatWindow/chat_window_controller.h"

using namespace uicore;

ApplicationInstance<Program> app;

Program::Program()
{
	std::string resource_path = "Resources";

#ifdef __APPLE__
	resource_path = Directory::get_resourcedata("CarambolaChat", resource_path);
#endif

	ui_thread = UIThread(resource_path);

	UIThread::add_font_face("font-family: 'Source Sans Pro'", "SourceSansPro/SourceSansPro-Regular.ttf");
	UIThread::add_font_face("font-family: 'Source Sans Pro'; font-weight: bold", "SourceSansPro/SourceSansPro-Bold.ttf");
	UIThread::add_font_face("font-family: 'Source Sans Pro'; font-style: italic", "SourceSansPro/SourceSansPro-Italic.ttf");
	UIThread::add_font_face("font-family: 'Source Sans Pro'; font-weight: bold; font-style: italic", "SourceSansPro/SourceSansPro-BoldItalic.ttf");

	WindowManager::present_main<ChatWindowViewController>();
}
