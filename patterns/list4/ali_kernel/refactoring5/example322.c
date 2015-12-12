#ifdef CONFIG_PARAVIRT
if (likely(!paravirt_enabled()))
				ptent = __ptep_modify_prot_start(mm, addr, pte);
			else
#endif
				ptent = ptep_modify_prot_start(mm, addr, pte);
