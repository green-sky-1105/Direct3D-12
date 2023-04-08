#pragma once

//-------------------------------------------------------------------------------------------------
// Includes
//-------------------------------------------------------------------------------------------------
#include <Windows.h>
#include <cstdint>

///////////////////////////////////////////////////////////////////////////////////////////////////
// App class
///////////////////////////////////////////////////////////////////////////////////////////////////
class App {
	//=============================================================================================
	// list of friend classes and methods.
	//=============================================================================================
	/* NOTHING */

public:
	//=============================================================================================
	// public variables.
	//=============================================================================================
	/* NOTHING */

	//==============================================================================================
	// public methods.
	//=============================================================================================
	App(uint32_t width, uint32_t height);
	~App();
	void Run();

private:
	//=============================================================================================
	// private variables.
	//=============================================================================================
	HINSTANCE	m_hInst;	//インスタンスハンドル
	HWND		m_hWnd;		//ウィンドウハンドル
	uint32_t	m_Width;	//ウィンドウ幅
	uint32_t	m_Height;	//ウィンドウ高さ

	//=============================================================================================
	// private methods.
	//=============================================================================================
	bool InitApp();
	void TermApp();
	bool InitWnd();
	void TermWnd();
	void MainLoop();

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);
};