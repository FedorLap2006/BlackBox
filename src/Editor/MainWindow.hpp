#pragma once
#include <BlackBox/Renderer/IRender.hpp>

class MainWindow : public IRenderCallback
{
public:
	MainWindow();
	void Draw();
	bool Update();

	int m_ViewRenderTarget = -1;
	IGame* m_pGame = nullptr;

	// Inherited via IRenderCallback
	virtual void CallBack(Type type) override;
};