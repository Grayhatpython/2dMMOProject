#pragma once

class Font;
class Texture;
class UIButton
{
public:
	UIButton(const std::string& name, std::shared_ptr<Font> font, std::function<void()> onClick, const Vector2& pos, const Vector2& dims);
	~UIButton();

public:
	bool IsPointInside(const Vector2& point) const;
	void OnClick();

public:
	void						SetName(const std::string& name);

	// Getters/setters
	std::shared_ptr<Texture>	GetNameTexture() { return _nameTexture; }
	const Vector2&				GetPosition() const { return _position; }
	void						SetHighlighted(bool highlighted) { _highlighted = highlighted; }
	bool						GetHighlighted() const { return _highlighted; }

private:
	std::function<void()>		_onClick;

	std::string					_name;

	std::shared_ptr<Texture>	_nameTexture;
	std::shared_ptr<Font>		_font;

	Vector2						_position;
	Vector2						_dimensions;
	bool						_highlighted;
};
