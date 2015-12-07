#ifdef HAVE_MULTILINK
if (!(multilink && go->neg_mrru && ho->neg_mrru))
#endif /* HAVE_MULTILINK */
	netif_set_mtu(f->unit, MIN(mtu, mru));
