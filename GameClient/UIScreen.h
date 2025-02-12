#pragma once

class Font;
class UIButton;
class Texture;

class UIScreen : public std::enable_shared_from_this<UIScreen>
{
public:
	UIScreen();
	virtual ~UIScreen();

public:
	virtual void Update();
	virtual void Render();
	virtual void ProcessInput();
	virtual void HandleKeyPress();

	void Close();

	void SetTitle(const std::string& text,const Vector3& color = Color::White,int32 pointSize = 40);
	void AddButton(const std::string& name, std::function<void()> onClick);

protected:
	void DrawTexture(std::shared_ptr<Texture> texture,const Vector2& offset = Vector2::Zero,float scale = 1.0f);

public:
	void				SetRelativeMouseMode(bool relative);
	UIState				GetState() const { return _state; }

	void				SetTitlePosition(const Vector2& position) { _titlePosition = position; }
	const Vector2&		GetTitlePosition() { return _titlePosition; }

	void				SetNextButtonPosition(const Vector2& position) { _nextButtonPosition = position; }
	const Vector2&		GetNextButtonPosition() { return _nextButtonPosition; }

	void				SetBackGroundPosition(const Vector2& position) { _backGroundPosition = position; }
	const Vector2&		GetBackGroundPosition() { return _backGroundPosition; }

	void				SetFont(std::shared_ptr<Font> font) { _font = font; }
	void				SetBackGroundTexture(std::shared_ptr<Texture> texture) { _background = texture; }
	void				SetButtonOnTexture(std::shared_ptr<Texture> texture) { _buttonOn = texture; }
	void				SetButtonOffTexture(std::shared_ptr<Texture> texture) { _buttonOff = texture; }

protected:
	std::shared_ptr<Font>		_font;
	std::shared_ptr<Texture>	_title;
	std::shared_ptr<Texture>	_background;
	std::shared_ptr<Texture>	_buttonOn;
	std::shared_ptr<Texture>	_buttonOff;

	Vector2 _titlePosition{ 0.0f, 300.0f };
	Vector2 _nextButtonPosition{ 0.0f, 200.0f };
	Vector2 _backGroundPosition{ 0.0f, 250.0f };

	UIState									_state = UIState::Active;
	std::vector<std::shared_ptr<UIButton>>	_buttons;
};
