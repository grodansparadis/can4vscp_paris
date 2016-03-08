/////////////////////////////////////////////////////////////////////////////
// Name:        paristestapp.cpp
// Purpose:     
// Author:      Ake Hedman
// Modified by: 
// Created:     Mon 28 Oct 2013 14:47:03 CET
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

#include "paristestapp.h"

////@begin XPM images

////@end XPM images


/*
 * Application instance implementation
 */

////@begin implement app
IMPLEMENT_APP( ParistestApp )
////@end implement app


/*
 * ParistestApp type definition
 */

IMPLEMENT_CLASS( ParistestApp, wxApp )


/*
 * ParistestApp event table definition
 */

BEGIN_EVENT_TABLE( ParistestApp, wxApp )

////@begin ParistestApp event table entries
////@end ParistestApp event table entries

END_EVENT_TABLE()


/*
 * Constructor for ParistestApp
 */

ParistestApp::ParistestApp()
{
    Init();
}


/*
 * Member initialisation
 */

void ParistestApp::Init()
{
////@begin ParistestApp member initialisation
////@end ParistestApp member initialisation
}

/*
 * Initialisation for ParistestApp
 */

bool ParistestApp::OnInit()
{    
////@begin ParistestApp initialisation
    // Remove the comment markers above and below this block
    // to make permanent changes to the code.

#if wxUSE_XPM
    wxImage::AddHandler(new wxXPMHandler);
#endif
#if wxUSE_LIBPNG
    wxImage::AddHandler(new wxPNGHandler);
#endif
#if wxUSE_LIBJPEG
    wxImage::AddHandler(new wxJPEGHandler);
#endif
#if wxUSE_GIF
    wxImage::AddHandler(new wxGIFHandler);
#endif
////@end ParistestApp initialisation

    return true;
}


/*
 * Cleanup for ParistestApp
 */

int ParistestApp::OnExit()
{    
////@begin ParistestApp cleanup
    return wxApp::OnExit();
////@end ParistestApp cleanup
}

