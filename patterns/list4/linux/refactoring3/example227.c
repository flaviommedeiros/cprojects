switch (rdev->asic_type) {
#ifdef CONFIG_DRM_AMDGPU_CIK
	case CHIP_KAVERI:
		kfd2kgd = amdgpu_amdkfd_gfx_7_get_functions();
		break;
#endif
	case CHIP_CARRIZO:
		kfd2kgd = amdgpu_amdkfd_gfx_8_0_get_functions();
		break;
	default:
		return false;
	}
