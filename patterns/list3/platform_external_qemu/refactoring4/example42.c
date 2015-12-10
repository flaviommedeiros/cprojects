#ifdef STORMC4_WOS
if( (actual=MapRawKey(&event,buffer,5,NULL))>=0)
			#else
			if( (actual=RawKeyConvert(&event,buffer,5,NULL))>=0)
			#endif
			{
				if(actual>1)
				{
					D(bug("Warning (%ld) character conversion!\n",actual));
				}
				else if(actual==1)
				{
					keysym->sym=*buffer;
					D(bug("Converted rawcode %ld to <%lc>\n",code,*buffer));
// Bufferizzo x le successive chiamate!
					MISC_keymap[code]=*buffer;
				}
			}
