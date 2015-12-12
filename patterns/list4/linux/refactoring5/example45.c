#ifdef CONFIG_COPS_TANGENT
if(lp->board==TANGENT)
        {
                ltf->length=sizeof(ltdrv_code);
                ltf->data=ltdrv_code;
        }
        else
#endif
	{
		printk(KERN_INFO "%s; unsupported board type.\n", dev->name);
		return;
	}
