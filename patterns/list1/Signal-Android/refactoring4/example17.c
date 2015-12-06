#ifndef CHARSET_EBCDIC
if ((*p == ':') || (*p == ',') || (*p == '.'))
#else
			if ((*p == os_toascii[':']) || (*p == os_toascii[',']) || (*p == os_toascii['.']))
#endif
				{
				p++;
				if(*p) type = p;
				break;
				}
