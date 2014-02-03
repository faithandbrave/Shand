// Copyright Akira Takahashi 2006
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef _CE_TRAY_ICON_HPP_
#define _CE_TRAY_ICON_HPP_

#define WM_TRAY_ICON 0x1000

// ※MFC用

//==============================//
//								//
// トレイアイコン管理クラス		//
//								//
//==============================//
class CTrayIcon {
public:
	explicit CTrayIcon() {}

	~CTrayIcon()
	{
		Hide();
	}

	//--------------------------//
	// アイコン作成				//
	// OnInitDialog()で実行		//
	//--------------------------//
	void Create(HWND hWnd, UINT nIconID)
	{
		m_stTrayIcon.cbSize	= sizeof(NOTIFYICONDATA);
		m_stTrayIcon.uID	= 0;
		m_stTrayIcon.hWnd	= hWnd;
		m_stTrayIcon.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
		m_stTrayIcon.hIcon	= (HICON)LoadImage(AfxGetResourceHandle(),
											   MAKEINTRESOURCE(nIconID),
											   IMAGE_ICON,
											   16, 16,
											   LR_DEFAULTCOLOR);
		m_stTrayIcon.uCallbackMessage	= WM_TRAY_ICON;
		lstrcpy(m_stTrayIcon.szTip, _T("Tray"));
	}

	//--------------------------//
	// アイコン表示				//
	//--------------------------//
	void Show()
	{
		Shell_NotifyIcon(NIM_ADD, &m_stTrayIcon);
	}

	//--------------------------//
	// アイコン非表示			//
	//--------------------------//
	void Hide()
	{
		Shell_NotifyIcon(NIM_DELETE, &m_stTrayIcon);
	}

	//--------------------------//
	// アイコン切替				//
	//--------------------------//
	void Modify(UINT nIconID)
	{
		m_stTrayIcon.hIcon = (HICON)LoadImage(AfxGetResourceHandle(),
											  MAKEINTRESOURCE(nIconID),
											  IMAGE_ICON,
											  16, 16,
											  LR_DEFAULTCOLOR);
		Shell_NotifyIcon(NIM_MODIFY, &m_stTrayIcon);
	}

private:
	NOTIFYICONDATA m_stTrayIcon;	// トレイアイコン
};

#endif	// _CE_TRAY_ICON_HPP_
