#ifndef NETSNMP_ACCESS_INTERFACE_NOARCH
if (0 == if_index)
        entry->index = netsnmp_access_interface_index_find(name);
    else
#endif
        entry->index = if_index;
