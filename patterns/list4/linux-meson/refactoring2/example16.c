#ifdef AMVDEC_USE_STATIC_MEMORY
if (mc_addr == NULL)
#endif
        {
            mc_addr = kmalloc(MC_SIZE, GFP_KERNEL);
        }
