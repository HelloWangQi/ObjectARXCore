//////////////////////////////////////////////////////////////////////////////
//
//  Copyright 2013 Autodesk, Inc.  All rights reserved.
//
//  Use of this software is subject to the terms of the Autodesk license 
//  agreement provided at the time of installation or download, or which 
//  otherwise accompanies this software in either electronic or hard copy form.   
//
//////////////////////////////////////////////////////////////////////////////
// 
// Name:            AcValue.h
//
// Description:     
//////////////////////////////////////////////////////////////////////////////

#pragma once
#include "adesk.h"
#include "AdAChar.h"

class AcDbEvalVariant;
typedef struct tagVARIANT VARIANT;
typedef struct _SYSTEMTIME SYSTEMTIME;
class AcDbObjectId;
class AcGePoint2d;
class AcGePoint3d;
class AcCmColor;
struct resbuf;
class AcDbDwgFiler;
class AcDbDxfFiler;
#if __LP64__
typedef unsigned int DWORD;
#else
typedef unsigned long       DWORD;
#endif
//*************************************************************************
// AcValue
//*************************************************************************

class AcValue : public AcRxObject
{
public:
    enum DataType
    {
        kUnknown            = 0,
        kLong               = (0x1 << 0),
        kDouble             = (0x1 << 1),
        kString             = (0x1 << 2),
        kDate               = (0x1 << 3),
        kPoint              = (0x1 << 4),
        k3dPoint            = (0x1 << 5),
        kObjectId           = (0x1 << 6),
        kBuffer             = (0x1 << 7),
        kResbuf             = (0x1 << 8),
        kGeneral            = (0x1 << 9),
        kColor              = (0x1 << 10),
    };

    enum UnitType
    {
        kUnitless           = 0,
        kDistance           = (0x1 << 0),
        kAngle              = (0x1 << 1),
        kArea               = (0x1 << 2),
        kVolume             = (0x1 << 3),
        kCurrency           = (0x1 << 4),
        kPercentage         = (0x1 << 5),
        kAngleNotTransformed = (0x1 << 16),
    };

    enum ParseOption
    {
        kParseOptionNone        = 0,
        kSetDefaultFormat       = (0x1 << 0),
        kPreserveMtextFormat    = (0x1 << 1),
        kConvertTextToValue     = (0x1 << 2),
        kChangeDataType         = (0x1 << 3),
        kParseTextForFieldCode  = (0x1 << 4),
    };

    enum FormatOption
    {
        kFormatOptionNone       = 0,
        kForEditing             = (0x1 << 0),
        kForExpression          = (0x1 << 1),
        kUseMaximumPrecision    = (0x1 << 2),
        kIgnoreMtextFormat      = (0x1 << 3),
    };

public:
    static bool     isValidDataType         (const VARIANT& var);

public:
    ACRX_DECLARE_MEMBERS(AcValue);
    
    ACDB_PORT AcValue(void);
    ACDB_PORT AcValue(AcValue::DataType nDataType);
    ACDB_PORT AcValue(const AcValue& value);
    ACDB_PORT AcValue(const ACHAR * pszValue);
    ACDB_PORT AcValue(Adesk::Int32 lValue);
    ACDB_PORT AcValue(double fValue);
    ACDB_PORT AcValue(const __time64_t& date);
    ACDB_PORT AcValue(const SYSTEMTIME& date);
    ACDB_PORT AcValue(const AcGePoint2d& pt);
    ACDB_PORT AcValue(double x, double y);
    ACDB_PORT AcValue(const AcGePoint3d& pt);
    ACDB_PORT AcValue(double x, double y, double z);
    ACDB_PORT AcValue(const AcDbObjectId& id);
    ACDB_PORT AcValue(const resbuf& rb);
    ACDB_PORT AcValue(const AcDbEvalVariant& evalVar);
    ACDB_PORT AcValue(const VARIANT& var);
    ACDB_PORT AcValue(const AcCmColor& var);
    ACDB_PORT AcValue(const void* pBuf, DWORD dwBufSize);

    ACDB_PORT ~AcValue(void);

    ACDB_PORT bool  reset                   (void);
    ACDB_PORT bool  reset                   (AcValue::DataType nDataType);
    ACDB_PORT bool  resetValue              (void);
    ACDB_PORT AcValue::DataType dataType     (void) const;
    ACDB_PORT AcValue::UnitType unitType     (void) const;
    ACDB_PORT bool  setUnitType             (AcValue::UnitType nUnitType);
    ACDB_PORT const ACHAR* getFormat        (void) const;
    ACDB_PORT bool  setFormat               (const ACHAR* pszFormat);

    ACDB_PORT bool  isValid                 (void) const;

    ACDB_PORT       operator const ACHAR *  (void) const;
    ACDB_PORT       operator Adesk::Int32  (void) const;
    ACDB_PORT       operator double         (void) const;
    ACDB_PORT       operator __time64_t     (void) const;
    ACDB_PORT       operator AcGePoint2d    (void) const;
    ACDB_PORT       operator AcGePoint3d    (void) const;
    ACDB_PORT       operator AcDbObjectId   (void) const;

    ACDB_PORT AcValue& operator=            (const AcValue& value);
    ACDB_PORT AcValue& operator=            (const ACHAR * pszValue);
    ACDB_PORT AcValue& operator=            (Adesk::Int32 lValue);
    ACDB_PORT AcValue& operator=            (double fValue);
    ACDB_PORT AcValue& operator=            (__time64_t date);
    ACDB_PORT AcValue& operator=            (const AcGePoint2d& pt);
    ACDB_PORT AcValue& operator=            (const AcGePoint3d& pt);
    ACDB_PORT AcValue& operator=            (const AcDbObjectId& objId);
    ACDB_PORT AcValue& operator=            (const resbuf& rb);
    ACDB_PORT AcValue& operator=            (const AcDbEvalVariant& evalVar);
    ACDB_PORT AcValue& operator=            (const VARIANT& var);
    ACDB_PORT AcValue& operator=            (const AcCmColor& clr);
    ACDB_PORT bool  operator==              (const AcValue& val) const;
    ACDB_PORT bool  operator!=              (const AcValue& val) const;

    Adesk::Boolean  isEqualTo               (const AcRxObject* pOther) const;

    ACDB_PORT bool  get                     (const ACHAR *& pszValue) const;
    ACDB_PORT bool  get                     (ACHAR *& pszValue) const;
    ACDB_PORT bool  get                     (Adesk::Int32& lValue) const;
    ACDB_PORT bool  get                     (double& fValue) const;
    ACDB_PORT bool  get                     (__time64_t& date) const;
    ACDB_PORT bool  get                     (SYSTEMTIME& date) const;
    ACDB_PORT bool  get                     (AcGePoint2d& pt) const;
    ACDB_PORT bool  get                     (double& x, 
                                             double& y) const;
    ACDB_PORT bool  get                     (AcGePoint3d& pt) const;
    ACDB_PORT bool  get                     (double& x, 
                                             double& y, 
                                             double& z) const;
    ACDB_PORT bool  get                     (AcDbObjectId& objId) const;
    ACDB_PORT bool  get                     (resbuf** pRb) const;
    ACDB_PORT bool  get                     (AcDbEvalVariant& evalVar) const;
    ACDB_PORT bool  get                     (VARIANT& var) const;
    ACDB_PORT bool  get                     (AcCmColor& clr) const;
    ACDB_PORT bool  get                     (void*& pBuf, 
                                             DWORD& dwBufSize) const;

    ACDB_PORT bool  set                     (const AcValue& value);
    ACDB_PORT bool  set                     (const ACHAR* pszValue);
    ACDB_PORT bool  set                     (AcValue::DataType nDataType, 
                                             const ACHAR* pszValue);
    ACDB_PORT bool  set                     (Adesk::Int32 lValue);
    ACDB_PORT bool  set                     (double fValue);
    ACDB_PORT bool  set                     (const __time64_t& date);
    ACDB_PORT bool  set                     (const SYSTEMTIME& date);
    ACDB_PORT bool  set                     (const AcGePoint2d& pt);
    ACDB_PORT bool  set                     (double x, 
                                             double y);
    ACDB_PORT bool  set                     (const AcGePoint3d& pt);
    ACDB_PORT bool  set                     (double x, 
                                             double y, 
                                             double z);
    ACDB_PORT bool  set                     (const AcDbObjectId& objId);
    ACDB_PORT bool  set                     (const resbuf& rb);
    ACDB_PORT bool  set                     (const AcDbEvalVariant& evalVar);
    ACDB_PORT bool  set                     (const VARIANT& var);
    ACDB_PORT bool  set                     (const AcCmColor& clr);
    ACDB_PORT bool  set                     (const void* pBuf, 
                                             DWORD dwBufSize);

    ACDB_PORT bool  parse                   (const ACHAR* pszText, 
                                             AcValue::DataType nDataType, 
                                             AcValue::UnitType nUnitType, 
                                             const ACHAR* pszFormat, 
                                             AcValue::ParseOption nOption, 
                                             const AcDbObjectId* pTextStyleId);

    ACDB_PORT const ACHAR* format           (void) const;
    ACDB_PORT AcString format               (const ACHAR* pszFormat) const;
    ACDB_PORT bool  format                  (ACHAR*& pszValue) const;
    ACDB_PORT bool  format                  (const ACHAR* pszFormat, 
                                             ACHAR*& pszValue) const;
    ACDB_PORT AcString format               (AcValue::FormatOption nOption);
    ACDB_PORT AcString format               (const ACHAR* pszFormat, 
                                             AcValue::FormatOption nOption);

    ACDB_PORT bool  convertTo               (AcValue::DataType nDataType, 
                                             AcValue::UnitType nUnitType);
    ACDB_PORT bool  convertTo               (AcValue::DataType nDataType, 
                                             AcValue::UnitType nUnitType, 
                                             bool bResetIfIncompatible);
    Acad::ErrorStatus dwgInFields           (AcDbDwgFiler* pFiler);
    Acad::ErrorStatus dwgOutFields          (AcDbDwgFiler* pFiler) const;
    Acad::ErrorStatus dxfInFields           (AcDbDxfFiler* pFiler);
    Acad::ErrorStatus dxfOutFields          (AcDbDxfFiler* pFiler) const;

protected:
    void        *   mpImpObj;

private:
    friend class AcSystemInternals;
};


typedef AcArray<AcValue, AcArrayObjectCopyReallocator<AcValue> > AcValueArray;
