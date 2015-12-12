#ifdef CONFIG_PARAVIRT
if (likely(!paravirt_enabled()))
				__ptep_modify_prot_commit(mm, addr, pte, ptent);
			else
#endif
				ptep_modify_prot_commit(mm, addr, pte, ptent);
