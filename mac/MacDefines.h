//
//  MacDefines.h
//  channelSwapper
//
//  Created by ClearWave Interactive on 11/8/18.
//

#ifndef MacDefines_h
    #define MacDefines_h

    /*
     * The following block of defines were required because the types were defined in winnt.h and windef.h
     * (Windows header files). I can't for the life of me figure out why, because the documentation says
     * this code was designed to run on Mac first... Just another gotcha in this rabbit hole of hell.
     */

    #if (defined(macintosh) || defined(__POWERPC__) || defined(__powerc)) || defined(__APPLE_CC__)
        #define __IS_MAC            1
    #endif

    #ifdef __IS_MAC
        #define DECLARE_HANDLE(name) struct name##__{int unused;}; typedef struct name##__ *name
        DECLARE_HANDLE(HWND);
        typedef signed char BOOL;
        typedef unsigned int UINT;
        typedef unsigned int WPARAM;
        typedef long LPARAM;
    #endif // end __IS_MAC
#endif /* MacDefines_h */
