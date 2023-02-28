
#include "main.h"
#include "input.h"


BYTE Input::m_OldKeyState[256];
BYTE Input::m_KeyState[256];
POINT Input::m_PointState;
POINT Input::m_OldPointState;
POINT Input::m_WindowPoint;
RECT Input::m_Rect;

bool Input::m_LockPosition;
bool Input::m_ShowCursor;


void Input::Init()
{
	m_LockPosition = false;
	memset( m_OldKeyState, 0, 256 );
	memset( m_KeyState, 0, 256 );
	GetCursorPos(&m_PointState);
	m_OldPointState = m_PointState;
	ShowCursor(FALSE);
}

void Input::Uninit()
{


}

void Input::Update()
{
	memcpy( m_OldKeyState, m_KeyState, 256 );

	GetKeyboardState( m_KeyState );
	
	// マウスカーソルを取得する
	GetCursorPos(&m_PointState);
	m_WindowPoint = m_PointState;

	// ウインド画面の位置からカーソルの位置を調整
	GetWindowRect(GetWindow(), &m_Rect);
	m_WindowPoint.x -= m_Rect.left;
	m_WindowPoint.y -= m_Rect.top;

	if (m_LockPosition)
	{
		SetCursorPos(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	}
}

bool Input::GetKeyPress(BYTE KeyCode)
{
	return (m_KeyState[KeyCode] & 0x80);
}

bool Input::GetKeyTrigger(BYTE KeyCode)
{
	return ((m_KeyState[KeyCode] & 0x80) && !(m_OldKeyState[KeyCode] & 0x80));
}

bool Input::GetKeyRelease(BYTE KeyCode)
{
	return ((~m_KeyState[KeyCode] & 0x80) && (m_OldKeyState[KeyCode] & 0x80));
}

D3DXVECTOR2 Input::GetMousePos()
{
	return D3DXVECTOR2((float)m_PointState.x, (float)m_PointState.y);
}

D3DXVECTOR2 Input::GetOldMousePos()
{
	return D3DXVECTOR2((float)m_OldPointState.x, (float)m_OldPointState.y);
}

D3DXVECTOR2 Input::GetWindowMousePos()
{
	return D3DXVECTOR2((float)m_WindowPoint.x, (float)m_WindowPoint.y);
}

