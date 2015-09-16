
#include "precomp.h"
#include "connections_controller.h"
#include "Controller/EditConnection/edit_connection_controller.h"
#include "Controller/About/about_controller.h"
#include "View/Connections/network_list_view.h"
#include "View/Connections/network_list_item_view.h"
#include "Model/XMLSettings/xml_settings_list.h"
#include "Model/app_model.h"

using namespace uicore;

ConnectionsController::ConnectionsController()
{
	set_page_view(view);

	slots.connect(AppModel::instance()->cb_irc_session_created, this, &ConnectionsController::on_irc_session_created);
	slots.connect(AppModel::instance()->cb_irc_session_destroyed, this, &ConnectionsController::on_irc_session_destroyed);

#if defined(XMPP_SUPPORT)
	slots.connect(AppModel::instance()->cb_xmpp_session_created, this, &ConnectionsController::on_xmpp_session_created);
	slots.connect(AppModel::instance()->cb_xmpp_session_destroyed, this, &ConnectionsController::on_xmpp_session_destroyed);
#endif

	XMLSettingsList connections = AppModel::instance()->settings.xml_settings.get_list("connections");
	int connection_count = connections.get_count();
	for (int i = 0; i < connection_count; ++i)
	{
		XMLSettings connection = connections.get(i);
		std::string name = connection.get_string("connectionname");
		auto item = view->networks->add_item(name);

		slots.connect(item->connect_button->sig_pointer_release(), [=](PointerEvent &) { connect_clicked(connection); });
		slots.connect(item->edit_button->sig_pointer_release(), [=](PointerEvent &) { edit_clicked(connection); });
		slots.connect(item->remove_button->sig_pointer_release(), [=](PointerEvent &) { remove_clicked(connection); });
	}

	slots.connect(AppModel::instance()->sig_connection_added, [this](XMLSettings connection)
	{
		std::string name = connection.get_string("connectionname");
		auto item = view->networks->add_item(name);

		slots.connect(item->connect_button->sig_pointer_release(), [=](PointerEvent &) { connect_clicked(connection); });
		slots.connect(item->edit_button->sig_pointer_release(), [=](PointerEvent &) { edit_clicked(connection); });
		slots.connect(item->remove_button->sig_pointer_release(), [=](PointerEvent &) { remove_clicked(connection); });
	});

	slots.connect(AppModel::instance()->sig_connection_edited, [this](XMLSettings connection)
	{
	});

	slots.connect(AppModel::instance()->sig_connection_removed, [this](const std::string &connection_name)
	{
	});

	view->networks->add_button->func_clicked() = [this]() { add_clicked(); };
	view->about_button->func_clicked() = [this]() { windows.present_modal<AboutController>(view.get()); };
}

void ConnectionsController::add_clicked()
{
	windows.present_modal<EditConnectionController>(view.get());
}

void ConnectionsController::connect_clicked(XMLSettings connection)
{
	AppModel::instance()->connect_to_server(connection);
}

void ConnectionsController::edit_clicked(XMLSettings connection)
{
	windows.present_modal<EditConnectionController>(view.get(), connection);
}

void ConnectionsController::remove_clicked(XMLSettings connection)
{
}

void ConnectionsController::on_irc_session_created(IRCSession *session)
{
	slots.connect(session->cb_connect_status_changed, [=](IRCSession::ConnectStatus status) { on_session_connect_status_changed(status, session); });
}

void ConnectionsController::on_irc_session_destroyed(IRCSession *session)
{
	auto item = view->networks->get_item(session->get_connection_name());
	if (item)
	{
		item->set_status_offline("Not connected");
	}
}

#if defined(XMPP_SUPPORT)
void ConnectionsController::on_xmpp_session_created(XMPPSession *session)
{
	slots.connect(session->cb_error_text, this, &ServerListView::on_xmpp_session_error_text, session);
	slots.connect(session->cb_roster_updated, this, &ServerListView::on_xmpp_session_roster_updated, session);
}

void ConnectionsController::on_xmpp_session_destroyed(XMPPSession *session)
{
}

void ConnectionsController::on_xmpp_session_error_text(const CL_String &text, XMPPSession *session)
{
	int count = friends_view->get_item_count(index_group_networks);
	for (int i = 0; i < count; i++)
	{
		ConnectionItem *item = dynamic_cast<ConnectionItem*>(friends_view->get_item(index_group_networks, i));
		if (item && item->get_name() == session->get_connection_name())
		{
			break;
		}
	}
}

void ConnectionsController::on_xmpp_session_roster_updated(XMPPSession *session)
{
	if (index_group_friends == -1)
		index_group_friends = friends_view->add_group("Friends");
	else
		friends_view->clear_group(index_group_friends);

	std::vector<XMPPRosterItem> roster = session->get_roster();
	for (size_t i = 0; i < roster.size(); i++)
	{
		CL_Image icon = icon_offline;
		switch (roster[i].show_type)
		{
		case show_offline: icon = icon_offline; break;
		case show_away: icon = icon_away; break;
		case show_chat: icon = icon_chat; break;
		case show_dnd: icon = icon_dnd; break;
		case show_extended_away: icon = icon_extended_away; break;
		}
		FriendsViewItem *item = new FriendsViewItem(icon, roster[i].name, roster[i].show_text);
		friends_view->add_item(index_group_friends, item);
	}
}
#endif

void ConnectionsController::on_session_connect_status_changed(IRCSession::ConnectStatus status, IRCSession *session)
{
	auto item = view->networks->get_item(session->get_connection_name());
	if (item)
	{
		switch (status)
		{
		case IRCSession::status_connected:
			item->set_status_online("Connected");
			break;
		case IRCSession::status_connecting:
			item->set_status_online("Connecting..");
			break;
		case IRCSession::status_disconnected:
			item->set_status_offline("Not connected");
			break;
		default:
			item->set_status_online("Unknown");
			break;
		}
	}
}
