
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
	//CStringArray* parTRData;		/// TRó���� �ʿ��� �����͸� �����ϱ� ���� 
	void* pTRInfo;
};

enum TRID
{
	TRID_SCP = 1,
	TRID_SCPC,
	TRID_SCPH,
	TRID_SCABO,			/// �ż��ֹ�
	TRID_SCAAO,			/// �ŵ��ֹ�
	TRID_SMCO,			/// ����/����ֹ�
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
	double			dLastPrice;				// ���簡
	float			dOpenPrice;				// �ð�
	float			dHighPrice;				// ��
	float			dLowPrice;				// ����
	float			dPrevClosePrice;		// ��������
	unsigned long	lTotalVol;				// �ŷ���
	unsigned long	lPrevTotalVol;			// ���ϰŷ���
	unsigned long	lContVol;				// �����ŷ���
	float			d12MonthHigh;			// 12���� ��
	float			d12MonthLow;			// 12���� ����
	double			dBidPrice[10];			// �ż� ȣ��
	double			dAskPrice[10];			// �ŵ� ȣ��
	unsigned long	lBidSize[10];			// �ż� ȣ�� ����
	unsigned long	lAskSize[10];			// �ŵ� ȣ�� ����
	unsigned long	lBidCnt[10];			// �ż� ȣ�� �Ǽ�
	unsigned long	lAskCnt[10];			// �ŵ� ȣ�� �Ǽ�
	unsigned long	lBidSizeTotal;			// �ż� ȣ�� ������
	unsigned long	lAskSizeTotal;			// �ŵ� ȣ�� ������
	unsigned long	lBidCntTotal;			// �ż� ȣ�� �Ǽ���
	unsigned long	lAskCntTotal;			// �ŵ� ȣ�� �Ǽ���
};

/*
������ (00: ����, 11: IOC, 12: FOK)
���尡 (01: ����, 13: IOC, 14: FOK)
���Ǻ������� : 02
������������ : (03: ����, 15: IOC, 16: FOK)
�ֿ켱������ : 04
�ð��ܴ��ϰ� : 07
��ҽÿ��� 00 ������*/

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
	CString strKRXOrderNo;			/// �ѱ��ŷ��� �ֹ����۹�ȣ
	CString	strOrderTime;
	CString	strFilledTime;
	int		nOrderType;				/// �ŵ�, �ż�, ����, ���
	int		nOrderStatus;			/// 0=Open, 1=Fille Close, 2= Replced Close, 3=Canceld Close, 4=Rejected

	int		nOrderQty;
	int		nOpenQty;
	int		nFilledQty;
	int		nCanceledQty;
	int		nReplacedQty;

	int		nOrderPriceType;		/// ������, ���尡
	double	dOrderPrice;
	double	dFilledPrice;
	
	CTypedPtrList<CPtrList, stFill*>* pListFill;		/// ü�� ����Ʈ
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
