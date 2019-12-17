#ifndef DECLSPEC_HIDDEN
    #define DECLSPEC_HIDDEN
#endif
#ifndef __WINE_ALLOC_SIZE
    #define __WINE_ALLOC_SIZE(x)
#endif
#ifndef ERR
    #define ERR(arg, ...)
#endif
#ifndef WARN
    #define WARN(arg, ...)
#endif
#ifndef TRACE
    #define TRACE(arg, ...)
#endif
#ifndef ARRAY_SIZE
    #define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))
#endif
