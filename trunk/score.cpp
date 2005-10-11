/////////////////////////////////////////////////////////////////////////////
// Name:            score.cpp
// Purpose:         Stores and renders a score
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 16, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#include "stdwx.h"
#include "score.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/// Default Constructor
Score::Score()
{
    //------Last Checked------//
    // - Jan 5, 2005
}

/// Copy Constructor
Score::Score(const Score& score)
{
    //------Last Checked------//
    // - Jan 5, 2005
    *this = score;
}

/// Destructor
Score::~Score()
{
    //------Last Checked------//
    // - Jan 5, 2005
    m_guitarArray.DeleteContents();
    m_chordDiagramArray.DeleteContents();
    m_floatingTextArray.DeleteContents();
    m_guitarInArray.DeleteContents();
    m_tempoMarkerArray.DeleteContents();
    m_dynamicArray.DeleteContents();
    m_alternateEndingArray.DeleteContents();
    m_systemArray.DeleteContents();    
}

// Operators
/// Assignment Operator
const Score& Score::operator=(const Score& score)
{
    //------Last Checked------//
    // - Jan 5, 2005
    
    // Check for assignment to self
    if (this != &score)
    {
        m_guitarArray.Copy(score.m_guitarArray);
        m_chordDiagramArray.Copy(score.m_chordDiagramArray);
        m_floatingTextArray.Copy(score.m_floatingTextArray);
        m_guitarInArray.Copy(score.m_guitarInArray);
        m_tempoMarkerArray.Copy(score.m_tempoMarkerArray);
        m_dynamicArray.Copy(score.m_dynamicArray);
        m_alternateEndingArray.Copy(score.m_alternateEndingArray);
        m_systemArray.Copy(score.m_systemArray);
    }
    return (*this);
}

/// Equality Operator
bool Score::operator==(const Score& score) const
{
    //------Last Checked------//
    // - Jan 5, 2005
    return (
        (m_guitarArray.Equals(score.m_guitarArray)) &&
        (m_chordDiagramArray.Equals(score.m_chordDiagramArray)) &&
        (m_floatingTextArray.Equals(score.m_floatingTextArray)) &&
        (m_guitarInArray.Equals(score.m_guitarInArray)) &&
        (m_tempoMarkerArray.Equals(score.m_tempoMarkerArray)) &&
        (m_dynamicArray.Equals(score.m_dynamicArray)) &&
        (m_alternateEndingArray.Equals(score.m_alternateEndingArray)) &&
        (m_systemArray.Equals(score.m_systemArray))
    );
}

/// Inequality Operator
bool Score::operator!=(const Score& score) const
{
    //------Last Checked------//
    // - Jan 5, 2005
    return (!operator==(score));
}
    
// Serialization Functions
/// Performs serialization for the class
/// @param stream Power Tab output stream to serialize to
/// @return True if the object was serialized, false if not
bool Score::DoSerialize(PowerTabOutputStream& stream)
{
    //------Last Checked------//
    // - Jan 5, 2005
    m_guitarArray.Serialize(stream);
    wxCHECK(stream.CheckState(), false);

    m_chordDiagramArray.Serialize(stream);
    wxCHECK(stream.CheckState(), false);
    
    m_floatingTextArray.Serialize(stream);
    wxCHECK(stream.CheckState(), false);
    
    m_guitarInArray.Serialize(stream);
    wxCHECK(stream.CheckState(), false);
    
    m_tempoMarkerArray.Serialize(stream);
    wxCHECK(stream.CheckState(), false);
    
    m_dynamicArray.Serialize(stream);
    wxCHECK(stream.CheckState(), false);
    
    m_alternateEndingArray.Serialize(stream);
    wxCHECK(stream.CheckState(), false);
    
    m_systemArray.Serialize(stream);
    wxCHECK(stream.CheckState(), false);

    return (stream.CheckState());
}

/// Performs deserialization for the class
/// @param stream Power Tab input stream to load from
/// @param version File version
/// @return True if the object was deserialized, false if not
bool Score::DoDeserialize(PowerTabInputStream& stream, wxWord version)
{
    //------Last Checked------//
    // - Jan 5, 2005
    m_guitarArray.Deserialize(stream, version);
    wxCHECK(stream.CheckState(), false);

    m_chordDiagramArray.Deserialize(stream, version);
    wxCHECK(stream.CheckState(), false);
    
    m_floatingTextArray.Deserialize(stream, version);
    wxCHECK(stream.CheckState(), false);
    
    m_guitarInArray.Deserialize(stream, version);
    wxCHECK(stream.CheckState(), false);
    
    m_tempoMarkerArray.Deserialize(stream, version);
    wxCHECK(stream.CheckState(), false);
    
    m_dynamicArray.Deserialize(stream, version);
    wxCHECK(stream.CheckState(), false);
    
    m_alternateEndingArray.Deserialize(stream, version);
    wxCHECK(stream.CheckState(), false);
    
    m_systemArray.Deserialize(stream, version);
    wxCHECK(stream.CheckState(), false);
        
    return (stream.CheckState());
}
