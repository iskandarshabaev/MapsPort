//
//  matrices.c
//  MapsPort
//
//  Created by Iskandar on 04.06.16.
//  Copyright © 2016 Iskandar. All rights reserved.
//

#include <stdio.h>
#include <math.h>

// Pre-calculated value of PI / 180.
#define kPI180     0.017453

// Pre-calculated value of 180 / PI.
#define k180PI    57.295780

// Converts degrees to radians.
#define degreesToRadians(x) (x * kPI180)

// Converts radians to degrees.
#define radiansToDegrees(x) (x * k180PI)

typedef double mat4[16];

static inline void matrixIdentity(mat4 m)
{
    m[0] = m[5] = m[10] = m[15] = 1.0;
    m[1] = m[2] = m[3] = m[4] = 0.0;
    m[6] = m[7] = m[8] = m[9] = 0.0;
    m[11] = m[12] = m[13] = m[14] = 0.0;
}

static inline void matrixTranslate(float x, float y, float z, mat4 matrix)
{
    matrixIdentity(matrix);
    
    // Translate slots.
    matrix[12] = x;
    matrix[13] = y;
    matrix[14] = z;
}

static inline void matrixScale(float sx, float sy, float sz, mat4 matrix)
{
    matrixIdentity(matrix);
    
    // Scale slots.
    matrix[0] = sx;
    matrix[5] = sy;
    matrix[10] = sz;
}

static inline void matrixRotateX(float degrees, mat4 matrix)
{
    float radians = degreesToRadians(degrees);
    
    matrixIdentity(matrix);
    
    // Rotate X formula.
    matrix[5] = cos(radians);
    matrix[6] = -sin(radians);
    matrix[9] = -matrix[6];
    matrix[10] = matrix[5];
}

static inline void matrixRotateY(float degrees, mat4 matrix)
{
    float radians = degreesToRadians(degrees);
    
    matrixIdentity(matrix);
    
    // Rotate Y formula.
    matrix[0] = cos(radians);
    matrix[2] = sin(radians);
    matrix[8] = -matrix[2];
    matrix[10] = matrix[0];
}

static inline void matrixRotateZ(float degrees, mat4 matrix)
{
    float radians = degreesToRadians(degrees);
    
    matrixIdentity(matrix);
    
    // Rotate Z formula.
    matrix[0] = cos(radians);
    matrix[1] = sin(radians);
    matrix[4] = -matrix[1];
    matrix[5] = matrix[0];
}

static inline void matrixMultiply(mat4 m1, mat4 m2, mat4 result)
{
    // Fisrt Column
    result[0] = m1[0]*m2[0] + m1[4]*m2[1] + m1[8]*m2[2] + m1[12]*m2[3];
    result[1] = m1[1]*m2[0] + m1[5]*m2[1] + m1[9]*m2[2] + m1[13]*m2[3];
    result[2] = m1[2]*m2[0] + m1[6]*m2[1] + m1[10]*m2[2] + m1[14]*m2[3];
    result[3] = m1[3]*m2[0] + m1[7]*m2[1] + m1[11]*m2[2] + m1[15]*m2[3];
    
    // Second Column
    result[4] = m1[0]*m2[4] + m1[4]*m2[5] + m1[8]*m2[6] + m1[12]*m2[7];
    result[5] = m1[1]*m2[4] + m1[5]*m2[5] + m1[9]*m2[6] + m1[13]*m2[7];
    result[6] = m1[2]*m2[4] + m1[6]*m2[5] + m1[10]*m2[6] + m1[14]*m2[7];
    result[7] = m1[3]*m2[4] + m1[7]*m2[5] + m1[11]*m2[6] + m1[15]*m2[7];
    
    // Third Column
    result[8] = m1[0]*m2[8] + m1[4]*m2[9] + m1[8]*m2[10] + m1[12]*m2[11];
    result[9] = m1[1]*m2[8] + m1[5]*m2[9] + m1[9]*m2[10] + m1[13]*m2[11];
    result[10] = m1[2]*m2[8] + m1[6]*m2[9] + m1[10]*m2[10] + m1[14]*m2[11];
    result[11] = m1[3]*m2[8] + m1[7]*m2[9] + m1[11]*m2[10] + m1[15]*m2[11];
    
    // Fourth Column
    result[12] = m1[0]*m2[12] + m1[4]*m2[13] + m1[8]*m2[14] + m1[12]*m2[15];
    result[13] = m1[1]*m2[12] + m1[5]*m2[13] + m1[9]*m2[14] + m1[13]*m2[15];
    result[14] = m1[2]*m2[12] + m1[6]*m2[13] + m1[10]*m2[14] + m1[14]*m2[15];
    result[15] = m1[3]*m2[12] + m1[7]*m2[13] + m1[11]*m2[14] + m1[15]*m2[15];
}