
#pragma once

#include "View/Theme/theme_views.h"

class AboutView : public uicore::ColumnView
{
public:
	AboutView()
	{
		auto h1 = add_subview<uicore::TextBlockView>();
		auto p1 = add_subview<uicore::TextBlockView>();
		auto image_view = add_subview<uicore::ImageView>();
		auto p2 = add_subview<uicore::TextBlockView>();
		add_subview<uicore::SpacerView>();

		auto buttons = add_subview<uicore::RowView>();
		buttons->add_subview<uicore::SpacerView>();
		ok_button = buttons->add_subview<ThemeButtonView>();

		style()->set("background: rgb(240,240,240); padding: 11px");
		h1->style()->set("font: bold 22px/26px 'Source Sans Pro'");
		p1->style()->set("font: 13px/17px 'Source Sans Pro'; margin: 0 0 20px 0; width: 370px;");
		p2->style()->set("font: 13px/17px 'Source Sans Pro'; margin: 11px 0; width: 370px;");
		image_view->style()->set("margin: 0 auto");
		ok_button->style()->set("width: 75px");

		h1->set_text_alignment(uicore::TextAlignment::center);
		p1->set_text_alignment(uicore::TextAlignment::center);
		p2->set_text_alignment(uicore::TextAlignment::center);

		h1->add_text("Carambola Chat");
		p1->add_text("Copyright 2015 The ClanLib Team");
		image_view->set_image(uicore::ImageSource::from_resource("Icons/carambola-256.png"));
		p2->add_text("This is where you usually read a long tale about how much we are going to put you behind bars if you pirate this software. But luckily for you this product is free!");

		ok_button->label()->set_text("OK");
	}

	std::shared_ptr<ThemeButtonView> ok_button;
};
