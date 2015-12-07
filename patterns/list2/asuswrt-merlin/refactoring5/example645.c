#ifdef HAVE_DHCP6
if (context->flags & CONTEXT_RA_STATELESS)
	{
	  if (context->flags & CONTEXT_TEMPLATE)
	    strncpy(daemon->dhcp_buff, context->template_interface, 256);
	  else
	    strcpy(daemon->dhcp_buff, daemon->addrbuff);
	}
      else 
#endif
	inet_ntop(family, start, daemon->dhcp_buff, 256);
