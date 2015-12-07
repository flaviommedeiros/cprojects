if( !(sd->sc.option&(OPTION_RIDING|OPTION_FALCON|OPTION_DRAGON|OPTION_MADOGEAR))
#ifdef NEW_CARTS
		&& sd->sc.data[SC_PUSH_CART] )
		pc_setcart(sd,0);
