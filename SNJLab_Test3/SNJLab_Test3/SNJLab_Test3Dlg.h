
// SNJLab_Test3Dlg.h : header file
//

#pragma once
#include "cditgexpertctl.h"
#include "afxwin.h"
#include "afxcmn.h"

struct stRequest
{
	WORD wKey;
	int	nTRID;
	//CStringArray* parTRData;		/// TR처리에 필요한 데이터를 보관하기 위해 
	void* pTRInfo;
};

enum TRID
{
	TRID_SCP = 1,
	TRID_SCPC,
	TRID_SCPH,
	TRID_SCABO,			/// 매수주문
	TRID_SCAAO,			/// 매도주문
	TRID_SMCO,			/// 정정/취소주문
};

enum ORDERTYPE
{
	ORDER_SELL = 0,
	ORDER_BUY,
	ORDER_REPLACE,
	ORDER_CANCEL
};

enum ORDER_STATUS
{
	ORDER_OPEN = 0,
	ORDER_FILLED_CLOSE,
	ORDER_REPLACED_CLOSE,
	ORDER_CANCELED_CLOSE,
	ORDER_REJECTED
};

struct stCurPrice
{
	CString			strCode;
	CString			strKorName;
	int				nLastTime;
	double			dLastPrice;				// 현재가
	float			dOpenPrice;				// 시가
	float			dHighPrice;				// 고가
	float			dLowPrice;				// 저가
	float			dPrevClosePrice;		// 전일종가
	unsigned long	lTotalVol;				// 거래량
	unsigned long	lPrevTotalVol;			// 전일거래량
	unsigned long	lContVol;				// 단위거래량
	float			d12MonthHigh;			// 12개월 고가
	float			d12MonthLow;			// 12개월 저가
	double			dBidPrice[10];			// 매수 호가
	double			dAskPrice[10];			// 매도 호가
	unsigned long	lBidSize[10];			// 매수 호가 수량
	unsigned long	lAskSize[10];			// 매도 호가 수량
	unsigned long	lBidCnt[10];			// 매수 호가 건수
	unsigned long	lAskCnt[10];			// 매도 호가 건수
	unsigned long	lBidSizeTotal;			// 매수 호가 수량합
	unsigned long	lAskSizeTotal;			// 매도 호가 수량합
	unsigned long	lBidCntTotal;			// 매수 호가 건수합
	unsigned long	lAskCntTotal;			// 매도 호가 건수합
};

/*
지정가 (00: 없음, 11: IOC, 12: FOK)
시장가 (01: 없음, 13: IOC, 14: FOK)
조건부지정가 : 02
최유리지정가 : (03: 없음, 15: IOC, 16: FOK)
최우선지정가 : 04
시간외단일가 : 07
취소시에는 00 넣을것*/

enum ORDER_PRICE_TYPE
{
	ORDER_LIMIT = 0,
	ORDER_MARKET = 1,
	ORDER_LIMIT_IOC,
	ORDER_LIMIT_FOK,
	ORDER_MARKET_IOC,
	ORDER_MARKET_FOK,
};

enum SCN_R_INDEX
{
	SCN_R_ID = 0,
	SCN_R_ACCT,
	SCN_R_ORDER_NO,
	SCN_R_ORG_ORDER_NO,
	SCN_R_BUY_SELL,
	SCN_R_REPLACE_CALCEL,
	SCN_R_ORDER_TYPE,
	SCN_R_ORDER_CONDITION,
	SCN_R_CODE,
	SCN_R_FILLED_QTY,
	SCN_R_FILLED_PRICE,
	SCN_R_FILLED_TIME,
	SCN_R_REJECT,
	SCN_R_FILLED,
	SCN_R_CONFIRM,
	SCN_R_BRANCH_NO,
	SCN_R_ORDER_QTY,
	SCN_R_ACCT_NAME,
	SCN_R_CODE_NAME,
	SCN_R_CREDIT,
	SCN_R_CREDIT_DATE,
};

struct stFill
{
	CString strAcct;
	CString strGDCode;
	CString strCode;
	CString strOrderNo;
	CString	strFilledTime;
	int		nOrderType;
	int		nFilledQty;
	double	dFilledPrice;
};

struct stOrderInfo
{
	CString strAcct;
	CString strGDCode;
	CString strCode;
	CString strOrderNo;
	CString strOrgOrderNo;
	CString strKRXOrderNo;			/// 한국거래소 주문조작번호
	CString	strOrderTime;
	CString	strFilledTime;
	int		nOrderType;				/// 매도, 매수, 정정, 취소
	int		nOrderStatus;			/// 0=Open, 1=Fille Close, 2= Replced Close, 3=Canceld Close, 4=Rejected

	int		nOrderQty;
	int		nOpenQty;
	int		nFilledQty;
	int		nCanceledQty;
	int		nReplacedQty;

	int		nOrderPriceType;		/// 지정가, 시장가
	double	dOrderPrice;
	double	dFilledPrice;
	
	CTypedPtrList<CPtrList, stFill*>* pListFill;		/// 체결 리스트
};

struct stPosition
{
	CString strAcct;
	CString strCode;
	int		nQty;
	double	dPrice;
};
// CSNJLab_Test3Dlg dialog
class CSNJLab_Test3Dlg : public CDialogEx
{
// Construction
public:
	CSNJLab_Test3Dlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_SNJLAB_TEST3_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CDITGExpertCtl m_ctlOCXTR;
	CDITGExpertCtl m_ctlOCXReal;
	/// Request Data
	CMap<WORD, WORD, stRequest*, stRequest*> m_mapRequest;				/// TR Request Map (Key : RQID)
	
	/// Order Data
	CTypedPtrMap<CMapStringToPtr, CString, stOrderInfo*>	m_mapOrder;			/// Order Map (Key : OrderNo)
	CTypedPtrList<CPtrList, stOrderInfo*>					m_listOrder;		/// Order List(Whole)
	CTypedPtrMap<CMapStringToPtr, CString, CPtrList*>		m_mapCodeOrder;		/// Order Map (Key : Code)
	CTypedPtrMap<CMapStringToPtr, CString, CStringArray*>	m_mapReverseOrder;	/// Reversed Order Map (Key : OrderNo)
	
	/// Fill Data
	CTypedPtrList<CPtrList, stFill*>						m_listFill	;		/// Fill List(Whole)
	CTypedPtrMap<CMapStringToPtr, CString, CPtrList*>		m_mapCodeFill;		/// Fill Map (Key : Code)

	/// Position Data
	CTypedPtrMap<CMapStringToPtr, CString, stPosition*>		m_mapPosition;		/// Fill Map (Key : Acct_Code)

	CEdit m_EDCode;
	CComboBox m_CBOrderType;
	CComboBox m_CBPriceType;
	CEdit m_EDOrderQty;
	CEdit m_EDOrderPrice;
	CComboBox m_CBAcctNo;
	stCurPrice m_stCurPrice;
	CEdit m_EDOrgOrderNo;
	CEdit m_EDPWD;
	CListCtrl m_ctlOrderList;
	CListCtrl m_ctlFillList;
	CComboBox m_CBFillBase;
	CEdit m_EDFillBase;
	CComboBox m_CBFull;
	CEdit m_ctrEDOrderCode;
	CListCtrl m_ctlPositionList;
	CEdit m_EDLog;

	DECLARE_EVENTSINK_MAP()
	void ReceiveDataItgexpertctlctrl1();
	void ReceiveErrorDataItgexpertctlctrl1();
	void ReceiveSysMessageItgexpertctlctrl1(short nSysMsg);
	void ReceiveRealDataItgexpertctlctrl2();

	void InitControls();
	void InItAccountNo();
	void RequestCurPrice(CString strCode, BOOL bRegisterReal = TRUE);
	void RequestOrder(int nOrderType, CString strAcctNo, CString strPWD, CString strCode, unsigned int nOrderQty, int nPriceType, double dOrderPrice, CString strOrgOrderNo);
	void ProcessSCN_R(CStringArray* parOrderReal);
	void ProcessOrderDS(stOrderInfo* pOrderInfo);
	CString GetOrderTypeString(int nOrderType);
	CString GetOrderPriceTypeString(int nOrderPriceType);
	CString GetOrderStatusString(int nOrderStatus);
	void ShowOrderList(CString strCode);
	void ShowFillList(int nBase, CString strKey);
	void SendLog(CString strText);
	void ClearMemory();
	void HookExert(HWND hExpertLogin);

	afx_msg void OnBnClickedButtonRequest();
	afx_msg void OnCbnSelchangeComboOrder();
	afx_msg void OnBnClickedButtonOrderView();
	afx_msg void OnClose();
	afx_msg void OnNMClickListOrder(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnCbnSelchangeComboPricetype();
	afx_msg void OnCbnSelchangeComboFull();
	afx_msg void OnBnClickedButtonFillView();
	afx_msg void OnCbnSelchangeComboFillBase();
	afx_msg void OnBnClickedButtonPositionView();
	afx_msg void OnBnClickedButtonStartExpert();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
