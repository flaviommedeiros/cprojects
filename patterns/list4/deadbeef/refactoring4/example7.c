#if defined(OPLTYPE_IS_OPL3)
if (step_skip>=60)
#else
		if (step_skip>=62)
#endif
		{
			op_pt->a0 = (fltype)(2.0);	// something that triggers an immediate transition to amp:=1.0
			op_pt->a1 = (fltype)(0.0);
			op_pt->a2 = (fltype)(0.0);
			op_pt->a3 = (fltype)(0.0);
		}
