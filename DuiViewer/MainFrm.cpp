// MainFrm.cpp : implmentation of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"
#include "MainFrm.h"
#include "shellapi.h"
CString gstrError;
HINSTANCE CMainFrame::s_hInstance = NULL;
LRESULT CMainFrame::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
    //其他的初始化
    SetTimer(100, 2000, NULL);
    CenterWindow();
    return TRUE;
}
LRESULT CMainFrame::OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    EndDialog(wID);
    return 0;
}

LRESULT CMainFrame::OnBtnReload(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    // TODO: Add your control notification handler code here
    UpdatePath();
    Reload();
    return 0;
}

HRESULT CMainFrame::Reload()
{
    CString strPath = m_strXML;
    if(!PathFileExists(strPath)) return E_ACCESSDENIED;
    int nPos = strPath.ReverseFind(L'\\');
    if(nPos == -1) return E_FAIL;    
    CString strName = strPath.Mid(nPos + 1);
    CString strFolder = strPath.Left(nPos);
    if(m_pFrame)
    {
        m_pFrame->Close();
        //delete m_pFrame;
    }
    CPaintManagerUI::SetInstance(s_hInstance);
    CPaintManagerUI::SetResourcePath(strFolder);
    m_tUpdateTime = GetFileModifyTime(m_strXML);
    m_pFrame = new CFrameWindowWnd(strName);
    if( m_pFrame == NULL ) return 0;
    m_pFrame->Create(m_hWnd, _T(""), UI_WNDSTYLE_CHILD, WS_EX_WINDOWEDGE | WS_EX_NOACTIVATE, 10, 50, 300, 300);
    //pFrame->CenterWindow();
    m_pFrame->ShowWindow(true, false);    
    return S_OK;    
}

LRESULT CMainFrame::OnItemSize(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/ )
{
    int nWidth = (short)LOWORD(lParam);
    int nHeigh = (short)HIWORD(lParam);
    CRect rcWin;
    GetWindowRect(&rcWin);
    int nNewWidth = rcWin.Width(), nNewHeight = rcWin.Height();
    if (nNewWidth < nWidth + 20)
    {
        nNewWidth = nWidth + 20;
    }
    if (nNewHeight < nHeigh + 80)
    {
        nNewHeight = nHeigh + 80;
    }
    if (nNewWidth < 200)
    {
        nNewWidth = 200;
    }
    if (nNewHeight < 200)
    {
        nNewHeight = 200;
    }
    if (nNewWidth != rcWin.Width() || nNewHeight != rcWin.Height())
    {
        MoveWindow(rcWin.left, rcWin.top, nNewWidth, nNewHeight, TRUE);
    }
    return 0;
}

LRESULT CMainFrame::OnSize( UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM lParam, BOOL& )
{
    if (!m_pFrame) return 0;
    if (!m_pFrame->GetHWND()) return 0;
    CRect rcFrame;
    ::GetWindowRect(m_pFrame->GetHWND(), &rcFrame);
    CRect rcClient;
    GetWindowRect(&rcClient);
    //CRect rcNew
    return 0;    
}

LRESULT CMainFrame::OnTimer( UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& )
{
    if (wParam == 100)
    {
        UpdatePath();
        time_t tModify = GetFileModifyTime(m_strXML);
        if (tModify && tModify != m_tUpdateTime)
        {
            Reload();
        }
    }
    return 0;
}

HRESULT CMainFrame::UpdatePath()
{
    WCHAR szText[MAX_PATH] = {0};
    GetDlgItemText(IDC_EDIT_PATH, szText, _countof(szText));
    if (m_strXML != szText)
    {
        m_tLastModify = 0;
        m_tUpdateTime = 0;
    }
    m_strXML = szText;
    return S_OK;
}

HRESULT CMainFrame::UpdateFileTime()
{
    CString strPath = m_strXML;
    if(!PathFileExists(strPath))
    {
        m_tLastModify = 0;
        return E_ACCESSDENIED;
    }
    _stat times = {0};
    _wstat(m_strXML, &times);
    m_tLastModify = times.st_mtime;
    return S_OK;
}

time_t CMainFrame::GetFileModifyTime(const CString&strPath)
{
    if (strPath.IsEmpty())
    {
        return 0;
    }    
    if(!PathFileExists(strPath))
    {
        return 0;
    }
    if (PathIsDirectory(strPath))
    {
        return 0;
    }
    _stat times = {0};
    _wstat(m_strXML, &times);
    return times.st_mtime;    
}


LRESULT CMainFrame::OnDropFiles(UINT /*uMsg*/, WPARAM wp, LPARAM lp, BOOL &bHandled)
{	
    SetActiveWindow();
    bHandled = TRUE;	
    std::wstring strFilePath;
    HDROP hDropInfo = (HDROP)wp;
    UINT uFile = DragQueryFile( hDropInfo, (UINT)-1, NULL, 0);   
    if (!uFile)
    {
        return 0;
    }
    TCHAR szFileName[MAX_PATH] = {0};
    ::DragQueryFile(hDropInfo, 0, szFileName, MAX_PATH);
    OpenXML(szFileName);
    DragFinish(hDropInfo);
    hDropInfo = NULL;
    return 0;
}

HRESULT CMainFrame::OpenXML( const CString&strPath )
{   
    if(!IsValidPath(strPath)) return E_FAIL;
    SetDlgItemText(IDC_EDIT_PATH, strPath);
    UpdatePath();
    time_t tModify = GetFileModifyTime(m_strXML);
    if (tModify && tModify != m_tUpdateTime)
    {
        Reload();
    }
    return S_OK;
}

bool CMainFrame::IsValidPath( const CString&strPath )
{
    if (strPath.IsEmpty())
    {
        return false;
    }    
    if(!PathFileExists(strPath))
    {
        return false;
    }
    if (PathIsDirectory(strPath))
    {
        return false;
    }
    return true;
}
