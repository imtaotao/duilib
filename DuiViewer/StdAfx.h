#pragma once

#define WIN32_LEAN_AND_MEAN	
#define _CRT_SECURE_NO_DEPRECATE

#include <windows.h>
#include <objbase.h>
#include <atlbase.h>
#include <atlstr.h>
#include <atltypes.h>


#if (_ATL_VER >= 0x0700)
#define _WTL_NO_CSTRING
#define _WTL_NO_WTYPES
#define _WTL_NO_UNION_CLASSES
#endif
#include <atlstr.h>
#include <wtl/atlapp.h>
#include <wtl/atlmisc.h>
#include <atltypes.h>
#include <atlutil.h>
#include <wtl/atlctrls.h>
#include <wtl/atlctrlw.h>
#include <wtl/atldlgs.h>
#include <wtl/atlframe.h>
#include <atltime.h>
#include <atlsync.h>
#include <map>
#include <set>
#include <vector>
#include <list>
#include <deque>
#include <string>
#include <algorithm>

#if _MSC_VER >= 1300
#include <atlstr.h>
#else
#include <atlapp.h>
#include <atlmisc.h>
#include <minibase.h>
#endif

extern CAppModule _Module;	


#include "..\DuiLib\UIlib.h"

using namespace DuiLib;

