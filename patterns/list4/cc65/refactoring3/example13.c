switch (c) {

            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
                ActivateFrame (c - '1', 0);
                break;

            case '?':
#ifdef CH_F1
            case CH_F1:
#endif
                HelpHandler ();
                break;

            case 'u':
#ifdef CH_F3
            case CH_F3:
#endif
                /* Go until return */
                SetRTSBreak ();
                done = 1;
                break;

            case 'h':
#ifdef CH_F4
            case CH_F4:
#endif
                /* Go to cursor, only possible if cursor not at current PC */
                if (AsmAddr != brk_pc) {
                    DbgSetTmpBreak (AsmAddr);
                    done = 1;
                }
                break;

            case ' ':
#ifdef CH_F7
            case CH_F7:
#endif
                SingleStep (1);
                if (DbgTmpBreaksOk ()) {
                    /* Could set breakpoints */
                    done = 1;
                }
                break;

            case '\n':
#ifdef CH_F8
            case CH_F8:
#endif
                SingleStep (0);
                if (DbgTmpBreaksOk ()) {
                    /* Could set breakpoints */
                    done = 1;
                }
                break;

            case 'c':
            case 0:
                done = 1;
                break;

            case 's':
                /* Skip instruction */
                brk_pc += DbgDisAsmLen (brk_pc);
                InitAsm ();
                break;

            case 'r':
                /* Redraw screen */
                Redraw (ActiveFrame);
                break;

            case 'q':
                /* Quit program */
                clrscr ();
                exit (1);

        }
