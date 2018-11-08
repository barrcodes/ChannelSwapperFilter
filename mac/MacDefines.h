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

#ifndef BOOL
typedef signed char BOOL;
#endif

#ifndef DECLARE_HANDLE
#define DECLARE_HANDLE(name) struct name##__{int unused;}; typedef struct name##__ *name
#endif

#ifndef  HWND
DECLARE_HANDLE(HWND);
#endif

#ifndef UINT
typedef unsigned int UINT;
#endif

#ifndef WPARAM
typedef unsigned int WPARAM;
#endif

#ifndef LPARAM
typedef long LPARAM;
#endif

#endif /* MacDefines_h */
