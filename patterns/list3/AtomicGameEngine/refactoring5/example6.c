#ifndef NO_SSL
if (ssl != NULL) {
            n = SSL_write(ssl, buf + sent, k);
        } else
#endif
            if (fp != NULL) {
                n = (int) fwrite(buf + sent, 1, (size_t) k, fp);
                if (ferror(fp))
                    n = -1;
            } else {
                n = send(sock, buf + sent, (size_t) k, MSG_NOSIGNAL);
            }
