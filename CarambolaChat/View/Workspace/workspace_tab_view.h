
#pragma once

class WorkspaceTabView : public uicore::View
{
public:
	WorkspaceTabView(const std::string &label_text, bool app_label);

	std::shared_ptr<uicore::LabelBaseView> label;
	std::shared_ptr<uicore::LabelBaseView> message_count;
	std::shared_ptr<uicore::ImageBaseView> close;
};
