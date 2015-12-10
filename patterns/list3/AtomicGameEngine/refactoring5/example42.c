#ifndef CURL_DISABLE_POP3
if(conn->handler->protocol&PROTO_FAMILY_POP3)
                result = Curl_pop3_write(conn, k->str, nread);
              else
#endif /* CURL_DISABLE_POP3 */

                result = Curl_client_write(conn, CLIENTWRITE_BODY, k->str,
                                           nread);
