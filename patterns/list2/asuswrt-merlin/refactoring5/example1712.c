#ifdef HAVE_DHCP6
if (context->flags & CONTEXT_V6) 
      {
	if ((config->flags & CONFIG_ADDR6) && is_same_net6(&config->addr6, &context->start6, context->prefix))
	  return 1;
      }
    else 
#endif
      if ((config->flags & CONFIG_ADDR) && is_same_net(config->addr, context->start, context->netmask))
	return 1;
