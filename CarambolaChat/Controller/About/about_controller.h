
#pragma once

#include "View/About/about_view.h"

class AboutController : public clan::WindowController
{
public:
	AboutController();

private:
	std::shared_ptr<AboutView> about_view = std::make_shared<AboutView>();
};
