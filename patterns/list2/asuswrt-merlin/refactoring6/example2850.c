if (request_irq (irq0, &c4_linux_interrupt,
#if defined(SBE_ISR_TASKLET)
                     IRQF_DISABLED | IRQF_SHARED,
#elif defined(SBE_ISR_IMMEDIATE)
                     IRQF_DISABLED | IRQF_SHARED,
#elif defined(SBE_ISR_INLINE)
                     IRQF_SHARED,
#endif
                     ndev->name, ndev))
    {
        pr_warning("%s: MUSYCC could not get irq: %d\n", ndev->name, irq0);
        unregister_netdev (ndev);
        OS_kfree (netdev_priv(ndev));
        OS_kfree (ndev);
        error_flag = EIO;
        return 0;
    }
