#ifdef CONFIG_MAC
if (!arg)
#endif
    {
        if ((in_8(&via[IFR]) & SR_INT) == 0) {
            spin_unlock(&cuda_lock);
            return IRQ_NONE;
        } else {
            out_8(&via[IFR], SR_INT);
        }
    }
