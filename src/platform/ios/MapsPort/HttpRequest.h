//
//  HttpRequest.h
//  MapsPort
//
//  Created by Iskandar on 11.03.16.
//  Copyright © 2016 Iskandar. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface HttpRequest : NSObject

-(NSData*)send:(int) x :(int) y :(int) z;

@end
