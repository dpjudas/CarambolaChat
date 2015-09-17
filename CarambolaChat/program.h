
#pragma once

#include "Model/app_model.h"

class Program : public uicore::Application
{
public:
	Program();

	uicore::UIThread ui_thread;
	AppModel app_model;
};
