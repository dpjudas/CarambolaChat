
#include "precomp.h"
#include "about_controller.h"

AboutController::AboutController()
{
	set_title("About Carambola Chat");
	set_root_view(about_view);

	slots.connect(about_view->ok_button->sig_clicked(), [=]() { dismiss(); });
}
