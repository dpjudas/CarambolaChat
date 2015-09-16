
#pragma once

class WorkspaceTabView : public uicore::View
{
public:
	WorkspaceTabView(const std::string &label_text, bool app_label);

	std::shared_ptr<uicore::LabelView> label;
	std::shared_ptr<uicore::LabelView> message_count;
	std::shared_ptr<uicore::ImageView> close;
};
