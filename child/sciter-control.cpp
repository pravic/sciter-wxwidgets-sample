#include <wx/wx.h>
#include <wx/control.h>
#include <wx/gdicmn.h>

#include "sciter-control.h"
#include <sciter-x-debug.h>

BEGIN_EVENT_TABLE(wxSciterControl, wxControl)
  EVT_SIZE(wxSciterControl::OnSize)
  EVT_SHOW(wxSciterControl::OnShow)
END_EVENT_TABLE();

IMPLEMENT_DYNAMIC_CLASS(wxSciterControl, wxControl);

wxSciterControl::wxSciterControl(wxWindow* parent, wxWindowID id)
  :m_hwnd()
{
  Init();
  Create(parent, id);
}

wxSciterControl::wxSciterControl()
  :m_hwnd()
{
  Init();
}

wxSciterControl::~wxSciterControl()
{
#ifdef __WINDOWS__
  ::DestroyWindow(m_hwnd);
#endif
}

bool wxSciterControl::Create(wxWindow* parent, wxWindowID id, const wxPoint& pos /*= wxDefaultPosition*/, const wxSize& size /*= wxDefaultSize*/, long style /*= wxSUNKEN_BORDER*/, const wxValidator& validator /*= wxDefaultValidator*/)
{
  if (!wxControl::Create(parent, id, pos, size, style, validator))
    return false;

  SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_WINDOW));
  SetInitialSize(size);

  // Create Sciter child window with size exactly as our control.
  const auto crc = this->GetClientRect();
  RECT rc = {crc.GetLeft(), crc.GetTop(), crc.GetRight(), crc.GetBottom()};
  m_hwnd = SciterCreateWindow(SW_CHILD, &rc, nullptr, nullptr, this->GetHandle());

  if(m_hwnd) {
    static volatile sciter::debug_output setup_dbg;

    // Setup sciter callbacks
    setup_callback();
    sciter::attach_dom_event_handler(m_hwnd, this);

    // Adjust our window style to eliminate double edge 
    if(this->HasFlag(wxBORDER_MASK)) {
      auto style = this->GetWindowStyleFlag();
      style &= ~wxBORDER_MASK;
      style |= wxBORDER_NONE;
      this->SetWindowStyleFlag(style);
    }

    // Show Sciter window
#ifdef __WINDOWS__
    ::ShowWindow(m_hwnd, this->IsShown() ? SW_SHOW : SW_HIDE);
#endif

    this->Refresh();
  }
  return true;
}

void wxSciterControl::Init()
{

}

wxSize wxSciterControl::DoGetBestSize() const
{
  return this->GetClientSize();
}

void wxSciterControl::OnSize(wxSizeEvent& evt)
{
  wxRect rc = this->GetClientRect();
  rc.SetSize(evt.GetSize());
#ifdef __WINDOWS__
  SetWindowPos(m_hwnd, nullptr, rc.GetX(), rc.GetY(), rc.GetWidth(), rc.GetHeight(), SWP_NOZORDER);
#endif
}

void wxSciterControl::OnShow(wxShowEvent& evt)
{
#ifdef __WINDOWS__
  ShowWindow(m_hwnd, evt.IsShown() ? SW_SHOW : SW_HIDE);
#endif
}

sciter::dom::element wxSciterControl::get_root() const
{
  if(!m_root) {
    m_root = __super::get_root();
  }
  return m_root;
}
