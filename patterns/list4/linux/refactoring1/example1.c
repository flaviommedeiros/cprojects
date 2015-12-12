if (!IS_ENABLED(CONFIG_64BIT) || smmu->version == ARM_SMMU_V1) {
			iova &= ~12UL;
			iova |= ARM_SMMU_CB_ASID(cfg);
			writel_relaxed(iova, reg);
#ifdef CONFIG_64BIT
		} else {
			iova >>= 12;
			iova |= (u64)ARM_SMMU_CB_ASID(cfg) << 48;
			writeq_relaxed(iova, reg);
#endif
		}
#endif
