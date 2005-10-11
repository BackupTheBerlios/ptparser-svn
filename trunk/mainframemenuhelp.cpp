/////////////////////////////////////////////////////////////////////////////
// Name:            mainframemenuhelp.cpp
// Purpose:         Event handlers for the Help menu
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 31, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "mainframe.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void MainFrame::OnHelpAbout(wxCommandEvent& event)
{
    // Menu Help -> About
    //------Last Checked------//
    // - Dec 30, 2004
    WXUNUSED(event);
    
    wxString aboutCaption = wxString::Format(wxT("About %s"), wxTheApp->GetAppName().c_str());
    wxMessageBox(wxT("Power Tab Parser 1.0.0.0\nA wxWidgets application that can load and save Power Tab (.ptb) files.\n\nWritten by Brad Larsen\nCopyright (c) 2005 by Brad Larsen. All rights reserved."), aboutCaption, wxICON_INFORMATION);
}
