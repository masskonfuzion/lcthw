#ifndef _shell_h
#define _shell_h

#define MAX_COMMAND_ARGS 100

#include <apr_thread_proc.h>


typedef struct Shell{
	const char *dir;
	const char *exe;

	apr_procattr_t *attr;
	apr_proc_t proc;
	apr_exit_why_e exit_why;
	int exit_code;

	const char *args[MAX_COMMAND_ARGS];
} Shell;


// Declare Shell_run()
int Shell_run(apr_pool_t *p, Shell *cmd);
// Declare Shell_exec() that takes a variable # of arguments
int Shell_exec(Shell cmd, ...);

// "extern" indicates that other .c files can access the variables defined here
extern Shell CLEANUP_SH;
extern Shell GIT_SH;
extern Shell TAR_SH;
extern Shell CURL_SH;
extern Shell CONFIGURE_SH;
extern Shell MAKE_SH;
extern Shell INSTALL_SH;

#endif
