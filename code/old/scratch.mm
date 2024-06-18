#import <Cocoa/Cocoa.h>
#import <iostream>

@interface AppDelegate : NSObject <NSApplicationDelegate>
- (void)buttonClicked:(id)sender;
@end

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

@implementation AppDelegate
- (BOOL)applicationShouldTerminateAfterLastWindowClosed:
    (NSApplication *)sender {
  return YES;
}

- (void)buttonClicked:(id)sender {
  NSLog(@"Button was clicked");
}
@end

@interface CustomView : NSView
@end

@implementation CustomView
- (void)drawRect:(NSRect)dirtyRect {
  [[NSColor redColor] setFill];
  NSRectFill(dirtyRect);
}
@end

int main(int argc, const char *argv[]) {
  std::cout << "print test" << std::endl;
  @autoreleasepool {
    NSApplication *app = [NSApplication sharedApplication];

    AppDelegate *delegate = [[AppDelegate alloc] init];
    [app setDelegate:delegate];

    NSRect frame = NSMakeRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    NSUInteger style = NSWindowStyleMaskTitled | NSWindowStyleMaskClosable |
                       NSWindowStyleMaskResizable;
    NSWindow *window =
        [[NSWindow alloc] initWithContentRect:frame
                                    styleMask:style
                                      backing:NSBackingStoreBuffered
                                        defer:NO];
    [window setTitle:@"This is gam"];
    [window makeKeyAndOrderFront:nil];

    // Create a label (NSTextField)
    NSTextField *label = [[NSTextField alloc]
        initWithFrame:NSMakeRect(20, WINDOW_HEIGHT - 50, 200, 40)];
    [label setStringValue:@"Hello, Cocoa!"];
    [label setBezeled:NO];
    [label setDrawsBackground:NO];
    [label setEditable:NO];
    [label setSelectable:NO];
    [[window contentView] addSubview:label];

    // Create a button (NSButton)
    NSButton *button = [[NSButton alloc] initWithFrame:NSMakeRect(20, WINDOW_HEIGHT - 100, 100, 40)];
    [button setTitle:@"Click Me"];
    [button setButtonType:NSButtonTypeMomentaryPushIn];
    [button setTarget:delegate];
    [button setAction:@selector(buttonClicked:)];
    [[window contentView] addSubview:button];

    // Create a custom view with a smaller frame
    CustomView *customView = [[CustomView alloc] initWithFrame:NSMakeRect(250, WINDOW_HEIGHT - 300, 200, 100)];
    [customView setWantsLayer:YES];
    [customView.layer setBackgroundColor:[[NSColor blueColor] CGColor]];
    [[window contentView] addSubview:customView];

    [app run];
  }
  return 0;
}
