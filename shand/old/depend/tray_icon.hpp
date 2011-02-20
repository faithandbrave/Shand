#ifndef _CE_TRAY_ICON_HPP_
#define _CE_TRAY_ICON_HPP_

#define WM_TRAY_ICON 0x1000

// ��MFC�p

//==============================//
//								//
// �g���C�A�C�R���Ǘ��N���X		//
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
	// �A�C�R���쐬				//
	// OnInitDialog()�Ŏ��s		//
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
	// �A�C�R���\��				//
	//--------------------------//
	void Show()
	{
		Shell_NotifyIcon(NIM_ADD, &m_stTrayIcon);
	}

	//--------------------------//
	// �A�C�R����\��			//
	//--------------------------//
	void Hide()
	{
		Shell_NotifyIcon(NIM_DELETE, &m_stTrayIcon);
	}

	//--------------------------//
	// �A�C�R���ؑ�				//
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
	NOTIFYICONDATA m_stTrayIcon;	// �g���C�A�C�R��
};

#endif	// _CE_TRAY_ICON_HPP_