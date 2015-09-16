
#pragma once

#include "View/EditConnection/edit_connection_view.h"
#include "Model/XMLSettings/xml_settings.h"

class EditConnectionController : public uicore::WindowController
{
public:
	EditConnectionController();
	EditConnectionController(XMLSettings connection);

private:
	void ok_clicked();
	void cancel_clicked();

	std::shared_ptr<EditConnectionView> edit_view = std::make_shared<EditConnectionView>();

	XMLSettings connection;
	bool add_dialog = false;
};
