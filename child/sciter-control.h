#pragma once

#include <wx/control.h>
#include <sciter-x-window.hpp>

class wxSciterControl: 
  public wxControl,
  public sciter::host<wxSciterControl>,
  protected sciter::event_handler
{
  friend struct sciter::host<wxSciterControl>;
  DECLARE_EVENT_TABLE();
  DECLARE_DYNAMIC_CLASS(wxSciterControl);
public:

  // Constructors
  wxSciterControl();
  wxSciterControl(wxWindow* parent, wxWindowID id);
  ~wxSciterControl();

  // Creation
  bool Create(wxWindow* parent, wxWindowID id, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize,
    long style = wxSUNKEN_BORDER, const wxValidator& validator = wxDefaultValidator);

public:
  sciter::dom::element get_root() const;
  
protected:
  // Common initialization
  void Init();

  // Overrides
  wxSize DoGetBestSize() const;

  // Event handlers
  void OnSize(wxSizeEvent& evt);
  void OnShow(wxShowEvent& evt);

  // sciter:host
  HWINDOW get_hwnd() const { return m_hwnd; }
  HINSTANCE get_resource_instance() const { return NULL; }
  
protected:
  HWINDOW m_hwnd;
  mutable sciter::dom::element m_root;
};
