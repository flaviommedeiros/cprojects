pg_data_t discontig_node_data[MAX_NUMNODES] = {
  { .bdata = &bootmem_node_data[0] },
  { .bdata = &bootmem_node_data[1] },
  { .bdata = &bootmem_node_data[2] },
  { .bdata = &bootmem_node_data[3] },
#if MAX_NUMNODES == 16
  { .bdata = &bootmem_node_data[4] },
  { .bdata = &bootmem_node_data[5] },
  { .bdata = &bootmem_node_data[6] },
  { .bdata = &bootmem_node_data[7] },
  { .bdata = &bootmem_node_data[8] },
  { .bdata = &bootmem_node_data[9] },
  { .bdata = &bootmem_node_data[10] },
  { .bdata = &bootmem_node_data[11] },
  { .bdata = &bootmem_node_data[12] },
  { .bdata = &bootmem_node_data[13] },
  { .bdata = &bootmem_node_data[14] },
  { .bdata = &bootmem_node_data[15] },
#endif
};
