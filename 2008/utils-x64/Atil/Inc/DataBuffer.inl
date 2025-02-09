///////////////////////////////////////////////////////////////////////////////
//
//
//  (C) Copyright 2005-2007 by Autodesk, Inc.  All rights reserved.
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

#ifndef DATABUFFER_INL
#define DATABUFFER_INL

namespace Atil
{

/// <summary>
/// Inlined query for the number of bytes in the buffer.
/// </summary>
///
/// <returns>
/// Returns the integer count of bytes allocated in the internal buffer.
/// </returns>
inline int DataBuffer::numBytes () const
{
    return mnBufferBytes;
}

/// <summary>
/// Inlined query for modifiable access to the enclosed buffer.
/// </summary>
///
/// <returns>
/// Returns a pointer that may be used to write into the enclosed buffer.
/// </returns>
inline unsigned char* DataBuffer::dataPtr ()
{
    return mpBuffer;
}

/// <summary>
/// Inlined query for read-only access to the enclosed buffer.
/// </summary>
///
/// <returns>
/// Returns a pointer that may be used to read from the enclosed buffer.
/// </returns>
inline const unsigned char* DataBuffer::dataPtr () const
{
    return mpBuffer;
}    

}

#endif
