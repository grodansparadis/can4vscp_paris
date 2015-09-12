/////////////////////////////////////////////////////////////////////////////
// Name:        parissimpletestapplication.cpp
// Purpose:     
// Author:      Ake Hedman
// Modified by: 
// Created:     Mon 28 Oct 2013 14:49:35 CET
// RCS-ID:      
// Copyright:   Copyright (C) 2013 Ake Hedman, Grodans Paradis AB
// Licence:     
/////////////////////////////////////////////////////////////////////////////

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

////@begin includes
////@end includes

#include "parissimpletestapplication.h"

////@begin XPM images
////@end XPM images


/*
 * Parissimpletestapplication type definition
 */

IMPLEMENT_CLASS( Parissimpletestapplication, wxFrame )


/*
 * Parissimpletestapplication event table definition
 */

BEGIN_EVENT_TABLE( Parissimpletestapplication, wxFrame )

////@begin Parissimpletestapplication event table entries
////@end Parissimpletestapplication event table entries

END_EVENT_TABLE()


/*
 * Parissimpletestapplication constructors
 */

Parissimpletestapplication::Parissimpletestapplication()
{
    Init();
}

Parissimpletestapplication::Parissimpletestapplication( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
    Init();
    Create( parent, id, caption, pos, size, style );
}


/*
 * Parissimpletestapplication creator
 */

bool Parissimpletestapplication::Create( wxWindow* parent, wxWindowID id, const wxString& caption, const wxPoint& pos, const wxSize& size, long style )
{
////@begin Parissimpletestapplication creation
    wxFrame::Create( parent, id, caption, pos, size, style );

    CreateControls();
    Centre();
////@end Parissimpletestapplication creation
    return true;
}


/*
 * Parissimpletestapplication destructor
 */

Parissimpletestapplication::~Parissimpletestapplication()
{
////@begin Parissimpletestapplication destruction
////@end Parissimpletestapplication destruction
}


/*
 * Member initialisation
 */

void Parissimpletestapplication::Init()
{
////@begin Parissimpletestapplication member initialisation
////@end Parissimpletestapplication member initialisation
}


/*
 * Control creation for Parissimpletestapplication
 */

void Parissimpletestapplication::CreateControls()
{    
////@begin Parissimpletestapplication content construction
    Parissimpletestapplication* itemFrame1 = this;

////@end Parissimpletestapplication content construction
}


/*
 * Should we show tooltips?
 */

bool Parissimpletestapplication::ShowToolTips()
{
    return true;
}

/*
 * Get bitmap resources
 */

wxBitmap Parissimpletestapplication::GetBitmapResource( const wxString& name )
{
    // Bitmap retrieval
////@begin Parissimpletestapplication bitmap retrieval
    wxUnusedVar(name);
    return wxNullBitmap;
////@end Parissimpletestapplication bitmap retrieval
}

/*
 * Get icon resources
 */

wxIcon Parissimpletestapplication::GetIconResource( const wxString& name )
{
    // Icon retrieval
////@begin Parissimpletestapplication icon retrieval
    wxUnusedVar(name);
    return wxNullIcon;
////@end Parissimpletestapplication icon retrieval
}
