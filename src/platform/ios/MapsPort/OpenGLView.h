//
//  GameViewController.h
//  MapsPort
//
//  Created by Iskandar on 06.03.16.
//  Copyright © 2016 Iskandar. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>
#include <OpenGLES/ES2/gl.h>
#include <OpenGLES/ES2/glext.h>

#if __cplusplus
#include "mapview.hpp"
#endif

@interface OpenGLView : UIView {
    CAEAGLLayer* _eaglLayer;
    EAGLContext* _context;
    GLuint _colorRenderBuffer;
}

+ (Class)layerClass;

- (void)setupLayer;

- (void)setupContext;

- (void)render;

- (void)handleDidChangeStatusBarOrientationNotification:(NSNotification *)notification;
/*
- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event;
- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event;
- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event;
- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event;
*/
@end