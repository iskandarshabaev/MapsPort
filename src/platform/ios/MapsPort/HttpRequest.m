//
//  HttpRequest.m
//  MapsPort
//
//  Created by Iskandar on 11.03.16.
//  Copyright © 2016 Iskandar. All rights reserved.
//

#import "HttpRequest.h"
#import <AFURLSessionManager.h>

@implementation HttpRequest

-(NSData*)send:(int) x : (int) y : (int) z{
    
    NSURLSessionConfiguration *configuration = [NSURLSessionConfiguration defaultSessionConfiguration];
    AFURLSessionManager *manager = [[AFURLSessionManager alloc] initWithSessionConfiguration:configuration];
    
    NSString *path = [NSString stringWithFormat:@"http://c.tile.openstreetmap.org/%d/%d/%d.png",-z,x,y];
    
    NSURL *URL = [NSURL URLWithString:path];
    NSURLRequest *request = [NSURLRequest requestWithURL:URL];
    
    
    NSURLRequest * urlRequest = [NSURLRequest requestWithURL:URL];
    NSURLResponse * response = nil;
    NSError * error = nil;
    NSData * data = [NSURLConnection sendSynchronousRequest:urlRequest returningResponse:&response error:&error];
    NSURL *documentsDirectoryURL = [[NSFileManager defaultManager] URLForDirectory:NSDocumentDirectory inDomain:NSUserDomainMask appropriateForURL:nil create:YES error:nil];
    documentsDirectoryURL = [documentsDirectoryURL URLByAppendingPathComponent:[NSString stringWithFormat:@"tiles/osm/%d/%d/", -z,x]];
    if (![[NSFileManager defaultManager] fileExistsAtPath:[documentsDirectoryURL path]])
        [[NSFileManager defaultManager] createDirectoryAtURL:documentsDirectoryURL withIntermediateDirectories:YES attributes:nil error:&error];

    documentsDirectoryURL = [documentsDirectoryURL URLByAppendingPathComponent:[NSString stringWithFormat:@"%d.png", y]];
    [data writeToURL: documentsDirectoryURL atomically:YES];
    return data;
    /*
    NSURLSessionDownloadTask *downloadTask = [manager downloadTaskWithRequest:request progress:nil destination:^NSURL *(NSURL *targetPath, NSURLResponse *response) {
        NSURL *documentsDirectoryURL = [[NSFileManager defaultManager] URLForDirectory:NSDocumentDirectory inDomain:NSUserDomainMask appropriateForURL:nil create:YES error:nil];
        documentsDirectoryURL = [documentsDirectoryURL URLByAppendingPathComponent:[NSString stringWithFormat:@"tiles/osm/%d/%d/", -z,x]];
        NSError *error = nil;
        if (![[NSFileManager defaultManager] fileExistsAtPath:[documentsDirectoryURL path]])
            [[NSFileManager defaultManager] createDirectoryAtURL:documentsDirectoryURL withIntermediateDirectories:YES attributes:nil error:&error];
        return [documentsDirectoryURL URLByAppendingPathComponent:[response suggestedFilename]];
    } completionHandler:^(NSURLResponse *response, NSURL *filePath, NSError *error) {
        NSLog(@"File downloaded to: %@", filePath);
    }];
    [downloadTask resume];
     */
}

@end
