#include "StdAfx.h"
#include "MainFrm.h"
CAppModule _Module;
UINT sMsg[] ={0x0049, WM_COPYDATA, WM_DROPFILES};
void OpenMessages( const UINT*pMsg, size_t uCount )
{
    if(!pMsg) return;
    if(!uCount) return;
    HMODULE hUser32Dll = LoadLibraryW(L"user32.dll");
    if(!hUser32Dll) return;    
    typedef BOOL (WINAPI *_ChangeWindowMessageFilter)( UINT , DWORD);
    _ChangeWindowMessageFilter pChangeWindowMessageFilter =  (_ChangeWindowMessageFilter)GetProcAddress( hUser32Dll, "ChangeWindowMessageFilter" );
    if(!pChangeWindowMessageFilter) return;
    for (size_t i = 0; i < uCount; i ++)
    {
        if(!pMsg[i]) continue;
        pChangeWindowMessageFilter(pMsg[i], MSGFLT_ADD);
    }
}

int Run( void )
{  
    CMessageLoop theLoop;
    _Module.AddMessageLoop(&theLoop);    
    CMainFrame wndMain;    
    RECT rc = {0,0, 633, 448};
    wndMain.DoModal();
    //wndMain.ShowWindow(SW_HIDE);
    int nRet = 0;//theLoop.Run();   
    _Module.RemoveMessageLoop();
    return nRet;
    
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPSTR /*lpCmdLine*/, int nCmdShow)
{
    CMainFrame::s_hInstance = hInstance;
    OpenMessages(sMsg, _countof(sMsg));
    CPaintManagerUI::SetInstance(hInstance);   

    HRESULT Hr = ::CoInitialize(NULL);
    if( FAILED(Hr) ) return 0;  
    _Module.Init(NULL, hInstance);
    Run();
    _Module.Term();
    ::CoUninitialize();
    return 0;
}
