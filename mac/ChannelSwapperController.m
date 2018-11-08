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

#import "ChannelSwapperController.h"
#import "ChannelSwapperProxyView.h"

ChannelSwapperController *gChannelSwapperController = NULL;

// controller for the entire dialog
@implementation ChannelSwapperController

+ (ChannelSwapperController *) channelSwapperController 
{
    return gChannelSwapperController;
}

- (id) init 
{
    self = [super init];
    
    NSBundle * plugin = [NSBundle bundleForClass:[self class]];

    if (![plugin loadNibNamed:@"ChannelSwapperDialog"
                 owner:self
                 topLevelObjects:nil])
	{
        NSLog(@"ChannelSwapper failed to load ChannelSwapperDialog xib");
    }
    
	gChannelSwapperController = self;

    bool rSelected = TestMaskBit(gParams->channelMask, 0);
    bool gSelected = TestMaskBit(gParams->channelMask, 1);
    bool bSelected = TestMaskBit(gParams->channelMask, 2);
    bool aSelected = TestMaskBit(gParams->channelMask, 3);
    [channelR setState:rSelected];
    [channelG setState:gSelected];
    [channelB setState:bSelected];
    [channelA setState:aSelected];

	NSLog(@"ChannelSwapper Trying to set setNeedsDisplay");

	[proxyPreview setNeedsDisplay:YES];

	NSLog(@"ChannelSwapper Done with init");

    return self;
}

- (int) showWindow 
{
    [channelSwapperWindow makeKeyAndOrderFront:nil];
	int b = [[NSApplication sharedApplication] runModalForWindow:channelSwapperWindow];
	[channelSwapperWindow orderOut:self];
	return b;
}

- (IBAction) okPressed: (id) sender
{
	[NSApp stopModalWithCode:1];
	NSLog(@"ChannelSwapper after nsapp stopmodal");
}

- (IBAction) cancelPressed: (id) sender 
{
	NSLog(@"ChannelSwapper cancel pressed");
	[NSApp stopModalWithCode:0];
	NSLog(@"ChannelSwapper after nsapp abortmodal");
}

- (IBAction)channelRPressed:(id)sender
{
    NSLog(@"Channel R pressed");
    NSControlStateValue state = channelR.state;
    SetMaskBit(gParams->channelMask, 0, state == NSControlStateValueOn);
    [gChannelSwapperController updateProxy];
}

- (IBAction)channelGPressed:(id)sender
{
    NSLog(@"Channel G pressed");
    NSControlStateValue state = channelG.state;
    SetMaskBit(gParams->channelMask, 1, state == NSControlStateValueOn);
    [gChannelSwapperController updateProxy];
}

- (IBAction)channelBPressed:(id)sender
{
    NSLog(@"Channel B pressed");
    NSControlStateValue state = channelB.state;
    SetMaskBit(gParams->channelMask, 2, state == NSControlStateValueOn);
    [gChannelSwapperController updateProxy];
}

- (IBAction)channelAPressed:(id)sender
{
    NSLog(@"Channel A pressed");
    NSControlStateValue state = channelA.state;
    SetMaskBit(gParams->channelMask, 3, state == NSControlStateValueOn);
    [gChannelSwapperController updateProxy];
}

- (void) updateProxy
{
	[proxyPreview setNeedsDisplay:YES];
}

- (void) updateCursor
{
	NSLog(@"ChannelSwapper Trying to updateCursor");
	sPSUIHooks->SetCursor(kPICursorArrow);
	NSLog(@"ChannelSwapper Seemed to updateCursor");
}

@end

/* Carbon entry point and C-callable wrapper functions*/
OSStatus initializeCocoaChannelSwapper(void) 
{
	[[ChannelSwapperController alloc] init];
    return noErr;
}

OSStatus orderWindowFrontChannelSwapper(void) 
{
    int okPressed = [[ChannelSwapperController channelSwapperController] showWindow];
    return okPressed;
}

// end ChannelSwapperController.m
