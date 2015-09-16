
#pragma once
#include "Controller/ChatWindow/chat_window_controller.h"
#include "Model/app_model.h"

class Program : public uicore::Application
{
public:
	Program();
	bool update() override;

	uicore::UIThread ui_thread;
	bool exit = false;
	uicore::Slot exit_slot;
	AppModel app_model;
	std::shared_ptr<uicore::TopLevelWindow> window;
	std::shared_ptr<ChatWindowViewController> chat_window_controller;
};
