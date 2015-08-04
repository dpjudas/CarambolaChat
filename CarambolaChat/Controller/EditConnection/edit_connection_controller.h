
#pragma once

#include "View/EditConnection/edit_connection_view.h"

class EditConnectionController : public clan::WindowController
{
public:
	EditConnectionController(const std::string &title, std::function<void(EditConnectionController *)> ok_clicked);

	std::string connection_name() const { return edit_view->connection_name->value->text(); }
	std::string server() const { return edit_view->server->value->text(); }
	std::string port() const { return edit_view->port->value->text(); }
	std::string nick() const { return edit_view->nick->value->text(); }
	std::string alt_nick() const { return edit_view->alt_nick->value->text(); }
	bool auto_connect() const { return edit_view->auto_connect->value->checked(); }

	void set_connection_name(const std::string v) { edit_view->connection_name->value->set_text(v); }
	void set_server(const std::string v) { edit_view->server->value->set_text(v); }
	void set_port(const std::string v) { edit_view->port->value->set_text(v); }
	void set_nick(const std::string v) { edit_view->nick->value->set_text(v); }
	void set_alt_nick(const std::string v) { edit_view->alt_nick->value->set_text(v); }
	void set_auto_connect(bool v) { edit_view->auto_connect->value->set_check(v); }

private:
	std::shared_ptr<EditConnectionView> edit_view;
};
