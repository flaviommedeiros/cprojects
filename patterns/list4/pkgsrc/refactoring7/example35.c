return value of malloc

--- metamail/shared.c~	1993-05-16 18:19:32.000000000 +0000
+++ metamail/shared.c
@@ -1,4 +1,6 @@
 #include <stdio.h>
+#include <stdlib.h>
+#include <string.h>
 #include <ctype.h>
 #include <config.h>
 #ifdef SYSV
@@ -6,7 +8,6 @@
 #include <sys/utsname.h>
 #endif
 
-extern char *malloc();
