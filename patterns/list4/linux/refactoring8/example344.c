static const int register_offset[] = {
	PT_REG(er1), PT_REG(er2), PT_REG(er3), PT_REG(er4),
	PT_REG(er5), PT_REG(er6), PT_REG(er0), -1,
	PT_REG(orig_er0), PT_REG(ccr), PT_REG(pc),
#if defined(CONFIG_CPU_H8S)
	PT_REG(exr),
#endif
};
