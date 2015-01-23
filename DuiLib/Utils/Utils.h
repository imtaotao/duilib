#ifndef __UTILS_H__
#define __UTILS_H__

#pragma once
#include <atldef.h>

namespace DuiLib
{
	/////////////////////////////////////////////////////////////////////////////////////
	//

	class STRINGorID
	{
	public:
		STRINGorID(LPCTSTR lpString) : m_lpstr(lpString)
		{ }
		STRINGorID(UINT nID) : m_lpstr(MAKEINTRESOURCE(nID))
		{ }
		LPCTSTR m_lpstr;
	};

	/////////////////////////////////////////////////////////////////////////////////////
	//

	class UILIB_API CPoint : public tagPOINT
	{
	public:
		CPoint();
		CPoint(const POINT& src);
		CPoint(int x, int y);
		CPoint(LPARAM lParam);
	};


	/////////////////////////////////////////////////////////////////////////////////////
	//

	class UILIB_API CSize : public tagSIZE
	{
	public:
		CSize();
		CSize(const SIZE& src);
		CSize(const RECT rc);
		CSize(int cx, int cy);
	};


	/////////////////////////////////////////////////////////////////////////////////////
	//

	class UILIB_API CDuiRect : public tagRECT
	{
	public:
		CDuiRect();
		CDuiRect(const RECT& src);
		CDuiRect(int iLeft, int iTop, int iRight, int iBottom);

		int GetWidth() const;
		int GetHeight() const;
		void Empty();
		bool IsNull() const;
		void Join(const RECT& rc);
		void ResetOffset();
		void Normalize();
		void Offset(int cx, int cy);
		void Inflate(int cx, int cy);
		void Deflate(int cx, int cy);
		void Union(CDuiRect& rc);
	};

	/////////////////////////////////////////////////////////////////////////////////////
	//

	class UILIB_API CStdPtrArray
	{
	public:
		CStdPtrArray(int iPreallocSize = 0);
		CStdPtrArray(const CStdPtrArray& src);
		~CStdPtrArray();

		void Empty();
		void Resize(int iSize);
		bool IsEmpty() const;
		int Find(LPVOID iIndex) const;
		bool Add(LPVOID pData);
		bool SetAt(int iIndex, LPVOID pData);
		bool InsertAt(int iIndex, LPVOID pData);
		bool Remove(int iIndex);
		int GetSize() const;
		LPVOID* GetData();

		LPVOID GetAt(int iIndex) const;
		LPVOID operator[] (int nIndex) const;

	protected:
		LPVOID* m_ppVoid;
		int m_nCount;
		int m_nAllocated;
	};


	/////////////////////////////////////////////////////////////////////////////////////
	//

	class UILIB_API CStdValArray
	{
	public:
		CStdValArray(int iElementSize, int iPreallocSize = 0);
		~CStdValArray();

		void Empty();
		bool IsEmpty() const;
		bool Add(LPCVOID pData);
		bool Remove(int iIndex);
		int GetSize() const;
		LPVOID GetData();

		LPVOID GetAt(int iIndex) const;
		LPVOID operator[] (int nIndex) const;

	protected:
		LPBYTE m_pVoid;
		int m_iElementSize;
		int m_nCount;
		int m_nAllocated;
	};


	/////////////////////////////////////////////////////////////////////////////////////
	//

	class UILIB_API CDuiString
	{
	public:
		enum { MAX_LOCAL_STRING_LEN = 63 };

		CDuiString();
		CDuiString(const TCHAR ch);
		CDuiString(const CDuiString& src);
		CDuiString(LPCTSTR lpsz, int nLen = -1);
		~CDuiString();

		void Empty();
		int GetLength() const;
		bool IsEmpty() const;
		TCHAR GetAt(int nIndex) const;
		void Append(LPCTSTR pstr);
		void Assign(LPCTSTR pstr, int nLength = -1);
		LPCTSTR GetData() const;

		void SetAt(int nIndex, TCHAR ch);
		operator LPCTSTR() const;

		TCHAR operator[] (int nIndex) const;
		const CDuiString& operator=(const CDuiString& src);
		const CDuiString& operator=(const TCHAR ch);
		const CDuiString& operator=(LPCTSTR pstr);
#ifdef _UNICODE
		const CDuiString& CDuiString::operator=(LPCSTR lpStr);
		const CDuiString& CDuiString::operator+=(LPCSTR lpStr);
#else
		const CDuiString& CDuiString::operator=(LPCWSTR lpwStr);
		const CDuiString& CDuiString::operator+=(LPCWSTR lpwStr);
#endif
		CDuiString operator+(const CDuiString& src) const;
		CDuiString operator+(LPCTSTR pstr) const;
		const CDuiString& operator+=(const CDuiString& src);
		const CDuiString& operator+=(LPCTSTR pstr);
		const CDuiString& operator+=(const TCHAR ch);

		bool operator == (LPCTSTR str) const;
		bool operator != (LPCTSTR str) const;
		bool operator <= (LPCTSTR str) const;
		bool operator <  (LPCTSTR str) const;
		bool operator >= (LPCTSTR str) const;
		bool operator >  (LPCTSTR str) const;

		int Compare(LPCTSTR pstr) const;
		int CompareNoCase(LPCTSTR pstr) const;

		void MakeUpper();
		void MakeLower();

		CDuiString Left(int nLength) const;
		CDuiString Mid(int iPos, int nLength = -1) const;
		CDuiString Right(int nLength) const;

		int Find(TCHAR ch, int iPos = 0) const;
		int Find(LPCTSTR pstr, int iPos = 0) const;
		int ReverseFind(TCHAR ch) const;
		int Replace(LPCTSTR pstrFrom, LPCTSTR pstrTo);

		int __cdecl Format(LPCTSTR pstrFormat, ...);
        int __cdecl Format(LPCTSTR pstrFormat, va_list Args);
		int __cdecl SmallFormat(LPCTSTR pstrFormat, ...);

	protected:
		LPTSTR m_pstr;
		TCHAR m_szBuffer[MAX_LOCAL_STRING_LEN + 1];
	};


	/////////////////////////////////////////////////////////////////////////////////////
	//

	struct TITEM
	{
		CDuiString Key;
		LPVOID Data;
		struct TITEM* pPrev;
		struct TITEM* pNext;
	};

	class UILIB_API CStdStringPtrMap
	{
	public:
		CStdStringPtrMap(int nSize = 83);
		~CStdStringPtrMap();

		void Resize(int nSize = 83);
		LPVOID Find(LPCTSTR key, bool optimize = true) const;
		bool Insert(LPCTSTR key, LPVOID pData);
		LPVOID Set(LPCTSTR key, LPVOID pData);
		bool Remove(LPCTSTR key);
		void RemoveAll();
		int GetSize() const;
		LPCTSTR GetAt(int iIndex) const;
		LPCTSTR operator[] (int nIndex) const;

	protected:
		TITEM** m_aT;
		int m_nBuckets;
		int m_nCount;
	};

	/////////////////////////////////////////////////////////////////////////////////////
	//

	class UILIB_API CWaitCursor
	{
	public:
		CWaitCursor();
		~CWaitCursor();

	protected:
		HCURSOR m_hOrigCursor;
	};

	/////////////////////////////////////////////////////////////////////////////////////
	//

	class CVariant : public VARIANT
	{
	public:
		CVariant() 
		{ 
			VariantInit(this); 
		}
		CVariant(int i)
		{
			VariantInit(this);
			this->vt = VT_I4;
			this->intVal = i;
		}
		CVariant(float f)
		{
			VariantInit(this);
			this->vt = VT_R4;
			this->fltVal = f;
		}
		CVariant(LPOLESTR s)
		{
			VariantInit(this);
			this->vt = VT_BSTR;
			this->bstrVal = s;
		}
		CVariant(IDispatch *disp)
		{
			VariantInit(this);
			this->vt = VT_DISPATCH;
			this->pdispVal = disp;
		}

		~CVariant() 
		{ 
			VariantClear(this); 
		}
	};

	class CMemLockStream : public IStream
	{
	public:
		CMemLockStream(LPBYTE pBytes, UINT uSize)
			: m_pBytes(pBytes), m_uSize(uSize)
			, m_uPos(0) , m_nRefCnt(0)
		{

		}
		virtual ~CMemLockStream()
		{
			ATLASSERT(!m_nRefCnt);
		}
		virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID iid, void ** ppvObject)
		{ 
			if (iid == __uuidof(IUnknown) || iid == __uuidof(IStream))
			{
				*ppvObject = static_cast<IStream*>(this);
				AddRef();
				return S_OK;
			} 
			else
				return E_NOINTERFACE; 
		}
		virtual ULONG STDMETHODCALLTYPE AddRef( void )
		{
			InterlockedIncrement(&m_nRefCnt);
			return m_nRefCnt;
		}

		virtual ULONG STDMETHODCALLTYPE Release( void )
		{
			InterlockedDecrement(&m_nRefCnt);
			if (m_nRefCnt <= 0)
			{
				delete this;
				return 0;
			}
			return m_nRefCnt;
		}
		virtual HRESULT STDMETHODCALLTYPE Read(void* pv, ULONG cb, ULONG* pcbRead)
		{
			if (!pv)
			{
				return E_INVALIDARG;
			}
			if (!m_pBytes)
			{
				return E_ACCESSDENIED;
			}		
			if (m_uSize > 0  && m_uPos < m_uSize)
			{
				ULONG nRead = __min(cb, m_uSize - m_uPos);
				if (nRead)
				{
					memcpy(pv, m_pBytes + m_uPos, nRead);
				}
				if (pcbRead)
				{
					*pcbRead = nRead;
				}
				m_uPos += nRead;
				if (nRead != cb)
				{
					return S_FALSE;
				}
				return S_OK;			
			}
			return E_FAIL;
		}
		virtual HRESULT STDMETHODCALLTYPE Seek(LARGE_INTEGER dlibMove, DWORD dwOrigin, ULARGE_INTEGER* lpNewFilePointer)
		{
			if (!m_pBytes || !m_uSize)
			{
				return E_FAIL;
			}		
			UINT nNewPos = m_uPos;
			switch (dwOrigin)
			{
			case STREAM_SEEK_SET:
				nNewPos = 0;			
				break;
			case STREAM_SEEK_CUR:
				break;
			case STREAM_SEEK_END:
				nNewPos = m_uSize - 1;
				break;
			default:
				return STG_E_SEEKERROR;
				break;
			}
			nNewPos += (ULONG)dlibMove.QuadPart;
			HRESULT hr = S_OK;
			if (dlibMove.u.LowPart >= 0x80000000 &&	nNewPos >= dlibMove.u.LowPart)
			{			
				hr = STG_E_SEEKERROR;
				goto end;
			}

			m_uPos = nNewPos;
end:
			if (lpNewFilePointer) 
			{
				lpNewFilePointer->LowPart = nNewPos;
			}
			return S_OK;
		}

		virtual HRESULT STDMETHODCALLTYPE Stat(STATSTG* pstatstg, DWORD grfStatFlag) 
		{
			memset(pstatstg, 0, sizeof(STATSTG));
			pstatstg->pwcsName = NULL;
			pstatstg->type     = STGTY_STREAM;
			pstatstg->cbSize.LowPart   = (DWORD)m_uSize;
			return S_OK;
		}
		virtual HRESULT STDMETHODCALLTYPE Write(void const*, ULONG, ULONG*)
		{
			return E_NOTIMPL;
		}
		virtual HRESULT STDMETHODCALLTYPE SetSize(ULARGE_INTEGER)
		{ 
			return E_NOTIMPL;   
		}

		virtual HRESULT STDMETHODCALLTYPE CopyTo(IStream*, ULARGE_INTEGER, ULARGE_INTEGER*,
			ULARGE_INTEGER*) 
		{ 
			return E_NOTIMPL;   
		}

		virtual HRESULT STDMETHODCALLTYPE Commit(DWORD)                                      
		{ 
			return E_NOTIMPL;   
		}

		virtual HRESULT STDMETHODCALLTYPE Revert(void)                                       
		{ 
			return E_NOTIMPL;   
		}

		virtual HRESULT STDMETHODCALLTYPE LockRegion(ULARGE_INTEGER, ULARGE_INTEGER, DWORD)              
		{ 
			return E_NOTIMPL;   
		}

		virtual HRESULT STDMETHODCALLTYPE UnlockRegion(ULARGE_INTEGER, ULARGE_INTEGER, DWORD)            
		{ 
			return E_NOTIMPL;   
		}

		virtual HRESULT STDMETHODCALLTYPE Clone(IStream **)                                  
		{ 
			return E_NOTIMPL;   
		}
	protected:
		BYTE* m_pBytes;	
		UINT m_uSize;
		UINT m_uPos;
		LONG m_nRefCnt;
	};

}// namespace DuiLib

#endif // __UTILS_H__