/////////////////////////////////////////////////////////////////////////////
// Name:            mainframemenutools.cpp
// Purpose:         Event handlers for the Tools menu
// Author:          Brad Larsen
// Modified by:     
// Created:         Jan 9, 2005
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "mainframe.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void MainFrame::OnToolsMergeScores(wxCommandEvent& event)
{
    // Menu Tools -> Merge Scores
    //------Last Checked------//
    // - Jan 27, 2005
    wxMessageBox(wxT("TODO: Add a dialog interface to merge guitar and bass scores from different files. (see the PowerTabDocument::Mergexxx functions)"));
}
