#include "Window.h"
#include "Prerrequisitos.h"

Window::Window() {

}

Window::~Window() {

}

HRESULT
Window::init(HINSTANCE hInstance, int nCmdShow, WNDPROC wndprow, LPCSTR windowName) {
	
	windowName = windowName;
	m_hInst = hInstance;
	
	WNDCLASSEX wdex;
	wdex.cbSize = sizeof(WNDCLASSEX);
	wdex.style = CS_HREDRAW | CS_VREDRAW;
	wdex.lpfnWndProc = wndprow;
	wdex.cbClsExtra = 0;
	wdex.cbWndExtra = 0;
	wdex.hInstance = m_hInst;
	wdex.hIcon = LoadIcon(m_hInst, (LPCTSTR)IDI_TUTORIAL1);
	wdex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wdex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wdex.lpszClassName = "TutorialWindowClass";
	wdex.hIconSm = LoadIcon(wdex.hInstance, (LPCTSTR)IDI_TUTORIAL1);
	wdex.hIconSm = NULL;
	if (!RegisterClassEx(&wdex)) {
		return E_FAIL;
	}
	RECT rc = { 0, 0, 640, 480 };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

	if (!m_hWnd) {
		return E_FAIL;
	}

	ShowWindow(m_hWnd, nCmdShow);

	GetClientRect(m_hWnd, &m_rect);
	m_width = m_rect.right - m_rect.left;
	m_height = m_rect.bottom - m_rect.top;

	return S_OK;
}

void
Window::update() {

}

void
Window::render() {

}

void
Window::destroy() {

}