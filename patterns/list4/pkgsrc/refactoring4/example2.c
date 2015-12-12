#ifdef HAVE_LIBLOGGING_STDLOG
if defined(OS_SOLARIS) || defined(OS_BSD)
 #	include <errno.h>
 #else
 #	include <sys/errno.h>
@@ -87,7 +87,7 @@ void rsyslogdDoDie(int sig);
