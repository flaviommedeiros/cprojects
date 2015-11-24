#ifndef HWLOC_DEBUG
if (getenv("HWLOC_DEBUG_CHECK"))
#endif
    hwloc_topology_check(topology);
