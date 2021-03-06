/////////////////////////////////////////////////////////////////////////////
// Name:            fontsetting.h
// Purpose:         Stores information about a font format (facename, point size, weight, style, etc.)
// Author:          Brad Larsen
// Modified by:     
// Created:         Dec 5, 2004
// RCS-ID:          
// Copyright:       (c) Brad Larsen
// License:         wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifndef __FONTSETTING_H__
#define __FONTSETTING_H__

/// Stores information about a font format (facename, point size, weight, style, etc.)
class FontSetting : public PowerTabObject
{
friend class FontSettingTestSuite;

// Constants
public:
    // Default constants
    static const wxChar*        DEFAULT_FACENAME;               ///< Default value for the face name member variable
    static const wxInt32        DEFAULT_POINTSIZE;              ///< Defualt value for the point size member variable
    static const wxInt32        DEFAULT_WEIGHT;                 ///< Defualt value for the weight member variable
    static const bool           DEFAULT_ITALIC;                 ///< Default value for the italic member variable
    static const bool           DEFAULT_UNDERLINE;              ///< Default value for the underline member variable
    static const bool           DEFAULT_STRIKEOUT;              ///< Default value for the strikeout member variable
    static const wxColor        DEFAULT_COLOR;                  ///< Default value for the color member variable

    // Point Size constants
    static const wxInt32        MIN_POINTSIZE;                  ///< Minimum allowed value for the point size member variable
    static const wxInt32        MAX_POINTSIZE;                  ///< Maximum allowed value for the point size member variable
    
    // Font weight constants
    enum weightConstants
    {
        weightDontCare          = 0,
        weightThin              = 100,
        weightExtraLight        = 200,
        weightUltraLight        = 200,
        weightLight             = 300,
        weightNormal            = 400,
        weightRegular           = 400,
        weightMedium            = 500,
        weightSemiBold          = 600,
        weightDemiBold          = 600,
        weightBold              = 700,
        weightExtraBold         = 800,
        weightUltraBold         = 800,
        weightBlack             = 900,
        weightHeavy             = 900
    };

// Member Variables
protected:
    wxString    m_faceName;         ///< Face name of the font; i.e. Arial, Times New Roman, etc.
    wxInt32     m_pointSize;        ///< Height of the font, in points
    wxInt32     m_weight;           ///< Font weight (see enum for values)
    wxByte      m_italic;           ///< Determines whether or not the font uses italics
    wxByte      m_underline;        ///< Determines whether or not the font is underlined
    wxByte      m_strikeOut;        ///< Determines whether or not the font is struck out
    wxColor     m_color;            ///< Color of the font

public:
    // Constructor/Destructor
    FontSetting();
    FontSetting(const wxChar* faceName, wxInt32 pointSize, wxInt32 weight, bool italic, bool underline, bool strikeOut, wxColor color);
    FontSetting(const FontSetting& fontSetting);
    ~FontSetting();

    // Creation Functions
    /// Creates an exact duplicate of the object
    /// @return The duplicate object
    PowerTabObject* CloneObject() const                         
        {return (new FontSetting(*this));}
    
    // Operators
    const FontSetting& operator=(const FontSetting& fontSetting);
    bool operator==(const FontSetting& fontSetting) const;
    bool operator!=(const FontSetting& fontSetting) const;

    // MFC Class Functions
    /// Gets the MFC Class Name for the object
    /// @return The MFC Class Name
    wxString GetMFCClassName() const                            
        {return (wxT("CFontItem"));}
    /// Gets the MFC Class Schema for the object
    /// @return The MFC Class Schema
    wxWord GetMFCClassSchema() const                            
        {return ((wxWord)1);}
    
    // Serialization Functions
protected:
    bool DoSerialize(PowerTabOutputStream& stream);
    bool DoDeserialize(PowerTabInputStream& stream, wxWord version);
    
public:
    // Data Functions
    bool SetFontSetting(const wxChar* faceName, wxInt32 pointSize, wxInt32 weight, bool italic, bool underline, bool strikeOut, wxColor color);
    bool SetFontSettingFromString(const wxChar* string);

    // Face Name Functions
    /// Sets the face name used by the FontSetting object
    /// @param faceName Face name to set
    /// @return True if the face name was set, false if not
    bool SetFaceName(const wxChar* faceName)                
        {wxCHECK(faceName != NULL, false); m_faceName = faceName; return (true);}
    /// Gets the face name used by the FontSetting object
    /// @return The face name used by the FontSetting object
    wxString GetFaceName() const                            
        {return (m_faceName);}

    // Point Size Functions
    /// Determines if a point size is valid
    /// @param pointSize Point size to validate
    /// @return True if the point size is valid, false if not
    static bool IsValidPointSize(wxInt32 pointSize)         
        {return ((pointSize >= MIN_POINTSIZE) && (pointSize <= MAX_POINTSIZE));}
    /// Sets the point size used by the FontSetting object
    /// @param pointSize Point size to set
    /// @return true if the point size was set, false if not
    bool SetPointSize(wxInt32 pointSize)                    
        {wxCHECK(IsValidPointSize(pointSize), false); m_pointSize = pointSize; return (true);}
    /// Gets the point size used by the FontSetting object
    /// @return The point size used by the FontSetting object
    int GetPointSize() const                                
        {return (m_pointSize);}

    // Weight Functions
    /// Determines if a weight is valid
    /// @param weight Weight to validate
    /// @return True if the weight is valid, false if not
    static bool IsValidWeight(wxInt32 weight)               
        {return (((weight >= weightDontCare) && (weight <= weightHeavy)) && ((weight % 100) == 0));}
    /// Sets the weight used by the FontSetting object
    /// @param weight Weight to set
    /// @return True if the weight was set, false if not
    bool SetWeight(wxInt32 weight)                          
        {wxCHECK(IsValidWeight(weight), false); m_weight = weight; return (true);}
    /// Gets the weight used by the FontSetting object
    /// @return The weight used by the FontSetting object
    int GetWeight() const                                   
        {return (m_weight);}

    // Effects Functions
    /// Sets or clears the italic effect
    /// @param set True sets the italic effect, false clears it
    void SetItalic(bool set = true)                         
        {m_italic = (wxByte)set;}
    /// Determines if the italic effect is set
    /// @return True if the italic effect is set, false if not
    bool IsItalic() const                                   
        {return (m_italic == (wxByte)true);}
    /// Sets or clears the underline effect
    /// @param set True sets the underline effect, false clears it
    void SetUnderline(bool set = true)                      
        {m_underline = (wxByte)set;}
    /// Determines if the underline effect is set
    /// @return True if the underline effect is set, false if not
    bool IsUnderline() const                                
        {return (m_underline == (wxByte)true);}
    /// Sets or clears the strikeout effect
    /// @param set True sets the strikeout effect, false clears it
    void SetStrikeOut(bool set = true)                      
        {m_strikeOut = (wxByte)set;}
    /// Determines if the strikeout effect is set
    /// @return True if the strikeout effect is set, false if not
    bool IsStrikeOut() const                                
        {return (m_strikeOut == (wxByte)true);}
        
    // Color Functions
    /// Sets the color used by the FontSetting object
    /// @param color Color to set
    void SetColor(wxColor color)                            
        {m_color = color;}
    /// Gets the color used by the FontSetting object
    /// @return The color used by the FontSetting object
    wxColor GetColor() const                                
        {return (m_color);}

    // Operations
    void GetFont(wxFont& font) const;
};

#endif
