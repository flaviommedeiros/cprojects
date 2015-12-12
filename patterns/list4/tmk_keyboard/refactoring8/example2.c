struct mib_node* const mib2_nodes[MIB2_GROUPS] = {
  (struct mib_node*)&sys_tem,
  (struct mib_node*)&interfaces,
  (struct mib_node*)&at,
  (struct mib_node*)&mib2_ip,
  (struct mib_node*)&icmp,
#if LWIP_TCP
  (struct mib_node*)&tcp,
#endif
  (struct mib_node*)&udp,
  (struct mib_node*)&snmp
};
