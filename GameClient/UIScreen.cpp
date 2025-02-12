#include "pch.h"
#include "UIScreen.h"
#include "UIButton.h"
#include "Manager.h"
#include "Texture.h"
#include "Font.h"

UIScreen::UIScreen()
{
}

UIScreen::~UIScreen()
{
	std::wcout << L"~UIScreen" << std::endl;
}

void UIScreen::Update()
{
}

void UIScreen::Render()
{
	if (_background)
		DrawTexture(_background, _backGroundPosition);
	if (_title)
		DrawTexture(_title, _titlePosition);

	// Draw buttons
	for (auto& button : _buttons)
	{
		// Draw background of button
		auto& texture = button->GetHighlighted() ? _buttonOn : _buttonOff;
		DrawTexture(texture, button->GetPosition());
		// Draw text of button
		DrawTexture(button->GetNameTexture(), button->GetPosition());
	}
}

void UIScreen::ProcessInput()
{
	if (_buttons.empty() == false)
	{
		const auto& state = Manager::GetInputManager()->GetState();
		const auto& mousePosition = state.mouse.GetPosition();

		// Highlight any buttons
		for (auto& button : _buttons)
		{
			if (button->IsPointInside(mousePosition))
				button->SetHighlighted(true);
			else
				button->SetHighlighted(false);
		}
	}
}

void UIScreen::HandleKeyPress()
{
	const auto& state = Manager::GetInputManager()->GetState();

	if (state.mouse.GetButtonState(SDL_BUTTON_LEFT) == ButtonState::Released)
	{
		if (_buttons.empty() == false)
		{
			for (auto& button : _buttons)
			{
				if (button->GetHighlighted())
				{
					button->OnClick();
					break;
				}
			}
		}
	}
}

void UIScreen::Close()
{
	_state = UIState::Close;
}

void UIScreen::SetTitle(const std::string& text, const Vector3& color, int32 pointSize)
{
	if (_title)
		_title->Clear();

	_title = _font->RenderText(text, color, pointSize);
}

void UIScreen::AddButton(const std::string& name, std::function<void()> onClick)
{
	Vector2 dims(static_cast<float>(_buttonOn->GetTextureWidth()),static_cast<float>(_buttonOn->GetTextureHeight()));
	std::shared_ptr<UIButton> button = std::make_shared<UIButton>(name, _font, onClick, _nextButtonPosition, dims);
	button->SetName(name);
	_buttons.push_back(button);

	_nextButtonPosition.y += _buttonOff->GetTextureHeight() + 20.0f;
}

void UIScreen::DrawTexture(std::shared_ptr<Texture> texture, const Vector2& offset, float scale)
{
	SDL_Rect r;

	auto width = texture->GetTextureWidth();
	auto height = texture->GetTextureHeight();

	r.w = static_cast<int32>(width * scale);
	r.h = static_cast<int32>(height * scale);

	r.x = static_cast<int32>(offset.x - r.w / 2);
	r.y = static_cast<int32>(offset.y - r.h / 2);

	auto renderer = Manager::GetRenderManager()->GetRenderer();
	::SDL_RenderCopyEx(renderer,
		texture->GetSDLTexture(),
		nullptr,
		&r,
		0.0f,
		nullptr,
		SDL_FLIP_NONE);
}

void UIScreen::SetRelativeMouseMode(bool relative)
{
	if (relative)
	{
		::SDL_SetRelativeMouseMode(SDL_TRUE);
		::SDL_GetRelativeMouseState(nullptr, nullptr);
	}
	else
		::SDL_SetRelativeMouseMode(SDL_FALSE);
}
