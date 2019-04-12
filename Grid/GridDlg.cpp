// SwapColorDlg.cpp : implementation file
// http://www.realcoding.net/article/rubric/CCplus/MFC?page=4 MFC

#include "stdafx.h"
#include "resource.h"
#include <vfw.h>
#include "NameValueBuffer.h"
#include "ModuleDlg.h"
#include "GridDlg.h"
#include "afxcmn.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SwapColorDlg dialog
//
// Function:
// Provides an example module to swapping the color channels in an image
// being processed by RoboRealm.
//
// 1. You will need to update the RRModule.dll file each time you recompile
// this module. This file is already located in the RoboRealm.zip download.
// You can automate this process by changing the
//
//   Project->Settings->Debug->General->Executable for Debug Session
//
// path so that it overwrites the file in the RoboRealm folder.
// 2. To run this set the
//
//   Project->Settings->Debug->General->Working Directory
//
// to the RoboRealm folder and run this project.
// 3. RoboRealm show run and if you select
//
//   Extensions->SwapColor
//
// the interface to this module should appear. You can then set and breakpoints
// in this project to trap the execution.
/////////////////////////////////////////////////////////////////////////////

GridDlg::GridDlg(CWnd* pParent /*=NULL*/)
: ModuleDlg(GridDlg::IDD, pParent)
{		
	//{{AFX_DATA_INIT(GridDlg)
	color = 1;
	thikness = 1;
	m_bChk1 = true;
	m_bChk2 = true;
	//}}AFX_DATA_INIT
}

void GridDlg::DoDataExchange(CDataExchange* pDX)
{		
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(GridDlg)

	//}}AFX_DATA_MAP	
	DDX_Control(pDX, IDC_CHECK1, m_Check1);
	DDX_Control(pDX, IDC_COLOR, m_ComboBoxColor);
	DDX_Control(pDX, IDC_CHECK2, m_Check2);
	DDX_Control(pDX, IDC_SPIN1, m_Spin1);
	DDX_Control(pDX, IDC_C1, m_EditCount1);
	DDX_Control(pDX, IDC_SPIN2, m_Spin2);
	DDX_Control(pDX, IDC_S1, m_EditStep1);
	DDX_Control(pDX, IDC_SPIN3, m_Spin3);
	DDX_Control(pDX, IDC_X1, m_EditX1);
	DDX_Control(pDX, IDC_SPIN5, m_Spin5);
	DDX_Control(pDX, IDC_X2, m_EditX2);
	DDX_Control(pDX, IDC_SPIN4, m_Spin4);
	DDX_Control(pDX, IDC_Y1, m_EditY1);
	DDX_Control(pDX, IDC_SPIN6, m_Spin6);
	DDX_Control(pDX, IDC_Y2, m_EditY2);

	DDX_Control(pDX, IDC_SPIN7, m_Spin7);
	DDX_Control(pDX, IDC_C2, m_EditCount2);
	DDX_Control(pDX, IDC_SPIN8, m_Spin8);
	DDX_Control(pDX, IDC_S2, m_EditStep2);
	DDX_Control(pDX, IDC_SPIN9, m_Spin9);
	DDX_Control(pDX, IDC_X3, m_EditX3);
	DDX_Control(pDX, IDC_SPIN11, m_Spin11);
	DDX_Control(pDX, IDC_X4, m_EditX4);
	DDX_Control(pDX, IDC_SPIN10, m_Spin10);
	DDX_Control(pDX, IDC_Y3, m_EditY3);
	DDX_Control(pDX, IDC_SPIN12, m_Spin12);
	DDX_Control(pDX, IDC_Y4, m_EditY4);
	DDX_Control(pDX, IDC_THIKNESS, m_ComboBoxThikness);
	// горизонтальные переменные
	DDX_Text(pDX, IDC_X1, strX1);
	DDX_Text(pDX, IDC_X2, strX2);
	DDX_Text(pDX, IDC_Y1, strY1);
	DDX_Text(pDX, IDC_Y2, strY2);
	DDX_Text(pDX, IDC_S1, strStep1);
	DDX_Text(pDX, IDC_C1, strCount1);
	// вертикальные переменные
	DDX_Text(pDX, IDC_X3, strX3);
	DDX_Text(pDX, IDC_X4, strX4);
	DDX_Text(pDX, IDC_Y3, strY3);
	DDX_Text(pDX, IDC_Y4, strY4);
	DDX_Text(pDX, IDC_S2, strStep2);
	DDX_Text(pDX, IDC_C2, strCount2);
}

BEGIN_MESSAGE_MAP(GridDlg, CDialog)
	//{{AFX_MSG_MAP(GridDlg)
	ON_BN_CLICKED(IDC_SHOW_HELP, OnHelp)	
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_CHECK1, &GridDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &GridDlg::OnBnClickedCheck2)
	ON_WM_LBUTTONDOWN()
	ON_EN_CHANGE(IDC_Y1, &GridDlg::OnEnChangeY1)
	ON_EN_CHANGE(IDC_C1, &GridDlg::OnEnChangeC1)
	ON_EN_CHANGE(IDC_S1, &GridDlg::OnEnChangeS1)
	ON_EN_CHANGE(IDC_X1, &GridDlg::OnEnChangeX1)
	ON_EN_CHANGE(IDC_X2, &GridDlg::OnEnChangeX2)
	ON_EN_CHANGE(IDC_C2, &GridDlg::OnEnChangeC2)
	ON_EN_CHANGE(IDC_S2, &GridDlg::OnEnChangeS2)
	ON_EN_CHANGE(IDC_X3, &GridDlg::OnEnChangeX3)
	ON_EN_CHANGE(IDC_Y3, &GridDlg::OnEnChangeY3)
	ON_EN_CHANGE(IDC_X4, &GridDlg::OnEnChangeX4)
	ON_EN_CHANGE(IDC_Y4, &GridDlg::OnEnChangeY4)
	ON_CBN_SELENDOK(IDC_COLOR, &GridDlg::OnCbnSelendokColor)
	ON_CBN_SELENDOK(IDC_THIKNESS, &GridDlg::OnCbnSelendokThikness)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN4, &GridDlg::OnDeltaposSpin4)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// GridDlg message handlers

// Called on initialization of the dll
bool GridDlg::Initialize()
{
  // tell RoboRealm that we have a GUI dialog
  hasDialog = true;

  // Заполянем выпадающий список Color
  m_ComboBoxColor.AddString("");
  m_ComboBoxColor.AddString("Black");
  m_ComboBoxColor.AddString("White");
  m_ComboBoxColor.AddString("Green");
  m_ComboBoxColor.AddString("Blue");
  m_ComboBoxColor.AddString("Red");
  m_ComboBoxColor.SetCurSel(color);
  
// Заполянем выпадающий список Thikness
  m_ComboBoxThikness.AddString("");
  m_ComboBoxThikness.AddString("1");
  m_ComboBoxThikness.AddString("2");
  m_ComboBoxThikness.AddString("3");
  m_ComboBoxThikness.AddString("4");
  m_ComboBoxThikness.AddString("5");
  m_ComboBoxThikness.AddString("6");
  m_ComboBoxThikness.AddString("7");
  m_ComboBoxThikness.AddString("8");
  m_ComboBoxThikness.AddString("9");
  m_ComboBoxThikness.AddString("10");
  m_ComboBoxThikness.AddString("11");
  m_ComboBoxThikness.AddString("12");
  m_ComboBoxThikness.AddString("13");
  m_ComboBoxThikness.AddString("14");
  m_ComboBoxThikness.AddString("15");
  m_ComboBoxThikness.SetCurSel(thikness);

// При загрузке окна галочки в Check1 и Check2 проставлены
  m_Check2.SetCheck(m_bChk2);
  m_Check1.SetCheck(m_bChk1);

  // настройка Spin и дружественных им EditBox
  const int N = 10000;				// максимальная ширина или высота изображений в Roborealm

  // настройки для горизонтальных линий
  m_Spin1.SetBuddy(&m_EditCount1); // подружить окно
  m_Spin1.SetRange(0, 1000);	   // диапазон значений спина
  m_Spin2.SetBuddy(&m_EditStep1); 
  m_Spin2.SetRange(0, 10000);
  m_Spin3.SetBuddy(&m_EditX1);
  m_Spin3.SetRange(0, N);
 // m_Spin4.SetBuddy(&m_EditY1);
  //m_Spin4.SetRange(0, N);
  m_Spin5.SetBuddy(&m_EditX2); 
  m_Spin5.SetRange(0, N); 
  m_Spin6.SetBuddy(&m_EditY2);
  m_Spin6.SetRange(0, N);

  // настройки для вертикальных линий
  m_Spin7.SetBuddy(&m_EditCount2); // подружить окно
  m_Spin7.SetRange(0, 1000);	   // диапазон значений спина
  m_Spin8.SetBuddy(&m_EditStep2);
  m_Spin8.SetRange(0, N);
  m_Spin9.SetBuddy(&m_EditX3);
  m_Spin9.SetRange(0, N);
  m_Spin10.SetBuddy(&m_EditY3);
  m_Spin10.SetRange(0, N);
  m_Spin11.SetBuddy(&m_EditX4);  
  m_Spin11.SetRange(0, N);
  m_Spin12.SetBuddy(&m_EditY4);
  m_Spin12.SetRange(0, N);
    
	return true;
}

void GridDlg::Destroy()
{	

}

// used to indentify this plugin
char *GridDlg::GetName()
{
  return "Grid";
}

// when the ok button is pressed this is called and used to indicate in the RoboRealm program pipeline
// what this module is. You can use this routine to include basic indicators that help the end user
// know what operation is being performed.
char *GridDlg::GetDisplay()
{
	// configure our module text display in the pipeline
	_snprintf(display, 256, "Grid %s", "");

  return display;
}

// The main image processing call.
// data - contains the current image data as BGR pixels
// tmp2Image - a temporary short int buffer than can be used for storage during image processing
// tmpImage - a temporary char buffer than can be used for storage during image processing
int GridDlg::Process(unsigned char *data, short int *tmp2Image, unsigned char *tmpImage, int left, int top, int width, int height)
{  	
	// переменные необходимые для отрисовки ширины
	int thiknesshalf = thikness / 2;
	int edge1;
	int edge2;
	if (thiknesshalf != thikness / 2.0)
	{
		edge1 = -thiknesshalf;
		edge2 = thiknesshalf;
	}
	else
	{
		edge1 = -thiknesshalf + 1;
		edge2 = thiknesshalf;
	}
	unsigned char RGB[3] = { 0, 0, 0 };
	bool FlagColor = ColorChoise(color, RGB);

	// горизонтальные переменные
	//int X1 = atoi(strX1);
	//int X2 = atoi(strX2);
	//int Y1 = atoi(strY1);
	//int Y2 = atoi(strY2);

	int X1 = ParseInt(&strX1);
	int X2 = ParseInt(&strX2);
	int Y1 = ParseInt(&strY1);
	int Y2 = ParseInt(&strY2);
	int Count1 = atoi(strCount1);
	int Step1 = atoi(strStep1);
	// вертикальные переменные
	/*int X3 = atoi(strX3);
	int X4 = atoi(strX4);
	int Y3 = atoi(strY3);
	int Y4 = atoi(strY4);*/
	int X3 = ParseInt(&strX3);
	int X4 = ParseInt(&strX4);
	int Y3 = ParseInt(&strY3);
	int Y4 = ParseInt(&strY4);
	int Count2 = atoi(strCount2);
	int Step2 = atoi(strStep2);

	// Вывод переменных для отладки
	//SetVariable("My_Count1", Count1);
	//SetVariable("My_Step1", Step1);
	//SetVariable("My_X1", X1);
	//SetVariable("My_X2", X2);
	SetVariable("My_Y1", Y1);
	SetVariable("My_strY1", &strY1);
	//SetVariable("My_Y2", Y2);
	//SetVariable("My_Count2", Count2);
	//SetVariable("My_Step2", Step2);
	//SetVariable("My_X3", X3);
	//SetVariable("My_X4", X4);
	//SetVariable("My_Y3", Y3);
	//SetVariable("My_Y4", Y4);

	Y2 = height;
	X4 = width;
	if (X1 == 0) X1 = 0;
	if (X2 == 0) X2 = width;
	if (Y3 == 0) Y3 = 0;
	if (Y4 == 0) Y4 = height;

	m_Spin1.SetPos(Count1);
	m_Spin2.SetPos(Step1);
	m_Spin3.SetPos(X1);
	m_Spin5.SetPos(X2);
	m_Spin10.SetPos(Y3);
	m_Spin12.SetPos(Y4);

	m_Spin7.SetPos(Count2);
	m_Spin8.SetPos(Step2);
	//m_Spin4.SetPos(Y1);
	m_Spin6.SetPos(Y2);
	m_Spin9.SetPos(X3);
	m_Spin11.SetPos(X4);

	if (FlagColor){
		unsigned char R = RGB[0];
		unsigned char G = RGB[1];
		unsigned char B = RGB[2];		

		//проверяем, что введенные значения не превысили размерностей изображения
		if (X1 < 0) X1 = 0;
		if (X2 < 0) X2 = 0;
		if (X3 < 0) X3 = 0;
		if (X4 < 0) X4 = 0;
		if (Y1 < 0) Y1 = 0;
		if (Y2 < 0) Y2 = 0;
		if (Y3 < 0) Y3 = 0;
		if (Y4 < 0) Y4 = 0;


		if (X2 < X1) 	{int buf = X1; X1 = X2; X2 = buf;}
		if (X2 > width) X2 = width;
		if (Y2 < Y1){ int buf = Y1;	Y1 = Y2; Y2 = buf; }
		if (Y2 > height) Y2 = height;
		if (X4 < X3) { int buf = X3; X3 = X4; X4 = buf; }
		if (X4 > width) X4 = width;
		if (Y4 < Y3){ int buf = Y3;	Y3 = Y4; Y4 = buf; }
		if (Y4 > height) Y4 = height;
		
		// переменная, корректирующая выход за рамки изображения при добавлении толщины к линии
		int borderCorrect = 0;
		int dataSize = 3 * width*height;

		for (int line = Count1; line > 0; --line)
		if (Y1 + (line-1)*Step1 + edge1 > height)
			Count1--;
		else		
			break;
			
		for (int line = Count2; line > 0; --line)
		if (X3 + (line-1)*Step2 + edge1 > width)
			Count2--;
		else		
			break;
		
		for (int t = edge1; t <= edge2; ++t){ // задаем толщину линии
			if (m_bChk1 == TRUE)
			{
				for (int line = 0; line < Count1; ++line) // рисуем заданное кол-во линий
				{
					for (int i = 3 * X1; i < X2 * 3; i += 3)
					{		
						// удостоверимся, что добавление ширины к линии не выводит нас за рамки изображения
						if ((line == 0 || Y1 + t + Step1*line < 0) && (Y1 + t < 0 || Y1 + t > height))	borderCorrect = -t; else borderCorrect = 0;
						int index = width * 3 * (Y1 + t + borderCorrect + Step1*line) + i + 2;
						if (index < dataSize)
						{						
							data[index-2] = B;
							data[index-1] = G;
							data[index] = R;
						}
						else
						{
							SetVariable("GRID_ERROR", "Out of array bounds");
							break;
						}
					}				
				}
			}
			
			if (m_bChk2 == TRUE){
				for (int line = 0; line < Count2; ++line)
					for (int i = 3 * Y3 * width; i < Y4 * 3 * width; i += 3 * width)
					{
						if ((line == 0 || t + Step2*line + X3 < 0) && (X3 + t < 0 || X3 + t > width))  borderCorrect = -t; else borderCorrect = 0;
						int index = i + 2 + 3 * (t + borderCorrect + Step2*line + X3);
						if (t + borderCorrect + Step2*line + X3 < width)
							if (index < 3 * width*height)
							{
								data[index - 2] = B;
								data[index - 1] = G;
								data[index] = R;
							}
							else
								SetVariable("GRID ERROR", "Out of array bounds");
				}
			}
		}
	}

	
  return 1;
}

// The annotation call. This is called after all processing routines are done to annotate the image .. i.e. draw lines, circles, etc.
// data - contains the current image data as BGR pixels
// tmp2Image - a temporary short int buffer than can be used for storage during image processing
// tmpImage - a temporary char buffer than can be used for storage during image processing
void GridDlg::Annotate(unsigned char *data, short int *tmp2Image, unsigned char *tmpImage, int left, int top, int width, int height)
{		

}

// returns the IDD for this module. This is needed so that RoboRealm can correctly display the
// GUI dialog.
int GridDlg::GetIDD()
{	
	return IDD_GRID;
}

// Saves the current configuration values for this module. Note that you need to save all values every time
// in order for RoboRealm to correctly update the values. This is called when the RoboRealm needs to save
// your configuration information into a robofile.
void GridDlg::SaveValues()
{
  // get current values from GUI
	UpdateData(TRUE);
	
	// reset state table to empty
	ResetState();

  // save the current variables to the state table
	SetString("strX1", &strX1);
	SetString("strX2", &strX2);
	SetString("strX3", &strX3);
	SetString("strX4", &strX4);
	SetString("strY1", &strY1);
	SetString("strY2", &strY2);
	SetString("strY3", &strY3);
	SetString("strY4", &strY4);
	SetString("strCount1", &strCount1);
	SetString("strCount2", &strCount2);
	SetString("strStep1", &strStep1);
	SetString("strStep2", &strStep2);
	SetInt("color", color);
	SetInt("thikness", thikness);
	SetBool("m_bChk1", m_bChk1);
	SetBool("m_bChk2", m_bChk2);
}

// Loads the configuration values back into your module.
void GridDlg::LoadValues()
{		
	// update values from GUI variables to GUI interface
    
	
	strX1 = GetString("strX1");
	strX2 = GetString("strX2");
	strX3 = GetString("strX3");
	strX4 = GetString("strX4");
	strY1 = GetString("strY1");
	strY2 = GetString("strY2");
	strY3 = GetString("strY3");
	strY4 = GetString("strY4");
	strCount1 = GetString("strCount1");
	strCount2 = GetString("strCount2");
	strStep1 = GetString("strStep1");
	strStep2 = GetString("strStep2");
	m_bChk1 = GetBool("m_bChk1");
	m_bChk2 = GetBool("m_bChk2");
	m_Check2.SetCheck(m_bChk2);
	m_Check1.SetCheck(m_bChk1);

	color = GetInt("color", color);
	m_ComboBoxColor.SetCurSel(color);

	thikness = GetInt("thikness", thikness);
	m_ComboBoxThikness.SetCurSel(thikness);

	UpdateData(FALSE);	
}

// Specify a url that describes more about your module
void GridDlg::OnHelp()
{
  ModuleDlg::OnHelp("http://www.roborealm.com/help/DLL_Program.php");
}



bool GridDlg::ColorChoise(int color, unsigned char* RGB)
{	
	switch (color){
	case 1:		
		break;
	case 2:
		RGB[0] = 255;
		RGB[1] = 255;
		RGB[2] = 255;		
		break;
	case 3:
		RGB[1] = 255;
		break;
	case 4:
		RGB[2] = 255;
		break;
	case 5:
		RGB[0] = 255;		
		break;
	default:
		return false;
		break;
	}
	return true;
}

void GridDlg::OnBnClickedCheck1()
{
	// TODO: добавьте свой код обработчика уведомлений
	if (m_Check1.GetCheck())
		m_bChk1 = true;
	else
		m_bChk1 = false;
	m_Check1.SetCheck(m_bChk1);
	UpdateData(TRUE);
}

void GridDlg::OnBnClickedCheck2()
{
	// TODO: добавьте свой код обработчика уведомлений
	if (m_Check2.GetCheck())
		m_bChk2 = true;
	else
		m_bChk2 = false;	
	m_Check2.SetCheck(m_bChk2);
	UpdateData(TRUE);
}

void GridDlg::OnEnChangeY1()
{
	// TODO:  Если это элемент управления RICHEDIT, то элемент управления не будет
	// send this notification unless you override the ModuleDlg::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	UpdateData(TRUE);
	// TODO:  Добавьте код элемента управления
}

void GridDlg::OnEnChangeC1()
{
	UpdateData(TRUE);
	// TODO:  Добавьте код элемента управления
}

void GridDlg::OnEnChangeS1()
{
	UpdateData(TRUE);
	// TODO:  Добавьте код элемента управления
}

void GridDlg::OnEnChangeX1()
{
	UpdateData(TRUE);
	// TODO:  Добавьте код элемента управления
}


void GridDlg::OnEnChangeX2()
{
	UpdateData(TRUE);
	// TODO:  Добавьте код элемента управления
}


void GridDlg::OnEnChangeC2()
{	
	UpdateData(TRUE);
	// TODO:  Добавьте код элемента управления
}

void GridDlg::OnEnChangeS2()
{
	UpdateData(TRUE);
	// TODO:  Добавьте код элемента управления
}


void GridDlg::OnEnChangeX3()
{
	UpdateData(TRUE);
	// TODO:  Добавьте код элемента управления
}


void GridDlg::OnEnChangeY3()
{
	UpdateData(TRUE);
	// TODO:  Добавьте код элемента управления
}


void GridDlg::OnEnChangeX4()
{
	UpdateData(TRUE);
	// TODO:  Добавьте код элемента управления
}


void GridDlg::OnEnChangeY4()
{
	UpdateData(TRUE);
	// TODO:  Добавьте код элемента управления
}

void GridDlg::OnCbnSelendokColor()
{
	color = m_ComboBoxColor.GetCurSel();
	m_ComboBoxColor.SetCurSel(color);
	UpdateData(TRUE);

	// TODO: добавьте свой код обработчика уведомлений
}

void GridDlg::OnCbnSelendokThikness()
{
	thikness = m_ComboBoxThikness.GetCurSel();
	m_ComboBoxThikness.SetCurSel(thikness);
	UpdateData(TRUE);
	// TODO: добавьте свой код обработчика уведомлений
}


void GridDlg::OnDeltaposSpin4(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO: добавьте свой код обработчика уведомлений
	
	*pResult = 0;
}
