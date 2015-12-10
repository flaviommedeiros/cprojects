#ifdef NEW_CARTS
if( (type == 9 && sd->status.base_level > 131) ||
		(type == 8 && sd->status.base_level > 121) ||
		(type == 7 && sd->status.base_level > 111) ||
		(type == 6 && sd->status.base_level > 101) ||
		(type == 5 && sd->status.base_level >  90) ||
		(type == 4 && sd->status.base_level >  80) ||
		(type == 3 && sd->status.base_level >  65) ||
		(type == 2 && sd->status.base_level >  40) ||
		(type == 1))
#else
	if( (type == 5 && sd->status.base_level > 90) ||
	    (type == 4 && sd->status.base_level > 80) ||
	    (type == 3 && sd->status.base_level > 65) ||
	    (type == 2 && sd->status.base_level > 40) ||
	    (type == 1))
#endif
		pc->setcart(sd,type);
