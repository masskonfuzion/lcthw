#ifndef __dbg_h__
#define __dbh_h__

#include <stdio.h>
#include <errno.h>
#include <string.h>

#ifdef NDEBUG
// if NDEBUG is defined, then the debug macro does nothing (so NDEBUG means no-debug)
#define debug(M, ...)
#else
// if NDEBUG is NOT defined, then the debug macro outputs stuff
#define debug(M, ...) fprintf(stderr, "DEBUG %s:%d: " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)
#endif

/*
__FILE__ is a CPP (C Pre-Processor) pre-defined macro to display the current input file
__LINE__ is a CPP pre-defined macro to display the input line number
NOTE:  The ellipsis ("...") means variable # of parameters

*/

#define clean_errno() (errno == 0 ? "None" : strerror(errno))

#define log_err(M, ...) fprintf(stderr, "[ERROR] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)

#define log_warn(M, ...) fprintf(stderr, "[WARN] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__, clean_errno(), ##__VA_ARGS__)

#define log_info(M, ...) fprintf(stderr, "[INFO] (%s:%d) " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)

#define check(A, M, ...) if(!(A)) { log_err(M, ##__VA_ARGS__); errno=0; goto error; }

#define sentinel(M, ...) {log_err(M, ##__VA_ARGS__); errno=0; goto error; }

#define check_mem(A) check((A), "Out of memory.")

#define check_debug(A, M, ...) if (!(A)) { debug(M, ##__VA_ARGS__); errno=0; goto error; }

#endif
