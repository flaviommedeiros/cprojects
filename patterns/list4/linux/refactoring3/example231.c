switch (target_link_speed) {
#ifdef CONFIG_ACPI
		case RADEON_PCIE_GEN3:
			if (radeon_acpi_pcie_performance_request(rdev, PCIE_PERF_REQ_PECI_GEN3, false) == 0)
				break;
			pi->force_pcie_gen = RADEON_PCIE_GEN2;
			if (current_link_speed == RADEON_PCIE_GEN2)
				break;
		case RADEON_PCIE_GEN2:
			if (radeon_acpi_pcie_performance_request(rdev, PCIE_PERF_REQ_PECI_GEN2, false) == 0)
				break;
#endif
		default:
			pi->force_pcie_gen = ci_get_current_pcie_speed(rdev);
			break;
		}
