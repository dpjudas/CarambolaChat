
#pragma once

#include "Model/XMLSettings/xml_settings.h"

class Settings
{
public:
	Settings();
	~Settings();

	XMLSettings xml_settings;

	uicore::Rect get_window_geometry();
	void set_window_geometry(const uicore::Rect &rect);

	bool get_minimize_to_tray();
	void set_minimize_to_tray(bool enable_minimize_to_tray);

	std::string get_dcc_port();
	void set_dcc_port(const std::string &port);

private:
	XMLSettings load_settings(const std::string &settings_file);
	void save_settings(const std::string &settings_file, XMLSettings settings);
};
