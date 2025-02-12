#include "pch.h"
#include "UIButton.h"
#include "Font.h"
#include "Texture.h"

UIButton::UIButton(const std::string& name, std::shared_ptr<Font> font, std::function<void()> onClick, const Vector2& pos, const Vector2& dims)
	: _name(name), _font(font), _onClick(onClick), _position(pos), _dimensions(dims)
{

}

UIButton::~UIButton()
{
	if (_nameTexture)
		_nameTexture->Clear();
}

bool UIButton::IsPointInside(const Vector2& point) const
{
	bool noInsided = point.x < (_position.x - _dimensions.x / 2.0f) ||
		point.x >(_position.x + _dimensions.x / 2.0f) ||
		point.y < (_position.y - _dimensions.y / 2.0f) ||
		point.y >(_position.y + _dimensions.y / 2.0f);

	return !noInsided;
}

void UIButton::OnClick()
{
	if (_onClick)
		_onClick();
}

//	È£Ãâ
void UIButton::SetName(const std::string& name)
{
	_name = name;

	if (_nameTexture)
		_nameTexture->Clear();

	_nameTexture = _font->RenderText(name);
}
