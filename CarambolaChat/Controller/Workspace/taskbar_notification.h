
#pragma once

class TaskbarNotification
{
public:
	TaskbarNotification(std::shared_ptr<uicore::View> view);
	void notify();

private:
#ifdef WIN32
	HBITMAP create_bitmap(HDC hdc, const uicore::PixelBufferPtr &image);
	HICON create_icon(const uicore::PixelBufferPtr &image, HWND hwnd);
#endif

	std::shared_ptr<uicore::View> view;
	uicore::PixelBufferPtr icon;
	uicore::SlotContainer slots;
};
