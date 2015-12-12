#if defined (PDP15)
if ((IR & 0004000) && (eae_ac_sign ^ link_init))
#else
            if (eae_ac_sign ^ link_init)                /* result negative? */
#endif
                MQ = MQ ^ DMASK;
