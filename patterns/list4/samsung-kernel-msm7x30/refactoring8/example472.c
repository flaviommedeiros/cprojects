static void mxs_set_mode(enum clock_event_mode mode,
				struct clock_event_device *evt)
{
	/* Disable interrupt in timer module */
	timrot_irq_disable();

	if (mode != mxs_clockevent_mode) {
		/* Set event time into the furthest future */
		if (timrot_is_v1())
			__raw_writel(0xffff,
				mxs_timrot_base + HW_TIMROT_TIMCOUNTn(1));
		else
			__raw_writel(0xffffffff,
				mxs_timrot_base + HW_TIMROT_FIXED_COUNTn(1));

		/* Clear pending interrupt */
		timrot_irq_acknowledge();
	}

#ifdef DEBUG
	pr_info("%s: changing mode from %s to %s\n", __func__,
		clock_event_mode_label[mxs_clockevent_mode],
		clock_event_mode_label[mode]);
#endif /* DEBUG */

	/* Remember timer mode */
	mxs_clockevent_mode = mode;

	switch (mode) {
	case CLOCK_EVT_MODE_PERIODIC:
		pr_err("%s: Periodic mode is not implemented\n", __func__);
		break;
	case CLOCK_EVT_MODE_ONESHOT:
		timrot_irq_enable();
		break;
	case CLOCK_EVT_MODE_SHUTDOWN:
	case CLOCK_EVT_MODE_UNUSED:
	case CLOCK_EVT_MODE_RESUME:
		/* Left event sources disabled, no more interrupts appear */
		break;
	}
}
