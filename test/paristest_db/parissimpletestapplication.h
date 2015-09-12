/////////////////////////////////////////////////////////////////////////////
// Name:        parissimpletestapplication.h
// Purpose:     
// Author:      Ake Hedman
// Modified by: 
// Created:     Mon 28 Oct 2013 14:49:35 CET
// RCS-ID:      
// Copyright:   Copyright (C) 2013 Ake Hedman, Grodans Paradis AB
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _PARISSIMPLETESTAPPLICATION_H_
#define _PARISSIMPLETESTAPPLICATION_H_


/*!
 * Includes
 */

////@begin includes
#include "wx/frame.h"
////@end includes

/*!
 * Forward declarations
 */

////@begin forward declarations
////@end forward declarations

/*!
 * Control identifiers
 */

////@begin control identifiers
#define ID_PARISSIMPLETESTAPPLICATION 10000
#define SYMBOL_PARISSIMPLETESTAPPLICATION_STYLE wxCAPTION|wxRESIZE_BORDER|wxSYSTEM_MENU|wxCLOSE_BOX
#define SYMBOL_PARISSIMPLETESTAPPLICATION_TITLE _("Paris simple test application")
#define SYMBOL_PARISSIMPLETESTAPPLICATION_IDNAME ID_PARISSIMPLETESTAPPLICATION
#define SYMBOL_PARISSIMPLETESTAPPLICATION_SIZE wxSize(400, 300)
#define SYMBOL_PARISSIMPLETESTAPPLICATION_POSITION wxDefaultPosition
////@end control identifiers


/*!
 * Parissimpletestapplication class declaration
 */

class Parissimpletestapplication: public wxFrame
{    
    DECLARE_CLASS( Parissimpletestapplication )
    DECLARE_EVENT_TABLE()

public:
    /// Constructors
    Parissimpletestapplication();
    Parissimpletestapplication( wxWindow* parent, wxWindowID id = SYMBOL_PARISSIMPLETESTAPPLICATION_IDNAME, const wxString& caption = SYMBOL_PARISSIMPLETESTAPPLICATION_TITLE, const wxPoint& pos = SYMBOL_PARISSIMPLETESTAPPLICATION_POSITION, const wxSize& size = SYMBOL_PARISSIMPLETESTAPPLICATION_SIZE, long style = SYMBOL_PARISSIMPLETESTAPPLICATION_STYLE );

    bool Create( wxWindow* parent, wxWindowID id = SYMBOL_PARISSIMPLETESTAPPLICATION_IDNAME, const wxString& caption = SYMBOL_PARISSIMPLETESTAPPLICATION_TITLE, const wxPoint& pos = SYMBOL_PARISSIMPLETESTAPPLICATION_POSITION, const wxSize& size = SYMBOL_PARISSIMPLETESTAPPLICATION_SIZE, long style = SYMBOL_PARISSIMPLETESTAPPLICATION_STYLE );

    /// Destructor
    ~Parissimpletestapplication();

    /// Initialises member variables
    void Init();

    /// Creates the controls and sizers
    void CreateControls();

////@begin Parissimpletestapplication event handler declarations

////@end Parissimpletestapplication event handler declarations

////@begin Parissimpletestapplication member function declarations

    /// Retrieves bitmap resources
    wxBitmap GetBitmapResource( const wxString& name );

    /// Retrieves icon resources
    wxIcon GetIconResource( const wxString& name );
////@end Parissimpletestapplication member function declarations

    /// Should we show tooltips?
    static bool ShowToolTips();

////@begin Parissimpletestapplication member variables
////@end Parissimpletestapplication member variables
};

#endif
    // _PARISSIMPLETESTAPPLICATION_H_
