
#pragma once

class TaskbarNotification
{
public:
	TaskbarNotification(std::shared_ptr<clan::View> view);
	void notify();

private:
#ifdef WIN32
	HBITMAP create_bitmap(HDC hdc, const clan::PixelBuffer &image);
	HICON create_icon(const clan::PixelBuffer &image, HWND hwnd);
#endif

	std::shared_ptr<clan::View> view;
	clan::PixelBuffer icon;
	clan::SlotContainer slots;
};
