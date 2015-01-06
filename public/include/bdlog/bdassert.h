#ifndef BDIME_ASSERT_H
#define BDIME_ASSERT_H

/** @file
 *  Baidu Assert 宏
 *
 *  BD_VERIFY系列: 出错后，打印错误日志，DEBUG版本出错后弹窗暂停程序运行
 *  BD_CHECK系列: 出错后，打印警告日志
 *
 */

#include "bdlog.h"
#include <windef.h>

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
// BD_VERIFY系列

#define DEBUG_BREAK(expr) 
#ifndef WIDESTRING
#define WIDESTRING2(str) L##str
#define WIDESTRING(str) WIDESTRING2(str)
#endif


#define BD_REPORT_ERROR(expr) \
	{\
	DEBUG_BREAK(WIDESTRING(expr));\
	HRESULT _hr_ = ::GetLastError(); \
	XLogError(XTAG(L"assert"), L"ASSERT(%s) LastError=0X%X @ %S(%d)", WIDESTRING(expr), _hr_, __FILE__, __LINE__);	\
	}

#define BD_REPORT_ERROR2(expr, fmt, ...) \
	{\
	DEBUG_BREAK(WIDESTRING(expr)); \
	HRESULT _hr_ = ::GetLastError(); \
	XLogError(LogTag(L"assert"), L"ASSERT(%s) LastError=0X%X @ %S(%d)" fmt, WIDESTRING(expr), _hr_, __FILE__, __LINE__, __VA_ARGS__);	\
	}

#define BD_VERIFY_BASE(expr, exprstr, statement) \
{ \
if (!(expr)) { BD_REPORT_ERROR(exprstr);statement; } \
}

#define BD_VERIFY_BASE_WITH_MSG(expr, exprstr, statement, fmt, ...) \
{		\
	if (!(expr)) { \
	BD_REPORT_ERROR2(exprstr, fmt, __VA_ARGS__) \
	statement; \
	} \
}

#define BD_VERIFY(expr, statement) \
BD_VERIFY_BASE(expr, #expr, statement)

#define BD_VERIFY_RETURN(expr) \
 BD_VERIFY_BASE(expr, #expr, return)

#define BD_VERIFY_RETURN_FALSE(expr) \
	BD_VERIFY_BASE(expr, #expr, return FALSE)

#define BD_VERIFY_HR(expr, statement) \
	{ \
		HRESULT hr_ = expr; \
		BD_VERIFY_BASE_WITH_MSG(SUCCEEDED(hr_), #expr, statement, L"HR=0X%X", hr_); \
	}

#define BD_VERIFY_LR(expr, statement) \
	{ \
	HRESULT hr_ = HRESULT_FROM_WIN32(expr); \
	BD_VERIFY_BASE_WITH_MSG(SUCCEEDED(hr_), #expr, statement, L"HR=0X%X", hr_); \
	}

#define BD_VERIFY_LR_RETURN_LR(expr) \
	{ \
	LRESULT lr_ = (expr);			\
	BD_VERIFY_LR(lr_, return lr_);			\
	}
#define BD_VERIFY_LR_RETURN_HR(expr) \
	{ \
	BD_VERIFY_LR((expr), return hr_);			\
	}


#define BD_VERIFY_HR_RETURN_HR(expr) \
	BD_VERIFY_HR(expr, return hr_)

#define BD_VERIFY_WIN32(expr, statement) \
	{		\
		if (!(expr)) { \
			DWORD dwErr = ::GetLastError(); \
			HRESULT hr_ = HRESULT_FROM_WIN32(dwErr); \
			BD_REPORT_ERROR2(#expr, L"lasterror=%u(0X%X)", dwErr, hr_); \
			statement; \
		}		\
	}

#define BD_VERIFY_RETURN_HRWIN32(expr) \
	BD_VERIFY_WIN32(expr, return hr_)

#define BD_VERIFY_REG(ret, statement) \
	BD_VERIFY_HR(HRESULT_FROM_WIN32(static_cast<unsigned long>(ret)), statement)

#define BD_VERIFY_RETURN_REGHR(ret) \
	BD_VERIFY_RETURN_HR(HRESULT_FROM_WIN32(static_cast<unsigned long>(ret)))






//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
// BD_CHECK系列

#define BD_REPORT_WARNING(expr) \
	{	\
		HRESULT _hr_ = ::GetLastError(); \
		XLogWarning(XTAG(L"assert"), L"ASSERT(%s) LastError=0X%X @ %S(%d)", WIDESTRING(expr), _hr_, __FILE__, __LINE__);	\
		}

#define BD_REPORT_WARNING2(expr, fmt, ...) \
	{		\
	HRESULT _hr_ = ::GetLastError(); \
	XLogWarning(XTAG(L"assert"), L"ASSERT(%s) LastError=0X%X @ %S(%d) " fmt, WIDESTRING(expr), _hr_, __FILE__, __LINE__, __VA_ARGS__); \
	}

#define BD_CHECK_BASE(expr, exprstr, statement) \
{		\
	if (!(expr)) { \
	BD_REPORT_WARNING(exprstr); \
	statement; \
	}		\
		}

#define BD_CHECK_BASE_WITH_MSG(expr, exprstr, statement, fmt, ...) \
	{	\
if (!(expr)) { \
	BD_REPORT_WARNING2(exprstr, fmt, __VA_ARGS__) \
	statement; \
	}	\
}

#define BD_CHECK(expr, statement) \
	BD_CHECK_BASE(expr, #expr, statement)

#define BD_CHECK_RETURN(expr) \
	BD_CHECK_BASE(expr, #expr, return)

#define BD_CHECK_RETURN_FALSE(expr) \
	BD_CHECK_BASE(expr, #expr, return FALSE)

#define BD_CHECK_HR(expr, statement) \
 { \
	HRESULT hr_ = expr; \
	BD_CHECK_BASE_WITH_MSG(SUCCEEDED(hr_), #expr, statement, L"HR=0X%X", hr_); \
}

#define BD_CHECK_HR_RETURN_HR(expr) \
	BD_CHECK_HR(expr, return hr_)


#define BD_CHECK_LR(expr, statement) \
	{ \
	HRESULT hr_ = HRESULT_FROM_WIN32(expr); \
	BD_CHECK_BASE_WITH_MSG(SUCCEEDED(hr_), #expr, statement, L"HR=0X%X", hr_); \
	}

#define BD_CHECK_RETURN_HRWIN32(expr) \
	BD_CHECK_WIN32(expr, return hr_)

#define BD_CHECK_LASTERROR(ret, statement) \
	BD_CHECK_HR(HRESULT_FROM_WIN32(ret), statement)

#define BD_CHECK_RETURN_LASTERROR(ret) \
	BD_CHECK_HR_RETURN_HR(HRESULT_FROM_WIN32(static_cast<unsigned long>(ret)))

#define BD_CHECK_REG(ret, statement) \
	BD_CHECK_HR(HRESULT_FROM_WIN32(static_cast<unsigned long>(ret)), statement)

#define BD_CHECK_RETURN_REGHR(ret) \
	BD_CHECK_HR_RETURN_HR(HRESULT_FROM_WIN32(static_cast<unsigned long>(ret)))


#if defined(DISABLE_XLOG_FUNCTION) || defined(DISABLE_XLOG)
#define XLOG_FUNCTION
#define XLOG_FUNCTION_WITH_PARAM1(fmt1, arg1)
#define XLOG_FUNCTION_WITH_PARAM2(fmt1, arg1, fmt2, arg2)
#define XLOG_FUNCTION_WITH_PARAM3(fmt1, arg1, fmt2, arg2, fmt3, arg3)
#define XLOG_FUNCTION_WITH_PARAM4(fmt1, arg1, fmt2, arg2, fmt3, arg3, fmt4, arg4)
#define XLOG_FUNCTION_WITH_PARAM5(fmt1, arg1, fmt2, arg2, fmt3, arg3, fmt4, arg4, fmt5, arg5)
#define XLOG_FUNCTION_WITH_PARAM6(fmt1, arg1, fmt2, arg2, fmt3, arg3, fmt4, arg4, fmt5, arg5, fmt6, arg6)
#else
#define XLOG_FUNCTION \
	XLogDebug(XTAG(L"func"), L"FUNCTION: %s", WIDESTRING(__FUNCTION__));
	
#define XLOG_FUNCTION_WITH_PARAM1(fmt1, arg1) \
	XLogDebug(XTAG(L"func"), L"FUNCTION: %s(" WIDESTRING(#arg1) L"=" fmt1 L")", WIDESTRING(__FUNCTION__), arg1);
	

#define XLOG_FUNCTION_WITH_PARAM2(fmt1, arg1, fmt2, arg2) \
	XLogDebug(XTAG(L"func"), L"FUNCTION: %s( " \
	WIDESTRING(#arg1) L"=" fmt1 \
	L" , " \
	WIDESTRING(#arg2) L"=" fmt2 \
	L" )", \
	WIDESTRING(__FUNCTION__), arg1, arg2);
	

#define XLOG_FUNCTION_WITH_PARAM3(fmt1, arg1, fmt2, arg2, fmt3, arg3) \
	XLogDebug(XTAG(L"func"), L"FUNCTION: %s( " \
	WIDESTRING(#arg1) L"=" fmt1 \
	L" , " \
	WIDESTRING(#arg2) L"=" fmt2 \
	L" , " \
	WIDESTRING(#arg3) L"=" fmt3 \
	L" )", \
	WIDESTRING(__FUNCTION__), arg1, arg2, arg3);
	

#define XLOG_FUNCTION_WITH_PARAM4(fmt1, arg1, fmt2, arg2, fmt3, arg3, fmt4, arg4) \
	XLogDebug(XTAG(L"func"), L"FUNCTION: %s( " \
	WIDESTRING(#arg1) L"=" fmt1 \
	L" , " \
	WIDESTRING(#arg2) L"=" fmt2 \
	L" , " \
	WIDESTRING(#arg3) L"=" fmt3 \
	L" , " \
	WIDESTRING(#arg4) L"=" fmt4 \
	L" )", \
	WIDESTRING(__FUNCTION__), arg1, arg2, arg3, arg4);
	

#define XLOG_FUNCTION_WITH_PARAM5(fmt1, arg1, fmt2, arg2, fmt3, arg3, fmt4, arg4, fmt5, arg5) \
	XLogDebug(XTAG(L"func"), L"FUNCTION: %s( " \
	WIDESTRING(#arg1) L"=" fmt1 \
	L" , " \
	WIDESTRING(#arg2) L"=" fmt2 \
	L" , " \
	WIDESTRING(#arg3) L"=" fmt3 \
	L" , " \
	WIDESTRING(#arg4) L"=" fmt4 \
	L" , " \
	WIDESTRING(#arg5) L"=" fmt5 \
	L" )", \
	WIDESTRING(__FUNCTION__), arg1, arg2, arg3, arg4, arg5); 	

#define XLOG_FUNCTION_WITH_PARAM6(fmt1, arg1, fmt2, arg2, fmt3, arg3, fmt4, arg4, fmt5, arg5, fmt6, arg6) \
	XLogDebug(XTAG(L"func"), L"FUNCTION: %s( " \
	WIDESTRING(#arg1) L"=" fmt1 \
	L" , " \
	WIDESTRING(#arg2) L"=" fmt2 \
	L" , " \
	WIDESTRING(#arg3) L"=" fmt3 \
	L" , " \
	WIDESTRING(#arg4) L"=" fmt4 \
	L" , " \
	WIDESTRING(#arg5) L"=" fmt5 \
	L" , " \
	WIDESTRING(#arg6) L"=" fmt6 \
	L" )", \
	WIDESTRING(__FUNCTION__), arg1, arg2, arg3, arg4, arg5, arg6); 

#define XLOG_FUNCTION_WITH_PARAM7(fmt1, arg1, fmt2, arg2, fmt3, arg3, fmt4, arg4, fmt5, arg5, fmt6, arg6, fmt7, arg7) \
	XLogDebug(XTAG(L"func"), L"FUNCTION: %s( " \
	WIDESTRING(#arg1) L"=" fmt1 \
	L" , " \
	WIDESTRING(#arg2) L"=" fmt2 \
	L" , " \
	WIDESTRING(#arg3) L"=" fmt3 \
	L" , " \
	WIDESTRING(#arg4) L"=" fmt4 \
	L" , " \
	WIDESTRING(#arg5) L"=" fmt5 \
	L" , " \
	WIDESTRING(#arg6) L"=" fmt6 \
	L" , " \
	WIDESTRING(#arg7) L"=" fmt7 \
	L" )", \
	WIDESTRING(__FUNCTION__), arg1, arg2, arg3, arg4, arg5, arg6, arg7); 
	
#endif

#ifndef SAFE_DELETE
#define SAFE_DELETE(ptr) \
	if ((ptr))\
{ \
	delete (ptr);\
	(ptr) = NULL; \
}
#endif




#ifndef BD_AUTO_RELEASE_CONCAT_INNER
#define BD_AUTO_RELEASE_CONCAT_INNER(a,b) a##b
#endif
#ifndef BD_AUTO_RELEASE_CONCAT
#define BD_AUTO_RELEASE_CONCAT(a,b) BD_AUTO_RELEASE_CONCAT_INNER(a,b)
#endif
#ifndef BDAR_LINE_NAME
#define BDAR_LINE_NAME(prefix) BD_AUTO_RELEASE_CONCAT(prefix,__LINE__)
#endif
#ifndef ON_LEAVE
#define ON_LEAVE(statement) \
struct BDAR_LINE_NAME(ols_) { \
    ~BDAR_LINE_NAME(ols_)() { statement; } \
} BDAR_LINE_NAME(olv_);
#endif
#ifndef ON_LEAVE_1
#define ON_LEAVE_1(statement, type, var) \
struct BDAR_LINE_NAME(ols_) { \
    type var; \
    BDAR_LINE_NAME(ols_)(type v): var(v) {} \
    ~BDAR_LINE_NAME(ols_)() { statement; } \
} BDAR_LINE_NAME(olv_)(var);
#endif
#ifndef ON_LEAVE_2
#define ON_LEAVE_2(statement, type1, var1, type2, var2) \
struct BDAR_LINE_NAME(ols_) { \
    type1 var1; type2 var2; \
    BDAR_LINE_NAME(ols_)(type1 v1, type2 v2): var1(v1), var2(v2) {} \
    ~BDAR_LINE_NAME(ols_)() { statement; } \
} BDAR_LINE_NAME(olv_)(var1, var2);
#endif
#ifndef ON_LEAVE_3
#define ON_LEAVE_3(statement, type1, var1, type2, var2, type3, var3) \
struct BDAR_LINE_NAME(ols_) { \
    type1 var1; type2 var2; type3 var3; \
    BDAR_LINE_NAME(ols_)(type1 v1, type2 v2, type3 v3): var1(v1), var2(v2), var3(v3) {} \
    ~BDAR_LINE_NAME(ols_)() { statement; } \
} BDAR_LINE_NAME(olv_)(var1, var2, var3);
#endif
#ifndef ON_LEAVE_4
#define ON_LEAVE_4(statement, type1, var1, type2, var2, type3, var3, type4, var4) \
struct BDAR_LINE_NAME(ols_) { \
    type1 var1; type2 var2; type3 var3; type4 var4; \
    BDAR_LINE_NAME(ols_)(type1 v1, type2 v2, type3 v3, type4 v4): var1(v1), var2(v2), var3(v3), var4(v4) {} \
    ~BDAR_LINE_NAME(ols_)() { statement; } \
} BDAR_LINE_NAME(olv_)(var1, var2, var3, var4);
#endif





#ifndef VALID_RET
#define VALID_RET( b, ret ) if ( !( b ) ) { XLogError( false ); return ret; }
#endif

#ifndef CHECK_RET
#define CHECK_RET( b, ret ) if ( !( b ) ) {  return ret; }
#endif

#ifndef CHECK
#define CHECK( b ) if ( !( b ) ) { return E_FAIL; }
#endif

#ifndef VALID
#define VALID( b ) if ( !( b ) ) { XLogError( false ); return E_FAIL; }
#endif

#ifndef VALIDARG
#define VALIDARG( b ) if ( !( b ) ) { XLogError( false ); return E_INVALIDARG; }
#endif

#ifndef CHECK_PTR
#define CHECK_PTR( x ) if ( ( x ) == NULL ) { return E_FAIL; }
#endif

#ifndef VALID_PTR
#define VALID_PTR( x ) if ( ( x ) == NULL ) { XLogError( false ); return E_FAIL; }
#endif

#ifndef VALIDARG_PTR
#define VALIDARG_PTR( x ) if ( ( x ) == NULL ) { XLogError( false ); return E_INVALIDARG; }
#endif

#ifndef CHECK_HRESULT
#define CHECK_HRESULT( h ) { HRESULT _hr = ( h ); if ( FAILED( _hr ) ) return ( _hr ); }
#endif

#ifndef VALID_HRESULT
#define VALID_HRESULT( h ) { HRESULT _hr = ( h ); if ( FAILED( _hr ) ) { XLogError( false ); return ( _hr ); } }
#endif

#endif
