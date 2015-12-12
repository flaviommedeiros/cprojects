if (text &&
#ifndef DOS_OS2_W32
        (keybd = fdopen(fileno(stderr), "r")) != NULL &&
#endif
        (textbuf = (char *)malloc((5 + 9)*75)) != NULL)
    {
        int i, valid, result;

        fprintf(stderr,
          "Enter text info (no more than 72 characters per line);\n");
        fprintf(stderr, "to skip a field, hit the <Enter> key.\n");
        /* note:  just <Enter> leaves len == 1 */

        do {
            valid = TRUE;
            p = textbuf + TEXT_TITLE_OFFSET;
            fprintf(stderr, "  Title: ");
            fflush(stderr);
            if (FGETS(p, 74, keybd) && (len = strlen(p)) > 1) {
                if (p[len-1] == '\n')
                    p[--len] = '\0';
                wpng_info.title = p;
                wpng_info.have_text |= TEXT_TITLE;
                if ((result = wpng_isvalid_latin1((uch *)p, len)) >= 0) {
                    fprintf(stderr, "    " PROGNAME " warning:  character code"
                      " %u is %sdiscouraged by the PNG\n    specification "
                      "[first occurrence was at character position #%d]\n",
                      (unsigned)p[result], (p[result] == 27)? "strongly " : "",
                      result+1);
                    fflush(stderr);
#ifdef FORBID_LATIN1_CTRL
                    wpng_info.have_text &= ~TEXT_TITLE;
                    valid = FALSE;
#else
                    if (p[result] == 27) {    /* escape character */
                        wpng_info.have_text &= ~TEXT_TITLE;
                        valid = FALSE;
                    }
#endif
                }
            }
        } while (!valid);

        do {
            valid = TRUE;
            p = textbuf + TEXT_AUTHOR_OFFSET;
            fprintf(stderr, "  Author: ");
            fflush(stderr);
            if (FGETS(p, 74, keybd) && (len = strlen(p)) > 1) {
                if (p[len-1] == '\n')
                    p[--len] = '\0';
                wpng_info.author = p;
                wpng_info.have_text |= TEXT_AUTHOR;
                if ((result = wpng_isvalid_latin1((uch *)p, len)) >= 0) {
                    fprintf(stderr, "    " PROGNAME " warning:  character code"
                      " %u is %sdiscouraged by the PNG\n    specification "
                      "[first occurrence was at character position #%d]\n",
                      (unsigned)p[result], (p[result] == 27)? "strongly " : "",
                      result+1);
                    fflush(stderr);
#ifdef FORBID_LATIN1_CTRL
                    wpng_info.have_text &= ~TEXT_AUTHOR;
                    valid = FALSE;
#else
                    if (p[result] == 27) {    /* escape character */
                        wpng_info.have_text &= ~TEXT_AUTHOR;
                        valid = FALSE;
                    }
#endif
                }
            }
        } while (!valid);

        do {
            valid = TRUE;
            p = textbuf + TEXT_DESC_OFFSET;
            fprintf(stderr, "  Description (up to 9 lines):\n");
            for (i = 1;  i < 10;  ++i) {
                fprintf(stderr, "    [%d] ", i);
                fflush(stderr);
                if (FGETS(p, 74, keybd) && (len = strlen(p)) > 1)
                    p += len;   /* now points at NULL; char before is newline */
                else
                    break;
            }
            if ((len = p - (textbuf + TEXT_DESC_OFFSET)) > 1) {
                if (p[-1] == '\n') {
                    p[-1] = '\0';
                    --len;
                }
                wpng_info.desc = textbuf + TEXT_DESC_OFFSET;
                wpng_info.have_text |= TEXT_DESC;
                p = textbuf + TEXT_DESC_OFFSET;
                if ((result = wpng_isvalid_latin1((uch *)p, len)) >= 0) {
                    fprintf(stderr, "    " PROGNAME " warning:  character code"
                      " %u is %sdiscouraged by the PNG\n    specification "
                      "[first occurrence was at character position #%d]\n",
                      (unsigned)p[result], (p[result] == 27)? "strongly " : "",
                      result+1);
                    fflush(stderr);
#ifdef FORBID_LATIN1_CTRL
                    wpng_info.have_text &= ~TEXT_DESC;
                    valid = FALSE;
#else
                    if (p[result] == 27) {    /* escape character */
                        wpng_info.have_text &= ~TEXT_DESC;
                        valid = FALSE;
                    }
#endif
                }
            }
        } while (!valid);

        do {
            valid = TRUE;
            p = textbuf + TEXT_COPY_OFFSET;
            fprintf(stderr, "  Copyright: ");
            fflush(stderr);
            if (FGETS(p, 74, keybd) && (len = strlen(p)) > 1) {
                if (p[len-1] == '\n')
                    p[--len] = '\0';
                wpng_info.copyright = p;
                wpng_info.have_text |= TEXT_COPY;
                if ((result = wpng_isvalid_latin1((uch *)p, len)) >= 0) {
                    fprintf(stderr, "    " PROGNAME " warning:  character code"
                      " %u is %sdiscouraged by the PNG\n    specification "
                      "[first occurrence was at character position #%d]\n",
                      (unsigned)p[result], (p[result] == 27)? "strongly " : "",
                      result+1);
                    fflush(stderr);
#ifdef FORBID_LATIN1_CTRL
                    wpng_info.have_text &= ~TEXT_COPY;
                    valid = FALSE;
#else
                    if (p[result] == 27) {    /* escape character */
                        wpng_info.have_text &= ~TEXT_COPY;
                        valid = FALSE;
                    }
#endif
                }
            }
        } while (!valid);

        do {
            valid = TRUE;
            p = textbuf + TEXT_EMAIL_OFFSET;
            fprintf(stderr, "  E-mail: ");
            fflush(stderr);
            if (FGETS(p, 74, keybd) && (len = strlen(p)) > 1) {
                if (p[len-1] == '\n')
                    p[--len] = '\0';
                wpng_info.email = p;
                wpng_info.have_text |= TEXT_EMAIL;
                if ((result = wpng_isvalid_latin1((uch *)p, len)) >= 0) {
                    fprintf(stderr, "    " PROGNAME " warning:  character code"
                      " %u is %sdiscouraged by the PNG\n    specification "
                      "[first occurrence was at character position #%d]\n",
                      (unsigned)p[result], (p[result] == 27)? "strongly " : "",
                      result+1);
                    fflush(stderr);
#ifdef FORBID_LATIN1_CTRL
                    wpng_info.have_text &= ~TEXT_EMAIL;
                    valid = FALSE;
#else
                    if (p[result] == 27) {    /* escape character */
                        wpng_info.have_text &= ~TEXT_EMAIL;
                        valid = FALSE;
                    }
#endif
                }
            }
        } while (!valid);

        do {
            valid = TRUE;
            p = textbuf + TEXT_URL_OFFSET;
            fprintf(stderr, "  URL: ");
            fflush(stderr);
            if (FGETS(p, 74, keybd) && (len = strlen(p)) > 1) {
                if (p[len-1] == '\n')
                    p[--len] = '\0';
                wpng_info.url = p;
                wpng_info.have_text |= TEXT_URL;
                if ((result = wpng_isvalid_latin1((uch *)p, len)) >= 0) {
                    fprintf(stderr, "    " PROGNAME " warning:  character code"
                      " %u is %sdiscouraged by the PNG\n    specification "
                      "[first occurrence was at character position #%d]\n",
                      (unsigned)p[result], (p[result] == 27)? "strongly " : "",
                      result+1);
                    fflush(stderr);
#ifdef FORBID_LATIN1_CTRL
                    wpng_info.have_text &= ~TEXT_URL;
                    valid = FALSE;
#else
                    if (p[result] == 27) {    /* escape character */
                        wpng_info.have_text &= ~TEXT_URL;
                        valid = FALSE;
                    }
#endif
                }
            }
        } while (!valid);

#ifndef DOS_OS2_W32
        fclose(keybd);
#endif

    } else if (text) {
        fprintf(stderr, PROGNAME ":  unable to allocate memory for text\n");
        text = FALSE;
        wpng_info.have_text = 0;
    }
