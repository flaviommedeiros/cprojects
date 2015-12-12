void xen_send_IPI_one(unsigned int cpu, enum ipi_vector vector)
{
	int irq;

#ifdef CONFIG_X86
	if (unlikely(vector == XEN_NMI_VECTOR)) {
		int rc =  HYPERVISOR_vcpu_op(VCPUOP_send_nmi, cpu, NULL);
		if (rc < 0)
			printk(KERN_WARNING "Sending nmi to CPU%d failed (rc:%d)\n", cpu, rc);
		return;
	}
#endif
	irq = per_cpu(ipi_to_irq, cpu)[vector];
	BUG_ON(irq < 0);
	notify_remote_via_irq(irq);
}
