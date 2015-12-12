static const char * const sym_regex_kernel[S_NSYMTYPES] = {
/*
 * Following symbols have been audited. There values are constant and do
 * not change if bzImage is loaded at a different physical address than
 * the address for which it has been compiled. Don't warn user about
 * absolute relocations present w.r.t these symbols.
 */
	[S_ABS] =
	"^(xen_irq_disable_direct_reloc$|"
	"xen_save_fl_direct_reloc$|"
	"VDSO|"
	"__crc_)",

/*
 * These symbols are known to be relative, even if the linker marks them
 * as absolute (typically defined outside any section in the linker script.)
 */
	[S_REL] =
	"^(__init_(begin|end)|"
	"__x86_cpu_dev_(start|end)|"
	"(__parainstructions|__alt_instructions)(|_end)|"
	"(__iommu_table|__apicdrivers|__smp_locks)(|_end)|"
	"__(start|end)_pci_.*|"
	"__(start|end)_builtin_fw|"
	"__(start|stop)___ksymtab(|_gpl|_unused|_unused_gpl|_gpl_future)|"
	"__(start|stop)___kcrctab(|_gpl|_unused|_unused_gpl|_gpl_future)|"
	"__(start|stop)___param|"
	"__(start|stop)___modver|"
	"__(start|stop)___bug_table|"
	"__tracedata_(start|end)|"
	"__(start|stop)_notes|"
	"__end_rodata|"
	"__initramfs_start|"
	"(jiffies|jiffies_64)|"
#if ELF_BITS == 64
	"__per_cpu_load|"
	"init_per_cpu__.*|"
	"__end_rodata_hpage_align|"
	"__vvar_page|"
#endif
	"_end)$"
};
