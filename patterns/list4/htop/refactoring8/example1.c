ProcessPidColumn Process_pidColumns[] = {
   { .id = PID, .label = "PID" },
   { .id = PPID, .label = "PPID" },
   #ifdef HAVE_OPENVZ
   { .id = VPID, .label = "VPID" },
   #endif
   { .id = TPGID, .label = "TPGID" },
   { .id = TGID, .label = "TGID" },
   { .id = PGRP, .label = "PGRP" },
   { .id = SESSION, .label = "SESN" },
   { .id = OOM, .label = "OOM" },
   { .id = 0, .label = NULL },
};
