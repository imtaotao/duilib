// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////
#pragma once
#include "resource.h"
#define MSG_SIZE_CHANGE      WM_USER + 100
extern CString gstrError;
class CFrameWindowWnd : public CWindowWnd, public INotifyUI
{
public:
    CFrameWindowWnd(const CString& strPath)
    {
        m_strXML = strPath;
        m_bLoadSuccess = true;
    };
    LPCTSTR GetWindowClassName() const 
    { 
        return _T("UIMainFrame"); 
    };
    UINT GetClassStyle() const 
    { 
        return UI_CLASSSTYLE_FRAME | CS_DBLCLKS; 
    };   
    void Init() 
    {

    }   
    LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        ::PostMessage(GetParent(m_hWnd), MSG_SIZE_CHANGE, wParam, lParam);
        return 0;
    }  

    void OnPrepare() 
    {
       
    }

    void Notify(TNotifyUI& msg)
    {
        if( msg.sType == _T("windowinit") ) 
            OnPrepare();        
    }
    LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        if( uMsg == WM_CREATE ) 
        {
            m_pm.Init(m_hWnd);
            CDialogBuilder builder;
            CControlUI* pRoot = builder.Create((LPCWSTR)m_strXML, (UINT)0, NULL, &m_pm);
            if(!pRoot)
            {
                gstrError = L"xmlΩ‚Œˆ ß∞‹";
                m_bLoadSuccess = false;
                return 0;
            }
            m_pm.AttachDialog(pRoot);
            m_pm.AddNotifier(this);
            Init();
            return 0;
        }
        else if( uMsg == WM_DESTROY )
        {
            
        }
        else if( uMsg == WM_ERASEBKGND ) 
        {
            return 1;
        }
        else if (uMsg == WM_SIZE)
        {
            OnSize(uMsg, wParam, lParam);
        }
        if (!m_bLoadSuccess)
        {
            return ::DefWindowProc(m_hWnd, uMsg, wParam, lParam);
        }
        LRESULT lRes = 0;
        if( m_pm.MessageHandler(uMsg, wParam, lParam, lRes) )
            return lRes;
        return CWindowWnd::HandleMessage(uMsg, wParam, lParam);
    }

public:
    CPaintManagerUI m_pm;
    CString m_strXML;
    bool m_bLoadSuccess;
};


class CMainFrame : public CDialogImpl<CMainFrame >
{
public:
    CMainFrame()
    {
        m_pFrame = NULL;
        m_tLastModify = 0;
    }
    enum { IDD = IDD_DIALOG_MAIN };
    BEGIN_MSG_MAP(CMainFrame )
        MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
        MESSAGE_HANDLER(MSG_SIZE_CHANGE, OnItemSize)
        MESSAGE_HANDLER(WM_SIZE, OnSize)
        MESSAGE_HANDLER(WM_TIMER, OnTimer)
        MESSAGE_HANDLER(WM_DROPFILES, OnDropFiles)
        COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
        COMMAND_HANDLER(IDC_BUTTON_RELOAD, BN_CLICKED, OnBtnReload)
    END_MSG_MAP()
    LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
    LRESULT OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnBtnReload(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnItemSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL&);
    LRESULT OnSize(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL&);
    LRESULT OnTimer(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL&);
    LRESULT OnDropFiles(UINT uMsg, WPARAM wp, LPARAM lp, BOOL& bHandled);
    HRESULT Reload();
    HRESULT UpdatePath();
    HRESULT OpenXML(const CString&);
    bool IsValidPath(const CString&);
private:
    HRESULT UpdateFileTime();
    time_t GetFileModifyTime(const CString&);
public:
    static HINSTANCE s_hInstance;
    CFrameWindowWnd* m_pFrame;
    CString m_strXML;
    time_t m_tLastModify;
    time_t m_tUpdateTime;
};