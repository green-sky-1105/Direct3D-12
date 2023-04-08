//-------------------------------------------------------------------------------------------------
// Includes
//-------------------------------------------------------------------------------------------------
#include "App.h"

namespace /* anonymous */ {
	const auto ClassName = TEXT("SampleWindowClass");	//!< ウィンドウクラス名
} // namespace /* anonymous */

//-------------------------------------------------------------------------------------------------
// コンストラクタ
//-------------------------------------------------------------------------------------------------
App::App(uint32_t width, uint32_t height)
	: m_hInst(nullptr)
	, m_hWnd(nullptr)
	, m_Width(width)
	, m_Height(height)
{ /* DO_NOTHING */ }

//-------------------------------------------------------------------------------------------------
// デストラクタ
//-------------------------------------------------------------------------------------------------
App::~App()
{ /* DO_NOTHING */ }

//-------------------------------------------------------------------------------------------------
// 実行
//-------------------------------------------------------------------------------------------------
void App::Run() {
	if (InitApp()) {
		MainLoop();
	}

	TermApp();
}

//-------------------------------------------------------------------------------------------------
// 初期化処理
//-------------------------------------------------------------------------------------------------
bool App::InitApp(){
	//ウィンドウの初期化
	if (!InitWnd()) { return false; }

	//正常終了
	return true;
}

//-------------------------------------------------------------------------------------------------
// 終了処理
//-------------------------------------------------------------------------------------------------
void App::TermApp() {
	// ウィンドウの終了処理
	TermWnd();
}

//-------------------------------------------------------------------------------------------------
// ウィンドウ初期化処理
//-------------------------------------------------------------------------------------------------
bool App::InitWnd() {
	// インスタントハンドル取得
	auto hInst = GetModuleHandle(nullptr);
	if (hInst == nullptr) { return false; }

	// ウィンドウの設定
	WNDCLASSEX wc = {};
	wc.cbSize			= sizeof(WNDCLASSEX);					// 構造体サイズの指定
	wc.style			= CS_HREDRAW | CS_VREDRAW;				// ウィンドウクラスのスタイル
	wc.lpfnWndProc		= WndProc;								// ウィンドウプロシージャの指定
	wc.hIcon			= LoadIcon(hInst, IDI_APPLICATION);		// アイコンハンドル
	wc.hCursor			= LoadCursor(hInst, IDC_ARROW);			// カーソルハンドル
	wc.hbrBackground	= GetSysColorBrush(COLOR_BACKGROUND);	// 背景ブラシのハンドル
	wc.lpszMenuName		= nullptr;								// メニュー名の指定
	wc.lpszClassName	= ClassName;							// ウィンドウクラスの名前
	wc.hIconSm			= LoadIcon(hInst, IDI_APPLICATION);		// スモールアイコンハンドル

	// ウィンドウの登録
	if (!RegisterClassEx(&wc)) { return false; }

	// インスタンスハンドル設定
	m_hInst = hInst;

	// ウィンドウサイズを設定
	RECT rc = {};
	rc.right = static_cast<LONG>(m_Width);
	rc.bottom = static_cast<LONG>(m_Height);

	// ウィンドウサイズを調整
	auto style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU;
	AdjustWindowRect(&rc, style, FALSE);

	// ウィンドウを生成
	m_hWnd = CreateWindowEx(
		0,
		ClassName,
		TEXT("Sample"),
		style,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		rc.right - rc.left,
		rc.bottom - rc.top,
		nullptr,
		nullptr,
		m_hInst,
		nullptr
	);

	if (m_hWnd == nullptr) { return false; }

	// ウィンドウを表示
	ShowWindow(m_hWnd, SW_SHOWNORMAL);

	// ウィンドウを更新
	UpdateWindow(m_hWnd);

	// ウィンドウにフォーカスを設定
	SetFocus(m_hWnd);

	// 正常終了
	return true;
 }

//-------------------------------------------------------------------------------------------------
// ウィンドウ終了処理
//-------------------------------------------------------------------------------------------------
void App::TermWnd() {
	// ウィンドウの登録を解除
	if (m_hInst != nullptr) { UnregisterClass(ClassName, m_hInst); }

	m_hInst = nullptr;
	m_hWnd = nullptr;
}

//-------------------------------------------------------------------------------------------------
// メインループ
//-------------------------------------------------------------------------------------------------
void App::MainLoop() {
	MSG msg = {};

	while (WM_QUIT != msg.message) {
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE) == TRUE) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}

//-------------------------------------------------------------------------------------------------
// ウィンドウプロシージャ
//-------------------------------------------------------------------------------------------------
LRESULT CALLBACK App::WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
	switch (msg) {
		case WM_DESTROY:
			{ PostQuitMessage(0); }
			break;

		default:
			{ /* DO_NOTHING */}
			break;
	}

	return DefWindowProc(hWnd, msg, wp, lp);
}