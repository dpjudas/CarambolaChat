
#include "precomp.h"
#include "edit_connection_controller.h"

using namespace clan;

EditConnectionController::EditConnectionController(const std::string &title, std::function<void(EditConnectionController *)> ok_clicked)
{
	set_title(title);

	edit_view = root_view()->add_subview<EditConnectionView>();

	root_view()->style()->set("background: rgb(240,240,240)");
	root_view()->style()->set("flex-direction: column");

	edit_view->button_bar->ok_button->func_clicked() = [=]() { ok_clicked(this); dismiss(); };
	edit_view->button_bar->cancel_button->func_clicked() = [this]() { dismiss(); };
}
