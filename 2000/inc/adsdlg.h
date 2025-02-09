#ifndef _adsdlg_h
#define _adsdlg_h 1
//
// (C) Copyright 1989-1999 by Autodesk, Inc. 
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
// 
//   DESCRIPTION:
//       Definitions for ADS Programmable Dialogue Boxes


#include "ads.h"

#pragma pack (push, 8)

/* Defined only for OS/2 DLL Version 
 */
#ifndef CALLB
#define CALLB
#endif

/* There is a clash between the alignment required within structures for
   ADS and that required for members within Zortech structs and classes.
   ADS requires byte alignment (-a1) while 32-bit Zortech requires 4-byte
   alignment (-a4).  To work around this clash the alignment is set to one
   at the top of this header file and restored to four at the bottom so
   that ADS structures are byte-aligned.
 */
#ifdef __ZTC__
#pragma ZTC align 1
#endif

/* Ensure that C++ modules use the right linking conventions when calling
   functions contained in C.
 */
#ifdef __cplusplus
    extern /*MSG0*/"C" {
#endif

typedef void *ads_hdlg;
typedef void *ads_htile;

typedef struct {
    ads_hdlg  dialog;
    ads_htile tile;
    char*     value;
    void*     client_data;
    int       reason;
    long      x, y;
} ads_callback_packet;

/* The following are used in tile callback packets. Their meaning
   for each kind of tile can be found in the Programmable Dialogue
   Boxes documentation.
*/
#define CBR_SELECT       1
#define CBR_LOST_FOCUS   2
#define CBR_DRAG         3
#define CBR_DOUBLE_CLICK 4

#ifndef _PROTEUS_H
    /* ADS user's function, passed to AutoCAD to be called later
     */
    typedef void (*CLIENTFUNC) (ads_callback_packet *cpkt);
#endif /* _PROTEUS_H */

#define NULLCB ((CLIENTFUNC)0)
#define BAD_DIALOG NULL

/* Return by reference integers for ads_start_dialog
 */
#define DLGCANCEL     0 /* User pressed Cancel or equivalent */
#define DLGOK         1 /* User pressed Ok */
#define DLGALLDONE   -1 /* All dialogs terminated with
                           term_dialog */
#define DLGSTATUS     2 /* start of user return codes */

#ifndef _PROCONST_H
/* Preventing redefined warnings.
   List argument type for ads_start_list();
 */
#define LIST_CHANGE ((short) 1) /* Change selected listbox contents */
#define LIST_APPEND ((short) 2) /* Append new listbox entry */
#define LIST_NEW    ((short) 3) /* Delete old list and create new list */
/*
  Mode argument type for ads_mode_tile();
 */
#define MODE_ENABLE   ((short) 0) /* Enable tile */
#define MODE_DISABLE  ((short) 1) /* Disable tile */
#define MODE_SETFOCUS ((short) 2) /* Set focus to tile */
#define MODE_SETSEL   ((short) 3) /* Set editbox selection--allows 
                                     auto-clearing of old string */
#define MODE_FLIP     ((short) 4) /* Invert current state */
#endif  // _PROCONST_H

/* For buffers that receive values for tiles.  The number is
   arbitrary--it's just here to allow changing them all from
   one place.
 */
#ifndef _PROTEUS_H
#define MAX_TILE_STR  40
#endif

#define TILE_STR_LIMIT 255  /* real limit of dialog strings */

/* Dialog Functions
 */

int ads_load_dialog            (const char *dclfile, int *dcl_id);
int ads_unload_dialog          (int dcl_id);
int ads_new_dialog             (const char *dlgname, int dcl_id,
                                CLIENTFUNC def_callback, ads_hdlg *hdlg);
int ads_new_positioned_dialog  (const char *dlgname, int dcl_id,
                                CLIENTFUNC def_callback, int x, int y,
                                ads_hdlg *hdlg);
int ads_start_dialog           (ads_hdlg hdlg, int *status);
int ads_term_dialog            (void);
int ads_action_tile            (ads_hdlg hdlg, const char *key, CLIENTFUNC tilefunc);
int ads_done_dialog            (ads_hdlg hdlg, int status);
int ads_done_positioned_dialog (ads_hdlg hdlg, int status, int *x_result,
                                  int *y_result);
int ads_set_tile          (ads_hdlg hdlg, const char *key, const char *value);
int ads_client_data_tile  (ads_hdlg hdlg, const char *key, void *clientdata);
int ads_get_tile          (ads_hdlg hdlg, const char *key,
                           char *value, int maxlen);
int ads_get_attr          (ads_hdlg hdlg, const char *key,
                           char *attr, char *value, int len);
int ads_get_attr_string   (ads_htile tile, char *attr, char *value, int len);
int ads_start_list        (ads_hdlg hdlg, const char *key, short operation, short index);
int ads_add_list          (const char *item);
int ads_end_list          (void);
int ads_mode_tile         (ads_hdlg hdlg, const char *key, short mode);
int ads_dimensions_tile   (ads_hdlg hdlg, const char *key,
                           short *cx, short *cy);
int ads_start_image       (ads_hdlg hdlg, const char *key);
int ads_vector_image      (short x1, short y1, short x2, short y2, short color);
int ads_fill_image        (short x1, short y1, short x2, short y2, short color);
int ads_slide_image       (short x1, short y1, short x2, short y2,
                           const char *slnam);
int ads_end_image         (void);

#ifdef __cplusplus
}
#endif

#pragma pack (pop)

#endif
