static const int __initdata divide_rate[] = {
#if CONFIG_H8300_TPU_CH == 0
	1,4,16,64,0,0,0,0,
#elif (CONFIG_H8300_TPU_CH == 1) || (CONFIG_H8300_TPU_CH == 5)
	1,4,16,64,0,0,256,0,
#elif (CONFIG_H8300_TPU_CH == 2) || (CONFIG_H8300_TPU_CH == 4)
	1,4,16,64,0,0,0,1024,
#elif CONFIG_H8300_TPU_CH == 3
	1,4,16,64,0,1024,256,4096,
#endif
};
