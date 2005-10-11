/////////////////////////////////////////////////////////////////////////////
// Name:            mainframemenutest.cpp
// Purpose:         Event handlers for the Test menu
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 31, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "mainframe.h"

#include "globaltestsuite.h"
#include "powertabdocumenttestsuite.h"
#include "fontsettingtestsuite.h"
#include "scoretestsuite.h"
#include "alternateendingtestsuite.h"
#include "barlinetestsuite.h"
#include "chordtexttestsuite.h"
#include "chordnametestsuite.h"
#include "chorddiagramtestsuite.h"
#include "directiontestsuite.h"
#include "systemsymboltestsuite.h"
#include "powertabfileheadertestsuite.h"
#include "floatingtexttestsuite.h"
#include "guitartestsuite.h"
#include "guitarintestsuite.h"
#include "tuningtestsuite.h"
#include "systemtestsuite.h"
#include "rhythmslashtestsuite.h"
#include "stafftestsuite.h"
#include "positiontestsuite.h"
#include "notetestsuite.h"
#include "chordtexttestsuite.h"
#include "dynamictestsuite.h"
#include "keysignaturetestsuite.h"
#include "timesignaturetestsuite.h"
#include "tempomarkertestsuite.h"
#include "rehearsalsigntestsuite.h"
#include "generalmiditestsuite.h"
#include "powertabobjecttestsuite.h"
#include "oldrehearsalsigntestsuite.h"
#include "oldtimesignaturetestsuite.h"
#include "powertabdocument.h"
#include <wx/dir.h>
#include <wx/dirdlg.h>
#include <wx/mstream.h>
#include <wx/progdlg.h>
#include <wx/textfile.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void MainFrame::OnTestTestingFramework(wxCommandEvent& event)
{    
    // Menu Test -> Testing Framework
    //------Last Checked------//
    // - Jan 3, 2005
    WXUNUSED(event);
    
    // TODO: Add any future test suites here
    TestingFramework* testingFramework = new TestingFramework;
    testingFramework->AddTestSuite(new AlternateEndingTestSuite);
    testingFramework->AddTestSuite(new BarlineTestSuite);
    testingFramework->AddTestSuite(new ChordDiagramTestSuite);
    testingFramework->AddTestSuite(new ChordNameTestSuite);
    testingFramework->AddTestSuite(new ChordTextTestSuite);
    testingFramework->AddTestSuite(new DirectionTestSuite);
    testingFramework->AddTestSuite(new DynamicTestSuite);
    testingFramework->AddTestSuite(new FloatingTextTestSuite);
    testingFramework->AddTestSuite(new FontSettingTestSuite);
    testingFramework->AddTestSuite(new GeneralMidiTestSuite);
    testingFramework->AddTestSuite(new GlobalTestSuite);
    testingFramework->AddTestSuite(new GuitarInTestSuite);
    testingFramework->AddTestSuite(new GuitarTestSuite);
    testingFramework->AddTestSuite(new KeySignatureTestSuite);
    testingFramework->AddTestSuite(new NoteTestSuite);
    testingFramework->AddTestSuite(new OldRehearsalSignTestSuite);
    testingFramework->AddTestSuite(new OldTimeSignatureTestSuite);
    testingFramework->AddTestSuite(new PositionTestSuite);
    testingFramework->AddTestSuite(new PowerTabDocumentTestSuite);
    testingFramework->AddTestSuite(new PowerTabFileHeaderTestSuite);
    testingFramework->AddTestSuite(new PowerTabObjectTestSuite);
    testingFramework->AddTestSuite(new RehearsalSignTestSuite);
    testingFramework->AddTestSuite(new RhythmSlashTestSuite);
    testingFramework->AddTestSuite(new ScoreTestSuite);
    testingFramework->AddTestSuite(new StaffTestSuite);
    testingFramework->AddTestSuite(new SystemSymbolTestSuite);
    testingFramework->AddTestSuite(new SystemTestSuite);
    testingFramework->AddTestSuite(new TempoMarkerTestSuite);
    testingFramework->AddTestSuite(new TimeSignatureTestSuite);
    testingFramework->AddTestSuite(new TuningTestSuite);
        
    testingFramework->SortTestSuitesByName();
    
    TestingFrameworkDialog dlg;
    dlg.SetTestingFramework(testingFramework);
    
    // Center craps on Linux
#ifdef __WXMSW__
    dlg.Center();
#endif

    dlg.ShowModal();
}

void MainFrame::OnTestBatchFileSerialization(wxCommandEvent& event)
{    
    // Menu Test -> Batch File Serialization
    //------Last Checked------//
    // - Dec 31, 2004
    WXUNUSED(event);
    
    // Display critical warning!!!
    if (wxMessageBox(wxT("CRITICAL WARNING: Do NOT perform this test on your original Power Tab files. Make a copy of files, place them in a temporary folder, and perform the test on the copied files instead.\n\nProceed with the the test?"),
        wxT("Batch File Serialization Test"),
        wxYES_NO | wxICON_ERROR) == wxNO)
        return;
    
    // Notes: This function will load (individually) all .ptb files
    // in a folder (and its subfolders), to ensure deserialization
    // is working correctly.  If a file is the most recent file
    // format (v1.7), the file is saved to a memory stream, and
    // then compared with the original file to ensure serialization
    // is working correctly. If any errors occur, you will be prompted
    // to save the errors to a text file.
    
    wxArrayString errors;
    
    const wxString& dir = wxDirSelector(wxT("Select the folder where your Power Tab files (.ptb) reside, and then click OK."));
    if (!dir.empty())
    {
        const wxChar* errorMessageFormat = wxT("%s - [%s]");
        
        // Get all .ptb files in the folder and its subfolders
        // This can take some time if you have alot of files or a slow machine
        wxArrayString files;
        {
            wxProgressDialog progressDialog(wxT("Scanning for Files"), wxT("Please wait. Scanning folders for Power Tab files..."), 0, this, wxPD_AUTO_HIDE | wxPD_APP_MODAL);
        
            wxDir::GetAllFiles(dir, &files, wxT("*.ptb"));
            progressDialog.Show(false);
        }
       
        // Process each file
        size_t i = 0;
        size_t fileCount = files.GetCount();
        
        wxProgressDialog progressDialog(wxT("Batch File Serialization Test Progress"), wxT(""), fileCount, this, wxPD_AUTO_HIDE | wxPD_APP_MODAL | wxPD_CAN_ABORT | wxPD_ELAPSED_TIME | wxPD_ESTIMATED_TIME | wxPD_REMAINING_TIME);
        
        bool cancelled = false;  // If true, user pressed Cancel button
        
        for (; i < fileCount; i++)
        {
            wxFileName fileName(files[i]);
            
            // Update progress status
            if (!progressDialog.Update(i, wxString::Format(wxT("Testing file %d of %d\n%s..."), i + 1, fileCount, fileName.GetFullName().c_str())))
            {
                cancelled = true;
                break;
            }
            
            // Open the file
            wxFileInputStream stream(files[i]);
            if (stream.IsOk())
            {
                PowerTabInputStream input_stream(stream);
                
                // Load the file
                PowerTabDocument document;
                if (!document.Load(input_stream))
                {
                    errors.Add(wxString::Format(errorMessageFormat, files[i].c_str(), input_stream.GetLastErrorMessage().c_str()));
                    document.DeleteContents();
                    continue;
                }
                
                // If file version is the most current, we can perform a memory save test; if not, continue
                if (document.GetHeaderRef().GetVersion() != PowerTabFileHeader::FILEVERSION_CURRENT)
                {
                    document.DeleteContents();
                    continue;
                }
                
                // Save the document to memory
                wxMemoryOutputStream memory_stream;
                document.SaveObject(memory_stream);
                
                // Size should be the same
                if (stream.GetSize() != memory_stream.GetSize())
                {
                    errors.Add(wxString::Format(errorMessageFormat, files[i].c_str(), wxT("Memory Save Test failure")));
                    document.DeleteContents();
                    continue;
                }

                // Compare each byte in the file to each byte of the saved memory data
                wxStreamBuffer* streamBuffer = memory_stream.GetOutputStreamBuffer();
                if ((stream.GetSize() > 0) && (streamBuffer != NULL))
                {
                    // Set file position to start of file
                    stream.SeekI(0);
                
                    // Get a pointer to the memory stream buffer
                    wxUint8* ptr = (wxUint8*)streamBuffer->GetBufferStart();
                
                    // Get number of bytes left to read from the file
                    wxUint32 bytesLeft = stream.GetSize();
                    
                    while (bytesLeft > 0)
                    {
                        // Read a chunk of data from the file
                        const wxUint32 bufferSize = 4096;
                        wxUint8 buffer[bufferSize];
                        wxUint32 bytesRead = min(bytesLeft, bufferSize);
                        stream.Read(buffer, bufferSize);
                        
                        // Compare each byte in the chunk to the corresponding byte in the memory stream buffer
                        wxUint32 b = 0;
                        for (; b < bytesRead; b++)
                        {
                            if (buffer[b] != *ptr)
                            {
                                errors.Add(wxString::Format(errorMessageFormat, files[i].c_str(), wxT("Memory Save Test failure")));
                                document.DeleteContents();
                                // This line will force the while statement to fail
                                bytesRead = bytesLeft;
                                break;
                            }
                            ptr++;
                        }
                        bytesLeft -= bytesRead;
                    }
                }
                else
                    errors.Add(wxString::Format(errorMessageFormat, files[i].c_str(), wxT("Memory Save Test failure")));
                    
                document.DeleteContents();
            }
            else
                errors.Add(wxString::Format(errorMessageFormat, files[i].c_str(), wxT("Could not open file")));
            
            // Update progress
            if (!progressDialog.Update(i + 1))
            {
                cancelled = true;
                break;
            }
        }
        
        // User didn't cancel
        if (!cancelled)
        {
            wxString message = wxString::Format(wxT("Testing complete\n\nFiles tested: %d\nErrors: %d"), fileCount, errors.GetCount());
            int style = wxICON_INFORMATION;
            
            // Add text to allow user to save error messages
            if (errors.GetCount() > 0)
            {
                message += wxT("\n\nThere were errors that occurred during the testing process. Would you like to save them to file?");
                style |= wxYES_NO;
            }
            
            // Display results of test to user; If user clicks Yes, save errors to file
            if (wxMessageBox(message, wxT("Batch File Serialization Test"), style) == wxYES)
            {
                wxFileDialog fileDialog(this, wxT("Save Results"), wxT(""), wxT("results.txt"), wxT("Text files (*.txt)|*.txt"), wxSAVE | wxHIDE_READONLY | wxOVERWRITE_PROMPT);
                if (fileDialog.ShowModal() == wxID_OK)
                {
                    wxString pathName = fileDialog.GetPath();
                    
                    // Create a new file
                    wxTextFile file;
                    file.Create(pathName);
                    
                    // Write the errors
                    size_t e = 0;
                    size_t count = errors.GetCount();
                    for (; e < count; e++)
                        file.AddLine(errors[e]);
                        
                    file.Write();
                    file.Close();
                }
            }
        }
    }
}
