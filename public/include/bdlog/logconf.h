#ifndef BDXLOG_XLOG_CONF_H_INCLUDED
#define BDXLOG_XLOG_CONF_H_INCLUDED

#include "bdlog.h"
#include "log_interface.h"
#include <shlobj.h>
#include <string>
#include <Shlwapi.h>
#include <atlcomcli.h>
#include <strsafe.h>
#include "bdassert.h"
#pragma comment(lib, "shlwapi.lib")
// 想启用日志功能的主程序在程序一启动时调用
static SIZE_T GetCommonAppDataDir( LPWSTR pszPath, UINT nlen, BOOL bCreate = TRUE );
static HRESULT InitLogService(LPCWSTR pszDir = L"")
{
#ifndef DISABLE_XLOG
    //RETAILMSG(MSG_LEVEL_INFO, L"InitLogService");
    WCHAR szDllPath[MAX_PATH] = {0};
    if (pszDir && *pszDir)
    {
        StringCchCopy(szDllPath, _countof(szDllPath), pszDir);
    }
    if (sizeof(HANDLE) == 8)
    {
        PathAppend(szDllPath, L"bdlogx64.dll");
    }
    else
    {		
        PathAppend(szDllPath, L"bdlog.dll");
    }
	SetLastError(0);
    OutputDebugString(szDllPath);
	HMODULE hModule = LoadLibrary(szDllPath);
	if (!hModule)
	{
		//RETAILMSG(MSG_LEVEL_WARNING, L"InitLogService::LoadLibrary[%s] Failed[%08X]", XLOGDLL_NAME, GetLastError());
		return E_FAIL;
	}
	ON_LEAVE_1(FreeLibrary(hModule), HMODULE, hModule);
	XLogInterface::Init(szDllPath);

	CComPtr<ILogController>pController = NULL;
	XLogInterface::GetLogController(&pController);
	if (pController)
	{
		ON_LEAVE_1(pController.Detach(), CComPtr<ILogController>&, pController);   //兼容旧版本 不释放策略 稳妥起见 暂时保留
		WCHAR szLogConfDir[MAX_PATH] = {0};
		SetLastError(0);
		GetCommonAppDataDir(szLogConfDir, _countof(szLogConfDir));
        CComPtr<ILogController2>pController2;
        pController->QueryInterface(__uuidof(ILogController2), (void**)&pController2);
        if(pController2)
        {
            if(FAILED(pController2->InitEx(L"BaiduSearch", Conf_Reg, 5000, TRUE)))
                return E_FAIL;
        }
        else
        {
            if(FAILED(pController->Init(szLogConfDir, 5000, TRUE))) return E_FAIL;
        }
		pController->AddLOD(L"file", LOD_FILE, L"enable:false path:`%temp%\\Baidu\\BaiduSearch\\log\\log_${T}_${PF}.xlog`");
		pController->AddLOD(L"pipe", LOD_PIPE, L"enable:true");
		pController->AddLOD(L"sharingmemory", LOD_SHARINGMEMORY,L"enable:true outlvl:0 ");
		pController->AddLOD(L"debugoutput", LOD_DEBUGOUTPUT, L"enable:false");
//		pController->AddLOD(L"console", LOD_CONSOLE, L"enable:false");
//		pController->AddLOD(L"memory", LOD_MEMORY,L"enalbe:false");

	}

	return S_OK;
#else  // DISABLE_XLOG
  return E_FAIL;
#endif  // DISABLE_XLOG
}

static HRESULT UninitLogService()
{	
#ifndef DISABLE_XLOG
	{
		CComPtr<ILogController> pController = NULL;
		XLogInterface::GetLogController(&pController);
		if (pController)
		{
			ON_LEAVE_1(pController.Detach(), CComPtr<ILogController>&, pController);			//兼容旧版本 不释放策略 稳妥起见 暂时保留
			pController->UnInit();
		}
	}
	XLogInterface::Uninit();	
	return S_OK;
#else  // DISABLE_XLOG
  return E_FAIL;
#endif  // DISABLE_XLOG
}

SIZE_T GetCommonAppDataDir( LPWSTR pszPath, UINT nlen, BOOL bCreate )
{
    TCHAR szPath[MAX_PATH] = {0};
    SHGetFolderPath(NULL, CSIDL_COMMON_APPDATA, NULL, SHGFP_TYPE_CURRENT, szPath);
    PathAppend(szPath,  TEXT("\\Baidu\\BaiduSearch"));
    if (bCreate)
    {
        if (!PathFileExists(szPath))
        {
            SHCreateDirectory(NULL, szPath);
        }
    }
    if(pszPath && nlen)
    {
        StringCchCopy(pszPath, nlen, szPath);
        return wcslen(pszPath);
    }
    return wcslen(szPath);
}
#endif
