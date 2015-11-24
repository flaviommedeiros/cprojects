static struct r_bp_arch_t r_bp_plugin_arm_bps[] = {
	{ 64, 4, 0, (const ut8*)"\xfe\xde\xff\xe7" }, // le - arm64
	{ 64, 1, 0, (const ut8*)"\xfe\xde\xff\xe7" }, // le - arm64 // hacky fix
	{ 32, 1, 0, (const ut8*)"\xff\xff\xff\xff" }, // le - linux only? (undefined instruction)
	{ 32, 4, 0, (const ut8*)"\x01\x00\x9f\xef" }, // le - linux only? (undefined instruction)
	{ 32, 4, 1, (const ut8*)"\xef\x9f\x00\x01" }, // be
#if 0
	{ 4, 0, (const ut8*)"\xfe\xde\xff\xe7" }, // arm-le - from a gdb patch
	{ 4, 1, (const ut8*)"\xe7\xff\xde\xfe" }, // arm-be
        { 4, 0, (const ut8*)"\xf0\x01\xf0\xe7" }, // eabi-le - undefined instruction - for all kernels
	{ 4, 1, (const ut8*)"\xe7\xf0\x01\xf0" }, // eabi-be
#endif
	{ 16, 2, 0, (const ut8*)"\xde\x01" },         // thumb-le
	{ 16, 2, 1, (const ut8*)"\x01\xde" },         // thumb-be
	{ 16, 2, 0, (const ut8*)"\xfe\xdf" },         // arm-thumb-le
	{ 16, 2, 1, (const ut8*)"\xdf\xfe" },         // arm-thumb-be
	{ 16, 4, 1, (const ut8*)"\xff\xff\xff\xff" },         // arm-thumb-be
	{ 16, 1, 1, (const ut8*)"\xff\xff\xff\xff" },         // arm-thumb-be
	{ 0, 0, 0, NULL }
};
