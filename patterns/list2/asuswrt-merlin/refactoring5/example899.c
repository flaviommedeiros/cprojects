#ifdef CONFIG_X86_64
if (is_long_mode(vcpu)) {
		nr = vcpu->regs[VCPU_REGS_RAX];
		a0 = vcpu->regs[VCPU_REGS_RDI];
		a1 = vcpu->regs[VCPU_REGS_RSI];
		a2 = vcpu->regs[VCPU_REGS_RDX];
		a3 = vcpu->regs[VCPU_REGS_RCX];
		a4 = vcpu->regs[VCPU_REGS_R8];
		a5 = vcpu->regs[VCPU_REGS_R9];
	} else
#endif
	{
		nr = vcpu->regs[VCPU_REGS_RBX] & -1u;
		a0 = vcpu->regs[VCPU_REGS_RAX] & -1u;
		a1 = vcpu->regs[VCPU_REGS_RCX] & -1u;
		a2 = vcpu->regs[VCPU_REGS_RDX] & -1u;
		a3 = vcpu->regs[VCPU_REGS_RSI] & -1u;
		a4 = vcpu->regs[VCPU_REGS_RDI] & -1u;
		a5 = vcpu->regs[VCPU_REGS_RBP] & -1u;
	}
