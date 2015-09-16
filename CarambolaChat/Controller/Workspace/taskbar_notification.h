
#pragma once

class TaskbarNotification
{
public:
	TaskbarNotification(std::shared_ptr<uicore::View> view);
	void notify();

private:
#ifdef WIN32
	HBITMAP create_bitmap(HDC hdc, const uicore::PixelBuffer &image);
	HICON create_icon(const uicore::PixelBuffer &image, HWND hwnd);
#endif

	std::shared_ptr<uicore::View> view;
	uicore::PixelBuffer icon;
	uicore::SlotContainer slots;
};
