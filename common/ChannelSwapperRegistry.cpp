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

#include "ChannelSwapperRegistry.h"

//-------------------------------------------------------------------------------
//
// ReadRegistryParameters
//
// Read our parameters out of the Photoshop Registry. This saves us from writing
// to a preferences file and the pains of managing that on each OS. You should 
// probably ignore errors from this routine as other hosts have not 
// implemented a registry.
//
//-------------------------------------------------------------------------------
SPErr ReadRegistryParameters(void)
{
	SPErr err = noErr;
	SPBasicSuite* basicSuite = gFilterRecord->sSPBasic;
	PSDescriptorRegistryProcs* registryProcs = NULL;
	PSActionDescriptorProcs* descriptorProcs = NULL;
	PIActionDescriptor descriptor = NULL;
	int32 channelMask;
	Boolean ignoreSelection;

	if (basicSuite == NULL)
		return errPlugInHostInsufficient;

	err = basicSuite->AcquireSuite(kPSDescriptorRegistrySuite, 
		                           kPSDescriptorRegistrySuiteVersion, 
								   (const void **)&registryProcs);
	if (err) goto returnError;

	err = basicSuite->AcquireSuite(kPSActionDescriptorSuite, 
		                           kPSActionDescriptorSuiteVersion, 
								   (const void **)&descriptorProcs);
	if (err) goto returnError;

	err = registryProcs->Get(plugInUniqueID, &descriptor);
	if (err) goto returnError;
	if (descriptor == NULL) goto returnError;

	err = descriptorProcs->GetInteger(
		descriptor,
		keyChannels,
		&channelMask);

	if (err) goto returnError;
	gParams->channelMask = channelMask;

	err = descriptorProcs->GetBoolean(descriptor, 
		                              keyIgnoreSelection, 
									  &ignoreSelection);
	if (err) goto returnError;
	gParams->ignoreSelection = ignoreSelection;

returnError:
	if (descriptor != NULL)
		descriptorProcs->Free(descriptor);
	if (registryProcs != NULL)
		basicSuite->ReleaseSuite(kPSDescriptorRegistrySuite, 
		                         kPSDescriptorRegistrySuiteVersion);
	if (descriptorProcs != NULL)
		basicSuite->ReleaseSuite(kPSActionDescriptorSuite, 
		                         kPSActionDescriptorSuiteVersion);
	return err;
}



//-------------------------------------------------------------------------------
//
// WriteRegistryParameters
//
// Write our parameters out to the Photoshop Registry. This saves us from writing
// to a preferences file and the pains of managing that on each OS. You should 
// probably ignore errors from this routine as other hosts have not 
// implemented a registry.
// 
//-------------------------------------------------------------------------------
SPErr WriteRegistryParameters(void)
{
	SPErr err = noErr;
	SPBasicSuite* basicSuite = gFilterRecord->sSPBasic;
	PSDescriptorRegistryProcs* registryProcs = NULL;
	PSActionDescriptorProcs* descriptorProcs = NULL;
	PIActionDescriptor descriptor = NULL;


	if (basicSuite == NULL)
		return errPlugInHostInsufficient;

	err = basicSuite->AcquireSuite(kPSDescriptorRegistrySuite, 
		                           kPSDescriptorRegistrySuiteVersion, 
								   (const void **)&registryProcs);
	if (err) goto returnError;

	err = basicSuite->AcquireSuite(kPSActionDescriptorSuite, 
		                           kPSActionDescriptorSuiteVersion, 
								   (const void **)&descriptorProcs);
	if (err) goto returnError;

	err = descriptorProcs->Make(&descriptor);
	if (err) goto returnError;

	err = descriptorProcs->PutInteger(
		descriptor,
		keyChannels,
		gParams->channelMask
	);

	if (err) goto returnError;

	err = descriptorProcs->PutBoolean(descriptor, 
		                              keyIgnoreSelection, 
									  gParams->ignoreSelection);
	if (err) goto returnError;

	err = registryProcs->Register(plugInUniqueID, descriptor, true);
	if (err) goto returnError;

returnError:
	if (descriptor != NULL)
		descriptorProcs->Free(descriptor);
	if (registryProcs != NULL)
		basicSuite->ReleaseSuite(kPSDescriptorRegistrySuite, 
		                         kPSDescriptorRegistrySuiteVersion);
	if (descriptorProcs != NULL)
		basicSuite->ReleaseSuite(kPSActionDescriptorSuite, 
		                         kPSActionDescriptorSuiteVersion);
	return err;
}

// end ChannelSwapperRegistry.cpp
