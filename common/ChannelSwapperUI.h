// ADOBE SYSTEMS INCORPORATED
// Copyright  1993 - 2002 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this 
// file in accordance with the terms of the Adobe license agreement
// accompanying it.  If you have received this file from a source
// other than Adobe, then your use, modification, or distribution
// of it requires the prior written permission of Adobe.
//-------------------------------------------------------------------------------
#ifndef _CHANNELSWAPPERUI_H
#define _CHANNELSWAPPERUI_H

#include "PITypes.h"
#include "DialogUtilities.h"

const int16 kDOK = 1;
const int16 kDCancel = 2;
const int16 kDProxyItem = 5;
// ID # 6 appears to be in use, as it failed to work for kDRed
const int16 kDRed = 7;
const int16 kDGreen = 8;
const int16 kDBlue = 9;
const int16 kDAlpha = 10;
const int16 kDEntireImage = 11;

DLLExport BOOL __stdcall ChannelSwapperProc(HWND hDlg, UINT wMsg, WPARAM wParam, LPARAM lParam);

Boolean DoUI(void);
void DoAbout(void);
void InitColorCheckboxes(HWND hDlg);
void UpdateCheckbox(HWND hDlg, uint16 item);
#endif
// end ChannelSwapperUI.h
