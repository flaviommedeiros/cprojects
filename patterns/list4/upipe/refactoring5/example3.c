#ifndef __native_client__
if (connect_addr.ss.ss_family != AF_UNSPEC) {
                /* Source-specific multicast */
                struct ip_mreq_source imr;
                imr.imr_multiaddr = bind_addr.sin.sin_addr;
                imr.imr_interface.s_addr = if_addr;
                imr.imr_sourceaddr = connect_addr.sin.sin_addr;
                if (bind_if_index) {
                    upipe_warn(upipe, "ignoring ifindex option in SSM");
                }

                if (setsockopt(fd, IPPROTO_IP, IP_ADD_SOURCE_MEMBERSHIP,
                            (char *)&imr, sizeof(struct ip_mreq_source)) < 0) {
                    upipe_err_va(upipe, "couldn't join multicast group (%m)");
                    upipe_udp_print_socket(upipe, "socket definition:", &bind_addr,
                                 &connect_addr);
                    close(fd);
                    return -1;
                }
            } else if (bind_if_index) {
                /* Linux-specific interface-bound multicast */
                struct ip_mreqn imr;
                imr.imr_multiaddr = bind_addr.sin.sin_addr;
                imr.imr_address.s_addr = if_addr;
                imr.imr_ifindex = bind_if_index;

                if (setsockopt(fd, IPPROTO_IP, IP_ADD_MEMBERSHIP,
                                 (char *)&imr, sizeof(struct ip_mreqn)) < 0) {
                    upipe_err_va(upipe, "couldn't join multicast group (%m)");
                    upipe_udp_print_socket(upipe, "socket definition:", &bind_addr,
                                 &connect_addr);
                    close(fd);
                    return -1;
                }
            } else
#endif
            {
                /* Regular multicast */
                struct ip_mreq imr;
                imr.imr_multiaddr = bind_addr.sin.sin_addr;
                imr.imr_interface.s_addr = if_addr;

                if (setsockopt(fd, IPPROTO_IP, IP_ADD_MEMBERSHIP,
                                 (char *)&imr, sizeof(struct ip_mreq)) < 0) {
                    upipe_err_va(upipe, "couldn't join multicast group (%m)");
                    upipe_udp_print_socket(upipe, "socket definition:", &bind_addr,
                                 &connect_addr);
                    close(fd);
                    return -1;
                }
            }
