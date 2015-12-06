switch (request->type)
	{
	  case T_PTR:
		  do_query_number(NULL, &request->addr, request);
		  break;
	  case T_A:
#ifdef RB_IPV6
	  case T_AAAA:
#endif
		  do_query_name(NULL, request->name, request, request->type);
		  break;
	  default:
		  break;
	}
