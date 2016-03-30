/*
* hworld.cpp
* Hello world sample by Robert Roebling
*/

#include <wx/wx.h> 
#include <wx/filedlg.h>

#include "sciter-control.h" 

class MyApp: public wxApp
{
  virtual bool OnInit();
};


class MyFrame: public wxFrame
{
  wxSciterControl* m_sciter;
public:

  MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);

  void OnQuit(wxCommandEvent& event);
  void OnAbout(wxCommandEvent& event);
  void OnOpen(wxCommandEvent& event);

  DECLARE_EVENT_TABLE()
};

enum
{
  ID_Quit = 1,
  ID_About,
  ID_Open,
};

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
  EVT_MENU(ID_Quit, MyFrame::OnQuit)
  EVT_MENU(ID_About, MyFrame::OnAbout)
  EVT_MENU(ID_Open, MyFrame::OnOpen)
END_EVENT_TABLE();

IMPLEMENT_APP(MyApp);

bool MyApp::OnInit()
{
  SciterClassName();
  MyFrame *frame = new MyFrame( "Hello World", wxPoint(50,50), wxSize(600,550) );
  frame->Show(TRUE);
  SetTopWindow(frame);
  return TRUE;
} 

MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
  : wxFrame((wxFrame *)NULL, -1, title, pos, size)
  , m_sciter()
{
  wxMenu *menuFile = new wxMenu;
  menuFile->Append( ID_Open, "&Open...", "Load html to sciter window." );
  menuFile->Append( ID_About, "&About..." );
  menuFile->AppendSeparator();
  menuFile->Append( ID_Quit, "E&xit", "Quit application." );

  wxMenuBar *menuBar = new wxMenuBar;
  menuBar->Append( menuFile, "&File" );

  SetMenuBar( menuBar );

  //wxFontSelectorCtrl* ctl = new wxFontSelectorCtrl(this, this->NewControlId());
  m_sciter = new wxSciterControl(this, this->NewControlId());
  m_sciter->load_file(L"http://httpbin.org/html");

  CreateStatusBar();
  SetStatusText( "Welcome to wxWindows!" );
}


void MyFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
  Close(TRUE);
}

void MyFrame::OnAbout(wxCommandEvent& WXUNUSED(event))
{
  wxMessageBox("This is a wxWindows Hello world sample", "About Hello World", wxOK | wxICON_INFORMATION, this);
}

void MyFrame::OnOpen(wxCommandEvent& event)
{
  wxFileDialog dlg(this);
  dlg.SetWildcard("HTML files|*.htm;*.html|All files|*.*");
  if(dlg.ShowModal() == wxID_CANCEL)
    return;

  const wxString path = "file:///" + dlg.GetPath();
  m_sciter->load_file(path.ToStdWstring().c_str());
}
