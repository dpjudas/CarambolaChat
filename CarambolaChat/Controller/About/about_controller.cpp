
#include "precomp.h"
#include "about_controller.h"

AboutController::AboutController()
{
	set_title("About Carambola Chat");
	set_root_view(about_view);

	about_view->ok_button->func_clicked() = [=]() { dismiss(); };
}
