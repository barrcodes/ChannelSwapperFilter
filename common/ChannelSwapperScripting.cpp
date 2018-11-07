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

#include "ChannelSwapperScripting.h"

//-------------------------------------------------------------------------------
//
// ReadScriptParameters
//
// See if we were called by the Photoshop scripting system and return the value
// in displayDialog if the user wants to see our dialog.
// 
//-------------------------------------------------------------------------------
OSErr ReadScriptParameters(Boolean* displayDialog)
{
	OSErr err = noErr;
	PIReadDescriptor token = NULL;
	DescriptorKeyID key = 0;
	DescriptorTypeID type = 0;
	int32 flags = 0;
	int32 channelMask;
	Boolean ignoreSelection;
	DescriptorKeyIDArray array = { 0 };

	if (displayDialog != NULL)
		*displayDialog = gData->queryForParameters;
	else
		return errMissingParameter;

	PIDescriptorParameters* descParams = gFilterRecord->descriptorParameters;
	if (descParams == NULL) return err;
	
	ReadDescriptorProcs* readProcs = gFilterRecord->descriptorParameters->readDescriptorProcs;
	if (readProcs == NULL) return err;

	gParams->ignoreSelection = false;

	if (descParams->descriptor != NULL)
	{
		token = readProcs->openReadDescriptorProc(descParams->descriptor, array);
		if (token != NULL)
		{
			while(readProcs->getKeyProc(token, &key, &type, &flags) && !err)
			{
				switch (key)
				{
					case keyChannels:
						err = readProcs->getIntegerProc(token, &channelMask);
						if (!err)
							gParams->channelMask = channelMask;
						break;
					case keyIgnoreSelection:
						err = readProcs->getBooleanProc(token, &ignoreSelection);
						if (!err)
							gParams->ignoreSelection = ignoreSelection;
						break;
					default:
						err = readErr;
						break;
				}
			}
			err = readProcs->closeReadDescriptorProc(token);
			gFilterRecord->handleProcs->disposeProc(descParams->descriptor);
			descParams->descriptor = NULL;
		}
		*displayDialog = descParams->playInfo == plugInDialogDisplay;
	}
	return err;
}



//-------------------------------------------------------------------------------
//
// WriteScriptParameters
//
// Write our parameters to the Photoshop scripting system in case we are being
// recorded in the actions pallete.
// 
//-------------------------------------------------------------------------------
OSErr WriteScriptParameters(void)
{
	OSErr err = noErr;
	PIWriteDescriptor token = NULL;
	PIDescriptorHandle h;

	PIDescriptorParameters*	descParams = gFilterRecord->descriptorParameters;
	if (descParams == NULL) return err;
	
	WriteDescriptorProcs* writeProcs = gFilterRecord->descriptorParameters->writeDescriptorProcs;
	if (writeProcs == NULL) return err;

	token = writeProcs->openWriteDescriptorProc();
	if (token != NULL)
	{
		writeProcs->putIntegerProc(
			token,
			keyChannels,
			gParams->channelMask
		);

		if (gParams->ignoreSelection)
			writeProcs->putBooleanProc(token, 
			                           keyIgnoreSelection, 
									   gParams->ignoreSelection);
		gFilterRecord->handleProcs->disposeProc(descParams->descriptor);
		writeProcs->closeWriteDescriptorProc(token, &h);
		descParams->descriptor = h;
		descParams->recordInfo = plugInDialogOptional;
	}
	else
	{
		return errMissingParameter;
	}
	return err;
}

// end ChannelSwapperScripting.cpp
