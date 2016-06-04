//
//  PlatformFileSystemTileLoader.m
//  MapsPort
//
//  Created by Iskandar on 29.05.16.
//  Copyright © 2016 Iskandar. All rights reserved.
//

#import "PlatformFileSystemTileWriter.h"
#import <Foundation/Foundation.h>

bool PlatformFileSystemTileWriter:: writeTile(int z, int x, int y, void* data, long length){
    
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString *documentsDirectory = [paths objectAtIndex:0];
    
    NSString *file = [documentsDirectory stringByAppendingPathComponent:[NSString stringWithFormat:@"tiles/osm/%d/%d",  z, x]];
    
    
    
    
    NSFileManager *manager = [NSFileManager defaultManager];

    
    [manager createDirectoryAtPath:file withIntermediateDirectories:YES attributes:nil error:nil];
    
    NSData *myData = [[NSData alloc] initWithBytes:data length:length];
    [myData writeToFile:[file stringByAppendingString:[NSString stringWithFormat:@"/%d.png",y]] atomically:YES];
    

    //NSMutableData *d = [NSMutableData dataWithLength:sizeof(float)];
    //[d appendBytes:&data length:length];
    //[d writeToFile:[file stringByAppendingString:[NSString stringWithFormat:@"/%d.png",y]] atomically:YES];
    
    return true;
}