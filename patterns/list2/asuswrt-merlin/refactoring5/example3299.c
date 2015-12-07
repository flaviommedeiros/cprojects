#ifdef kIOPMAcknowledgmentOptionSystemCapabilityRequirements
if (m->p->IOPMConnection) IOPMConnectionAcknowledgeEventWithOptions(m->p->IOPMConnection, m->p->SleepCookie, opts);
	else
#endif
	if (result == kIOReturnSuccess) IOAllowPowerChange (m->p->PowerConnection, m->p->SleepCookie);
	else                            IOCancelPowerChange(m->p->PowerConnection, m->p->SleepCookie);
