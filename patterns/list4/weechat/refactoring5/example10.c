#ifdef HAVE_GNUTLS
if (ptr_client->ssl)
                    {
                        if ((num_sent == GNUTLS_E_AGAIN)
                            || (num_sent == GNUTLS_E_INTERRUPTED))
                        {
                            /* we will retry later this client's queue */
                            break;
                        }
                        else
                        {
                            weechat_printf_tags (NULL, "relay_client",
                                                 _("%s%s: sending data to client "
                                                   "%s%s%s: error %d %s"),
                                                 weechat_prefix ("error"),
                                                 RELAY_PLUGIN_NAME,
                                                 RELAY_COLOR_CHAT_CLIENT,
                                                 ptr_client->desc,
                                                 RELAY_COLOR_CHAT,
                                                 num_sent,
                                                 gnutls_strerror (num_sent));
                            relay_client_set_status (ptr_client,
                                                     RELAY_STATUS_DISCONNECTED);
                        }
                    }
                    else
#endif /* HAVE_GNUTLS */
                    {
                        if ((errno == EAGAIN) || (errno == EWOULDBLOCK))
                        {
                            /* we will retry later this client's queue */
                            break;
                        }
                        else
                        {
                            weechat_printf_tags (NULL, "relay_client",
                                                 _("%s%s: sending data to client "
                                                   "%s%s%s: error %d %s"),
                                                 weechat_prefix ("error"),
                                                 RELAY_PLUGIN_NAME,
                                                 RELAY_COLOR_CHAT_CLIENT,
                                                 ptr_client->desc,
                                                 RELAY_COLOR_CHAT,
                                                 errno,
                                                 strerror (errno));
                            relay_client_set_status (ptr_client,
                                                     RELAY_STATUS_DISCONNECTED);
                        }
                    }
