if (!uuid_le_cmp(*(uuid_le *)gdata->section_type,
				 CPER_SEC_PLATFORM_MEM)) {
			struct cper_sec_mem_err *mem_err;
			mem_err = (struct cper_sec_mem_err *)(gdata+1);
			ghes_edac_report_mem_error(ghes, sev, mem_err);

			arch_apei_report_mem_error(sev, mem_err);
			ghes_handle_memory_failure(gdata, sev);
		}
#ifdef CONFIG_ACPI_APEI_PCIEAER
		else if (!uuid_le_cmp(*(uuid_le *)gdata->section_type,
				      CPER_SEC_PCIE)) {
			struct cper_sec_pcie *pcie_err;
			pcie_err = (struct cper_sec_pcie *)(gdata+1);
			if (sev == GHES_SEV_RECOVERABLE &&
			    sec_sev == GHES_SEV_RECOVERABLE &&
			    pcie_err->validation_bits & CPER_PCIE_VALID_DEVICE_ID &&
			    pcie_err->validation_bits & CPER_PCIE_VALID_AER_INFO) {
				unsigned int devfn;
				int aer_severity;

				devfn = PCI_DEVFN(pcie_err->device_id.device,
						  pcie_err->device_id.function);
				aer_severity = cper_severity_to_aer(sev);

				/*
				 * If firmware reset the component to contain
				 * the error, we must reinitialize it before
				 * use, so treat it as a fatal AER error.
				 */
				if (gdata->flags & CPER_SEC_RESET)
					aer_severity = AER_FATAL;

				aer_recover_queue(pcie_err->device_id.segment,
						  pcie_err->device_id.bus,
						  devfn, aer_severity,
						  (struct aer_capability_regs *)
						  pcie_err->aer_info);
			}

		}
#endif
