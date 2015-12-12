struct mib_node* const mib2_nodes[MIB2_GROUPS] = {
  (struct mib_node* const)&sys_tem,
  (struct mib_node* const)&interfaces,
  (struct mib_node* const)&at,
  (struct mib_node* const)&mib2_ip,
  (struct mib_node* const)&icmp,
#if LWIP_TCP
  (struct mib_node* const)&tcp,
#endif
  (struct mib_node* const)&udp,
  (struct mib_node* const)&snmp
};
