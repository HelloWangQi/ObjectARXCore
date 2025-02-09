///////////////////////////////////////////////////////////////////////////////
//
//
//  (C) Copyright 2005 by Autodesk, Inc.  All rights reserved.
//
// Permission to use, copy, modify, and distribute this software in
// object code form for any purpose and without fee is hereby granted,
// provided that the above copyright notice appears in all copies and
// that both that copyright notice and the limited warranty and
// restricted rights notice below appear in all supporting
// documentation.
//
// AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS.
// AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC.
// DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
// UNINTERRUPTED OR ERROR FREE.
//
// Use, duplication, or disclosure by the U.S. Government is subject to
// restrictions set forth in FAR 52.227-19 (Commercial Computer
// Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
// (Rights in Technical Data and Computer Software), as applicable.
//
///////////////////////////////////////////////////////////////////////////////

#ifndef ATILDEFS_H
#include "AtilDefs.h"
#endif

#ifndef  PIXELSELECTORINTERFACE_H
#define  PIXELSELECTORINTERFACE_H

namespace AtilFilters
{

class PixelSelectorInterface 
{
public:
    virtual ~PixelSelectorInterface () {};
    virtual bool isSelected (Atil::Int32 x, Atil::Int32 y) = 0;
    virtual void setSelected (Atil::Int32 y, Atil::Int32 x, int nCount ) = 0;
    virtual void flush () = 0;
};

} //end of namespace
#endif
