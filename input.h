#pragma once


class Input
{
private:
	static BYTE m_OldKeyState[256];
	static BYTE m_KeyState[256];
	static POINT m_PointState;
	static POINT m_OldPointState;
	static POINT m_WindowPoint;
	static RECT m_Rect;

	static bool m_LockPosition;
	static bool m_ShowCursor;

public:
	static void Init();
	static void Uninit();
	static void Update();

	static bool GetKeyPress( BYTE KeyCode );
	static bool GetKeyTrigger( BYTE KeyCode );
	static bool GetKeyRelease(BYTE KeyCode);
	static D3DXVECTOR2 GetMousePos();
	static D3DXVECTOR2 GetOldMousePos();
	static D3DXVECTOR2 GetWindowMousePos();

	static void SetOldMousePos()
	{
		m_OldPointState = m_PointState;
	}

	static void SetShowCursor(BOOL _Show)
	{
		ShowCursor(_Show);
	}
	static void SetLockPosition(bool _Lock)
	{
		m_LockPosition = _Lock;
	}
};
