
// SNJLab_Test3Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "SNJLab_Test3.h"
#include "SNJLab_Test3Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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
	DDX_Control(pDX, IDC_EDIT_QTY, m_EDOrderQTY);
	DDX_Control(pDX, IDC_EDIT_PRICE, m_EDOrderPrice);
	DDX_Control(pDX, IDC_COMBO_ACCTNO, m_CBAcctNo);
	DDX_Control(pDX, IDC_EDIT_ORG_ORDERNO, m_EDOrgOrderNo);
	DDX_Control(pDX, IDC_EDIT_PWD, m_EDPWD);
}

BEGIN_MESSAGE_MAP(CSNJLab_Test3Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_REQUEST, &CSNJLab_Test3Dlg::OnBnClickedButtonRequest)
	ON_CBN_SELCHANGE(IDC_COMBO_ORDER, &CSNJLab_Test3Dlg::OnCbnSelchangeComboOrder)
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

	m_CBOrderType.AddString(_T("매도"));
	m_CBOrderType.AddString(_T("매수"));
	m_CBOrderType.AddString(_T("정정"));
	m_CBOrderType.AddString(_T("취소"));
	m_CBOrderType.SetCurSel(0);

	m_CBPriceType.AddString(_T("지정가"));
	m_CBPriceType.AddString(_T("시장가"));
	m_CBPriceType.SetCurSel(0);

	InItAccountNo();

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


void CSNJLab_Test3Dlg::ReceiveDataItgexpertctlctrl1()
{
	// TODO: Add your message handler code here
	short nRQID = m_ctlOCXTR.GetRecvRqID();
	//CString strTemp = m_ctlOCXTR.GetReqMsgCode();
	//strTemp = m_ctlOCXTR.GetReqMessage();
	
	stRequest* pRequest;

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
				CString strErrorCode = m_ctlOCXTR.GetRtCode();
				CString strRegMsgCode = m_ctlOCXTR.GetReqMsgCode();
				CString strGetReqMessage = m_ctlOCXTR.GetReqMessage();
				
				CStringArray* parOrderReal;
				stOrderInfo* pRcvOrderInfo = new stOrderInfo;
				stOrderInfo* pOrderInfo = (stOrderInfo*)(pRequest->pTRInfo);

				memcpy(pRcvOrderInfo, pOrderInfo, sizeof(stOrderInfo));
				
				pRcvOrderInfo->strKRXOrderNo = m_ctlOCXTR.GetSingleData(0, 0);
				pRcvOrderInfo->strOrderNo = m_ctlOCXTR.GetSingleData(1, 0);
				pRcvOrderInfo->strOrderTime = m_ctlOCXTR.GetSingleData(2, 0);

				if (pRcvOrderInfo->strOrderNo.Trim().IsEmpty())
				{
					/// 오류
				}
				else
				{
					m_mapOrder.SetAt(pOrderInfo->strOrderNo, pRcvOrderInfo);

					if (m_mapReverseOrder.Lookup(pOrderInfo->strOrderNo, parOrderReal))
					{
						ProcessSCN_R(parOrderReal);
						m_mapReverseOrder.RemoveKey(pOrderInfo->strOrderNo);
					}
				}
			}
			break;
		
		}

		m_mapRequest.RemoveKey(nRQID);
		delete pRequest->pTRInfo;
		delete pRequest;

	}
}


void CSNJLab_Test3Dlg::ReceiveErrorDataItgexpertctlctrl1()
{
	// TODO: Add your message handler code here
	CString strErrorCode = m_ctlOCXTR.GetRtCode();
	MessageBox(strErrorCode);
}


void CSNJLab_Test3Dlg::ReceiveSysMessageItgexpertctlctrl1(short nSysMsg)
{
	// TODO: Add your message handler code here
	CString strTemp;
	strTemp.Format(_T("SysMsg[%d] \n"), nSysMsg);
	TRACE(strTemp);
	switch (nSysMsg)
	{
	};
}


void CSNJLab_Test3Dlg::ReceiveRealDataItgexpertctlctrl2()
{
	// TODO: Add your message handler code here
	CString strText, strOrderNo;
	int nFieldCnt = m_ctlOCXReal.GetSingleFieldCount();
	CStringArray* parOrderReal = new CStringArray;
	parOrderReal->SetSize(nFieldCnt);
	stOrderInfo* pOrderInfo = NULL;

	for (int i = 0; i < nFieldCnt; i++)
		parOrderReal->SetAt(i, m_ctlOCXReal.GetSingleData(i, 0));

	strOrderNo = parOrderReal->GetAt(SCN_R_ORDER_NO);
	if (m_mapOrder.Lookup(strOrderNo, pOrderInfo))			/// 주문번호 있을시	
		ProcessSCN_R(parOrderReal);
	else													/// 실시간 들어왔는데 주문 번호가 없다->Reverse 발생
		m_mapReverseOrder.SetAt(strOrderNo, parOrderReal);



	strText.Format(_T("Real [%s][%f][%f]\n"), m_ctlOCXReal.GetSingleData(0,0), _ttof(m_ctlOCXReal.GetSingleData(1,0)), _ttof(m_ctlOCXReal.GetSingleData(2,0)));
	TRACE(strText);
}


void CSNJLab_Test3Dlg::InItAccountNo()
{
	int nAcntCnt = m_ctlOCXTR.GetAccountCount();
	CString strAcnt;
	for (int i = 0; i < nAcntCnt; i++)
	{
		strAcnt = m_ctlOCXTR.GetAccount(i);
		m_CBAcctNo.AddString(strAcnt);
	}

	m_CBAcctNo.SetCurSel(0);
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
	m_EDOrderQTY.GetWindowText(strOrderQty);
	m_EDOrgOrderNo.GetWindowText(strOrgOrderNo);
	m_EDPWD.GetWindowText(strPWD);

	nOrderQty = _ttoi(strOrderQty);
	dOrderPrice = _ttof(strOrderPrice);

	RequestOrder(nOrderType, strAcctNo, strPWD, strCode, nOrderQty, nPriceType, dOrderPrice, strOrgOrderNo);

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
}

void CSNJLab_Test3Dlg::RequestOrder(int nOrderType, CString strAcctNo, CString strPWD, CString strCode, unsigned int nOrderQty, int nPriceType, double dOrderPrice, CString strOrgOrderNo)
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
		break;
	case ORDER_MARKET:
		strPriceType = _T("01");
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
			pOrderInfo->strOrderNo = strOrgOrderNo;

			m_ctlOCXTR.SetSingleData(0, strAcct);		/// 종합계좌번호
			m_ctlOCXTR.SetSingleData(1, strGDCode);		/// 계좌상품코드 주식 : 01
			m_ctlOCXTR.SetSingleData(2, strEnPWD);		/// 계좌비밀번호
			//m_ctlOCXTR.SetSingleData(3, );			/// 한국거래소전송주문조작번호
			m_ctlOCXTR.SetSingleData(4, strOrgOrderNo);		/// 원주문번호
			
			if (nOrderType == ORDER_REPLACE)
			{
				m_ctlOCXTR.SetSingleData(5, strPriceType);	/// 주문구분 지정가 : 00, 시장가 01
				m_ctlOCXTR.SetSingleData(6, _T("01"));	/// 정정 01, 취소 02
			}
			else
			{
				m_ctlOCXTR.SetSingleData(5, _T("00"));	/// 주문구분 취소시 00
				m_ctlOCXTR.SetSingleData(6, _T("02"));	/// 정정 01, 취소 02
			}

			m_ctlOCXTR.SetSingleData(7, strOrderQty);	/// 주문수량
			m_ctlOCXTR.SetSingleData(8, strOrderPrice);	/// 주문단가
			//m_ctlOCXTR.SetSingleData(9, );	/// 잔량전부 "Y"
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

	if (m_mapOrder.Lookup(parOrderReal->GetAt(SCN_R_ORDER_NO), pOrderInfo))
	{

	}

	parOrderReal->RemoveAll();
	delete parOrderReal;
}