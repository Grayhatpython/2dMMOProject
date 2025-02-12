#pragma once
#include <SDL/SDL.h>
#include "Component.h"

class Texture;
class SpriteComponent : public Component
{
public:
	SpriteComponent(int32 drawOrder = 100);
	SpriteComponent(ComponentType type, int32 drawOrder = 100);
	~SpriteComponent();

	virtual void	Render();
	void			SetTexture(const std::string& filename);

protected:
	virtual void	SetTexture(std::shared_ptr<Texture> texture);

public:
	int32							GetDrawOrder() const { return _drawOrder; }
	const std::shared_ptr<Texture>&	GetTexture() { return _texture; }

protected:
	int32							_drawOrder{ 0 };	//	TODO
	std::shared_ptr<Texture>		_texture;
};