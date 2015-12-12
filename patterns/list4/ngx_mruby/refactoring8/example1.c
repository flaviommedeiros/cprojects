static ngx_command_t  ndk_http_commands[] = {
#if (NDK_UPSTREAM_LIST)
#define NDK_UPSTREAM_LIST_CMDS 1
#include  <ndk_upstream_list.h>
#undef  NDK_UPSTREAM_LIST_CMDS
#endif
    ngx_null_command
};
