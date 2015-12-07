if (!is6)
		buf = grab_extradata_lua(buf, end, "vendor_class");
#ifdef HAVE_DHCP6
	      else  if (data.vendorclass_count != 0)
		{
		  sprintf(daemon->dhcp_buff2, "vendor_class_id");
		  buf = grab_extradata_lua(buf, end, daemon->dhcp_buff2);
		  for (i = 0; i < data.vendorclass_count - 1; i++)
		    {
		      sprintf(daemon->dhcp_buff2, "vendor_class%i", i);
		      buf = grab_extradata_lua(buf, end, daemon->dhcp_buff2);
		    }
		}
#endif
