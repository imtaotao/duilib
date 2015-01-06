/** \file
*  日志接口
*
*  用户可以指定日志级别和日志标签，以便更好地对日志进行分类和过滤。多个标签使用半角分号隔开。
*
*  使用举例: \code
*  XLog(LOG_CLASS_DEBUG, XTAG(L"image;net;interact"), L"Image Path:%s", imagePath);
*  XLog(L"a simple log");
*  \endcode
*/

#ifndef BDIME_XLOG_H
#define BDIME_XLOG_H

#include <windows.h>
#include "compilerconf.h"
#include <atlbase.h>
#include <atlsync.h>
#define INDENTER_NUM		(1)
/// 日志级别
enum LogClass
{
   	LOG_CLASS_DIAGNOSE = 0x05,
	LOG_CLASS_DEBUG       = 0x0010,
	LOG_CLASS_INFO        = 0x0020,
    	LOG_CLASS_EVENT       = 0x0025,
	LOG_CLASS_WARNING     = 0x0030,
	LOG_CLASS_ERROR       = 0x0040,
	LOG_CLASS_CRITICAL    = 0x0050,
};
typedef LogClass LogLevel;

#ifndef MULTI_THREAD_GUARD
#define MULTI_THREAD_GUARD(cs) \
	EnterCriticalSection(&cs); \
	ON_LEAVE_1(LeaveCriticalSection(&cs), CRITICAL_SECTION&, cs)
#endif
struct ILogController;

class XLogInterface
{
public:
	static HRESULT Init(LPCWSTR pszDllPath = L"bdxlog.dll")
	{
		if (Instance().m_nAvailable != 1)
		{
			return E_ACCESSDENIED;
		}
		return Instance().InitInternal(pszDllPath);
	}
	static HRESULT Uninit()
	{
		if (Instance().m_nAvailable != 1)
		{
			return E_ACCESSDENIED;
		}
		return Instance().UninitInternal();
	}
	static void LogV(LogClass uClass, LPCWSTR pszTag, LPCWSTR pszFmt, va_list args)
	{
		if (Instance().m_nAvailable != 1)
		{
			return;
		}
		Instance().LogVInternal(uClass, pszTag, pszFmt, args);
	}
	static void LogAddIndent(int indent)
	{
		if (Instance().m_nAvailable != 1)
		{
			return;
		}
		Instance().XLogAddIndentInternal(indent);
	}
	static void DebugReport(const wchar_t* filename, int line, const wchar_t* expr)
	{
		if (Instance().m_nAvailable != 1)
		{
			return;
		}
		Instance().BdDebugReportInternal(filename, line, expr);
	}
	static HRESULT GetLogController(ILogController** pLog)
	{
		if (Instance().m_nAvailable != 1)
		{
			return E_ACCESSDENIED;
		}
		return Instance().GetLogControllerInternal(pLog);
	}
protected:
	XLogInterface()
		: bInited(FALSE)
		, m_hModule(NULL)
		, pFun_GetLogController(NULL)
		, pFun_BdDebugReport(NULL)
		, pFun_XLogAddIndent(NULL)
		, pFun_XLogV(NULL)
	{		
		InterlockedExchange(&m_nAvailable, 1);
	}
private:
	~XLogInterface()
	{
		pFun_GetLogController = NULL;
		pFun_BdDebugReport = NULL;
		pFun_XLogAddIndent = NULL;
		pFun_XLogV = NULL;
		bInited = FALSE;		
		InterlockedExchange(&m_nAvailable, 0);
	}
	typedef HRESULT (WINAPI *PFUN_GetLogController)(ILogController** pLog);
	typedef void (WINAPI *PFUN_BdDebugReport)(const wchar_t* filename, int line, const wchar_t* expr);
	typedef void (WINAPI *PFUN_XLogAddIndent)(int indent);
	typedef void (WINAPI *PFUN_XLogV)(LogClass uClass, LPCWSTR pszTag, LPCWSTR pszFmt, va_list args);

	volatile LONG m_nAvailable;
	BOOL bInited;
	HMODULE m_hModule;
	ATL::CComAutoCriticalSection m_CS;
	PFUN_GetLogController pFun_GetLogController;
	PFUN_BdDebugReport pFun_BdDebugReport;
	PFUN_XLogAddIndent pFun_XLogAddIndent;
	PFUN_XLogV pFun_XLogV;

	static XLogInterface& Instance()
	{
		static XLogInterface li;
		return li;
	}
protected:
	void CheckInit()
	{
		if (m_nAvailable != 1)
		{
			return;
		}
		if (!bInited)
		{
			InitInternal();
		}
	}
	HRESULT InitInternal(LPCWSTR pszDllPath = L"bdxlog.dll")
	{
		(pszDllPath);
#ifndef DISABLE_XLOG
		if (m_nAvailable != 1) return E_FAIL;
		if (bInited) return S_FALSE;
		ATL::CComCritSecLock<ATL::CComAutoCriticalSection> _(m_CS);
		if (bInited)
		{
			return S_FALSE;
		}
		SetLastError(0);
		HMODULE hDll = NULL;
		if (!GetModuleHandleExW(0, pszDllPath, &hDll) || !hDll)
		{
			//RETAILMSG(MSG_LEVEL_WARNING, L"XLogInterface::GetModuleHandleEx[%s] Failed[%08X]", pszDllPath, GetLastError());
			return E_FAIL;
		}
		bInited = TRUE;
		m_hModule = hDll;
		__pragma(warning(push, 1));
		__pragma(warning(disable: 4191));

		pFun_XLogV = reinterpret_cast<PFUN_XLogV>(::GetProcAddress(hDll, "XLogV"));
		pFun_BdDebugReport = reinterpret_cast<PFUN_BdDebugReport>(::GetProcAddress(hDll, "BdDebugReport"));
		pFun_XLogAddIndent = reinterpret_cast<PFUN_XLogAddIndent>(::GetProcAddress(hDll, "XLogAddIndent"));
		pFun_GetLogController = reinterpret_cast<PFUN_GetLogController>(::GetProcAddress(hDll, "GetLogController2"));
		__pragma(warning(pop));
		return S_OK;
#else
		return E_FAIL;
#endif
	}
	HRESULT UninitInternal()
	{
		if (m_nAvailable != 1) return S_FALSE;
		if (!bInited) return S_FALSE;
		ATL::CComCritSecLock<ATL::CComAutoCriticalSection> _(m_CS);
		if (!bInited) return S_FALSE;
		__pragma(warning(push, 1));
		__pragma(warning(disable: 4191));
		pFun_XLogV = NULL;
		pFun_BdDebugReport = NULL;
		pFun_XLogAddIndent = NULL;
		pFun_GetLogController = NULL;
		__pragma(warning(pop));

		HMODULE hDLL = m_hModule;
		m_hModule = NULL;
		if (hDLL)
		{
			FreeLibrary(hDLL);
			hDLL = NULL;
		}
		bInited = FALSE;
		return S_OK;
	}
	void LogVInternal(LogClass uClass, LPCWSTR pszTag, LPCWSTR pszFmt, va_list args)
	{
		if (m_nAvailable != 1) return;
		//MULTI_THREAD_GUARD(m_CS);
		CheckInit();
		if (pFun_XLogV)
			pFun_XLogV(uClass, pszTag, pszFmt, args);
	}
	void XLogAddIndentInternal(int indent)
	{
		if (m_nAvailable != 1) return;
		//MULTI_THREAD_GUARD(m_CS);
		CheckInit();
		if (pFun_XLogAddIndent)
			pFun_XLogAddIndent(indent);
	}
	void BdDebugReportInternal(const wchar_t* filename, int line, const wchar_t* expr)
	{
		if (m_nAvailable != 1) return;
		//MULTI_THREAD_GUARD(m_CS);
		CheckInit();
		if (pFun_BdDebugReport)
			pFun_BdDebugReport(filename, line, expr);
	}
	HRESULT GetLogControllerInternal(ILogController** pLog)
	{
		if (m_nAvailable != 1) return E_ACCESSDENIED;
		//MULTI_THREAD_GUARD(m_CS);
		CheckInit();
		if (pFun_GetLogController)
			return pFun_GetLogController(pLog);
		return E_FAIL;
	}
};

#ifdef XLOG_TAGNAME_MODULE
#define XTAG(str) XLogTag(XLOG_TAGNAME_MODULE L";" str)
#define XTAGDEFAULT XLogTag(XLOG_TAGNAME_MODULE)
#else
#define XTAG(str) XLogTag(str)
#define XTAGDEFAULT XLogTag(L"")
#endif


#define CALL_XLOG_ARGV(c, t, f) va_list args;va_start(args, f); XLogInterface::LogV(c, t.tag, f, args); va_end(args);
#include <stdarg.h>

#ifndef DISABLE_XLOG

/// 包装字符串类型参数，用于函数重载
struct XLogTag
{
	explicit XLogTag(const wchar_t* t): tag(t) {}
	const wchar_t* tag;
};

inline void XLog(LogClass c, XLogTag tag, const wchar_t* pszFmt, ...)
{
	CALL_XLOG_ARGV(c, tag, pszFmt);
}
inline void XLog(LogClass c, const wchar_t* pszFmt, ...)
{
	CALL_XLOG_ARGV(c, XTAGDEFAULT, pszFmt);
}
inline void XLog(XLogTag tag, const wchar_t* pszFmt, ...)
{
	CALL_XLOG_ARGV(LOG_CLASS_INFO, tag, pszFmt);
}
inline void XLog(const wchar_t* pszFmt, ...)
{
	CALL_XLOG_ARGV(LOG_CLASS_INFO, XTAGDEFAULT, pszFmt);
}
#define LogTag XLogTag
#else

#define XLogTag __noop
#define XLog __noop
#define LogTag XLogTag
#endif

// XLog快捷方式
#ifndef DISABLE_XLOG
#define XLogDebug(...)    XLog(LOG_CLASS_DEBUG, __VA_ARGS__)
#define XLogInfo(...)     XLog(LOG_CLASS_INFO, __VA_ARGS__)
#define XLogWarning(...)  XLog(LOG_CLASS_WARNING, __VA_ARGS__)
#define XLogError(...)    XLog(LOG_CLASS_ERROR, __VA_ARGS__)
#define XLogCritical(...) XLog(LOG_CLASS_CRITICAL, __VA_ARGS__)
#else
#define XLogDebug         __noop
#define XLogInfo          __noop
#define XLogWarning       __noop
#define XLogError         __noop
#define XLogCritical      __noop
#endif

#ifndef DISABLE_XLOG

// 预定义tag
#define LT_PERF    L"perf;"

#define XLOG_PERF_TAG(xtag, ...)		XLogInfo(XTAG( LT_PERF xtag ), __VA_ARGS__ )

#define XLOG_PERF_BEGIN(xtag, ...)		XLOG_PERF_TAG( xtag, __VA_ARGS__ )
#define XLOG_PERF_END(xtag, statement)	ON_LEAVE( XLOG_PERF_TAG( xtag, statement ) )

#else

#define LT_PERF
#define XLOG_PERF_TAG __noop
#define XLOG_PERF_BEGIN __noop
#define XLOG_PERF_END __noop

#endif


// indent
struct XLogIndenter
{
	explicit XLogIndenter(int value) : m_value(value)
	{
		XLogInterface::LogAddIndent(value);
	}
	~XLogIndenter()
	{
		XLogInterface::LogAddIndent(-m_value);
	}

	int m_value;
};

// 函数trace

#endif // BDIME_XLOG_H

