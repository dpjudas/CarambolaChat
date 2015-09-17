
#include "precomp.h"
#include "program.h"

using namespace uicore;

uicore::ApplicationInstance<Program> app;

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

	chat_window_controller = std::make_shared<ChatWindowViewController>();

	exit_slot = chat_window_controller->view->sig_close().connect([&](CloseEvent &e) { exit = true; });

	DisplayWindowDescription desc;
	desc.set_title("Carambola Chat");
	desc.set_allow_resize(true);
	desc.set_size(uicore::Size(1536, 864), false);

	window = std::make_shared<TopLevelWindow>(desc);
	window->set_root_view(chat_window_controller->view);
	window->get_display_window().set_large_icon(ImageFile::load(PathHelp::combine(resource_path, "Icons/carambola-256.png")));
	window->get_display_window().set_small_icon(ImageFile::load(PathHelp::combine(resource_path, "Icons/carambola-32.png")));
	window->show(WindowShowType::show_default);

	Application::use_timeout_timing(250);
}

bool Program::update()
{
	return !exit;
}
