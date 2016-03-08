/////////////////////////////////////////////////////////////////////////////
// Name:        paristestapp.h
// Purpose:     
// Author:      Ake Hedman
// Modified by: 
// Created:     Mon 28 Oct 2013 14:47:03 CET
// RCS-ID:      
// Copyright:   Copyright (C) 2013 Ake Hedman, Grodans Paradis AB
// Licence:     
/////////////////////////////////////////////////////////////////////////////

#ifndef _PARISTESTAPP_H_
#define _PARISTESTAPP_H_


/*!
 * Includes
 */

////@begin includes
#include "wx/image.h"
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
////@end control identifiers

/*!
 * ParistestApp class declaration
 */

class ParistestApp: public wxApp
{    
    DECLARE_CLASS( ParistestApp )
    DECLARE_EVENT_TABLE()

public:
    /// Constructor
    ParistestApp();

    void Init();

    /// Initialises the application
    virtual bool OnInit();

    /// Called on exit
    virtual int OnExit();

////@begin ParistestApp event handler declarations
////@end ParistestApp event handler declarations

////@begin ParistestApp member function declarations
////@end ParistestApp member function declarations

////@begin ParistestApp member variables
////@end ParistestApp member variables
};

/*!
 * Application instance declaration 
 */

////@begin declare app
DECLARE_APP(ParistestApp)
////@end declare app

#endif
    // _PARISTESTAPP_H_
