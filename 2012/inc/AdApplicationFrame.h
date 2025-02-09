//////////////////////////////////////////////////////////////////////////////
//
//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright 2009-2011 by Autodesk, Inc.
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
//////////////////////////////////////////////////////////////////////////////
//
// Name:            AdApplicationFrame.h
//
//////////////////////////////////////////////////////////////////////////////

#ifndef __AD_APPFRAME_H__
#define __AD_APPFRAME_H__

#include "AdExportDef.h"

// forward declarations
class AdImpApplicationFrame;
class AdImpMenuBar;
class AdVisualElementBase;
namespace Autodesk 
{ 
    namespace WebServices 
    {
        class IWebServicesConfiguration;
    }
}

class ADAF_PORT AdColorTheme;
class ADAF_PORT AdApplicationFrameReactor;
class ADAF_PORT AdMenuBar;


/// <summary>
/// The callback provided by the application that integrates the
/// application frame. 
/// </summary>                                                  
typedef LRESULT (*LPFNAPPFRAMECALLBACK)(UINT nIndex, void* pUserData, void *pContextData);

/// <summary>
/// The tooltip information that will be used for
/// kAd_ToolTip_Show when the application frame invokes the
/// application callback register with AddFrameCallback. 
/// </summary>                                             
class ADAF_PORT AdCallDataTooltipInfo
{
public:

    AdCallDataTooltipInfo(int nToolType, wchar_t* pBtnStr);

    int GetToolType();
    void SetToolType(int nToolType);
    wchar_t* GetButtonText();
    void SetButtonText(wchar_t* pBtnStr);

private:
    /// <summary>
    /// Default constructor is intentionally forbidden. 
    /// </summary>                                      
    AdCallDataTooltipInfo();
    /// <summary>
    // Copy constructor and assignment operator are forbidden intentionally.
    /// </summary>
    AdCallDataTooltipInfo(const AdCallDataTooltipInfo& callDataTooltipInfo);
    AdCallDataTooltipInfo& operator=(const AdCallDataTooltipInfo& callDataTooltipInfo);

    /// <summary> Type id of tool, refer to enum Ad_AppFrame_ToolTipId
    /// </summary>
    int m_nToolType;

    /// <summary> The string to be displayed as Tooltip content. </summary>
    wchar_t *m_pBtnStr;
};

class IWebServicesLoader
{
public:
    /// <summary>
    /// To avoid loading the web services modules at startup which will hurt startup performance,
    /// the application frame loads web services modules only when a services is invoked at the first
    /// time. And the integration product can plant a loader to hook into this loading process and load
    /// its web services module which links with AdWebServicesUI, thus indirectly loading AdWebServicesUI.
    /// And then the product has a chance to plant an observer(IWebServicesUIObserver) to listen to login events.
    /// </summary> 
    /// <returns>
    /// Return true if the module was successfully loaded, return false if it failed to 
    /// load the module. If this function returns false the web services operation will be aborted. 
    /// </returns>
    virtual bool LoadModule() = 0;

protected:
    virtual ~IWebServicesLoader() {}
};

//////////////////////////////////////////////////////////////////
// Application Frame

/// <summary>
/// This class represents ApplicationFrame in the AppFrame
/// component. 
/// </summary>                                            
class ADAF_PORT AdApplicationFrame
{
public:
    /// <summary>
    /// Size constants for the Autodesk Application Frame.
    /// </summary>                                                  
    enum Ad_AppFrame_Const 
    {
        kAdApplicationStatusBarHeight_Min = 24,                     // Minimum height of Application Status Bar
        kAdDefaultDpi = 96
    };

    /// <summary>
    /// The state of DocumentControl's host window. 
    /// </summary>                                  
    enum Ad_HostWindow_States 
    {
        kAd_DocumentActivated = 1,
        kAd_MenuSelect        = 2,
        kAd_MDIStateChanged   = 3,
        kAd_WindowPosChanged  = 4,
        kAd_SessionInit       = 5,
        kAd_SessionDone       = 6,
        kAd_SettingChanged    = 7,
        kAd_MDIMetricsChanged = 8,
        kAd_SetWindowText     = 9,
        kAd_VisibilityChanged = 10,
        kAd_GetWindowText     = 11,
        kAd_GetWindowTextLen  = 12,
        kAd_SysColorChanged   = 13
    };

    /// <summary>
    /// VisualElement's index order for the Autodesk Application
    /// Frame. 
    /// </summary>                                              
    enum Ad_AppFrame_ToolTipId 
    {
        kAd_ToolId_ApplicationButton    = 1000,
    };

    /// <summary>
    /// Callback ID list for the AppFrame. 
    /// </summary>                         
    enum Ad_Callback_Index 
    {
        kAd_ApplicationButton_IsOpen,
        kAd_ApplicationButton_ShowSmallButton,
        kAd_ToolTip_Close,
        kAd_ToolTip_Show,
        kAd_MenuBar_Show,
        kAd_MenuBar_ExecuteMenuItem,
        kAd_WorkSpaceInfo,
        kAd_GetProductName,
        kAd_Ribbon_IsDockedTop,
        kAd_ACAD_InPlotPreview,
        kAd_ACAD_GetDataSource,
        kAd_RecalcLayout,
        kAd_StayActive,
        kAd_GetMDIClient,
        kAd_MDIGetActive,
        kAd_SkipStandardBackgroundDraw,
        kAd_SkipProductNameUpdate
    };

    /// <summary>
    /// Defines the Client application character set, this defaults to Unicode
    /// </summary>                                          
    enum Ad_Product_Character_Set
    {
        kAd_Unicode,
        kAd_MBCS
    };

    static void SetResourcesPath(LPCWSTR lpszName);
    static AdApplicationFrame* CreateInstance(HWND hWndMainFrame);

    virtual ~AdApplicationFrame();

    bool Initialize();

    void SessionInitialized();

    AdMenuBar* GetMenuBar();

    void SetDocumentName(LPCWSTR wszDocumentName);

    bool SetProductLogo(HBITMAP hBitmap);
    bool SetBrand(HBITMAP hBitmap);
    bool SetProductIcon(HICON hIcon);
    bool SetMainMenu(HMENU hMainMenu);
    bool SetMainFrame(HWND hWndMainFrame);
    bool SetMainFrameRect(RECT rectMainFrame);
    bool SetProductCharacterSet(Ad_Product_Character_Set charSet);
    bool SetProductName(LPCWSTR lpszName);
    bool SetApplicationButton(HBITMAP hBitmap, 
        HBITMAP hHotBitmap, HBITMAP hSelectedBitmap);
    bool SetSmallApplicationButton(HBITMAP hBitmap, 
        HBITMAP hHotBitmap, HBITMAP hSelectedBitmap);

    bool IsMenuBarVisible();
    void ShowMenuBar(bool bShow = true);

    void UpdateApplicationButton();
    bool IsApplicationButtonEnabled() const;
    void EnableApplicationButton(bool bEnable = true);

    void ForceFrameRepaint(HWND hWnd);

    unsigned long GetFrameStates();
    unsigned long SetFrameStates(unsigned long dwFrameStates);

    bool AddFrameReactor(AdApplicationFrameReactor *pFrameReactor);
    bool RemoveFrameReactor(AdApplicationFrameReactor *pFrameReactor);

    LPFNAPPFRAMECALLBACK AddFrameCallback(LPFNAPPFRAMECALLBACK pfnCallback, void* pUserData);

    bool TranslateMainFrameMessage(MSG *pMessage);
    BOOL PreTranslateMessageHandler(MSG* pMsg);

    LRESULT ProcessMainFrameMessage(HWND hWnd, UINT nMsg, WPARAM wParam, LPARAM lParam);
    bool HostWindowStateChanged(UINT nState, WPARAM wParam, LPARAM lParam);

    HWND GetAppFrameHwnd();

    HWND GetQuickAccessToolBarHwnd();
    bool IsQuickAccessToolBarVisible();
    void ShowQuickAccessToolBar(bool bShow);

    HWND GetInfoCenterControl();
    bool SetInfoCenterControl(HWND hControl);
    void EnableInfoCtrCtrl(BOOL bEnable);
    void UpdateInfoCenterControl();


    int GetDocumentControlHeight() const;

    void TrackPopupByMenuCmd(int nIndex);
    void EnableMenuBar(bool bEnable);
    void EnableSysBtnGroup(bool bEnable);
    void SetExitOnApplicationButtonDoubleClick(bool bExit);
    bool GetExitOnApplicationButtonDoubleClick();
    const wchar_t * GetApplicationButtonClassName();

    ///////////////////////////////////////////////////////////////////////////////
    /// <summary>Check if the web services is enabled in the info center.</summary>
    /// <returns>Returns true if web services is enabled in the info center.</returns>
    bool IsWebServicesEnabled() const;

    ///////////////////////////////////////////////////////////////////////////////
    /// <summary>Enable web services feature in AdApplicationFrame.
    /// The login button in InfoCenter will be set to visible when this function called.
    /// This API is expected to be called at the very beginning, preferably after calling Initialize().
    /// NOTE: WebServices is default to disabled, and product should only call it with true to enable webservices.
    ///       Do not call it with false after web services has been enabled.
    /// <param name="isWebServicesEnabled">if the web services is enabled.</param>
    /// </summary>
    void EnableWebServices(bool isWebServicesEnabled);

    ///////////////////////////////////////////////////////////////////////////////
    /// <summary>Gets the current locale.</summary>
    /// <param name="locale">Buffer to receive the current locale. See 
    /// SetCurrentLocale for the format of this string.</param>
    /// <param name="size">Size of the buffer, in characters.</param>
    /// <returns>The number of characters copied to the buffer. If the client sets
    /// null or empty string with the setter API, it will return empty string here.</returns>
    int GetCurrentLocale(wchar_t* locale, int size) const;

    ///////////////////////////////////////////////////////////////////////////////
    /// <summary>Sets the current locale. By default current user locale 
    /// set in the system is used as current locale. This function can be 
    /// used to set an explicit locale as current locale.</summary>
    /// <param name="locale">The current locale string. The name must be 
    /// in the format xx-YY (examples: en-US, de-DE, fr-FR). If this is 
    /// null or empty string, current user locale set in the system will be 
    /// used as current locale, but the empty string will still be 
    /// returned if the client calls the getter API.</param>
    void SetCurrentLocale(const wchar_t* locale);
    
    ///////////////////////////////////////////////////////////////////////////////
    /// <summary>Gets the cache path which is used to store the 
    /// downloaded files (dynamic menu).</summary>
    /// <param name="path">Buffer to receive the path. If this is 
    /// NULL it returns the number of characters in the string excluding 
    /// null terminator.</param>
    /// <param name="size">Size of the buffer in characters.</param>
    /// <returns>The number of characters copied to the buffer if path 
    /// is not NULL or number of characters in the string excluding null 
    /// terminator if path is NULL.</returns>
    int GetCachePath(wchar_t *path, int size) const;

    ///////////////////////////////////////////////////////////////////////////////
    /// <summary>Sets the cache path which is used to store the files to
    /// downloaded files (dynamic menu).</summary>
    /// <param name="path">Path to set. The string must be null 
    /// terminated.</param>
    void SetCachePath(const wchar_t* path);

    ///////////////////////////////////////////////////////////////////////////////
    /// <summary>Sets the IWebServicesLoader instance to AdApplicationFrame.</summary>
    /// <param name="loader">IWebServicesLoader to set.</param>
    void SetWebServicesLoader(IWebServicesLoader* loader);

    ///////////////////////////////////////////////////////////////////////////////
    /// <summary>Gets the IWebServicesLoader pointer which will be used to dynamic 
    /// load web services module.</summary>
    /// <returns>The IWebServicesLoader pointer set by integration product.
    /// </returns>
    IWebServicesLoader* GetWebServicesLoader() const;

protected:
    AdApplicationFrame(HWND hWndMainFrame); 

    // Data members

    /// <summar>
    /// Member pointer to the single instance of the application frame; there can be only one per application.
    /// </summary>
    static AdApplicationFrame *spAppFrame;

    /// <summary>
    /// Member pointer to the implementation class for the application frame.
    /// </summary>
    AdImpApplicationFrame *mpImpAppFrame;

    /// <summary>
    /// Member pointer to the menu bar.
    /// </summary>
    AdMenuBar *mpAdMenuBar;
};

#endif
