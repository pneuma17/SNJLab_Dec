// CDITGExpertCtl.h  : Declaration of ActiveX Control wrapper class(es) created by Microsoft Visual C++

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CDITGExpertCtl

class CDITGExpertCtl : public CWnd
{
protected:
	DECLARE_DYNCREATE(CDITGExpertCtl)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0x8E39D09, 0x206D, 0x43D1, { 0xAC, 0x78, 0xD1, 0xAE, 0x36, 0x35, 0xA4, 0xE9 } };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle,
						const RECT& rect, CWnd* pParentWnd, UINT nID, 
						CCreateContext* pContext = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID); 
	}

    BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, 
				UINT nID, CFile* pPersist = NULL, BOOL bStorage = FALSE,
				BSTR bstrLicKey = NULL)
	{ 
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey); 
	}

// Attributes
public:

// Operations
public:

	void SetMultiData(short nRecIdx, short nFieldIdx, CString &rStrValue)
	{
		COleVariant oleVar(rStrValue);
		VARIANT vValue = oleVar.Detach();
		static BYTE parms[] = VTS_I2 VTS_I2 VTS_VARIANT ;
		InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, parms, nRecIdx, nFieldIdx, &vValue);
		VariantClear(&vValue);
	}
	
	void SetMultiData(short nRecIdx, short nFieldIdx, LPCTSTR szValue)
	{
		COleVariant oleVar(szValue);
		VARIANT vValue = oleVar.Detach();
		static BYTE parms[] = VTS_I2 VTS_I2 VTS_VARIANT;
		InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, parms, nRecIdx, nFieldIdx, &vValue);
		VariantClear(&vValue);
	}

	short GetSingleFieldCount()
	{
		short result;
		InvokeHelper(0x3, DISPATCH_METHOD, VT_I2, (void*)&result, NULL);
		return result;
	}
	short GetMultiBlockCount()
	{
		short result;
		InvokeHelper(0x4, DISPATCH_METHOD, VT_I2, (void*)&result, NULL);
		return result;
	}
	short GetMultiRecordCount(short nBlockIdx)
	{
		short result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x5, DISPATCH_METHOD, VT_I2, (void*)&result, parms, nBlockIdx);
		return result;
	}
	short GetMultiFieldCount(short nBlockIdx, short nRecIdx)
	{
		short result;
		static BYTE parms[] = VTS_I2 VTS_I2 ;
		InvokeHelper(0x6, DISPATCH_METHOD, VT_I2, (void*)&result, parms, nBlockIdx, nRecIdx);
		return result;
	}

	short UnRequestAllRealData()
	{
		short result;
		InvokeHelper(0x12, DISPATCH_METHOD, VT_I2, (void*)&result, NULL);
		return result;
	}
	void SetMultiBlockData(short nBlockIdx, short nRecIdx, short nFieldIdx, CString &rStrValue)
	{
		COleVariant oleVar(rStrValue);
		VARIANT vValue = oleVar.Detach();
		static BYTE parms[] = VTS_I2 VTS_I2 VTS_I2 VTS_VARIANT ;
		InvokeHelper(0x13, DISPATCH_METHOD, VT_EMPTY, NULL, parms, nBlockIdx, nRecIdx, nFieldIdx, &vValue);
		VariantClear(&vValue);
	}
	
	void SetMultiBlockData(short nBlockIdx, short nRecIdx, short nFieldIdx, LPCTSTR szValue)
	{
		COleVariant oleVar(szValue);
		VARIANT vValue = oleVar.Detach();
		static BYTE parms[] = VTS_I2 VTS_I2 VTS_I2 VTS_VARIANT;
		InvokeHelper(0x13, DISPATCH_METHOD, VT_EMPTY, NULL, parms, nBlockIdx, nRecIdx, nFieldIdx, &vValue);
		VariantClear(&vValue);
	}

	signed char IsMoreNextData()
	{
		signed char result;
		InvokeHelper(0x14, DISPATCH_METHOD, VT_I1, (void*)&result, NULL);
		return result;
	}
	short GetAccountCount()
	{
		short result;
		InvokeHelper(0x15, DISPATCH_METHOD, VT_I2, (void*)&result, NULL);
		return result;
	}
	

	void SetSingleData(short nFieldIdx, CString &rStrVal)
	{
		COleVariant oleVar(rStrVal);
		VARIANT vValue = oleVar.Detach();
		static BYTE parms[] = VTS_I2 VTS_VARIANT;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, parms, nFieldIdx, &vValue);
		VariantClear(&vValue);
	}

	void SetSingleData(short nFieldIdx, LPCTSTR szStrVal)
	{
		COleVariant oleVar(szStrVal);
		VARIANT vValue = oleVar.Detach();
		static BYTE parms[] = VTS_I2 VTS_VARIANT;
		InvokeHelper(0x1, DISPATCH_METHOD, VT_EMPTY, NULL, parms, nFieldIdx, &vValue);
		VariantClear(&vValue);
	}


	short RequestData(CString &rStrQryName)
	{
		COleVariant oleVar(rStrQryName);
		VARIANT vQryName = oleVar.Detach();
		short result;
		static BYTE parms[] = VTS_VARIANT;
		InvokeHelper(0xe, DISPATCH_METHOD, VT_I2, (void*)&result, parms, &vQryName);
		VariantClear(&vQryName);
		return result;
	}
	
	short RequestData(LPCTSTR szStrQryName)
	{
		COleVariant oleVar(szStrQryName);
		VARIANT vQryName = oleVar.Detach();
		short result;
		static BYTE parms[] = VTS_VARIANT;
		InvokeHelper(0xe, DISPATCH_METHOD, VT_I2, (void*)&result, parms, &vQryName);
		VariantClear(&vQryName);
		return result;
	}

	short RequestNextData(CString &rStrQryName)
	{
		COleVariant oleVar(rStrQryName);
		VARIANT vQryName = oleVar.Detach();
		short result;
		static BYTE parms[] = VTS_VARIANT;
		InvokeHelper(0xf, DISPATCH_METHOD, VT_I2, (void*)&result, parms, &vQryName);
		VariantClear(&vQryName);
		return result;
	}

	short RequestNextData(LPCTSTR szQryName)
	{
		COleVariant oleVar(szQryName);
		VARIANT vQryName = oleVar.Detach();
		short result;
		static BYTE parms[] = VTS_VARIANT;
		InvokeHelper(0xf, DISPATCH_METHOD, VT_I2, (void*)&result, parms, &vQryName);
		VariantClear(&vQryName);
		return result;
	}


	short RequestRealData(CString &rStrQryName, CString &rStrCode)
	{
		COleVariant oleVar1(rStrQryName), oleVar2(rStrCode);
		VARIANT vQryName = oleVar1.Detach();
		VARIANT vCode = oleVar2.Detach();
		short result;
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT;
		InvokeHelper(0x10, DISPATCH_METHOD, VT_I2, (void*)&result, parms, &vQryName, &vCode);
		VariantClear(&vQryName);
		VariantClear(&vCode);
		return result;
	}

	short RequestRealData(LPCTSTR szQryName, LPCTSTR szCode)
	{
		COleVariant oleVar1(szQryName), oleVar2(szCode);
		VARIANT vQryName = oleVar1.Detach();
		VARIANT vCode = oleVar2.Detach();
		short result;
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT;
		InvokeHelper(0x10, DISPATCH_METHOD, VT_I2, (void*)&result, parms, &vQryName, &vCode);
		VariantClear(&vQryName);
		VariantClear(&vCode);
		return result;
	}

	short UnRequestRealData(LPCTSTR szQryName, LPCTSTR szCode)
	{
		COleVariant oleVar1(szQryName), oleVar2(szCode);
		VARIANT vQryName = oleVar1.Detach();
		VARIANT vCode = oleVar2.Detach();
		short result;
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT;
		InvokeHelper(0x11, DISPATCH_METHOD, VT_I2, (void*)&result, parms, &vQryName, &vCode);
		VariantClear(&vQryName);
		VariantClear(&vCode);
		return result;
	}
	
	void SetSingleDataEx(short nBlockIdx, short nFieldIdx, CString &rStrValue)
	{
		COleVariant oleVar(rStrValue);
		VARIANT vValue = oleVar.Detach();
		static BYTE parms[] = VTS_I2 VTS_I2 VTS_VARIANT ;
		InvokeHelper(0x19, DISPATCH_METHOD, VT_EMPTY, NULL, parms, nBlockIdx, nFieldIdx, &vValue);
		VariantClear(&vValue);
	}

	void SetSingleDataEx(short nBlockIdx, short nFieldIdx, VARIANT vValue)
	{
		static BYTE parms[] = VTS_I2 VTS_I2 VTS_VARIANT;
		InvokeHelper(0x19, DISPATCH_METHOD, VT_EMPTY, NULL, parms, nBlockIdx, nFieldIdx, &vValue);
	}

	short GetSingleFieldCountEx(short nBlockIdx)
	{
		short result;
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x1b, DISPATCH_METHOD, VT_I2, (void*)&result, parms, nBlockIdx);
		return result;
	}

	CString GetSingleData(short nFieldIdx, short nAttrType)
	{
		VARIANT result;
		static BYTE parms[] = VTS_I2 VTS_I2;
		InvokeHelper(0x7, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, nFieldIdx, nAttrType);
		CString retStr(result);
		VariantClear(&result);
		return retStr;
	}

	CString GetMultiData(short nBlockIdx, short nRecIdx, short nFieldIdx, short nAttrType)
	{
		VARIANT result;
		static BYTE parms[] = VTS_I2 VTS_I2 VTS_I2 VTS_I2;
		InvokeHelper(0x8, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, nBlockIdx, nRecIdx, nFieldIdx, nAttrType);
		CString retStr(result);
		VariantClear(&result);
		return retStr;
	}

	CString GetSingleDataEx(short nBlockIdx, short nFieldIdx, short nAttrType)
	{
		VARIANT result;
		static BYTE parms[] = VTS_I2 VTS_I2 VTS_I2;
		InvokeHelper(0x1a, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, nBlockIdx, nFieldIdx, nAttrType);
		CString retStr(result);
		VariantClear(&result);
		return retStr;
	}

	CString GetReqMsgCode()
	{
		VARIANT result;
		InvokeHelper(0x9, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
		CString retStr(result);
		VariantClear(&result);
		return retStr;
	}

	CString GetReqMessage()
	{
		VARIANT result;
		InvokeHelper(0xa, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
		CString retStr(result);
		VariantClear(&result);
		return retStr;
	}
	
	CString GetRtCode()
	{
		VARIANT result;
		InvokeHelper(0x1c, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
		CString retStr(result);
		VariantClear(&result);
		return retStr;
	}

	CString GetAccount(short nIdx)
	{
		VARIANT result;
		static BYTE parms[] = VTS_I2;
		InvokeHelper(0x16, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, nIdx);
		CString retStr(result);
		VariantClear(&result);
		return retStr;
	}


	CString GetAccountBrcode(CString &rStrAcntNo)
	{
		COleVariant oleVar(rStrAcntNo);
		VARIANT vAcntNo = oleVar.Detach();
		VARIANT result;
		static BYTE parms[] = VTS_VARIANT;
		InvokeHelper(0x17, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, &vAcntNo);
		CString retStr(result);
		VariantClear(&result);
		VariantClear(&vAcntNo);
		return retStr;
	}

	CString GetEncryptPassword(CString &rStrPwd)
	{
		COleVariant oleVar(rStrPwd);
		VARIANT vPwd = oleVar.Detach();
		VARIANT result;
		static BYTE parms[] = VTS_VARIANT;
		InvokeHelper(0x18, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, &vPwd);
		CString retStr(result);
		VariantClear(&result);
		VariantClear(&vPwd);
		return retStr;
	}

	CString GetSingleDataStockMaster(LPCTSTR vStkCode, short nFieldIdx)
	{
		VARIANT result;
		static BYTE parms[] = VTS_VARIANT VTS_I2 ;
		COleVariant oleVar(vStkCode);
		VARIANT vValue = oleVar.Detach();
		InvokeHelper(0x24, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, &vValue, nFieldIdx);
		CString retStr(result);
		VariantClear(&result);
		return retStr;
	}

	CString GetOverSeasStockSise()
	{
		VARIANT result;
		InvokeHelper(0x1d, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
		CString retStr(result);
		VariantClear(&result);
		return retStr;
	}

	short GetSendRqID()
	{
		short result;
		InvokeHelper(0x1f, DISPATCH_METHOD, VT_I2, (void*)&result, NULL);
		return result;
	}

	short GetRecvRqID()
	{
		short result;
		InvokeHelper(0x20, DISPATCH_METHOD, VT_I2, (void*)&result, NULL);
		return result;
	}

	BOOL IsVTS()
	{
		BOOL result;
		InvokeHelper(0x23, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
		return result;
	}

	void AboutBox()
	{
		InvokeHelper(DISPID_ABOUTBOX, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}

};
