
#pragma once

class ButtonView : public uicore::ButtonBaseView
{
public:
	ButtonView();
};

class CheckBoxView : public uicore::CheckBoxBaseView
{
public:
	CheckBoxView();
};

class ImageView : public uicore::ImageBaseView
{
public:
	ImageView();
};

class LabelView : public uicore::LabelBaseView
{
public:
	LabelView();
};

class ListBoxView : public uicore::ListBoxBaseView
{
public:
	ListBoxView();
};

class ListBoxLabelView : public uicore::LabelBaseView
{
public:
	ListBoxLabelView(const std::string &text = std::string());
};

class RadioButtonView : public uicore::RadioButtonBaseView
{
public:
	RadioButtonView();
};

class ScrollView : public uicore::ScrollBaseView
{
public:
	ScrollView();
};

class ScrollBarView : public uicore::ScrollBarBaseView
{
public:
	ScrollBarView();
};

class SliderView : public uicore::SliderBaseView
{
public:
	SliderView();
};

class SpinView : public uicore::SpinBaseView
{
public:
	SpinView();
};

class TextFieldView : public uicore::TextFieldBaseView
{
public:
	TextFieldView();
};

class TextAreaView : public uicore::TextAreaBaseView
{
public:
	TextAreaView();
};
