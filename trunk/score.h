/////////////////////////////////////////////////////////////////////////////
// Name:            score.h
// Purpose:         Stores and renders a score
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 16, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef __SCORE_H__
#define __SCORE_H__

#include "guitar.h"
#include "chorddiagram.h"
#include "floatingtext.h"
#include "guitarin.h"
#include "tempomarker.h"
#include "dynamic.h"
#include "alternateending.h"
#include "system.h"

/// Stores and renders a score
// Note: This is a class used to make life easier - it's not a class that exists in PTE v1.7
class Score : public PowerTabObject
{
friend class ScoreTestSuite;

public:
    GuitarArray                 m_guitarArray;              ///< Guitars used by the score
    ChordDiagramArray           m_chordDiagramArray;        ///< Chord diagrams used in the score
    FloatingTextArray           m_floatingTextArray;        ///< Floating text used in the score
    GuitarInArray               m_guitarInArray;            ///< Guitar Ins used in the score
    TempoMarkerArray            m_tempoMarkerArray;         ///< Tempo Markers used in the score
    DynamicArray                m_dynamicArray;             ///< Dynamic markers used in the score
    AlternateEndingArray        m_alternateEndingArray;     ///< Alternate endings used in the score
    SystemArray                 m_systemArray;              ///< Systems used in the score
    
public:
    // Constructor/Destructor
    Score();
    Score(const Score& score);
    ~Score();
    
    // Creation Functions
    /// Creates an exact duplicate of the object
    /// @return The duplicate object
    PowerTabObject* CloneObject() const                     
        {return (new Score(*this));}
    
    // Operators
    const Score& operator=(const Score& score);
    bool operator==(const Score& score) const;
    bool operator!=(const Score& score) const;
    
    // Serialization Functions
protected:
    bool DoSerialize(PowerTabOutputStream& stream);
    bool DoDeserialize(PowerTabInputStream& stream, wxWord version);

public:   
    // Guitar Functions
    /// Determines if a guitar index is valid
    /// @param index guitar index to validate
    /// @return True if the guitar index is valid, false if not
    bool IsValidGuitarIndex(wxUint32 index) const
        {return (index < GetGuitarCount());}
    /// Gets the number of guitars in the score
    /// @return The number of guitars in the score
    size_t GetGuitarCount() const
        {return (m_guitarArray.GetCount());}
    /// Gets the nth guitar in the score
    /// @param index Index of the guitar to get
    /// @return The nth guitar in the score
    Guitar* GetGuitar(wxUint32 index) const
        {wxCHECK(IsValidGuitarIndex(index), NULL); return (m_guitarArray[index]);}
    
    // Chord Diagram Functions
    /// Determines if a guitar index is valid
    /// @param index ChordDiagram index to validate
    /// @return True if the guitar index is valid, false if not
    bool IsValidChordDiagramIndex(wxUint32 index) const
        {return (index < GetChordDiagramCount());}
    /// Gets the number of guitars in the score
    /// @return The number of guitars in the score
    size_t GetChordDiagramCount() const                         
        {return (m_chordDiagramArray.GetCount());}
    /// Gets the nth guitar in the score
    /// @param index Index of the guitar to get
    /// @return The nth guitar in the score
    ChordDiagram* GetChordDiagram(wxUint32 index) const         
        {wxCHECK(IsValidChordDiagramIndex(index), NULL); return (m_chordDiagramArray[index]);}
    
    // Floating Text Functions
    /// Determines if a floating text index is valid
    /// @param index floating text index to validate
    /// @return True if the floating text index is valid, false if not
    bool IsValidFloatingTextIndex(wxUint32 index) const         
        {return (index < GetFloatingTextCount());}
    /// Gets the number of floating text items in the score
    /// @return The number of floating text items in the score
    size_t GetFloatingTextCount() const                         
        {return (m_floatingTextArray.GetCount());}
    /// Gets the nth floating text in the score
    /// @param index Index of the floating text to get
    /// @return The nth floating text in the score
    FloatingText* GetFloatingText(wxUint32 index) const         
        {wxCHECK(IsValidFloatingTextIndex(index), NULL); return (m_floatingTextArray[index]);}
    
    // Guitar In Functions
    /// Determines if a guitar in index is valid
    /// @param index guitar in index to validate
    /// @return True if the guitar in index is valid, false if not
    bool IsValidGuitarInIndex(wxUint32 index) const             
        {return (index < GetGuitarInCount());}
    /// Gets the number of guitar ins in the score
    /// @return The number of guitar ins in the score
    size_t GetGuitarInCount() const                             
        {return (m_guitarInArray.GetCount());}
    /// Gets the nth guitar in in the score
    /// @param index Index of the guitar in to get
    /// @return The nth guitar in in the score
    GuitarIn* GetGuitarIn(wxUint32 index) const                 
        {wxCHECK(IsValidGuitarInIndex(index), NULL); return (m_guitarInArray[index]);}
    
    // Tempo Marker Functions
    /// Determines if a tempo marker index is valid
    /// @param index tempo marker index to validate
    /// @return True if the tempo marker index is valid, false if not
    bool IsValidTempoMarkerIndex(wxUint32 index) const
        {return (index < GetTempoMarkerCount());}
    /// Gets the number of tempo markers in the score
    /// @return The number of tempo markers in the score
    size_t GetTempoMarkerCount() const
        {return (m_tempoMarkerArray.GetCount());}
    /// Gets the nth tempo marker in the score
    /// @param index Index of the tempo marker to get
    /// @return The nth tempo marker in the score
    TempoMarker* GetTempoMarker(wxUint32 index) const
        {wxCHECK(IsValidTempoMarkerIndex(index), NULL); return (m_tempoMarkerArray[index]);}
    
    // Dynamic Functions
    /// Determines if a dynamic index is valid
    /// @param index dynamic index to validate
    /// @return True if the dynamic index is valid, false if not
    bool IsValidDynamicIndex(wxUint32 index) const              
        {return (index < GetDynamicCount());}
    /// Gets the number of dynamics in the score
    /// @return The number of dynamics in the score
    size_t GetDynamicCount() const                              
        {return (m_dynamicArray.GetCount());}
    /// Gets the nth dynamic in the score
    /// @param index Index of the dynamic to get
    /// @return The nth dynamic in the score
    Dynamic* GetDynamic(wxUint32 index) const                   
        {wxCHECK(IsValidDynamicIndex(index), NULL); return (m_dynamicArray[index]);}
    
    // Alternate Ending Functions
    /// Determines if a alternate ending index is valid
    /// @param index alternate ending index to validate
    /// @return True if the alternate ending index is valid, false if not
    bool IsValidAlternateEndingIndex(wxUint32 index) const      
        {return (index < GetAlternateEndingCount());}
    /// Gets the number of alternate endings in the score
    /// @return The number of alternate endings in the score
    size_t GetAlternateEndingCount() const                              
        {return (m_alternateEndingArray.GetCount());}
    /// Gets the nth alternate ending in the score
    /// @param index Index of the alternate ending to get
    /// @return The nth alternate ending in the score
    AlternateEnding* GetAlternateEnding(wxUint32 index) const
        {wxCHECK(IsValidAlternateEndingIndex(index), NULL); return (m_alternateEndingArray[index]);}
    
    // System Functions
    /// Determines if a system index is valid
    /// @param index system index to validate
    /// @return True if the system index is valid, false if not
    bool IsValidSystemIndex(wxUint32 index) const               
        {return (index < GetSystemCount());}
    /// Gets the number of systems in the score
    /// @return The number of systems in the score
    size_t GetSystemCount() const                               
        {return (m_systemArray.GetCount());}
    /// Gets the nth system in the score
    /// @param index Index of the system to get
    /// @return The nth system in the score
    System* GetSystem(wxUint32 index) const                     
        {wxCHECK(IsValidSystemIndex(index), NULL); return (m_systemArray[index]);}
};

// Array declarations
// Note: Do not use WX_DEFINE_POWERTABARRAY here! It will cause incorrect file serialization
WX_DEFINE_ARRAY(Score*, ScoreArray);

#endif
