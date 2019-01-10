/* This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 */

#ifndef DCMIMAGEAPI_H
#define DCMIMAGEAPI_H

#ifdef _MSC_VER
    #ifdef dcmimage_EXPORTS
        #define DCM_IMAGE_API __declspec(dllexport)
    #else
        #define DCM_IMAGE_API __declspec(dllimport)
    #endif
#else
    #define DCM_IMAGE_API
#endif // _MSC_VER

#endif // DCMIMAGEAPI_H
