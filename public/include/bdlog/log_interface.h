

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Sat Oct 18 16:36:29 2014
 */
/* Compiler settings for logctl.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 7.00.0555 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __log_interface_h__
#define __log_interface_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ILogHistoryMgr_FWD_DEFINED__
#define __ILogHistoryMgr_FWD_DEFINED__
typedef interface ILogHistoryMgr ILogHistoryMgr;
#endif 	/* __ILogHistoryMgr_FWD_DEFINED__ */


#ifndef __ILogOutputDevice_FWD_DEFINED__
#define __ILogOutputDevice_FWD_DEFINED__
typedef interface ILogOutputDevice ILogOutputDevice;
#endif 	/* __ILogOutputDevice_FWD_DEFINED__ */


#ifndef __ILogController_FWD_DEFINED__
#define __ILogController_FWD_DEFINED__
typedef interface ILogController ILogController;
#endif 	/* __ILogController_FWD_DEFINED__ */


#ifndef __ILogController2_FWD_DEFINED__
#define __ILogController2_FWD_DEFINED__
typedef interface ILogController2 ILogController2;
#endif 	/* __ILogController2_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __ILogHistoryMgr_INTERFACE_DEFINED__
#define __ILogHistoryMgr_INTERFACE_DEFINED__

/* interface ILogHistoryMgr */
/* [helpstring][uuid][unique][nonextensible][dual][object] */ 


EXTERN_C const IID IID_ILogHistoryMgr;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C8CD69A6-4B55-4694-AEED-9F25AD08B65B")
    ILogHistoryMgr : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE GetLogCount( 
            UINT *pCount) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetLogInfo( 
            UINT uIndex,
            unsigned __int64 *pID,
            __int64 *pTime,
            INT *pMillsec,
            UINT *pTID,
            UINT *pClass,
            BSTR *pTag,
            BSTR *pContent) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Lock( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Unlock( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ILogHistoryMgrVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILogHistoryMgr * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILogHistoryMgr * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILogHistoryMgr * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetLogCount )( 
            ILogHistoryMgr * This,
            UINT *pCount);
        
        HRESULT ( STDMETHODCALLTYPE *GetLogInfo )( 
            ILogHistoryMgr * This,
            UINT uIndex,
            unsigned __int64 *pID,
            __int64 *pTime,
            INT *pMillsec,
            UINT *pTID,
            UINT *pClass,
            BSTR *pTag,
            BSTR *pContent);
        
        HRESULT ( STDMETHODCALLTYPE *Lock )( 
            ILogHistoryMgr * This);
        
        HRESULT ( STDMETHODCALLTYPE *Unlock )( 
            ILogHistoryMgr * This);
        
        END_INTERFACE
    } ILogHistoryMgrVtbl;

    interface ILogHistoryMgr
    {
        CONST_VTBL struct ILogHistoryMgrVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILogHistoryMgr_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILogHistoryMgr_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILogHistoryMgr_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ILogHistoryMgr_GetLogCount(This,pCount)	\
    ( (This)->lpVtbl -> GetLogCount(This,pCount) ) 

#define ILogHistoryMgr_GetLogInfo(This,uIndex,pID,pTime,pMillsec,pTID,pClass,pTag,pContent)	\
    ( (This)->lpVtbl -> GetLogInfo(This,uIndex,pID,pTime,pMillsec,pTID,pClass,pTag,pContent) ) 

#define ILogHistoryMgr_Lock(This)	\
    ( (This)->lpVtbl -> Lock(This) ) 

#define ILogHistoryMgr_Unlock(This)	\
    ( (This)->lpVtbl -> Unlock(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILogHistoryMgr_INTERFACE_DEFINED__ */


#ifndef __ILogOutputDevice_INTERFACE_DEFINED__
#define __ILogOutputDevice_INTERFACE_DEFINED__

/* interface ILogOutputDevice */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_ILogOutputDevice;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("225A9013-3AB3-4363-9A74-F2EDC2B8C30C")
    ILogOutputDevice : public IDispatch
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetName( 
            BSTR *pbsName) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Open( 
            BSTR bsConfig) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Close( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Write( 
            unsigned __int64 uID,
            __int64 iTime,
            INT iMillSec,
            UINT uThreadID,
            UINT uClass,
            BSTR bsTag,
            BSTR bsContent) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE Flush( void) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE OnConfigChange( 
            BSTR bsConfig) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE SetLogHistoryMgr( 
            ILogHistoryMgr *pMgr) = 0;
        
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE GetConfig( 
            BSTR bsKey,
            BSTR *bsVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ILogOutputDeviceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILogOutputDevice * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILogOutputDevice * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILogOutputDevice * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ILogOutputDevice * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ILogOutputDevice * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ILogOutputDevice * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ILogOutputDevice * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetName )( 
            ILogOutputDevice * This,
            BSTR *pbsName);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *Open )( 
            ILogOutputDevice * This,
            BSTR bsConfig);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *Close )( 
            ILogOutputDevice * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *Write )( 
            ILogOutputDevice * This,
            unsigned __int64 uID,
            __int64 iTime,
            INT iMillSec,
            UINT uThreadID,
            UINT uClass,
            BSTR bsTag,
            BSTR bsContent);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *Flush )( 
            ILogOutputDevice * This);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *OnConfigChange )( 
            ILogOutputDevice * This,
            BSTR bsConfig);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *SetLogHistoryMgr )( 
            ILogOutputDevice * This,
            ILogHistoryMgr *pMgr);
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *GetConfig )( 
            ILogOutputDevice * This,
            BSTR bsKey,
            BSTR *bsVal);
        
        END_INTERFACE
    } ILogOutputDeviceVtbl;

    interface ILogOutputDevice
    {
        CONST_VTBL struct ILogOutputDeviceVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILogOutputDevice_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILogOutputDevice_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILogOutputDevice_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ILogOutputDevice_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ILogOutputDevice_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ILogOutputDevice_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ILogOutputDevice_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define ILogOutputDevice_GetName(This,pbsName)	\
    ( (This)->lpVtbl -> GetName(This,pbsName) ) 

#define ILogOutputDevice_Open(This,bsConfig)	\
    ( (This)->lpVtbl -> Open(This,bsConfig) ) 

#define ILogOutputDevice_Close(This)	\
    ( (This)->lpVtbl -> Close(This) ) 

#define ILogOutputDevice_Write(This,uID,iTime,iMillSec,uThreadID,uClass,bsTag,bsContent)	\
    ( (This)->lpVtbl -> Write(This,uID,iTime,iMillSec,uThreadID,uClass,bsTag,bsContent) ) 

#define ILogOutputDevice_Flush(This)	\
    ( (This)->lpVtbl -> Flush(This) ) 

#define ILogOutputDevice_OnConfigChange(This,bsConfig)	\
    ( (This)->lpVtbl -> OnConfigChange(This,bsConfig) ) 

#define ILogOutputDevice_SetLogHistoryMgr(This,pMgr)	\
    ( (This)->lpVtbl -> SetLogHistoryMgr(This,pMgr) ) 

#define ILogOutputDevice_GetConfig(This,bsKey,bsVal)	\
    ( (This)->lpVtbl -> GetConfig(This,bsKey,bsVal) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILogOutputDevice_INTERFACE_DEFINED__ */


/* interface __MIDL_itf_logctl_0000_0002 */
/* [local] */ 


enum ELODType
    {	LOD_FILE	= 0,
	LOD_CONSOLE	= ( LOD_FILE + 1 ) ,
	LOD_DEBUGOUTPUT	= ( LOD_CONSOLE + 1 ) ,
	LOD_PIPE	= ( LOD_DEBUGOUTPUT + 1 ) ,
	LOD_MEMORY	= ( LOD_PIPE + 1 ) ,
	LOD_SHARINGMEMORY	= ( LOD_MEMORY + 1 ) 
    } ;

enum EConfigType
    {	Conf_File	= 0,
	Conf_Reg	= ( Conf_File + 1 ) 
    } ;


extern RPC_IF_HANDLE __MIDL_itf_logctl_0000_0002_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_logctl_0000_0002_v0_0_s_ifspec;

#ifndef __ILogController_INTERFACE_DEFINED__
#define __ILogController_INTERFACE_DEFINED__

/* interface ILogController */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_ILogController;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("F04DEBB3-4771-4772-B147-EEE9887F2FB0")
    ILogController : public IDispatch
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Init( 
            BSTR bsConfigDir,
            UINT uLogHistorySize,
            BOOL bMonitorConfigChange) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE UnInit( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE Log( 
            UINT uClass,
            BSTR bsTag,
            BSTR bsContent) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AddIndent( 
            int indent) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AddLOD( 
            BSTR bsName,
            enum ELODType type,
            BSTR bsConfig) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE AddLODEx( 
            BSTR bsName,
            ILogOutputDevice *pDevice,
            BSTR bsConfig) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetLOD( 
            BSTR bsName,
            ILogOutputDevice **ppDevice) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE RemoveLOD( 
            BSTR bsName) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE ChangeLODConfig( 
            BSTR bsName,
            BSTR bsConfig) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetLODConfig( 
            BSTR bsName,
            BSTR bsKey,
            BSTR *bsVal) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetEnabledLODCount( 
            UINT *pCount) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ILogControllerVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILogController * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILogController * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILogController * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ILogController * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ILogController * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ILogController * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ILogController * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE *Init )( 
            ILogController * This,
            BSTR bsConfigDir,
            UINT uLogHistorySize,
            BOOL bMonitorConfigChange);
        
        HRESULT ( STDMETHODCALLTYPE *UnInit )( 
            ILogController * This);
        
        HRESULT ( STDMETHODCALLTYPE *Log )( 
            ILogController * This,
            UINT uClass,
            BSTR bsTag,
            BSTR bsContent);
        
        HRESULT ( STDMETHODCALLTYPE *AddIndent )( 
            ILogController * This,
            int indent);
        
        HRESULT ( STDMETHODCALLTYPE *AddLOD )( 
            ILogController * This,
            BSTR bsName,
            enum ELODType type,
            BSTR bsConfig);
        
        HRESULT ( STDMETHODCALLTYPE *AddLODEx )( 
            ILogController * This,
            BSTR bsName,
            ILogOutputDevice *pDevice,
            BSTR bsConfig);
        
        HRESULT ( STDMETHODCALLTYPE *GetLOD )( 
            ILogController * This,
            BSTR bsName,
            ILogOutputDevice **ppDevice);
        
        HRESULT ( STDMETHODCALLTYPE *RemoveLOD )( 
            ILogController * This,
            BSTR bsName);
        
        HRESULT ( STDMETHODCALLTYPE *ChangeLODConfig )( 
            ILogController * This,
            BSTR bsName,
            BSTR bsConfig);
        
        HRESULT ( STDMETHODCALLTYPE *GetLODConfig )( 
            ILogController * This,
            BSTR bsName,
            BSTR bsKey,
            BSTR *bsVal);
        
        HRESULT ( STDMETHODCALLTYPE *GetEnabledLODCount )( 
            ILogController * This,
            UINT *pCount);
        
        END_INTERFACE
    } ILogControllerVtbl;

    interface ILogController
    {
        CONST_VTBL struct ILogControllerVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILogController_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILogController_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILogController_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ILogController_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ILogController_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ILogController_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ILogController_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define ILogController_Init(This,bsConfigDir,uLogHistorySize,bMonitorConfigChange)	\
    ( (This)->lpVtbl -> Init(This,bsConfigDir,uLogHistorySize,bMonitorConfigChange) ) 

#define ILogController_UnInit(This)	\
    ( (This)->lpVtbl -> UnInit(This) ) 

#define ILogController_Log(This,uClass,bsTag,bsContent)	\
    ( (This)->lpVtbl -> Log(This,uClass,bsTag,bsContent) ) 

#define ILogController_AddIndent(This,indent)	\
    ( (This)->lpVtbl -> AddIndent(This,indent) ) 

#define ILogController_AddLOD(This,bsName,type,bsConfig)	\
    ( (This)->lpVtbl -> AddLOD(This,bsName,type,bsConfig) ) 

#define ILogController_AddLODEx(This,bsName,pDevice,bsConfig)	\
    ( (This)->lpVtbl -> AddLODEx(This,bsName,pDevice,bsConfig) ) 

#define ILogController_GetLOD(This,bsName,ppDevice)	\
    ( (This)->lpVtbl -> GetLOD(This,bsName,ppDevice) ) 

#define ILogController_RemoveLOD(This,bsName)	\
    ( (This)->lpVtbl -> RemoveLOD(This,bsName) ) 

#define ILogController_ChangeLODConfig(This,bsName,bsConfig)	\
    ( (This)->lpVtbl -> ChangeLODConfig(This,bsName,bsConfig) ) 

#define ILogController_GetLODConfig(This,bsName,bsKey,bsVal)	\
    ( (This)->lpVtbl -> GetLODConfig(This,bsName,bsKey,bsVal) ) 

#define ILogController_GetEnabledLODCount(This,pCount)	\
    ( (This)->lpVtbl -> GetEnabledLODCount(This,pCount) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILogController_INTERFACE_DEFINED__ */


#ifndef __ILogController2_INTERFACE_DEFINED__
#define __ILogController2_INTERFACE_DEFINED__

/* interface ILogController2 */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_ILogController2;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("276D2044-0243-4AA2-B90E-AC97A0878D6D")
    ILogController2 : public ILogController
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE InitEx( 
            BSTR bsConfigDir,
            enum EConfigType type,
            UINT uLogHistorySize,
            BOOL bMonitorConfigChange) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetOutputLogLevel( 
            UINT *puLevel) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ILogController2Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ILogController2 * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ILogController2 * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ILogController2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ILogController2 * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ILogController2 * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ILogController2 * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ILogController2 * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE *Init )( 
            ILogController2 * This,
            BSTR bsConfigDir,
            UINT uLogHistorySize,
            BOOL bMonitorConfigChange);
        
        HRESULT ( STDMETHODCALLTYPE *UnInit )( 
            ILogController2 * This);
        
        HRESULT ( STDMETHODCALLTYPE *Log )( 
            ILogController2 * This,
            UINT uClass,
            BSTR bsTag,
            BSTR bsContent);
        
        HRESULT ( STDMETHODCALLTYPE *AddIndent )( 
            ILogController2 * This,
            int indent);
        
        HRESULT ( STDMETHODCALLTYPE *AddLOD )( 
            ILogController2 * This,
            BSTR bsName,
            enum ELODType type,
            BSTR bsConfig);
        
        HRESULT ( STDMETHODCALLTYPE *AddLODEx )( 
            ILogController2 * This,
            BSTR bsName,
            ILogOutputDevice *pDevice,
            BSTR bsConfig);
        
        HRESULT ( STDMETHODCALLTYPE *GetLOD )( 
            ILogController2 * This,
            BSTR bsName,
            ILogOutputDevice **ppDevice);
        
        HRESULT ( STDMETHODCALLTYPE *RemoveLOD )( 
            ILogController2 * This,
            BSTR bsName);
        
        HRESULT ( STDMETHODCALLTYPE *ChangeLODConfig )( 
            ILogController2 * This,
            BSTR bsName,
            BSTR bsConfig);
        
        HRESULT ( STDMETHODCALLTYPE *GetLODConfig )( 
            ILogController2 * This,
            BSTR bsName,
            BSTR bsKey,
            BSTR *bsVal);
        
        HRESULT ( STDMETHODCALLTYPE *GetEnabledLODCount )( 
            ILogController2 * This,
            UINT *pCount);
        
        HRESULT ( STDMETHODCALLTYPE *InitEx )( 
            ILogController2 * This,
            BSTR bsConfigDir,
            enum EConfigType type,
            UINT uLogHistorySize,
            BOOL bMonitorConfigChange);
        
        HRESULT ( STDMETHODCALLTYPE *GetOutputLogLevel )( 
            ILogController2 * This,
            UINT *puLevel);
        
        END_INTERFACE
    } ILogController2Vtbl;

    interface ILogController2
    {
        CONST_VTBL struct ILogController2Vtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ILogController2_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ILogController2_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ILogController2_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ILogController2_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ILogController2_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ILogController2_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ILogController2_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define ILogController2_Init(This,bsConfigDir,uLogHistorySize,bMonitorConfigChange)	\
    ( (This)->lpVtbl -> Init(This,bsConfigDir,uLogHistorySize,bMonitorConfigChange) ) 

#define ILogController2_UnInit(This)	\
    ( (This)->lpVtbl -> UnInit(This) ) 

#define ILogController2_Log(This,uClass,bsTag,bsContent)	\
    ( (This)->lpVtbl -> Log(This,uClass,bsTag,bsContent) ) 

#define ILogController2_AddIndent(This,indent)	\
    ( (This)->lpVtbl -> AddIndent(This,indent) ) 

#define ILogController2_AddLOD(This,bsName,type,bsConfig)	\
    ( (This)->lpVtbl -> AddLOD(This,bsName,type,bsConfig) ) 

#define ILogController2_AddLODEx(This,bsName,pDevice,bsConfig)	\
    ( (This)->lpVtbl -> AddLODEx(This,bsName,pDevice,bsConfig) ) 

#define ILogController2_GetLOD(This,bsName,ppDevice)	\
    ( (This)->lpVtbl -> GetLOD(This,bsName,ppDevice) ) 

#define ILogController2_RemoveLOD(This,bsName)	\
    ( (This)->lpVtbl -> RemoveLOD(This,bsName) ) 

#define ILogController2_ChangeLODConfig(This,bsName,bsConfig)	\
    ( (This)->lpVtbl -> ChangeLODConfig(This,bsName,bsConfig) ) 

#define ILogController2_GetLODConfig(This,bsName,bsKey,bsVal)	\
    ( (This)->lpVtbl -> GetLODConfig(This,bsName,bsKey,bsVal) ) 

#define ILogController2_GetEnabledLODCount(This,pCount)	\
    ( (This)->lpVtbl -> GetEnabledLODCount(This,pCount) ) 


#define ILogController2_InitEx(This,bsConfigDir,type,uLogHistorySize,bMonitorConfigChange)	\
    ( (This)->lpVtbl -> InitEx(This,bsConfigDir,type,uLogHistorySize,bMonitorConfigChange) ) 

#define ILogController2_GetOutputLogLevel(This,puLevel)	\
    ( (This)->lpVtbl -> GetOutputLogLevel(This,puLevel) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ILogController2_INTERFACE_DEFINED__ */


/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


