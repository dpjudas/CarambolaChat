
#pragma once

class ThemeButtonView : public uicore::ButtonView
{
public:
	ThemeButtonView();
};

class ThemeCheckBoxView : public uicore::CheckBoxView
{
public:
	ThemeCheckBoxView();
};

class ThemeImageView : public uicore::ImageView
{
public:
	ThemeImageView();
};

class ThemeLabelView : public uicore::LabelView
{
public:
	ThemeLabelView();
};

class ThemeListBoxView : public uicore::ListBoxView
{
public:
	ThemeListBoxView();
};

class ThemeListBoxLabelView : public uicore::LabelView
{
public:
	ThemeListBoxLabelView(const std::string &text = std::string());
};

class ThemeRadioButtonView : public uicore::RadioButtonView
{
public:
	ThemeRadioButtonView();
};

class ThemeScrollView : public uicore::ScrollView
{
public:
	ThemeScrollView();
};

class ThemeScrollBarView : public uicore::ScrollBarView
{
public:
	ThemeScrollBarView();
};

class ThemeSliderView : public uicore::SliderView
{
public:
	ThemeSliderView();
};

class ThemeSpinView : public uicore::SpinView
{
public:
	ThemeSpinView();
};

class ThemeTextFieldView : public uicore::TextFieldView
{
public:
	ThemeTextFieldView();
};

class ThemeTextView : public uicore::TextView
{
public:
	ThemeTextView();
};
