
#include "precomp.h"
#include "edit_connection_controller.h"
#include "Model/app_model.h"
#include "Model/XMLSettings/xml_settings.h"
#include "Model/XMLSettings/xml_settings_list.h"

using namespace uicore;

EditConnectionController::EditConnectionController() : add_dialog(true)
{
	set_title("Add Connection");
	set_root_view(edit_view);

	slots.connect(edit_view->button_bar->ok_button->sig_clicked(), bind_member(this, &EditConnectionController::ok_clicked));
	slots.connect(edit_view->button_bar->cancel_button->sig_clicked(), bind_member(this, &EditConnectionController::cancel_clicked));
}

EditConnectionController::EditConnectionController(XMLSettings connection) : connection(connection)
{
	set_title("Edit Connection");
	set_root_view(edit_view);

	slots.connect(edit_view->button_bar->ok_button->sig_clicked(), bind_member(this, &EditConnectionController::ok_clicked));
	slots.connect(edit_view->button_bar->cancel_button->sig_clicked(), bind_member(this, &EditConnectionController::cancel_clicked));

	edit_view->connection_name->value->set_text(connection.get_string("connectionname"));
	edit_view->server->value->set_text(connection.get_string("server"));
	edit_view->nick->value->set_text(connection.get_string("nick"));
	edit_view->alt_nick->value->set_text(connection.get_string("altnick"));
	edit_view->auto_connect->value->set_check(connection.get_bool("autoconnect"));

	XMLSettingsList performlist = connection.get_list("performlist");
	std::string lines;
	int perform_count = performlist.get_count();
	for (int i = 0; i<perform_count; i++)
	{
		XMLSettings item = performlist.get(i);
		if (!lines.empty())
			lines.push_back('\n');
		lines += item.get_string("command");
	}
	edit_view->perform_list->set_text(lines);
}

void EditConnectionController::ok_clicked()
{
	if (add_dialog)
	{
		XMLSettingsList connections = AppModel::instance()->settings.xml_settings.get_list("connections");
		connection = connections.add();
		connection.set_string("username", "carambola");
		connection.set_string("name", "Anonymous Carambola User");
		connection.set_string("comment", "");
	}

	connection.set_string("connectioname", edit_view->connection_name->value->text());
	connection.set_string("server", edit_view->server->value->text());
	connection.set_string("nick", edit_view->nick->value->text());
	connection.set_string("altnick", edit_view->alt_nick->value->text());
	connection.set_bool("autoconnect", edit_view->auto_connect->value->checked());

	XMLSettingsList performlist = connection.get_list("performlist");

	std::vector<std::string> lines = Text::split(edit_view->perform_list->text(), "\n", true);
	int perform_count = performlist.get_count();
	for (int i = 0; i < perform_count; i++)
		performlist.remove(0);

	for (size_t i = 0; i < lines.size(); i++)
	{
		XMLSettings item = performlist.add();
		item.set_string("command", lines[i]);
	}

	if (add_dialog)
		AppModel::instance()->sig_connection_added(connection);
	else
		AppModel::instance()->sig_connection_edited(connection);

	dismiss();
}

void EditConnectionController::cancel_clicked()
{
	dismiss();
}
