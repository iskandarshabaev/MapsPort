//
//  file_data.hpp
//  MapsPort
//
//  Created by Iskandar on 15.03.16.
//  Copyright © 2016 Iskandar. All rights reserved.
//

#ifndef file_data_hpp
#define file_data_hpp

#include <stdio.h>
class TFileData{
public:
    long data_length;
    void* data;
    void* file_handle;
};
#endif /* file_data_hpp */
