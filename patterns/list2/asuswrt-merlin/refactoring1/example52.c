if ((current_drive->ored_ctl_adr&0x40)==0)
		{		
			msg(DBG_INF,"CD contains no data tracks.\n");
#ifdef SAFE_MIXED
			current_drive->has_data=0;
#endif /* SAFE_MIXED */
		}
#ifdef SAFE_MIXED
		else if (current_drive->has_data<1) current_drive->has_data=1;
#endif
