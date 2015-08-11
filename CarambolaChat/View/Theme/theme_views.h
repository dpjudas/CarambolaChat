
#pragma once

class ThemeButtonView : public clan::ButtonView
{
public:
	ThemeButtonView();
};

class ThemeCheckBoxView : public clan::CheckBoxView
{
public:
	ThemeCheckBoxView();
};

class ThemeImageView : public clan::ImageView
{
public:
	ThemeImageView();
};

class ThemeLabelView : public clan::LabelView
{
public:
	ThemeLabelView();
};

class ThemeListBoxView : public clan::ListBoxView
{
public:
	ThemeListBoxView();
};

class ThemeListBoxLabelView : public clan::LabelView
{
public:
	ThemeListBoxLabelView(const std::string &text = std::string());
};

class ThemeRadioButtonView : public clan::RadioButtonView
{
public:
	ThemeRadioButtonView();
};

class ThemeScrollView : public clan::ScrollView
{
public:
	ThemeScrollView();
};

class ThemeScrollBarView : public clan::ScrollBarView
{
public:
	ThemeScrollBarView();
};

class ThemeSliderView : public clan::SliderView
{
public:
	ThemeSliderView();
};

class ThemeSpinView : public clan::SpinView
{
public:
	ThemeSpinView();
};

class ThemeTextFieldView : public clan::TextFieldView
{
public:
	ThemeTextFieldView();
};

class ThemeTextView : public clan::TextView
{
public:
	ThemeTextView();
};
