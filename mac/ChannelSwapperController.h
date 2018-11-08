// ADOBE SYSTEMS INCORPORATED
// Copyright  2009 Adobe Systems Incorporated
// All Rights Reserved
//
// NOTICE:  Adobe permits you to use, modify, and distribute this 
// file in accordance with the terms of the Adobe license agreement
// accompanying it.  If you have received this file from a source
// other than Adobe, then your use, modification, or distribution
// of it requires the prior written permission of Adobe.
//-------------------------------------------------------------------------------

#import <Cocoa/Cocoa.h>
#include "ChannelSwapper.h"

OSStatus initializeCocoaChannelSwapper(void);
OSStatus orderWindowFrontChannelSwapper(void);

/* Make sure this is unique to you and everyone you might encounter, search for
"Preventing Name Conflicts" or use this link
http://developer.apple.com/mac/library/documentation/UserExperience/Conceptual/PreferencePanes/Tasks/Conflicts.html
*/

// sub class the dialog so all things work
@interface ChannelSwapperController : NSObject 
{
    id channelSwapperWindow;
    IBOutlet NSButton *channelR;
    IBOutlet NSButton *channelG;
    IBOutlet NSButton *channelB;
    IBOutlet NSButton *channelA;
	id proxyPreview;
	
}
- (void) updateProxy;
- (void) updateCursor;
- (int) showWindow;
+ (ChannelSwapperController *) channelSwapperController;
@end

// end ChannelSwapperController.h
