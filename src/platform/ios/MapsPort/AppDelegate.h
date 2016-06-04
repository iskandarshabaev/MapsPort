#import <UIKit/UIKit.h>
#import "OpenGLView.h"



@interface AppDelegate : UIResponder <UIApplicationDelegate>{
    // Inside @interface
    OpenGLView* _glView;
}

// After @interface
@property (nonatomic, retain) IBOutlet OpenGLView *glView;

@property (strong, nonatomic) UIWindow *window;


@end

