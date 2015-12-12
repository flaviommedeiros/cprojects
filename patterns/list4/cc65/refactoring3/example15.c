switch (cmd) {
        default: puts("internal error"); return;
        case CMD_NOTHING: return;
        case CMD_INVALID: puts("invalid command"); return;
        case CMD_HELP: cmd_help(); return;
        case CMD_QUIT: terminate = 1; return;
        case CMD_LS: cmd_ls(); return;
        case CMD_RM: cmd_rm(); return;
#ifdef HAVE_SUBDIRS
        case CMD_CHDIR: cmd_chdir(); return;
        case CMD_MKDIR: cmd_mkdir(); return;
        case CMD_RMDIR: cmd_rmdir(); return;
        case CMD_PWD: cmd_pwd(); return;
#endif
        case CMD_RENAME: cmd_rename(); return;
        case CMD_COPY: cmd_copy(); return;
#ifdef __ATARI__
        case CMD_CLS: cmd_cls(); return;
#endif
        case CMD_VERBOSE: cmd_verbose(); return;
    }
