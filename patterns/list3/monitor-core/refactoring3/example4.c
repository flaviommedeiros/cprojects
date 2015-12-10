switch(ceTag) {
	  case SFLOW_COUNTERBLOCK_HOST_HID: x->offset.HID = SFLOWXDR_mark(x,0); break; /* HID can be Physical or Virtual */

	  case SFLOW_COUNTERBLOCK_HOST_CPU: x->st_quads.CPU = ceQuads; x->offset.CPU = SFLOWXDR_mark(x,0); x->offset.foundPH++; break;
	  case SFLOW_COUNTERBLOCK_HOST_MEM: x->offset.MEM = SFLOWXDR_mark(x,0); x->offset.foundPH++; break;
	  case SFLOW_COUNTERBLOCK_HOST_DSK: x->offset.DSK = SFLOWXDR_mark(x,0); x->offset.foundPH++; break;
	  case SFLOW_COUNTERBLOCK_HOST_NIO: x->offset.NIO = SFLOWXDR_mark(x,0); x->offset.foundPH++; break;
	  case SFLOW_COUNTERBLOCK_HOST_VNODE: x->offset.VNODE = SFLOWXDR_mark(x,0); x->offset.foundPH++; break; /* hypervisor */

	  case SFLOW_COUNTERBLOCK_HOST_VCPU: x->offset.VCPU = SFLOWXDR_mark(x,0); x->offset.foundVM++; break;
	  case SFLOW_COUNTERBLOCK_HOST_VMEM: x->offset.VMEM = SFLOWXDR_mark(x,0); x->offset.foundVM++; break;
	  case SFLOW_COUNTERBLOCK_HOST_VDSK: x->offset.VDSK = SFLOWXDR_mark(x,0); x->offset.foundVM++; break;
	  case SFLOW_COUNTERBLOCK_HOST_VNIO: x->offset.VNIO = SFLOWXDR_mark(x,0); x->offset.foundVM++; break;
#ifdef SFLOW_MEMCACHE_2200
	  case SFLOW_COUNTERBLOCK_MEMCACHE_2200: x->offset.MEMCACHE_2200 = SFLOWXDR_mark(x,0); break;
#endif
	  case SFLOW_COUNTERBLOCK_MEMCACHE: x->offset.MEMCACHE = SFLOWXDR_mark(x,0); break;
	  case SFLOW_COUNTERBLOCK_HTTP: x->offset.HTTP = SFLOWXDR_mark(x,0); break;
	  case SFLOW_COUNTERBLOCK_JVM: x->offset.JVM = SFLOWXDR_mark(x,0); break;
	  case SFLOW_COUNTERBLOCK_NVML_GPU: x->offset.NVML_GPU = SFLOWXDR_mark(x, 0); break;
	  case SFLOW_COUNTERBLOCK_WORKERS: x->offset.WORKERS = SFLOWXDR_mark(x, 0); break;
	  }
