switch (vs->vd->auth) {
       case VNC_AUTH_NONE:
           VNC_DEBUG("Accept auth none\n");
           if (vs->minor >= 8) {
               vnc_write_u32(vs, 0); /* Accept auth completion */
               vnc_flush(vs);
           }
           start_client_init(vs);
           break;

       case VNC_AUTH_VNC:
           VNC_DEBUG("Start VNC auth\n");
           start_auth_vnc(vs);
           break;

#ifdef CONFIG_VNC_TLS
       case VNC_AUTH_VENCRYPT:
           VNC_DEBUG("Accept VeNCrypt auth\n");;
           start_auth_vencrypt(vs);
           break;
#endif /* CONFIG_VNC_TLS */

#ifdef CONFIG_VNC_SASL
       case VNC_AUTH_SASL:
           VNC_DEBUG("Accept SASL auth\n");
           start_auth_sasl(vs);
           break;
#endif /* CONFIG_VNC_SASL */

       default: /* Should not be possible, but just in case */
           VNC_DEBUG("Reject auth %d server code bug\n", vs->vd->auth);
           vnc_write_u8(vs, 1);
           if (vs->minor >= 8) {
               static const char err[] = "Authentication failed";
               vnc_write_u32(vs, sizeof(err));
               vnc_write(vs, err, sizeof(err));
           }
           vnc_client_error(vs);
       }
