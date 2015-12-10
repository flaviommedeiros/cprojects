#ifdef STORMC4_WOS
if(KeymapBase)
		#else
		if(ConsoleDevice)
		#endif
		{
			struct InputEvent event;
			long actual;
			char buffer[5];

			event.ie_Qualifier=0;
			event.ie_Class=IECLASS_RAWKEY;
			event.ie_SubClass=0L;
			event.ie_Code=code;
			event.ie_X=event.ie_Y=0;
			event.ie_EventAddress=NULL;
			event.ie_NextEvent=NULL;
			event.ie_Prev1DownCode=event.ie_Prev1DownQual=event.ie_Prev2DownCode=event.ie_Prev2DownQual=0;

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
		}
