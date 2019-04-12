// SwapColorDlg.cpp : implementation file
// http://www.realcoding.net/article/rubric/CCplus/MFC?page=4 MFC

#include "stdafx.h"
#include "resource.h"
#include <vfw.h>
#include "NameValueBuffer.h"
#include "ModuleDlg.h"
#include "QueueDlg.h"
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

QueueDlg::QueueDlg(CWnd* pParent /*=NULL*/)
: ModuleDlg(QueueDlg::IDD, pParent)
{	
	m_MaxCapacity = 50;
	m_CurCapacity = 0;
	//{{AFX_DATA_INIT(QueueDlg)

	//}}AFX_DATA_INIT
}

void QueueDlg::DoDataExchange(CDataExchange* pDX)
{	
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(QueueDlg)
	
	//}}AFX_DATA_MAP

	DDX_Text(pDX, IDC_MAX_CAPACITY, m_MaxCapacity);
	DDV_MinMaxInt(pDX, m_MaxCapacity, 0, 1000);
	DDX_Text(pDX, IDC_CUR_CAPACITY, m_CurCapacity);
	DDV_MinMaxInt(pDX, m_CurCapacity, 0, 1000);
	DDX_Control(pDX, IDC_CUR_CAPACITY, m_ctrlCurCapacity);
}

BEGIN_MESSAGE_MAP(QueueDlg, CDialog)
	//{{AFX_MSG_MAP(QueueDlg)
	ON_BN_CLICKED(IDC_SHOW_HELP, OnHelp)	
	//}}AFX_MSG_MAP
	ON_CBN_SELCHANGE(IDC_COMBO1, &QueueDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDC_CLEAR, &QueueDlg::OnBnClickedClear)
	
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// QueueDlg message handlers

// Called on initialization of the dll
bool QueueDlg::Initialize()
{
  // tell RoboRealm that we have a GUI dialog
  hasDialog = true;
 
  CComboBox * comboBox = (CComboBox *)GetDlgItem(IDC_COMBO1);
  comboBox->AddString("QueueFlag");

  UpdateData(FALSE);
	return true;
}

void QueueDlg::Destroy()
{
	unsigned char * BufImage;
	// очищаем память, зантяую BufImage, при выходе из приложения
	while (QueueFrame.size() > 0)
	{
		BufImage = QueueFrame.front();
		QueueFrame.pop();
		delete[] BufImage;
	}		
}

// used to indentify this plugin
char *QueueDlg::GetName()
{
  return "Queue";
}

// when the ok button is pressed this is called and used to indicate in the RoboRealm program pipeline
// what this module is. You can use this routine to include basic indicators that help the end user
// know what operation is being performed.
char *QueueDlg::GetDisplay()
{
	// configure our module text display in the pipeline
	_snprintf(display, 256, "Queue %i", m_MaxCapacity);

  return display;
}

// The main image processing call.
// data - contains the current image data as BGR pixels
// tmp2Image - a temporary short int buffer than can be used for storage during image processing
// tmpImage - a temporary char buffer than can be used for storage during image processing
int QueueDlg::Process(unsigned char *data, short int *tmp2Image, unsigned char *tmpImage, int left, int top, int width, int height)
{  	
	//MessageBoxA("Process", "OK", 0);
	try
	{
		unsigned char * BufImage;
		char * Flag = GetVariable("QueueFlag");	
		m_CurCapacity = (int)QueueFrame.size();	
		SetVariable("QUEUE_OVERFLOW", 0);
	
		// Флаг QueueFlag не опущен, значит формируем очередь, 
		// до тех пор пока не превысим максимальный объем очереди
		if (Flag != NULL) {
			int QueueFlag = atoi(Flag);
			if (m_CurCapacity < m_MaxCapacity && QueueFlag != 0)
			{
				int len = width*height * 3;
				BufImage = new unsigned char[len];
				for (int i = 0; i < len; ++i)
				{
					BufImage[i] = data[i];
				}

				QueueFrame.push(BufImage);
			}
			// Если объем превышен, а флаг еще не опущен, то удаляем кадры из начала очереди
			// и ставим текущий кадр в конец очереди
			if (m_CurCapacity >= m_MaxCapacity && QueueFlag != 0) {
				SetVariable("QUEUE_OVERFLOW", 1);
				BufImage = QueueFrame.front();
				QueueFrame.pop();
				delete[] BufImage;
				int len = width*height * 3;
				BufImage = new unsigned char[len];
				for (int i = 0; i < len; ++i)
				{
					BufImage[i] = data[i];
				}
				QueueFrame.push(BufImage);
			}
			// Если флаг опущен и в очереди есть фреймы, то выводим их на экран 
			if (m_CurCapacity > 0 && QueueFlag == 0)
			{
				BufImage = QueueFrame.front();
				QueueFrame.pop();				

				int len = width*height * 3;				

				for (int i = 0; i < len; ++i)
				{
					data[i] = BufImage[i];
				}

				delete[] BufImage;	
			}
			SetVariable("QUEUE_CURRENT_CAPACITY", (int)QueueFrame.size());
		}
		else
		{
			SetVariable("QUEUE_ERROR", "Variable QueueFlag does not exist");
		}

		//SetVariable("Q_m_CurCapacity", m_CurCapacity);		
		//if (QueueFrame.size() != m_CurCapacity)
		//{
		//		MessageBoxA("Not equal", "OK", 0);
		//		UpdateData(FALSE);
		//}
		/*m_ctrlCurCapacity.SetWindowText((LPCTSTR)m_CurCapacity);
		m_ctrlCurCapacity.UpdateData(FALSE);
		*/
	

		//Resize the current image that is passed back to RoboRealm. Note data is preserved but not
		//realigned to new size. Note that tmp2Image and tmpImage may also be reallocated but will
		//NOT be preserved.
		//Resize(400,400,&data, &tmp2Image, &tmpImage);
	}
	catch (...) {
		MessageBoxA("Something wrong", "Error", 0);
	}
  return 1;
}

// The annotation call. This is called after all processing routines are done to annotate the image .. i.e. draw lines, circles, etc.
// data - contains the current image data as BGR pixels
// tmp2Image - a temporary short int buffer than can be used for storage during image processing
// tmpImage - a temporary char buffer than can be used for storage during image processing
void QueueDlg::Annotate(unsigned char *data, short int *tmp2Image, unsigned char *tmpImage, int left, int top, int width, int height)
{		

}

// returns the IDD for this module. This is needed so that RoboRealm can correctly display the
// GUI dialog.
int QueueDlg::GetIDD()
{
  return IDD_QUEUE;
}

// Saves the current configuration values for this module. Note that you need to save all values every time
// in order for RoboRealm to correctly update the values. This is called when the RoboRealm needs to save
// your configuration information into a robofile.
void QueueDlg::SaveValues()
{
  // get current values from GUI
	UpdateData(TRUE);

	// reset state table to empty
	ResetState();

  // save the current text string to the state table
	SetInt("MaxCapacity", m_MaxCapacity);
	
}

// Loads the configuration values back into your module.
void QueueDlg::LoadValues()
{
	m_MaxCapacity = GetInt("MaxCapacity");

	// update values from GUI variables to GUI interface
    UpdateData(FALSE);		
}

// Specify a url that describes more about your module
void QueueDlg::OnHelp()
{
  ModuleDlg::OnHelp("http://www.roborealm.com/help/DLL_Program.php");
}



void QueueDlg::OnCbnSelchangeCombo1()
{
	
	// TODO: добавьте свой код обработчика уведомлений
}


void QueueDlg::OnBnClickedClear()
{
	// TODO: добавьте свой код обработчика уведомлений
	unsigned char * BufImage;
	while (QueueFrame.size() > 0)
	{
		BufImage = QueueFrame.front();
		QueueFrame.pop();
		delete[] BufImage;
	}
	SetVariable("QUEUE_CURRENT_CAPACITY", (int)QueueFrame.size());
	
	UpdateData(TRUE);
}


