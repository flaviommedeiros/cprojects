switch (chip) {
#ifdef CONFIG_ARCH_TEGRA_2x_SOC
			case TEGRA20:
				fuse->soc = &tegra20_fuse_soc;
				break;
#endif

#ifdef CONFIG_ARCH_TEGRA_3x_SOC
			case TEGRA30:
				fuse->soc = &tegra30_fuse_soc;
				break;
#endif

#ifdef CONFIG_ARCH_TEGRA_114_SOC
			case TEGRA114:
				fuse->soc = &tegra114_fuse_soc;
				break;
#endif

#ifdef CONFIG_ARCH_TEGRA_124_SOC
			case TEGRA124:
				fuse->soc = &tegra124_fuse_soc;
				break;
#endif

			default:
				pr_warn("Unsupported SoC: %02x\n", chip);
				break;
			}
