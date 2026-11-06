

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0366 */
/* at Fri Jul 05 12:35:33 2013
 */
/* Compiler settings for .\svcsvc.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

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


#ifndef __svcsvc_h__
#define __svcsvc_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IService_FWD_DEFINED__
#define __IService_FWD_DEFINED__
typedef interface IService IService;
#endif 	/* __IService_FWD_DEFINED__ */


#ifndef __Service_FWD_DEFINED__
#define __Service_FWD_DEFINED__

#ifdef __cplusplus
typedef class Service Service;
#else
typedef struct Service Service;
#endif /* __cplusplus */

#endif 	/* __Service_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 


#ifndef __SVCSVCLib_LIBRARY_DEFINED__
#define __SVCSVCLib_LIBRARY_DEFINED__

/* library SVCSVCLib */
/* [helpstring][version][uuid] */ 


DEFINE_GUID(LIBID_SVCSVCLib,0x489FF226,0x90AD,0x4CC9,0xB4,0x97,0xFD,0x17,0xCD,0xC4,0x8B,0xF8);

#ifndef __IService_INTERFACE_DEFINED__
#define __IService_INTERFACE_DEFINED__

/* interface IService */
/* [unique][helpstring][dual][uuid][object] */ 


DEFINE_GUID(IID_IService,0xA5194858,0xF330,0x4E3A,0x98,0x0A,0xFF,0x48,0x7A,0x5C,0x3F,0x6F);

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A5194858-F330-4E3A-980A-FF487A5C3F6F")
    IService : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AnsiToOEM( 
            /* [in] */ BSTR Ansi,
            /* [retval][out] */ BSTR *OEM) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OEMToAnsi( 
            /* [in] */ BSTR OEM,
            /* [retval][out] */ BSTR *Ansi) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SelectFile( 
            /* [in] */ VARIANT_BOOL ForSave,
            /* [in] */ BSTR FileName,
            /* [in] */ BSTR Filter,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL MultiSelect,
            /* [retval][out] */ BSTR *FilePath) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SelectFolder( 
            /* [defaultvalue][optional][in] */ BSTR Caption,
            /* [defaultvalue][optional][in] */ BSTR StartFolder,
            /* [defaultvalue][optional][in] */ long Flags,
            /* [defaultvalue][optional][in] */ BSTR Root,
            /* [retval][out] */ BSTR *FolderPath) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE FileA2O( 
            /* [in] */ BSTR Path) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE FileO2A( 
            /* [in] */ BSTR Path) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SelectValue( 
            /* [in] */ BSTR Values,
            /* [in] */ BSTR Caption,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Mark,
            /* [retval][out] */ BSTR *Select) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SelectInTree( 
            /* [in] */ BSTR Values,
            /* [in] */ BSTR Caption,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Mark,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL OnlyItems,
            /* [retval][out] */ BSTR *Select) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE PopupMenu( 
            /* [in] */ BSTR Values,
            /* [defaultvalue][optional][in] */ short ShowIn,
            /* [defaultvalue][optional][in] */ long X,
            /* [defaultvalue][optional][in] */ long Y,
            /* [retval][out] */ BSTR *Select) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE FilterValue( 
            /* [in] */ BSTR Values,
            /* [defaultvalue][optional][in] */ short Flags,
            /* [defaultvalue][optional][in] */ BSTR Caption,
            /* [defaultvalue][optional][in] */ long X,
            /* [defaultvalue][optional][in] */ long Y,
            /* [defaultvalue][optional][in] */ long W,
            /* [defaultvalue][optional][in] */ long H,
            /* [retval][out] */ BSTR *Result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetWindowText( 
            /* [defaultvalue][optional][in] */ long WH,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL IsList,
            /* [retval][out] */ BSTR *Result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetWindowText( 
            /* [in] */ long WH,
            /* [in] */ BSTR Text) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_Version( 
            /* [retval][out] */ long *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetImageList( 
            /* [in] */ BSTR Values,
            /* [retval][out] */ BSTR *Result) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetContext( 
            /* [in] */ IDispatch *Cont) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_KeyboardTimeout( 
            /* [retval][out] */ LONG *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_KeyboardTimeout( 
            /* [in] */ LONG newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddString( 
            BSTR str) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveAll( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IServiceVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IService * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IService * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IService * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IService * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IService * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IService * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IService * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AnsiToOEM )( 
            IService * This,
            /* [in] */ BSTR Ansi,
            /* [retval][out] */ BSTR *OEM);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *OEMToAnsi )( 
            IService * This,
            /* [in] */ BSTR OEM,
            /* [retval][out] */ BSTR *Ansi);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SelectFile )( 
            IService * This,
            /* [in] */ VARIANT_BOOL ForSave,
            /* [in] */ BSTR FileName,
            /* [in] */ BSTR Filter,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL MultiSelect,
            /* [retval][out] */ BSTR *FilePath);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SelectFolder )( 
            IService * This,
            /* [defaultvalue][optional][in] */ BSTR Caption,
            /* [defaultvalue][optional][in] */ BSTR StartFolder,
            /* [defaultvalue][optional][in] */ long Flags,
            /* [defaultvalue][optional][in] */ BSTR Root,
            /* [retval][out] */ BSTR *FolderPath);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *FileA2O )( 
            IService * This,
            /* [in] */ BSTR Path);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *FileO2A )( 
            IService * This,
            /* [in] */ BSTR Path);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SelectValue )( 
            IService * This,
            /* [in] */ BSTR Values,
            /* [in] */ BSTR Caption,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Mark,
            /* [retval][out] */ BSTR *Select);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SelectInTree )( 
            IService * This,
            /* [in] */ BSTR Values,
            /* [in] */ BSTR Caption,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL Mark,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL OnlyItems,
            /* [retval][out] */ BSTR *Select);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *PopupMenu )( 
            IService * This,
            /* [in] */ BSTR Values,
            /* [defaultvalue][optional][in] */ short ShowIn,
            /* [defaultvalue][optional][in] */ long X,
            /* [defaultvalue][optional][in] */ long Y,
            /* [retval][out] */ BSTR *Select);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *FilterValue )( 
            IService * This,
            /* [in] */ BSTR Values,
            /* [defaultvalue][optional][in] */ short Flags,
            /* [defaultvalue][optional][in] */ BSTR Caption,
            /* [defaultvalue][optional][in] */ long X,
            /* [defaultvalue][optional][in] */ long Y,
            /* [defaultvalue][optional][in] */ long W,
            /* [defaultvalue][optional][in] */ long H,
            /* [retval][out] */ BSTR *Result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetWindowText )( 
            IService * This,
            /* [defaultvalue][optional][in] */ long WH,
            /* [defaultvalue][optional][in] */ VARIANT_BOOL IsList,
            /* [retval][out] */ BSTR *Result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetWindowText )( 
            IService * This,
            /* [in] */ long WH,
            /* [in] */ BSTR Text);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_Version )( 
            IService * This,
            /* [retval][out] */ long *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetImageList )( 
            IService * This,
            /* [in] */ BSTR Values,
            /* [retval][out] */ BSTR *Result);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetContext )( 
            IService * This,
            /* [in] */ IDispatch *Cont);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_KeyboardTimeout )( 
            IService * This,
            /* [retval][out] */ LONG *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_KeyboardTimeout )( 
            IService * This,
            /* [in] */ LONG newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddString )( 
            IService * This,
            BSTR str);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RemoveAll )( 
            IService * This);
        
        END_INTERFACE
    } IServiceVtbl;

    interface IService
    {
        CONST_VTBL struct IServiceVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IService_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IService_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IService_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IService_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IService_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IService_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IService_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IService_AnsiToOEM(This,Ansi,OEM)	\
    (This)->lpVtbl -> AnsiToOEM(This,Ansi,OEM)

#define IService_OEMToAnsi(This,OEM,Ansi)	\
    (This)->lpVtbl -> OEMToAnsi(This,OEM,Ansi)

#define IService_SelectFile(This,ForSave,FileName,Filter,MultiSelect,FilePath)	\
    (This)->lpVtbl -> SelectFile(This,ForSave,FileName,Filter,MultiSelect,FilePath)

#define IService_SelectFolder(This,Caption,StartFolder,Flags,Root,FolderPath)	\
    (This)->lpVtbl -> SelectFolder(This,Caption,StartFolder,Flags,Root,FolderPath)

#define IService_FileA2O(This,Path)	\
    (This)->lpVtbl -> FileA2O(This,Path)

#define IService_FileO2A(This,Path)	\
    (This)->lpVtbl -> FileO2A(This,Path)

#define IService_SelectValue(This,Values,Caption,Mark,Select)	\
    (This)->lpVtbl -> SelectValue(This,Values,Caption,Mark,Select)

#define IService_SelectInTree(This,Values,Caption,Mark,OnlyItems,Select)	\
    (This)->lpVtbl -> SelectInTree(This,Values,Caption,Mark,OnlyItems,Select)

#define IService_PopupMenu(This,Values,ShowIn,X,Y,Select)	\
    (This)->lpVtbl -> PopupMenu(This,Values,ShowIn,X,Y,Select)

#define IService_FilterValue(This,Values,Flags,Caption,X,Y,W,H,Result)	\
    (This)->lpVtbl -> FilterValue(This,Values,Flags,Caption,X,Y,W,H,Result)

#define IService_GetWindowText(This,WH,IsList,Result)	\
    (This)->lpVtbl -> GetWindowText(This,WH,IsList,Result)

#define IService_SetWindowText(This,WH,Text)	\
    (This)->lpVtbl -> SetWindowText(This,WH,Text)

#define IService_get_Version(This,pVal)	\
    (This)->lpVtbl -> get_Version(This,pVal)

#define IService_SetImageList(This,Values,Result)	\
    (This)->lpVtbl -> SetImageList(This,Values,Result)

#define IService_SetContext(This,Cont)	\
    (This)->lpVtbl -> SetContext(This,Cont)

#define IService_get_KeyboardTimeout(This,pVal)	\
    (This)->lpVtbl -> get_KeyboardTimeout(This,pVal)

#define IService_put_KeyboardTimeout(This,newVal)	\
    (This)->lpVtbl -> put_KeyboardTimeout(This,newVal)

#define IService_AddString(This,str)	\
    (This)->lpVtbl -> AddString(This,str)

#define IService_RemoveAll(This)	\
    (This)->lpVtbl -> RemoveAll(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IService_AnsiToOEM_Proxy( 
    IService * This,
    /* [in] */ BSTR Ansi,
    /* [retval][out] */ BSTR *OEM);


void __RPC_STUB IService_AnsiToOEM_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IService_OEMToAnsi_Proxy( 
    IService * This,
    /* [in] */ BSTR OEM,
    /* [retval][out] */ BSTR *Ansi);


void __RPC_STUB IService_OEMToAnsi_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IService_SelectFile_Proxy( 
    IService * This,
    /* [in] */ VARIANT_BOOL ForSave,
    /* [in] */ BSTR FileName,
    /* [in] */ BSTR Filter,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL MultiSelect,
    /* [retval][out] */ BSTR *FilePath);


void __RPC_STUB IService_SelectFile_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IService_SelectFolder_Proxy( 
    IService * This,
    /* [defaultvalue][optional][in] */ BSTR Caption,
    /* [defaultvalue][optional][in] */ BSTR StartFolder,
    /* [defaultvalue][optional][in] */ long Flags,
    /* [defaultvalue][optional][in] */ BSTR Root,
    /* [retval][out] */ BSTR *FolderPath);


void __RPC_STUB IService_SelectFolder_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IService_FileA2O_Proxy( 
    IService * This,
    /* [in] */ BSTR Path);


void __RPC_STUB IService_FileA2O_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IService_FileO2A_Proxy( 
    IService * This,
    /* [in] */ BSTR Path);


void __RPC_STUB IService_FileO2A_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IService_SelectValue_Proxy( 
    IService * This,
    /* [in] */ BSTR Values,
    /* [in] */ BSTR Caption,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL Mark,
    /* [retval][out] */ BSTR *Select);


void __RPC_STUB IService_SelectValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IService_SelectInTree_Proxy( 
    IService * This,
    /* [in] */ BSTR Values,
    /* [in] */ BSTR Caption,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL Mark,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL OnlyItems,
    /* [retval][out] */ BSTR *Select);


void __RPC_STUB IService_SelectInTree_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IService_PopupMenu_Proxy( 
    IService * This,
    /* [in] */ BSTR Values,
    /* [defaultvalue][optional][in] */ short ShowIn,
    /* [defaultvalue][optional][in] */ long X,
    /* [defaultvalue][optional][in] */ long Y,
    /* [retval][out] */ BSTR *Select);


void __RPC_STUB IService_PopupMenu_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IService_FilterValue_Proxy( 
    IService * This,
    /* [in] */ BSTR Values,
    /* [defaultvalue][optional][in] */ short Flags,
    /* [defaultvalue][optional][in] */ BSTR Caption,
    /* [defaultvalue][optional][in] */ long X,
    /* [defaultvalue][optional][in] */ long Y,
    /* [defaultvalue][optional][in] */ long W,
    /* [defaultvalue][optional][in] */ long H,
    /* [retval][out] */ BSTR *Result);


void __RPC_STUB IService_FilterValue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IService_GetWindowText_Proxy( 
    IService * This,
    /* [defaultvalue][optional][in] */ long WH,
    /* [defaultvalue][optional][in] */ VARIANT_BOOL IsList,
    /* [retval][out] */ BSTR *Result);


void __RPC_STUB IService_GetWindowText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IService_SetWindowText_Proxy( 
    IService * This,
    /* [in] */ long WH,
    /* [in] */ BSTR Text);


void __RPC_STUB IService_SetWindowText_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IService_get_Version_Proxy( 
    IService * This,
    /* [retval][out] */ long *pVal);


void __RPC_STUB IService_get_Version_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IService_SetImageList_Proxy( 
    IService * This,
    /* [in] */ BSTR Values,
    /* [retval][out] */ BSTR *Result);


void __RPC_STUB IService_SetImageList_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IService_SetContext_Proxy( 
    IService * This,
    /* [in] */ IDispatch *Cont);


void __RPC_STUB IService_SetContext_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IService_get_KeyboardTimeout_Proxy( 
    IService * This,
    /* [retval][out] */ LONG *pVal);


void __RPC_STUB IService_get_KeyboardTimeout_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IService_put_KeyboardTimeout_Proxy( 
    IService * This,
    /* [in] */ LONG newVal);


void __RPC_STUB IService_put_KeyboardTimeout_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IService_AddString_Proxy( 
    IService * This,
    BSTR str);


void __RPC_STUB IService_AddString_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IService_RemoveAll_Proxy( 
    IService * This);


void __RPC_STUB IService_RemoveAll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IService_INTERFACE_DEFINED__ */


DEFINE_GUID(CLSID_Service,0x6CDD75A4,0xC42E,0x4DE3,0xB8,0x7A,0xC7,0x5D,0xAB,0x91,0xDD,0x02);

#ifdef __cplusplus

class DECLSPEC_UUID("6CDD75A4-C42E-4DE3-B87A-C75DAB91DD02")
Service;
#endif
#endif /* __SVCSVCLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


