
#include "precomp.h"
#include "taskbar_notification.h"
#ifdef WIN32
#include <shobjidl.h>
#endif

using namespace uicore;

TaskbarNotification::TaskbarNotification(std::shared_ptr<View> init_view) : view(init_view)
{
#ifdef WIN32
	slots.connect(view->sig_activated(), [this](ActivationChangeEvent *e)
	{
		if (e->type() != ActivationChangeType::activated)
			return;

		DisplayWindowPtr dispwindow = view->view_tree()->display_window();
		HWND hwnd = dispwindow->handle().hwnd;

		HRESULT result;
		ComPtr<ITaskbarList3> taskbar_list;
		result = CoCreateInstance(CLSID_TaskbarList, 0, CLSCTX_ALL, __uuidof(taskbar_list), reinterpret_cast<void**>(taskbar_list.output_variable()));
		if (SUCCEEDED(result))
		{
			taskbar_list->SetOverlayIcon(hwnd, nullptr, L"");
		}
	});
#endif
}

void TaskbarNotification::notify()
{
#ifdef WIN32
	DisplayWindowPtr dispwindow = view->view_tree()->display_window();
	if (dispwindow->has_focus() == false)
	{
		HWND hwnd = dispwindow->handle().hwnd;

		FLASHWINFO flash_info = { 0 };
		flash_info.cbSize = sizeof(FLASHWINFO);
		flash_info.hwnd = hwnd;
		flash_info.dwFlags = FLASHW_TRAY;
		flash_info.uCount = 1;
		flash_info.dwTimeout = 0;
		FlashWindowEx(&flash_info);

		HRESULT result;
		ComPtr<ITaskbarList3> taskbar_list;
		result = CoCreateInstance(CLSID_TaskbarList, 0, CLSCTX_ALL, __uuidof(taskbar_list), reinterpret_cast<void**>(taskbar_list.output_variable()));
		if (SUCCEEDED(result))
		{
			HICON icon = create_icon(ImageFile::load("Resources/Icons/taskbar_highlight_icon.png"), hwnd);
			if (icon)
			{
				taskbar_list->SetOverlayIcon(hwnd, icon, L"Chat activity occurred");
				DestroyIcon(icon);
			}
		}
	}
#endif
}

#ifdef WIN32
HBITMAP TaskbarNotification::create_bitmap(HDC hdc, const PixelBufferPtr &image)
{
	PixelBufferPtr bmp_image = image->to_format(tf_bgra8);
	bmp_image->flip_vertical();
	bmp_image->premultiply_alpha();

	BITMAPV5HEADER bmp_header;
	memset(&bmp_header, 0, sizeof(BITMAPV5HEADER));
	bmp_header.bV5Size = sizeof(BITMAPV5HEADER);
	bmp_header.bV5Width = bmp_image->width();
	bmp_header.bV5Height = bmp_image->height();
	bmp_header.bV5Planes = 1;
	bmp_header.bV5BitCount = 32;
	bmp_header.bV5Compression = BI_RGB;

	HBITMAP bitmap = CreateDIBitmap(hdc, (BITMAPINFOHEADER*)&bmp_header, CBM_INIT, bmp_image->data(), (BITMAPINFO *)&bmp_header, DIB_RGB_COLORS);
	return bitmap;
}

HICON TaskbarNotification::create_icon(const PixelBufferPtr &image, HWND hwnd)
{
	HDC hdc = GetDC(hwnd);
	HBITMAP bitmap = create_bitmap(hdc, image);
	if (bitmap == 0)
	{
		ReleaseDC(hwnd, hdc);
		return 0;
	}

	ICONINFO iconinfo;
	memset(&iconinfo, 0, sizeof(ICONINFO));
	iconinfo.fIcon = TRUE;
	iconinfo.hbmColor = bitmap;
	iconinfo.hbmMask = bitmap;
	HICON icon = CreateIconIndirect(&iconinfo);

	DeleteObject(bitmap);
	ReleaseDC(hwnd, hdc);
	return icon;
}
#endif
