
// SNJLab_Test3Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "SNJLab_Test3.h"
#include "SNJLab_Test3Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define FIND_TIMER 11023
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSNJLab_Test3Dlg dialog


CString strLogText;

CSNJLab_Test3Dlg::CSNJLab_Test3Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSNJLab_Test3Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSNJLab_Test3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ITGEXPERTCTLCTRL1, m_ctlOCXTR);
	DDX_Control(pDX, IDC_ITGEXPERTCTLCTRL2, m_ctlOCXReal);
	DDX_Control(pDX, IDC_EDIT_CODE, m_EDCode);
	DDX_Control(pDX, IDC_COMBO_ORDER, m_CBOrderType);
	DDX_Control(pDX, IDC_COMBO_PRICETYPE, m_CBPriceType);
	DDX_Control(pDX, IDC_EDIT_QTY, m_EDOrderQty);
	DDX_Control(pDX, IDC_EDIT_PRICE, m_EDOrderPrice);
	DDX_Control(pDX, IDC_COMBO_ACCTNO, m_CBAcctNo);
	DDX_Control(pDX, IDC_EDIT_ORG_ORDERNO, m_EDOrgOrderNo);
	DDX_Control(pDX, IDC_EDIT_PWD, m_EDPWD);
	DDX_Control(pDX, IDC_LIST_ORDER, m_ctlOrderList);
	DDX_Control(pDX, IDC_EDIT_CODE_ORDER, m_ctrEDOrderCode);
	DDX_Control(pDX, IDC_COMBO_FULL, m_CBFull);
	DDX_Control(pDX, IDC_COMBO_FILL_BASE, m_CBFillBase);
	DDX_Control(pDX, IDC_EDIT_FILL_BASE, m_EDFillBase);
	DDX_Control(pDX, IDC_LIST_FILL, m_ctlFillList);
	DDX_Control(pDX, IDC_LIST_POSITION, m_ctlPositionList);
	DDX_Control(pDX, IDC_EDIT_LOG, m_EDLog);
}

BEGIN_MESSAGE_MAP(CSNJLab_Test3Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_REQUEST, &CSNJLab_Test3Dlg::OnBnClickedButtonRequest)
	ON_CBN_SELCHANGE(IDC_COMBO_ORDER, &CSNJLab_Test3Dlg::OnCbnSelchangeComboOrder)
	ON_BN_CLICKED(IDC_BUTTON_ORDER_VIEW, &CSNJLab_Test3Dlg::OnBnClickedButtonOrderView)
	ON_WM_CLOSE()
	ON_NOTIFY(NM_CLICK, IDC_LIST_ORDER, &CSNJLab_Test3Dlg::OnNMClickListOrder)
	ON_CBN_SELCHANGE(IDC_COMBO_PRICETYPE, &CSNJLab_Test3Dlg::OnCbnSelchangeComboPricetype)
	ON_CBN_SELCHANGE(IDC_COMBO_FULL, &CSNJLab_Test3Dlg::OnCbnSelchangeComboFull)
	ON_BN_CLICKED(IDC_BUTTON_FILL_VIEW, &CSNJLab_Test3Dlg::OnBnClickedButtonFillView)
	ON_CBN_SELCHANGE(IDC_COMBO_FILL_BASE, &CSNJLab_Test3Dlg::OnCbnSelchangeComboFillBase)
	ON_BN_CLICKED(IDC_BUTTON_POSITION_VIEW, &CSNJLab_Test3Dlg::OnBnClickedButtonPositionView)
	ON_BN_CLICKED(IDC_BUTTON_START_EXPERT, &CSNJLab_Test3Dlg::OnBnClickedButtonStartExpert)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CSNJLab_Test3Dlg message handlers

BOOL CSNJLab_Test3Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	InitControls();
	InItAccountNo();

	///실시간 주문체결 등록
	m_ctlOCXReal.RequestRealData(_T("SCN_R"), _T("pneuma17"));
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSNJLab_Test3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CSNJLab_Test3Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CSNJLab_Test3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BEGIN_EVENTSINK_MAP(CSNJLab_Test3Dlg, CDialogEx)
	ON_EVENT(CSNJLab_Test3Dlg, IDC_ITGEXPERTCTLCTRL1, 1, CSNJLab_Test3Dlg::ReceiveDataItgexpertctlctrl1, VTS_NONE)
	ON_EVENT(CSNJLab_Test3Dlg, IDC_ITGEXPERTCTLCTRL1, 3, CSNJLab_Test3Dlg::ReceiveErrorDataItgexpertctlctrl1, VTS_NONE)
	ON_EVENT(CSNJLab_Test3Dlg, IDC_ITGEXPERTCTLCTRL1, 4, CSNJLab_Test3Dlg::ReceiveSysMessageItgexpertctlctrl1, VTS_I2)
	ON_EVENT(CSNJLab_Test3Dlg, IDC_ITGEXPERTCTLCTRL2, 2, CSNJLab_Test3Dlg::ReceiveRealDataItgexpertctlctrl2, VTS_NONE)
END_EVENTSINK_MAP()

void CSNJLab_Test3Dlg::InitControls()
{
	m_CBOrderType.AddString(_T("매도"));
	m_CBOrderType.AddString(_T("매수"));
	m_CBOrderType.AddString(_T("정정"));
	m_CBOrderType.AddString(_T("취소"));
	m_CBOrderType.SetCurSel(1);

	m_CBPriceType.AddString(_T("지정가"));
	m_CBPriceType.AddString(_T("시장가"));
	m_CBPriceType.SetCurSel(0);

	m_CBFull.AddString(_T("일부"));
	m_CBFull.AddString(_T("잔량"));
	m_CBFull.SetCurSel(0);

	m_CBFillBase.AddString(_T("전체"));
	m_CBFillBase.AddString(_T("종목별"));
	m_CBFillBase.AddString(_T("주문번호별"));
	m_CBFillBase.SetCurSel(0);

	m_ctlOrderList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ctlOrderList.InsertColumn(0, _T(" "), LVCFMT_CENTER, 0);
	m_ctlOrderList.InsertColumn(1, _T("계좌"), LVCFMT_CENTER, 65);
	m_ctlOrderList.InsertColumn(2, _T("종목"), LVCFMT_CENTER, 50);
	m_ctlOrderList.InsertColumn(3, _T("주문No"), LVCFMT_CENTER, 60);
	m_ctlOrderList.InsertColumn(4, _T("원주문No"), LVCFMT_CENTER, 60);
	m_ctlOrderList.InsertColumn(5, _T("시간"), LVCFMT_CENTER, 50);
	m_ctlOrderList.InsertColumn(6, _T("유형"), LVCFMT_CENTER, 50);
	m_ctlOrderList.InsertColumn(7, _T("상태"), LVCFMT_CENTER, 80);
	m_ctlOrderList.InsertColumn(8, _T("수량"), LVCFMT_RIGHT, 50);
	m_ctlOrderList.InsertColumn(9, _T("미체결"), LVCFMT_RIGHT, 50);
	m_ctlOrderList.InsertColumn(10, _T("체결"), LVCFMT_RIGHT, 50);
	m_ctlOrderList.InsertColumn(11, _T("취소"), LVCFMT_RIGHT, 50);
	m_ctlOrderList.InsertColumn(12, _T("정정"), LVCFMT_RIGHT, 50);
	m_ctlOrderList.InsertColumn(13, _T("가격유형"), LVCFMT_CENTER, 50);
	m_ctlOrderList.InsertColumn(14, _T("주문가"), LVCFMT_RIGHT, 70);
	m_ctlOrderList.InsertColumn(15, _T("체결가"), LVCFMT_RIGHT, 70);
	m_ctlOrderList.InsertColumn(16, _T("종목명"), LVCFMT_CENTER, 70);

	m_ctlFillList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ctlFillList.InsertColumn(0, _T(" "), LVCFMT_CENTER, 0);
	m_ctlFillList.InsertColumn(1, _T("계좌"), LVCFMT_CENTER, 65);
	m_ctlFillList.InsertColumn(2, _T("종목명"), LVCFMT_CENTER, 50);
	m_ctlFillList.InsertColumn(3, _T("주문No"), LVCFMT_CENTER, 85);
	m_ctlFillList.InsertColumn(4, _T("체결시간"), LVCFMT_CENTER, 60);
	m_ctlFillList.InsertColumn(5, _T("유형"), LVCFMT_CENTER, 60);
	m_ctlFillList.InsertColumn(6, _T("체결수량"), LVCFMT_RIGHT, 60);
	m_ctlFillList.InsertColumn(7, _T("체결가격"), LVCFMT_RIGHT, 75);

	m_ctlPositionList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ctlPositionList.InsertColumn(0, _T(" "), LVCFMT_CENTER, 0);
	m_ctlPositionList.InsertColumn(1, _T("계좌"), LVCFMT_CENTER, 65);
	m_ctlPositionList.InsertColumn(2, _T("종목명"), LVCFMT_CENTER, 50);
	m_ctlPositionList.InsertColumn(3, _T("수량"), LVCFMT_RIGHT, 45);
	m_ctlPositionList.InsertColumn(4, _T("가격"), LVCFMT_RIGHT, 60);
}

void CSNJLab_Test3Dlg::ReceiveDataItgexpertctlctrl1()
{
	// TODO: Add your message handler code here
	short nRQID = m_ctlOCXTR.GetRecvRqID();
	stRequest* pRequest;

	CString strErrorCode = m_ctlOCXTR.GetRtCode();
	CString strRegMsgCode = m_ctlOCXTR.GetReqMsgCode();
	CString strGetReqMessage = m_ctlOCXTR.GetReqMessage();

	if (m_mapRequest.Lookup(nRQID, pRequest))
	{
		switch(pRequest->nTRID)
		{
			case TRID_SCP:
			{
				m_stCurPrice.strKorName = m_ctlOCXTR.GetSingleData(2, 0);

				CStringArray* pTRInfo = (CStringArray*)(pRequest->pTRInfo);
				pTRInfo->RemoveAll();
			}
			break;
			case TRID_SCPC:
			{
				CString strTemp = m_ctlOCXTR.GetSingleData(1,0);
				m_stCurPrice.dLastPrice = _ttof(m_ctlOCXTR.GetSingleData(1,0));
				m_stCurPrice.nLastTime = _ttoi(m_ctlOCXTR.GetSingleData(0,0));
				
				CStringArray* pTRInfo = (CStringArray*)(pRequest->pTRInfo);
				
				if (_ttoi(pTRInfo->GetAt(1)) == 1)
				{
					m_ctlOCXReal.RequestRealData( _T("SC_R"), m_stCurPrice.strCode); //선물 체결 실시간 데이터 요청
					//m_ctlOCXReal.RequestRealData( _T("SC_R"), _T("000660")); //선물 체결 실시간 데이터 요청
				}

				pTRInfo->RemoveAll();
			}
			break;
			case TRID_SCPH:
			{
				m_stCurPrice.dAskPrice[0] = _ttof(m_ctlOCXTR.GetSingleData(1,0));
				m_stCurPrice.dBidPrice[0] = _ttof(m_ctlOCXTR.GetSingleData(11,0));

				CStringArray* pTRInfo = (CStringArray*)(pRequest->pTRInfo);

				//if(_ttoi(pTRInfo->GetAt(1)) == 1)
				//	m_ctlOCXReal.RequestRealData( _T("SH_R"), m_stCurPrice.strCode); //선물 체결 실시간 데이터 요청

				pTRInfo->RemoveAll();
			}
			break;

			case TRID_SCABO:	/// 매수주문
			case TRID_SCAAO:	/// 매도주문
			{
				CStringArray* parOrderReal;
				stOrderInfo* pRcvOrderInfo = new stOrderInfo;
				stOrderInfo* pOrderInfo = (stOrderInfo*)(pRequest->pTRInfo);

				memcpy(pRcvOrderInfo, pOrderInfo, sizeof(stOrderInfo));
				
				pRcvOrderInfo->strKRXOrderNo = m_ctlOCXTR.GetSingleData(0, 0);
				pRcvOrderInfo->strOrderNo = m_ctlOCXTR.GetSingleData(1, 0);
				pRcvOrderInfo->strOrderNo.TrimLeft('0');
				pRcvOrderInfo->strOrderTime = m_ctlOCXTR.GetSingleData(2, 0);
				pRcvOrderInfo->nOrderStatus = ORDER_OPEN;
				pRcvOrderInfo->nOpenQty = pRcvOrderInfo->nOrderQty;
				pRcvOrderInfo->nFilledQty = 0;
				pRcvOrderInfo->nCanceledQty = 0;
				pRcvOrderInfo->nReplacedQty = 0;
				pRcvOrderInfo->pListFill = new CTypedPtrList<CPtrList, stFill*>;

				if (pRcvOrderInfo->strOrderNo.IsEmpty())
				{
					/// 오류
					strLogText.Format(_T(" RQID[%d] ErrorCode[%s], ReqMsgCoce[%s], Msg[%s] Acct[%s], Code[%s] 주문 실패"), nRQID, strErrorCode, strRegMsgCode, strGetReqMessage, pRcvOrderInfo->strAcct, pRcvOrderInfo->strCode);
					SendLog(strLogText);

					delete pRcvOrderInfo->pListFill;
					delete pRcvOrderInfo;
				}
				else
				{
					ProcessOrderDS(pRcvOrderInfo);
					//m_mapOrder.SetAt(pOrderInfo->strOrderNo, pRcvOrderInfo);

					if (m_mapReverseOrder.Lookup(pRcvOrderInfo->strOrderNo, parOrderReal))
					{
						strLogText.Format(_T(" 주문번호[%s] 역전발생!!"), pRcvOrderInfo->strOrderNo);
						SendLog(strLogText);

						ProcessSCN_R(parOrderReal);
						m_mapReverseOrder.RemoveKey(pRcvOrderInfo->strOrderNo);
					}
				}
			}
			break;
			case TRID_SMCO:	/// 정정/취소주문
			{
				CStringArray* parOrderReal;
				stOrderInfo* pRcvOrderInfo = new stOrderInfo;
				stOrderInfo* pOrderInfo = (stOrderInfo*)(pRequest->pTRInfo);

				memcpy(pRcvOrderInfo, pOrderInfo, sizeof(stOrderInfo));

				pRcvOrderInfo->strKRXOrderNo = m_ctlOCXTR.GetSingleData(0, 0);
				pRcvOrderInfo->strOrderNo = m_ctlOCXTR.GetSingleData(1, 0);
				pRcvOrderInfo->strOrderNo.TrimLeft('0');
				pRcvOrderInfo->strOrderTime = m_ctlOCXTR.GetSingleData(2, 0);
				pRcvOrderInfo->nOrderStatus = ORDER_OPEN;
				pRcvOrderInfo->nOpenQty = pRcvOrderInfo->nOrderQty;
				pRcvOrderInfo->nFilledQty = 0;
				pRcvOrderInfo->nCanceledQty = 0;
				pRcvOrderInfo->nReplacedQty = 0;
				pRcvOrderInfo->pListFill = new CTypedPtrList<CPtrList, stFill*>;

				if (pRcvOrderInfo->strOrderNo.IsEmpty())
				{
					/// 오류
					strLogText.Format(_T(" RQID[%d] ErrorCode[%s], ReqMsgCoce[%s], Msg[%s] Acct[%s], Code[%s] 주문 실패"), nRQID, strErrorCode, strRegMsgCode, strGetReqMessage, pRcvOrderInfo->strAcct, pRcvOrderInfo->strCode);
					SendLog(strLogText);

					delete pRcvOrderInfo->pListFill;
					delete pRcvOrderInfo;
				}
				else
				{
					ProcessOrderDS(pRcvOrderInfo);
					//m_mapOrder.SetAt(pOrderInfo->strOrderNo, pRcvOrderInfo);

					if (m_mapReverseOrder.Lookup(pRcvOrderInfo->strOrderNo, parOrderReal))
					{
						strLogText.Format(_T(" 주문번호[%s] 역전발생!!"), pRcvOrderInfo->strOrderNo);
						SendLog(strLogText);

						ProcessSCN_R(parOrderReal);
						m_mapReverseOrder.RemoveKey(pRcvOrderInfo->strOrderNo);
					}
				}
			}
			break;
		
		}

		m_mapRequest.RemoveKey(nRQID);
		delete pRequest->pTRInfo;
		delete pRequest;

	}
	else
	{
		strLogText.Format(_T(" RQID - %d Request not found"), nRQID);
		SendLog(strLogText);
	}
}


void CSNJLab_Test3Dlg::ReceiveErrorDataItgexpertctlctrl1()
{
	// TODO: Add your message handler code here
	CString strErrorCode = m_ctlOCXTR.GetRtCode();
	CString strRegMsgCode = m_ctlOCXTR.GetReqMsgCode();
	CString strGetReqMessage = m_ctlOCXTR.GetReqMessage();

	strLogText.Format(_T(" ReceiveError ErrorCode[%s], ReqMsgCoce[%s], Msg[%s]"), strErrorCode, strRegMsgCode, strGetReqMessage);
	SendLog(strLogText);
}


void CSNJLab_Test3Dlg::ReceiveSysMessageItgexpertctlctrl1(short nSysMsg)
{
	// TODO: Add your message handler code here
	strLogText.Format(_T(" ReceiveSysMsg nSysMsg[%d]"), nSysMsg);
	
	SendLog(strLogText);

	switch (nSysMsg)
	{
	case 1:		/// 메인시작
		InItAccountNo();
		break;
	case 2:		/// 메인종료
		if (IDYES == AfxMessageBox(_T("eFriendExpert가 종료되었습니다. 재기동 하시겠습니까?"), MB_YESNO))
			OnBnClickedButtonStartExpert();
		else
			SendLog(_T(" eFriendExpert 종료!!"));
		break;
	case 3:		/// 메인 재접속
		InItAccountNo();
		break;
	}
}


void CSNJLab_Test3Dlg::ReceiveRealDataItgexpertctlctrl2()
{
	// TODO: Add your message handler code here
	CString strText, strOrderNo, strOrgOrderNo;
	int nFieldCnt = m_ctlOCXReal.GetSingleFieldCount();
	CStringArray* parOrderReal = new CStringArray;
	parOrderReal->SetSize(nFieldCnt);
	stOrderInfo* pOrderInfo = NULL;

	for (int i = 0; i < nFieldCnt; i++)
		parOrderReal->SetAt(i, m_ctlOCXReal.GetSingleData(i, 0));

	strOrderNo = parOrderReal->GetAt(SCN_R_ORDER_NO);
	strOrderNo.TrimLeft('0');
	parOrderReal->SetAt(SCN_R_ORDER_NO, strOrderNo);

	strOrgOrderNo = parOrderReal->GetAt(SCN_R_ORG_ORDER_NO);
	strOrgOrderNo.TrimLeft('0');
	parOrderReal->SetAt(SCN_R_ORG_ORDER_NO, strOrgOrderNo);

	if (m_mapOrder.Lookup(strOrderNo, pOrderInfo))			/// 주문번호 있을시	
		ProcessSCN_R(parOrderReal);
	else													/// 실시간 들어왔는데 주문 번호가 없다->Reverse or 타매체 발생
		m_mapReverseOrder.SetAt(strOrderNo, parOrderReal);

}


void CSNJLab_Test3Dlg::InItAccountNo()
{
	int nAcntCnt = m_ctlOCXTR.GetAccountCount();
	m_CBAcctNo.ResetContent();
	CString strAcnt;
	if (nAcntCnt > 0)
	{
		for (int i = 0; i < nAcntCnt; i++)
		{
			strAcnt = m_ctlOCXTR.GetAccount(i);
			m_CBAcctNo.AddString(strAcnt);
		}

		m_CBAcctNo.SetCurSel(0);

		strLogText.Format(_T(" [%d] Account Loaded"), nAcntCnt);
		SendLog(strLogText);
	}
	else
		SendLog(_T(" No Account"));
}

void CSNJLab_Test3Dlg::OnBnClickedButtonRequest()
{
	// TODO: Add your control notification handler code here
	CString strCode, strOrderPrice, strOrderQty, strAcctNo, strOrgOrderNo, strPWD;
	int nOrderType, nPriceType;
	unsigned int nOrderQty;
	double dOrderPrice;

	nOrderType = m_CBOrderType.GetCurSel();
	nPriceType = m_CBPriceType.GetCurSel();
	
	m_CBAcctNo.GetWindowText(strAcctNo);
	
	m_EDCode.GetWindowText(strCode);
	m_EDOrderPrice.GetWindowText(strOrderPrice);
	m_EDOrderQty.GetWindowText(strOrderQty);
	m_EDOrgOrderNo.GetWindowText(strOrgOrderNo);
	strOrgOrderNo.TrimLeft('0');

	m_EDPWD.GetWindowText(strPWD);

	nOrderQty = _ttoi(strOrderQty);
	dOrderPrice = _ttof(strOrderPrice);

	RequestOrder((ORDER_TYPE)nOrderType, strAcctNo, strPWD, strCode, nOrderQty, (ORDER_PRICE_TYPE)nPriceType, dOrderPrice, strOrgOrderNo);

	//RequestCurPrice(strCode, TRUE);
}

void CSNJLab_Test3Dlg::RequestCurPrice(CString strCode, BOOL bRegisterReal)
{
	short nRQID;

	m_stCurPrice.strCode = strCode;
	/// 현재가(마스터)
	m_ctlOCXTR.SetSingleData(0, _T("J"));
	m_ctlOCXTR.SetSingleData(1, strCode);
	nRQID = m_ctlOCXTR.RequestData(_T("SCP"));

	nRQID = m_ctlOCXTR.GetSendRqID();

	stRequest *pRequest = new stRequest;
	memset(pRequest, 0x00, sizeof(stRequest));
	pRequest->wKey = nRQID;
	pRequest->nTRID = TRID_SCP;

	CStringArray* parTRData = new CStringArray;
	pRequest->pTRInfo = parTRData;
	parTRData->SetSize(2);
	parTRData->SetAt(0, strCode);
	if (bRegisterReal)
		parTRData->SetAt(1, _T("1"));
	else
		parTRData->SetAt(1, _T("0"));
	
	m_mapRequest.SetAt(nRQID, pRequest);	

	/// 현재가 체결
	m_ctlOCXTR.SetSingleData(0, _T("J"));
	m_ctlOCXTR.SetSingleData(1, strCode);
	m_ctlOCXTR.RequestData(_T("SCPC"));

	nRQID = m_ctlOCXTR.GetSendRqID();

	pRequest = new stRequest;
	memset(pRequest, 0x00, sizeof(stRequest));
	pRequest->wKey = nRQID;
	pRequest->nTRID = TRID_SCPC;

	parTRData = new CStringArray;
	pRequest->pTRInfo = parTRData;
	parTRData->SetSize(2);
	parTRData->SetAt(0, strCode);
	if (bRegisterReal)
		parTRData->SetAt(1, _T("1"));
	else
		parTRData->SetAt(1, _T("0"));
	
	m_mapRequest.SetAt(nRQID, pRequest);

	/// 현재가호가
	m_ctlOCXTR.SetSingleData(0, _T("J"));
	m_ctlOCXTR.SetSingleData(1, strCode);
	m_ctlOCXTR.RequestData(_T("SCPH"));

	nRQID = m_ctlOCXTR.GetSendRqID();

	pRequest = new stRequest;
	memset(pRequest, 0x00, sizeof(stRequest));
	pRequest->wKey = nRQID;
	pRequest->nTRID = TRID_SCPH;

	parTRData = new CStringArray;
	pRequest->pTRInfo = parTRData;
	parTRData->SetSize(2);
	parTRData->SetAt(0, strCode);
	if (bRegisterReal)
		parTRData->SetAt(1, _T("1"));
	else
		parTRData->SetAt(1, _T("0"));
	
	m_mapRequest.SetAt(nRQID, pRequest);
}

void CSNJLab_Test3Dlg::OnCbnSelchangeComboOrder()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_CBOrderType.GetCurSel() < ORDER_REPLACE)
	{
		m_EDOrgOrderNo.EnableWindow(FALSE);
		m_CBFull.EnableWindow(FALSE);
		m_EDOrderQty.EnableWindow(TRUE);
	}
	else
	{
		m_EDOrgOrderNo.EnableWindow(TRUE);
		m_CBFull.EnableWindow(TRUE);
	}
}

void CSNJLab_Test3Dlg::RequestOrder(ORDER_TYPE nOrderType, CString strAcctNo, CString strPWD, CString strCode, unsigned int nOrderQty, ORDER_PRICE_TYPE nPriceType, double dOrderPrice, CString strOrgOrderNo)
{
	int nRQID;
	CString strAcct, strGDCode, strEnPWD, strOrderQty, strPriceType, strOrderPrice;
	strAcct = strAcctNo.Left(8);
	strGDCode = strAcctNo.Right(2);
	strEnPWD = m_ctlOCXReal.GetEncryptPassword(strPWD);
	
	stRequest *pRequest = new stRequest;
	memset(pRequest, 0x00, sizeof(stRequest));

	stOrderInfo* pOrderInfo = new stOrderInfo;
	pOrderInfo->strAcct = strAcct;
	pOrderInfo->strGDCode = strGDCode;
	pOrderInfo->strCode = strCode;
	pOrderInfo->nOrderType = nOrderType;
	pOrderInfo->nOrderPriceType = nPriceType;
	pOrderInfo->dOrderPrice = dOrderPrice;
	pOrderInfo->dFilledPrice = 0;
	pOrderInfo->nOrderQty = nOrderQty;
	strOrderQty.Format(_T("%d"), nOrderQty);

	/*
	지정가 (00: 없음, 11: IOC, 12: FOK)
	시장가 (01: 없음, 13: IOC, 14: FOK)
	조건부지정가 : 02
	최유리지정가 : (03: 없음, 15: IOC, 16: FOK)
	최우선지정가 : 04
	시간외단일가 : 07
	취소시에는 00 넣을것*/

	switch (nPriceType)
	{
	case ORDER_LIMIT:
		strPriceType = _T("00");
		strOrderPrice.Format(_T("%.0f"), dOrderPrice);
		break;
	case ORDER_MARKET:
		strPriceType = _T("01");
		strOrderPrice = _T("");
		break;
	}

	switch (nOrderType)
	{
		case  ORDER_SELL:
		{
			m_ctlOCXTR.SetSingleData(0, strAcct);		/// 종합계좌번호
			m_ctlOCXTR.SetSingleData(1, strGDCode);		/// 계좌상품코드 주식 : 01
			m_ctlOCXTR.SetSingleData(2, strEnPWD);		/// 계좌비밀번호
			m_ctlOCXTR.SetSingleData(3, strCode);		/// 종목코드
			m_ctlOCXTR.SetSingleData(4, _T("01"));	/// 매도유형 01
			m_ctlOCXTR.SetSingleData(5, strPriceType);	/// 주문구분 지정가 : 00, 시장가 01
			m_ctlOCXTR.SetSingleData(6, strOrderQty);	/// 주문수량
			m_ctlOCXTR.SetSingleData(7, strOrderPrice);	/// 주문단가
			//m_ctlOCXTR.SetSingleData(8, );			/// 연락전화번호

			m_ctlOCXTR.RequestData(_T("SCAAO"));

			pRequest->nTRID = TRID_SCAAO;
			
		}
		break;
		case  ORDER_BUY:
		{
			m_ctlOCXTR.SetSingleData(0, strAcct);		/// 종합계좌번호
			m_ctlOCXTR.SetSingleData(1, strGDCode);		/// 계좌상품코드 주식 : 01
			m_ctlOCXTR.SetSingleData(2, strEnPWD);		/// 계좌비밀번호
			m_ctlOCXTR.SetSingleData(3, strCode);		/// 종목코드
			m_ctlOCXTR.SetSingleData(4, strPriceType);	/// 주문구분 지정가 : 00, 시장가 01
			m_ctlOCXTR.SetSingleData(5, strOrderQty);	/// 주문수량
			m_ctlOCXTR.SetSingleData(6, strOrderPrice);	/// 주문단가
			//m_ctlOCXTR.SetSingleData(7, );			/// 연락전화번호

			m_ctlOCXTR.RequestData(_T("SCABO"));

			pRequest->nTRID = TRID_SCABO;
		}
		break;
	case  ORDER_REPLACE:
	case  ORDER_CANCEL:
		{
			stOrderInfo* pOrgOrderInfo;
			if (!m_mapOrder.Lookup(strOrgOrderNo, pOrgOrderInfo))
			{
				/// 원주문이 없는 경우
			}
			pOrderInfo->strOrgOrderNo = strOrgOrderNo;

			m_ctlOCXTR.SetSingleData(0, strAcct);		/// 종합계좌번호
			m_ctlOCXTR.SetSingleData(1, strGDCode);		/// 계좌상품코드 주식 : 01
			m_ctlOCXTR.SetSingleData(2, strEnPWD);		/// 계좌비밀번호
			m_ctlOCXTR.SetSingleData(3, pOrderInfo->strKRXOrderNo);			/// 한국거래소전송주문조작번호
			m_ctlOCXTR.SetSingleData(4, strOrgOrderNo);		/// 원주문번호
			
			if (nOrderType == ORDER_REPLACE)
			{
				m_ctlOCXTR.SetSingleData(5, strPriceType);	/// 주문구분 지정가 : 00, 시장가 01
				m_ctlOCXTR.SetSingleData(6, _T("01"));	/// 정정 01, 취소 02
				m_ctlOCXTR.SetSingleData(8, strOrderPrice);	/// 주문단가
			}
			else
			{
				m_ctlOCXTR.SetSingleData(5, _T("00"));	/// 주문구분 취소시 00
				m_ctlOCXTR.SetSingleData(6, _T("02"));	/// 정정 01, 취소 02
			}

			if (m_CBFull.GetCurSel() == 0)
				m_ctlOCXTR.SetSingleData(7, strOrderQty);	/// 주문수량
			else
			{
				pOrderInfo->nOrderQty = 0;				/// 잔량인 경우 주문 수량을 0으로 세팅한다
				m_ctlOCXTR.SetSingleData(7, _T(""));	/// 주문수량
				m_ctlOCXTR.SetSingleData(9, _T("Y"));	/// 잔량전부 "Y"
			}
			//m_ctlOCXTR.SetSingleData(10, );			/// 연락전화번호

			m_ctlOCXTR.RequestData(_T("SMCO"));

			pRequest->nTRID = TRID_SMCO;
		}
		break;
	}
	

	nRQID = m_ctlOCXTR.GetSendRqID();

	pRequest->wKey = nRQID;
	pRequest->pTRInfo = pOrderInfo;

	m_mapRequest.SetAt(nRQID, pRequest);
}

void CSNJLab_Test3Dlg::ProcessSCN_R(CStringArray* parOrderReal)
{
	stOrderInfo* pOrderInfo = NULL;
	CString strPositionKey;

	if (m_mapOrder.Lookup(parOrderReal->GetAt(SCN_R_ORDER_NO), pOrderInfo))
	{
		BOOL bFilled = _ttoi(parOrderReal->GetAt(SCN_R_FILLED)) == 2? TRUE : FALSE;
		CString strOrderNo = parOrderReal->GetAt(SCN_R_ORDER_NO);
		pOrderInfo->strCodeName = parOrderReal->GetAt(SCN_R_CODE_NAME);
		if (bFilled)
		{
			/// 체결시
			if (m_mapOrder.Lookup(strOrderNo, pOrderInfo))
			{
				int nFilledQty = _ttoi(parOrderReal->GetAt(SCN_R_FILLED_QTY));

				/// 체결정보
				stFill* pFillInfo = new stFill;
				pFillInfo->strAcct		= pOrderInfo->strAcct;
				pFillInfo->strOrderNo	= strOrderNo;
				pFillInfo->strCode		= pOrderInfo->strCode;
				pFillInfo->strCodeName = pOrderInfo->strCodeName;
				pFillInfo->strFilledTime = parOrderReal->GetAt(SCN_R_FILLED_TIME);
				pFillInfo->nOrderType	= pOrderInfo->nOrderType;
				pFillInfo->nFilledQty	= nFilledQty;
				pFillInfo->dFilledPrice = _ttof(parOrderReal->GetAt(SCN_R_FILLED_PRICE));

				/// 주문정보 결합
				pOrderInfo->pListFill->AddTail(pFillInfo);
				
				/// FillList
				m_listFill.AddTail(pFillInfo);
				
				/// FillMapByCode
				CPtrList* pList;
				if (!m_mapCodeFill.Lookup(pOrderInfo->strCode, pList))
				{
					pList = new CPtrList;
					m_mapCodeFill.SetAt(pOrderInfo->strCode, pList);
				}

				pList->AddTail(pFillInfo);
				
				/// Order Update
				pOrderInfo->nFilledQty = pOrderInfo->nFilledQty + nFilledQty;
				pOrderInfo->nOpenQty = pOrderInfo->nOpenQty - nFilledQty;

				if (pOrderInfo->nOpenQty == 0)
					pOrderInfo->nOrderStatus = ORDER_FILLED_CLOSE;

				/// Position Update
				stPosition* pPosition = NULL;
				strPositionKey.Format(_T("%s_%s"), pOrderInfo->strAcct, pOrderInfo->strCode);
				if (!m_mapPosition.Lookup(strPositionKey, pPosition))
				{
					pPosition = new stPosition;
					m_mapPosition.SetAt(strPositionKey, pPosition);
					
					pPosition->strAcct	= pOrderInfo->strAcct;
					pPosition->strCode = pOrderInfo->strCode;
					pPosition->strCodeName = pOrderInfo->strCodeName;
					pPosition->dPrice = 0;
					pPosition->nQty = 0;
				}

				if (pFillInfo->nOrderType == ORDER_BUY)
				{
					pPosition->dPrice = ((pPosition->nQty*pPosition->dPrice) + (pFillInfo->nFilledQty*pFillInfo->dFilledPrice)) / (pPosition->nQty + pFillInfo->nFilledQty);
					pPosition->nQty = pPosition->nQty + pFillInfo->nFilledQty;

					strLogText.Format(_T(" Acct[%s] Code[%s] Qty[%d] 매수 체결"), pFillInfo->strAcct, pFillInfo->strCode, pFillInfo->nFilledQty);
					SendLog(strLogText);
				}
				else
				{
					if (pPosition->nQty != pFillInfo->nFilledQty)
					{
						pPosition->dPrice = ((pPosition->nQty*pPosition->dPrice) - (pFillInfo->nFilledQty*pFillInfo->dFilledPrice)) / (pPosition->nQty - pFillInfo->nFilledQty);
						pPosition->nQty = pPosition->nQty - pFillInfo->nFilledQty;
					}
					else
					{
						pPosition->dPrice = 0;
						pPosition->nQty = 0;
					}
					
					strLogText.Format(_T(" Acct[%s] Code[%s] Qty[%d] 매도 체결"), pFillInfo->strAcct, pFillInfo->strCode, pFillInfo->nFilledQty);
					SendLog(strLogText);					
				}
			}
		}
		else
		{
			/// 주문 확인
			int nRejected = _ttoi(parOrderReal->GetAt(SCN_R_REJECT));

			if (nRejected == 0)
			{
				/// 정상
				int nReplaceCancel = _ttoi(parOrderReal->GetAt(SCN_R_REPLACE_CALCEL));

				switch (nReplaceCancel)
				{
					case 0:
					{
						/// 매도/매수 주문 확인 
						/// 주문 수량과 확인 수량 다른 경우 확인 불가
						if (m_mapOrder.Lookup(strOrderNo, pOrderInfo))
							pOrderInfo->nOrderQty = _ttoi(parOrderReal->GetAt(SCN_R_ORDER_QTY));

						break;
					}

					case 1:
					{
						/// 정정 주문 확인
						CString strOrgOrderNo = parOrderReal->GetAt(SCN_R_ORG_ORDER_NO);
						stOrderInfo *pOrderInfo, *pOrgOrderInfo;

						if (m_mapOrder.Lookup(strOrderNo, pOrderInfo) && m_mapOrder.Lookup(strOrgOrderNo, pOrgOrderInfo))
						{
							int nFilledQty = _ttoi(parOrderReal->GetAt(SCN_R_FILLED_QTY));
							pOrderInfo->nOrderType = pOrgOrderInfo->nOrderType;
							pOrgOrderInfo->nReplacedQty = pOrgOrderInfo->nReplacedQty + nFilledQty;
							pOrgOrderInfo->nOpenQty = pOrgOrderInfo->nOpenQty - nFilledQty;

							if (pOrgOrderInfo->nOpenQty == 0)		/// 원주문 끝
								pOrgOrderInfo->nOrderStatus = ORDER_REPLACED_CLOSE;
						
							///잔량 정정
							if (pOrderInfo->nOrderQty == 0)
							{
								pOrderInfo->nOrderQty = nFilledQty;
								pOrderInfo->nOpenQty = nFilledQty;
							}
							strLogText.Format(_T(" %s->%s 정정완료 Acct[%s], Code[%s]"), strOrgOrderNo, strOrderNo, pOrderInfo->strAcct, pOrderInfo->strCode);
							SendLog(strLogText);
						}
						break;
					}

					case 2:
					{
						/// 취소 주문 확인
						CString strOrgOrderNo = parOrderReal->GetAt(SCN_R_ORG_ORDER_NO);
						stOrderInfo *pOrderInfo, *pOrgOrderInfo;

						if (m_mapOrder.Lookup(strOrderNo, pOrderInfo) && m_mapOrder.Lookup(strOrgOrderNo, pOrgOrderInfo))
						{
							int nFilledQty = _ttoi(parOrderReal->GetAt(SCN_R_FILLED_QTY));
							pOrgOrderInfo->nCanceledQty = pOrgOrderInfo->nCanceledQty + nFilledQty;
							pOrgOrderInfo->nOpenQty = pOrgOrderInfo->nOpenQty - nFilledQty;

							if (pOrgOrderInfo->nOpenQty == 0)	/// 원주문 끝
								pOrgOrderInfo->nOrderStatus = ORDER_CANCELED_CLOSE;
						
							//pOrderInfo->nCanceledQty = _ttoi(parOrderReal->GetAt(SCN_R_ORDER_QTY));
							pOrderInfo->nFilledQty = nFilledQty;
							pOrderInfo->nOrderQty = nFilledQty;
							pOrderInfo->nOpenQty = 0;
							pOrderInfo->nOrderStatus = ORDER_FILLED_CLOSE;

							strLogText.Format(_T(" %s->%s 취소완료 Acct[%s], Code[%s]"), strOrgOrderNo, strOrderNo, pOrderInfo->strAcct, pOrderInfo->strCode);
							SendLog(strLogText);
						}
						break;
					}
				}
			}
			else
			{
				/// 거부
				if (m_mapOrder.Lookup(strOrderNo, pOrderInfo))
				{
					pOrderInfo->nOrderStatus = ORDER_REJECTED;
					strLogText.Format(_T(" 주문번호 : %s 주문거부 Acct[%s], Code[%s]"), strOrderNo, pOrderInfo->strAcct, pOrderInfo->strCode);
					SendLog(strLogText);
				}
			}
		}
	}

	parOrderReal->RemoveAll();
	delete parOrderReal;
}

void CSNJLab_Test3Dlg::ProcessOrderDS(stOrderInfo* pOrderInfo)
{
	CPtrList* pListOrder;

	m_mapOrder.SetAt(pOrderInfo->strOrderNo, pOrderInfo);
	m_listOrder.AddTail(pOrderInfo);

	if (!m_mapCodeOrder.Lookup(pOrderInfo->strCode, pListOrder))
	{
		pListOrder = new CPtrList;
		m_mapCodeOrder.SetAt(pOrderInfo->strCode, pListOrder);
	}
	
	pListOrder->AddTail(pOrderInfo);
}

void CSNJLab_Test3Dlg::ShowOrderList(CString strCode)
{
	stOrderInfo* pOrderInfo;
	int nRow = 0;
	CString strText;
	CPtrList* pPtrList;

	m_ctlOrderList.DeleteAllItems();

	if (strCode.IsEmpty())
		pPtrList = &m_listOrder;
	else
		m_mapCodeOrder.Lookup(strCode, pPtrList);

	if (pPtrList)
	{
		POSITION pos = pPtrList->GetHeadPosition();

		while (pos)
		{
			pOrderInfo = (stOrderInfo*)(pPtrList->GetNext(pos));
			m_ctlOrderList.InsertItem(nRow, _T(""));

			m_ctlOrderList.SetItemText(nRow, 1, pOrderInfo->strAcct);
			m_ctlOrderList.SetItemText(nRow, 2, pOrderInfo->strCode);
			m_ctlOrderList.SetItemText(nRow, 3, pOrderInfo->strOrderNo);
			m_ctlOrderList.SetItemText(nRow, 4, pOrderInfo->strOrgOrderNo);
			m_ctlOrderList.SetItemText(nRow, 5, pOrderInfo->strOrderTime);

			strText = GetOrderTypeString(pOrderInfo->nOrderType);
			m_ctlOrderList.SetItemText(nRow, 6, strText);

			strText = GetOrderStatusString(pOrderInfo->nOrderStatus);
			m_ctlOrderList.SetItemText(nRow, 7, strText);

			strText.Format(_T("%d"), pOrderInfo->nOrderQty);
			m_ctlOrderList.SetItemText(nRow, 8, strText);

			strText.Format(_T("%d"), pOrderInfo->nOpenQty);
			m_ctlOrderList.SetItemText(nRow, 9, strText);

			strText.Format(_T("%d"), pOrderInfo->nFilledQty);
			m_ctlOrderList.SetItemText(nRow, 10, strText);

			strText.Format(_T("%d"), pOrderInfo->nCanceledQty);
			m_ctlOrderList.SetItemText(nRow, 11, strText);

			strText.Format(_T("%d"), pOrderInfo->nReplacedQty);
			m_ctlOrderList.SetItemText(nRow, 12, strText);

			strText = GetOrderPriceTypeString(pOrderInfo->nOrderPriceType);
			m_ctlOrderList.SetItemText(nRow, 13, strText);

			strText.Format(_T("%.0f"), pOrderInfo->dOrderPrice);
			m_ctlOrderList.SetItemText(nRow, 14, strText);

			strText.Format(_T("%.0f"), pOrderInfo->dFilledPrice);
			m_ctlOrderList.SetItemText(nRow, 15, strText);

			m_ctlOrderList.SetItemText(nRow, 16, pOrderInfo->strCodeName);
			
			nRow++;
		}
	}
}


void CSNJLab_Test3Dlg::OnBnClickedButtonOrderView()
{
	CString strCode;
	m_ctrEDOrderCode.GetWindowText(strCode);

	if (strCode.GetLength() != 6)
		strCode = _T("");

	ShowOrderList(strCode);
}


void CSNJLab_Test3Dlg::OnClose()
{
	ClearMemory();

	CDialogEx::OnClose();
}


void CSNJLab_Test3Dlg::OnNMClickListOrder(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	NM_LISTVIEW* pListView = (NM_LISTVIEW*)pNMHDR;
	
	int nIdx = pListView->iItem;
	CString strCode, strOrgOrderNo;
	
	strCode = m_ctlOrderList.GetItemText(nIdx, 2);
	strOrgOrderNo = m_ctlOrderList.GetItemText(nIdx, 3);

	m_EDCode.SetWindowTextW(strCode);
	m_EDOrgOrderNo.SetWindowTextW(strOrgOrderNo);

	*pResult = 0;
}


void CSNJLab_Test3Dlg::OnCbnSelchangeComboPricetype()
{
	m_CBPriceType.GetCurSel() == 0 ? m_EDOrderPrice.EnableWindow(TRUE) : m_EDOrderPrice.EnableWindow(FALSE);
}


void CSNJLab_Test3Dlg::OnCbnSelchangeComboFull()
{
	m_CBFull.GetCurSel() == 0 ? m_EDOrderQty.EnableWindow(TRUE) : m_EDOrderQty.EnableWindow(FALSE);
}


void CSNJLab_Test3Dlg::OnBnClickedButtonFillView()
{
	CString strKey;
	int nCBIndex = m_CBFillBase.GetCurSel();

	m_EDFillBase.GetWindowText(strKey);

	ShowFillList(nCBIndex, strKey);
}


void CSNJLab_Test3Dlg::OnCbnSelchangeComboFillBase()
{
	m_CBFillBase.GetCurSel() == 0 ? m_EDFillBase.EnableWindow(FALSE) : m_EDFillBase.EnableWindow(TRUE);
}

void CSNJLab_Test3Dlg::ShowFillList(int nBase, CString strKey)
{
	CPtrList* pFillList = NULL;
	stFill* pFill;
	stOrderInfo* pOrderInfo;
	int nRow = 0;
	CString strText;
	
	m_ctlFillList.DeleteAllItems();

	switch (nBase)
	{
	case 0: /// 전체
		pFillList = &m_listFill;
		break;
	case 1: /// 종목별
		m_mapCodeFill.Lookup(strKey, pFillList);
		break;
	case 2: /// 주문번호별
		if (m_mapOrder.Lookup(strKey, pOrderInfo))
			pFillList = pOrderInfo->pListFill;
		break;
	}

	if (pFillList)
	{
		POSITION pos = pFillList->GetHeadPosition();

		while (pos)
		{
			pFill = (stFill*)(pFillList->GetNext(pos));

			m_ctlFillList.InsertItem(nRow, _T(""));

			m_ctlFillList.SetItemText(nRow, 1, pFill->strAcct);
			m_ctlFillList.SetItemText(nRow, 2, pFill->strCodeName);
			m_ctlFillList.SetItemText(nRow, 3, pFill->strOrderNo);
			m_ctlFillList.SetItemText(nRow, 4, pFill->strFilledTime);

			strText = GetOrderTypeString(pFill->nOrderType);
			m_ctlFillList.SetItemText(nRow, 5, strText);
			
			strText.Format(_T("%d"), pFill->nFilledQty);
			m_ctlFillList.SetItemText(nRow, 6, strText);

			strText.Format(_T("%.0f"), pFill->dFilledPrice);
			m_ctlFillList.SetItemText(nRow, 7, strText);
		
			nRow++;
		}
	}
}

void CSNJLab_Test3Dlg::OnBnClickedButtonPositionView()
{
	// TODO: Add your control notification handler code here
	POSITION pos;
	CString strPositionKey, strText;
	stPosition* pPosition;
	int nRow = 0;
	pos = m_mapPosition.GetStartPosition();

	m_ctlPositionList.DeleteAllItems();

	while (pos)
	{
		m_mapPosition.GetNextAssoc(pos, strPositionKey, pPosition);

		if (pPosition)
		{
			m_ctlPositionList.InsertItem(nRow, _T(""));

			m_ctlPositionList.SetItemText(nRow, 1, pPosition->strAcct);
			m_ctlPositionList.SetItemText(nRow, 2, pPosition->strCodeName);
			
			strText.Format(_T("%d"), pPosition->nQty);
			m_ctlPositionList.SetItemText(nRow, 3, strText);

			strText.Format(_T("%.2f"), pPosition->dPrice);
			m_ctlPositionList.SetItemText(nRow, 4, strText);
			nRow++;
		}
	}
}

void CSNJLab_Test3Dlg::SendLog(CString strText)
{
	CTime time = CTime::GetCurrentTime();
	CString strLog;

	strLog.Format(_T("[%02d:%02d:%02d]  [%s]"), time.GetHour(), time.GetMinute(), time.GetSecond(), strText);
	m_EDLog.SetWindowText(strLog);
}

void CSNJLab_Test3Dlg::ClearMemory()
{
	POSITION pos = m_listOrder.GetHeadPosition();
	POSITION posFill;
	CStringArray* parOrderReal;
	stOrderInfo* pOrderInfo;
	stFill* pFill;
	CString strCode;
	CPtrList* pPtrList;
	stPosition* pPosition;

	/// OrderInfo 전체 삭제
	while (pos)
	{
		pOrderInfo = m_listOrder.GetNext(pos);
		if (pOrderInfo->pListFill)
		{
			posFill = pOrderInfo->pListFill->GetHeadPosition();
			while (posFill)
			{
				/// Order에 연결된 체결정보 삭제
				pFill = pOrderInfo->pListFill->GetNext(posFill);
				delete pFill;
			}
			pOrderInfo->pListFill->RemoveAll();
			delete pOrderInfo->pListFill;
		}
		delete pOrderInfo;
	}

	m_listOrder.RemoveAll();
	m_mapOrder.RemoveAll();

	/// 코드별 주문 리스트 삭제
	pos = m_mapCodeOrder.GetStartPosition();
	while (pos)
	{
		m_mapCodeOrder.GetNextAssoc(pos, strCode, pPtrList);
		delete pPtrList;
	}
	m_mapCodeOrder.RemoveAll();

	/// 전체 체결 List 삭제
	m_listFill.RemoveAll();

	/// 코드별 주문 체결 리스트 삭제
	pos = m_mapCodeFill.GetStartPosition();
	while (pos)
	{
		m_mapCodeFill.GetNextAssoc(pos, strCode, pPtrList);
		delete pPtrList;
	}
	m_mapCodeFill.RemoveAll();

	/// 역전 주문 and 타 매체 주문 삭제
	pos = m_mapReverseOrder.GetStartPosition();
	while (pos)
	{
		m_mapReverseOrder.GetNextAssoc(pos, strCode, parOrderReal);
		parOrderReal->RemoveAll();
		delete parOrderReal;
	}

	m_mapReverseOrder.RemoveAll();


	/// Position 삭제
	pos = m_mapPosition.GetStartPosition();

	while (pos)
	{
		m_mapPosition.GetNextAssoc(pos, strCode, pPosition);
		delete pPosition;
	}

	m_mapPosition.RemoveAll();
}

CString CSNJLab_Test3Dlg::GetOrderTypeString(int nOrderType)
{
	CString strText;

	switch (nOrderType)
	{
		case ORDER_SELL:
			strText = _T("매도");
			break;
		case ORDER_BUY:
			strText = _T("매수");
			break;
		case ORDER_REPLACE:
			strText = _T("정정");
			break;
		case ORDER_CANCEL:
			strText = _T("취소");
			break;
		default:
			break;
	}

	return strText;
}

CString CSNJLab_Test3Dlg::GetOrderPriceTypeString(int nOrderPriceType)
{
	CString strText;

	switch (nOrderPriceType)
	{
		case ORDER_LIMIT:
			strText = _T("Limit");
			break;
		case ORDER_MARKET:
			strText = _T("Market");
			break;
		case ORDER_LIMIT_IOC:
			strText = _T("L-IOC");
			break;
		case ORDER_LIMIT_FOK:
			strText = _T("L-FOK");
			break;
		case ORDER_MARKET_IOC:
			strText = _T("M-IOC");
			break;
		case ORDER_MARKET_FOK:
			strText = _T("M-FOK");
			break;
		/// 추후 추가
		default:
			break;
	}

	return strText;
}

CString CSNJLab_Test3Dlg::GetOrderStatusString(ORDER_STATUS nOrderStatus)
{
	CString strText;

	switch (nOrderStatus)
	{
		case ORDER_OPEN:
			strText = _T("Open");
			break;
		case ORDER_FILLED_CLOSE:
			strText = _T("FIlledClose");
			break;
		case ORDER_REPLACED_CLOSE:
			strText = _T("ReplacedClose");
			break;
		case ORDER_CANCELED_CLOSE:
			strText = _T("CanceledClose");
			break;
		case ORDER_REJECTED:
			strText = _T("Rejected");
			break;
	}

	return strText;
}

void CSNJLab_Test3Dlg::OnBnClickedButtonStartExpert()
{
	// TODO: Add your control notification handler code here
	HWND hExpertLogin =  ::FindWindow(NULL, _T("eFriend Expert 로그인"));
	HWND hITGExpertMain = ::FindWindow(NULL, _T("ITGExpertMain"));

	if (hITGExpertMain)
		SendLog(_T("eFriendExpert 실행중"));
	else
	{
		if (hExpertLogin)
			HookExert(hExpertLogin);
		else
		{
			int nRet = WinExec("C:\\eFriend Expert\\efriendexpert\\efriendexpert.exe", SW_SHOW);
			if (nRet < 31)
			{
				strLogText.Format(_T(" [%d] Fail to execute eFriendExpert"), nRet);
				SendLog(strLogText);
			}
			else
			{
				strLogText.Format(_T(" Success to execute eFriendExpert"));
				SendLog(strLogText);

				SetTimer(FIND_TIMER, 1000, NULL);
			}
		}
	}
}


void CSNJLab_Test3Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nIDEvent == FIND_TIMER)
	{
		HWND hExpertLogin = ::FindWindow(NULL, _T("eFriend Expert 로그인"));
		if (hExpertLogin)
		{
			KillTimer(FIND_TIMER);
			HookExert(hExpertLogin);
		}
	}
	CDialogEx::OnTimer(nIDEvent);
}

void CSNJLab_Test3Dlg::HookExert(HWND hExpertLogin)
{
	HWND hID, hCheck, hPWDEdit, hAuthEdit;
	CString strID, strLoginPWD, strAuthPWD;

	hID = ::FindWindowEx(hExpertLogin, NULL, _T("Edit"), _T(""));
	hCheck = ::GetNextWindow(hID, GW_HWNDNEXT);
	hPWDEdit = ::GetNextWindow(hCheck, GW_HWNDNEXT);
	hAuthEdit = ::GetNextWindow(hPWDEdit, GW_HWNDNEXT);

	GetDlgItem(IDC_EDIT_ID)->GetWindowText(strID);
	GetDlgItem(IDC_EDIT_LOGIN_PWD)->GetWindowText(strLoginPWD);
	GetDlgItem(IDC_EDIT_AUTH_PWD)->GetWindowText(strAuthPWD);
	
	strID.Trim();
	strLoginPWD.Trim();
	strAuthPWD.Trim();

	if (!strID.IsEmpty() && !strLoginPWD.IsEmpty() && !strAuthPWD.IsEmpty())
	{
		SendKeyIn(hID, strID);
		SendKeyIn(hPWDEdit, strLoginPWD);
		SendKeyIn(hAuthEdit, strAuthPWD);

		::PostMessage(hExpertLogin, WM_KEYDOWN, VK_RETURN, 0L);
	}
	else
		SendLog(_T("ID, PWD, AUTH 입력필수!!"));
}

int	CSNJLab_Test3Dlg::SendKeyIn(HWND hTarget, CString strKeys)
{
	int i, nLength;
	wchar_t cKeyIn;

	nLength = strKeys.GetLength();

	for (i = 0; i < nLength; i++)
	{
		cKeyIn = strKeys.GetAt(i);
		::PostMessage(hTarget, WM_CHAR, (WPARAM)cKeyIn, (LPARAM)0);
	}

	return nLength;
}