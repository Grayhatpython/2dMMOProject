#pragma once
#include "UIScreen.h"

class UIPauseMenu : public UIScreen
{
public:
	UIPauseMenu();
	~UIPauseMenu();

public:
	virtual void HandleKeyPress() override;
};
