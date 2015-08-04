
#pragma once
#include "Controller/ChatWindow/chat_window_controller.h"
#include "Model/app_model.h"

class Program : public clan::Application
{
public:
	Program();
	bool update() override;

	clan::UIThread ui_thread;
	bool exit = false;
	clan::Slot exit_slot;
	AppModel app_model;
	std::shared_ptr<clan::TopLevelWindow> window;
	std::shared_ptr<ChatWindowViewController> chat_window_controller;
};
