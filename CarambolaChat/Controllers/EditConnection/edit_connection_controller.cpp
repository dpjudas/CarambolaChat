
#include "precomp.h"
#include "edit_connection_controller.h"

using namespace clan;

EditConnectionController::EditConnectionController(std::function<void(EditConnectionController *)> ok_clicked)
{
	edit_view = view->add_subview<EditConnectionView>();

	view->style()->set("background: rgb(240,240,240)");
	view->style()->set("flex-direction: column");

	edit_view->button_bar->ok_button->func_clicked() = [=]() { ok_clicked(this); dismiss_modal(); };
	edit_view->button_bar->cancel_button->func_clicked() = [this]() { dismiss_modal(); };
}
