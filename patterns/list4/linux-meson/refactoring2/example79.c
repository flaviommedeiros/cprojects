#if defined(CONFIG_X86_32) && !defined(CONFIG_X86_PAE)
if (k8_addr + rdev->mc.visible_vram_size < 0x100000000ULL)	
#endif
	{
		/* FastFB shall be used with UMA memory. Here it is simply disabled when sideport 
		 * memory is present.
		 */
		if (rdev->mc.igp_sideport_enabled == false && radeon_fastfb == 1) {
			DRM_INFO("Direct mapping: aper base at 0x%llx, replaced by direct mapping base 0x%llx.\n", 
					(unsigned long long)rdev->mc.aper_base, k8_addr);
			rdev->mc.aper_base = (resource_size_t)k8_addr;
			rdev->fastfb_working = true;
		}
	}
