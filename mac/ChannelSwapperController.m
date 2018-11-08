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

/* Make sure this is unique to you and everyone you might encounter, search for
"Preventing Name Conflicts" or use this link
http://developer.apple.com/mac/library/documentation/UserExperience/Conceptual/PreferencePanes/Tasks/Conflicts.html
*/

// get the current value and force an update
//@implementation ChannelSwapperTextField
//
//- (void)keyUp:(NSEvent *)theEvent
//{
//    NSLog(@"ChannelSwapper start keyUp, %d", [theEvent keyCode]);
//    [gChannelSwapperController updateAmountValue];
//    [gChannelSwapperController updateProxy];
//    NSLog(@"ChannelSwapper end keyUp, %d", gParams->percent);
//}
//
//@end

/* Make sure this is unique to you and everyone you might encounter, search for
"Preventing Name Conflicts" or use this link
http://developer.apple.com/mac/library/documentation/UserExperience/Conceptual/PreferencePanes/Tasks/Conflicts.html
*/

// controller for the entire dialog
@implementation ChannelSwapperController

+ (ChannelSwapperController *) channelSwapperController 
{
    return gChannelSwapperController;
}


- (id) init 
{
    self = [super init];

//    amountValue = [NSString stringWithFormat:@"%d", gParams->percent];
    
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

//    [textField setStringValue:amountValue];
//
//    switch (gParams->disposition)
//    {
//        case 0: // clear
//            [dispositionClear setState:true];
//            [dispositionCool setState:false];
//            [dispositionHot setState:false];
//            [dispositionSick setState:false];
//            break;
//        case 2: // hot
//            [dispositionClear setState:false];
//            [dispositionCool setState:false];
//            [dispositionHot setState:true];
//            [dispositionSick setState:false];
//            break;
//        case 3: // sick
//            [dispositionClear setState:false];
//            [dispositionCool setState:false];
//            [dispositionHot setState:false];
//            [dispositionSick setState:true];
//            break;
//        default:
//        case 1: // cool
//            [dispositionClear setState:false];
//            [dispositionCool setState:true];
//            [dispositionHot setState:false];
//            [dispositionSick setState:false];
//        break;
//    }
	
//    NSLog(@"ChannelSwapper Trying to set initial disposition");

//    [(ChannelSwapperProxyView*)proxyPreview setDispositionColor:gParams->disposition];

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

//- (NSString *) getAmountValue 
//{
//    return amountValue;
//}

//- (void) updateAmountValue
//{
//    amountValue = [textField stringValue];
//    NSLog(@"ChannelSwapper updateAmountValue channelSwapper %@", amountValue);
//    gParams->percent = [amountValue intValue];
//    NSLog(@"ChannelSwapper Percent after updateAmountValue: %d", gParams->percent);
//}

- (IBAction) okPressed: (id) sender 
{
//    amountValue = [textField stringValue];
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
    //bool selected = FlipMaskBit(gParams->channelMask, 0);
    //[channelR setState:selected];
    [gChannelSwapperController updateProxy];
}

- (IBAction)channelGPressed:(id)sender
{
    NSLog(@"Channel G pressed");
    NSControlStateValue state = channelG.state;
    SetMaskBit(gParams->channelMask, 1, state == NSControlStateValueOn);
    //bool selected = FlipMaskBit(gParams->channelMask, 1);
    //[channelG setState:selected];
    [gChannelSwapperController updateProxy];
}

- (IBAction)channelBPressed:(id)sender
{
    NSLog(@"Channel B pressed");
    NSControlStateValue state = channelB.state;
    SetMaskBit(gParams->channelMask, 2, state == NSControlStateValueOn);
    //bool selected = FlipMaskBit(gParams->channelMask, 2);
    //[channelB setState:selected];
    [gChannelSwapperController updateProxy];
}

- (IBAction)channelAPressed:(id)sender
{
    NSLog(@"Channel A pressed");
    NSControlStateValue state = channelA.state;
    SetMaskBit(gParams->channelMask, 3, state == NSControlStateValueOn);
    //bool selected = FlipMaskBit(gParams->channelMask, 3);
    //[channelA setState:selected];
    [gChannelSwapperController updateProxy];
}

//- (IBAction) clearPressed: (id) sender
//{
//    NSLog(@"ChannelSwapper clear pressed");
////    gParams->disposition = 0;
//    [gChannelSwapperController updateProxy];
//}
//
//- (IBAction) coolPressed: (id) sender
//{
//    NSLog(@"ChannelSwapper cool pressed");
////    gParams->disposition = 1;
//    [gChannelSwapperController updateProxy];
//}
//
//- (IBAction) hotPressed: (id) sender
//{
//    NSLog(@"ChannelSwapper hot pressed");
//    gParams->disposition = 2;
//    [gChannelSwapperController updateProxy];
//}
//
//- (IBAction) sickPressed: (id) sender
//{
//    NSLog(@"ChannelSwapper sick pressed");
//    gParams->disposition = 3;
//    [gChannelSwapperController updateProxy];
//}

- (void) updateProxy 
{
//    CopyColor(gData->color, gData->colorArray[gParams->disposition]);
//    [(ChannelSwapperProxyView*)proxyPreview setDispositionColor:gParams->disposition];
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
