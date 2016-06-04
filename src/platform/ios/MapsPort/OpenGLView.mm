#import "OpenGLView.h"


@implementation OpenGLView

+ (Class)layerClass {
    return [CAEAGLLayer class];
}

MapView *mapview;
- (IBAction)zoomIn:(id)sender {
    mapview->zoomIn();
}
- (IBAction)zoomOut:(id)sender {
    mapview->zoomOut();
}

-(void)setupLayer{
    _eaglLayer = (CAEAGLLayer*) self.layer;
    _eaglLayer.opaque = YES;
}

- (void)setupContext {
    EAGLRenderingAPI api = kEAGLRenderingAPIOpenGLES2;
    _context = [[EAGLContext alloc] initWithAPI:api];
    if (!_context) {
        NSLog(@"Failed to initialize OpenGLES 2.0 context");
        exit(1);
    }
    
    
    if (![EAGLContext setCurrentContext:_context]) {
        NSLog(@"Failed to set current OpenGL context");
        exit(1);
    }
    mapview = new MapView();
    mapview->on_surface_created();
    
    glGenRenderbuffers(1, &_colorRenderBuffer);
    glBindRenderbuffer(GL_RENDERBUFFER, _colorRenderBuffer);
    
    GLuint framebuffer;
    glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, _colorRenderBuffer);
}

- (void)render:(CADisplayLink*)displayLink {
    mapview->on_render();
    [_context presentRenderbuffer:GL_RENDERBUFFER];
}

- (void)setupDisplayLink {
    CADisplayLink* displayLink = [CADisplayLink displayLinkWithTarget:self selector:@selector(render:)];
    [displayLink addToRunLoop:[NSRunLoop currentRunLoop] forMode:NSDefaultRunLoopMode];
}

- (id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    if (self) {
        [self commonInit];
    }
    return self;
}

- (id)initWithCoder:(NSCoder*)coder
{
    if ((self = [super initWithCoder:coder])) {
        [self commonInit];
    }
    return self;
}

- (void)commonInit
{
    [self setupLayer];
    [self setupContext];
    [self setupDisplayLink];
    self.userInteractionEnabled = true;
    [self setContentScaleFactor:[[UIScreen mainScreen] scale]];
    CGFloat screenScale = [[UIScreen mainScreen] scale];
    
    CGRect screenBounds = [[UIScreen mainScreen] bounds];
    CGSize screenSize = CGSizeMake(screenBounds.size.width, screenBounds.size.height);
    
    mapview->setScale(screenScale);
    [_context renderbufferStorage:GL_RENDERBUFFER fromDrawable:_eaglLayer];
    mapview->on_surface_changed(screenSize.width, screenSize.height);
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(handleDidChangeStatusBarOrientationNotification:)
                                                 name:UIApplicationDidChangeStatusBarOrientationNotification
                                               object:nil];

}


- (void)dealloc
{
    //[_context release];
    //_context = nil;
    //[super dealloc];
}


- (void)handleDidChangeStatusBarOrientationNotification:(NSNotification *)notification;
{
    CGRect screenBounds = [[UIScreen mainScreen] bounds];
    [self setFrame:screenBounds];
    [self setContentScaleFactor:[[UIScreen mainScreen] scale]];
    CGFloat screenScale = [[UIScreen mainScreen] scale];
    CGSize screenSize = CGSizeMake(screenBounds.size.width, screenBounds.size.height);
    mapview->setScale(screenScale);
    mapview->on_surface_changed(screenSize.width, screenSize.height);
    _eaglLayer.frame = screenBounds;
    [_context renderbufferStorage:GL_RENDERBUFFER fromDrawable:_eaglLayer];
}



static CGPoint getNormalizedPoint(UIView* view, CGPoint locationInView)
{
    //const float normalizedX = locationInView.x/256;
    //const float normalizedY = -((locationInView.y)/256);
    CGFloat screenScale = [[UIScreen mainScreen] scale];
    const float normalizedX = (locationInView.x / 256)*2*screenScale;
    const float normalizedY = -((locationInView.y / 256))*2*screenScale;
    return CGPointMake(normalizedX, normalizedY);
}




- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event
{
    [super touchesMoved:touches withEvent:event];
    UITouch* touchEvent = [touches anyObject];
    CGPoint locationInView = [touchEvent locationInView:self];
    CGPoint normalizedPoint = getNormalizedPoint(self, locationInView);
    mapview->on_touch_press(normalizedPoint.x, normalizedPoint.y);
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event
{
    [super touchesMoved:touches withEvent:event];
    UITouch* touchEvent = [touches anyObject];
    CGPoint locationInView = [touchEvent locationInView:self];
    CGPoint normalizedPoint = getNormalizedPoint(self, locationInView);
    mapview->on_touch_drag(normalizedPoint.x, normalizedPoint.y);
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
    [super touchesMoved:touches withEvent:event];
    UITouch* touchEvent = [touches anyObject];
    CGPoint locationInView = [touchEvent locationInView:self];
    CGPoint normalizedPoint = getNormalizedPoint(self, locationInView);
    mapview->on_touches_ended(normalizedPoint.x, normalizedPoint.y);
}

- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event
{
    [super touchesCancelled:touches withEvent:event];
}

@end
