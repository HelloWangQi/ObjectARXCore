#ifndef AC_GECBNDRY_H
#define AC_GECBNDRY_H
//
// (C) Copyright 1993-1999 by Autodesk, Inc.
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
// Description:
//
// This files implements the class AcGeCurveBoundary, which represents
// the geometric content typically associated with a face loop.
// A face loop is represented as arrays of 3d curves (edge geometry),
// sense of edges, 2d curves (coedge geometry in the surfae parameter
// space), sense of coedges.
// In general, there is a one-to-one correspondence among all arrays that
// are present.  However, certain elements of either curve arrays could
// be NULL.  For example, the four tuple (curve3d, NULL, kFalse, kTrue)
// is legal.  In this case, the boolean sense on curve 2d is may or may
// not be meaningless, depending on the symantics of the usage of this
// class (consider that in ACIS, the sense of the coedge is relative to
// the edge, and not the parameter space curve).
//
// Loop degeneracies are represented as follows.
// 1. Entire loop degenerate to a single model space point, which is
// represented by the tuple (numElements = 1, position3d, curve2d).
// The curve2d may be NULL.  The edge sense, and the curve2d sense are
// irrelevant.  isDegenerate() method allows the dermination of this
// condition on a loop.
// 2. Loop consisting of one or more model space degeneracies.
// This case is represented as the general case with those edges that are
// degenerate represented by position3d.  This implies that in the
// general case, model space geometry of a curve boundary may consist of
// curve3d and/or position3d pointers.  Consequently, this geometry is
// obtained by the user as entity3d pointers.  The degeneracy of a
// constituent edge can be detected by the type of the model space
// geometry.
//
// This class also supports the ownership of its geometry.   Being the
// owner of its geometry would cause it to remove the geometry on
// destruction of an instance of the class.
//

#include "gegbl.h"
#pragma pack (push, 8)

class AcGeCurve2d;
class AcGeEntity3d;
class AcGePosition3d;
     
class 
#ifdef AC_GECBNDRY_CPP
GE_DLLEXPORT
#elif !defined(ACGE_XENTLIB)
GE_DLLIMPORT
#endif
AcGeCurveBoundary
{
public:
    AcGeCurveBoundary();
    AcGeCurveBoundary(int numberOfCurves, const AcGeEntity3d *const * crv3d,
                      const AcGeCurve2d *const * crv2d,
                      Adesk::Boolean* orientation3d,
                      Adesk::Boolean* orientation2d,
                      Adesk::Boolean makeCopy = Adesk::kTrue);
    AcGeCurveBoundary(const AcGeCurveBoundary&);

    ~AcGeCurveBoundary();

    // Assignment.
    //
    AcGeCurveBoundary& operator =   (const AcGeCurveBoundary& src);

    // Query the data.
    //
    Adesk::Boolean     isDegenerate () const;
    Adesk::Boolean     isDegenerate (AcGePosition3d& degenPoint, AcGeCurve2d** paramCurve) const;
    int                numElements  () const;
    void               getContour   (int& n, AcGeEntity3d*** crv3d,
                                     AcGeCurve2d*** paramGeometry,
                                     Adesk::Boolean** orientation3d,
                                     Adesk::Boolean** orientation2d) const;

    AcGeCurveBoundary& set (int numElements, const AcGeEntity3d *const * crv3d,
                            const AcGeCurve2d *const * crv2d,
                            Adesk::Boolean* orientation3d,
                            Adesk::Boolean* orientation2d,
                            Adesk::Boolean makeCopy = Adesk::kTrue);

    // Curve ownership.
    //
    Adesk::Boolean     isOwnerOfCurves() const;
    AcGeCurveBoundary& setToOwnCurves ();

protected:
    friend class AcGeImpCurveBoundary;

    AcGeImpCurveBoundary    *mpImpBnd;
    int                     mDelBnd;
};

#pragma pack (pop)
#endif
