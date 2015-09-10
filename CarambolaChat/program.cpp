
#include "precomp.h"
#include "program.h"

#ifdef __APPLE__
#include <CoreFoundation/CoreFoundation.h>
#endif

using namespace clan;

clan::ApplicationInstance<Program> clanapp;

class DisplayResources : public DisplayCache
{
public:
#ifdef __APPLE__
	DisplayResources()
	{
		resource_path() = Directory::get_resourcedata("CarambolaChat", resource_path());
	}
#endif
	
	Resource<Sprite> get_sprite(Canvas &canvas, const std::string &id) override { throw Exception("No sprite resources"); }
	Resource<Texture> get_texture(GraphicContext &gc, const std::string &id) override { throw Exception("No texture resources"); }

	Resource<Image> get_image(Canvas &canvas, const std::string &id) override
	{
		if (loaded_images.find(id) == loaded_images.end())
		{
			loaded_images[id] = Image(canvas, PathHelp::combine(resource_path(), id));
		}
		return loaded_images[id];
	}

	Resource<Font> get_font(Canvas &canvas, const std::string &family_name, const FontDescription &desc) override
	{
		if (loaded_fonts.find(family_name) == loaded_fonts.end())
		{
			if (family_name == "Source Sans Pro")
			{
				FontFamily family(family_name);

				FontDescription normal;
				family.add(normal, PathHelp::combine(resource_path(), "SourceSansPro/SourceSansPro-Regular.ttf"));

				FontDescription bold;
				bold.set_weight(FontWeight::bold);
				family.add(bold, PathHelp::combine(resource_path(), "SourceSansPro/SourceSansPro-Bold.ttf"));

				FontDescription italic;
				italic.set_style(FontStyle::italic);
				family.add(italic, PathHelp::combine(resource_path(), "SourceSansPro/SourceSansPro-Italic.ttf"));

				FontDescription bold_italic;
				bold_italic.set_weight(FontWeight::bold);
				bold_italic.set_style(FontStyle::italic);
				family.add(bold_italic, PathHelp::combine(resource_path(), "SourceSansPro/SourceSansPro-BoldItalic.ttf"));

				loaded_fonts[family_name] = family;
			}
			else
			{
				loaded_fonts[family_name] = FontFamily(family_name);
			}
		}
		return Font(loaded_fonts[family_name], desc);
	}

	static std::string &resource_path()
	{
		static std::string resource_path = "Resources";
		return resource_path;
	}

private:
	std::map<std::string, FontFamily > loaded_fonts;
	std::map<std::string, Resource<Image>> loaded_images;
};

Program::Program()
{
	/*
	#ifndef _DEBUG
	std::string appdata_dir = clan::Directory::get_appdata("ClanLib", "Carambola", "1.0");
	CrashReporter crash_reporter(appdata_dir);

	DetectHang detect_hang;
	#endif
	*/
#ifdef WIN32
	D3DTarget::enable();
#else
	OpenGLTarget::set_current();
#endif

	ResourceManager resources;
	DisplayCache::set(resources, std::make_shared<DisplayResources>());

	ui_thread = UIThread(resources);

	chat_window_controller = std::make_shared<ChatWindowViewController>();

	exit_slot = chat_window_controller->view->sig_close().connect([&](CloseEvent &e) { exit = true; });

	DisplayWindowDescription desc;
	desc.set_title("Carambola Chat");
	desc.set_allow_resize(true);
	desc.set_size(clan::Size(1536, 864), false);

	window = std::make_shared<TopLevelWindow>(desc);
	window->set_root_view(chat_window_controller->view);
	window->get_display_window().set_large_icon(ImageProviderFactory::load(PathHelp::combine(DisplayResources::resource_path(), "Icons/carambola-256.png")));
	window->get_display_window().set_small_icon(ImageProviderFactory::load(PathHelp::combine(DisplayResources::resource_path(), "Icons/carambola-32.png")));
	window->show(WindowShowType::show_default);

	Application::use_timeout_timing(250);
}

bool Program::update()
{
	return !exit;
}

