#ifndef NDEBUG
if (!main_config.debug_memory)
#endif
	if (inst->handle) dlclose(inst->handle);
