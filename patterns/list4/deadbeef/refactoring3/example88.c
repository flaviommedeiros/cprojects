switch(KeyCode)
			{
#ifndef WIN32
			case 0x1B:	// Special Key
				KeyCode = _getch();
				if (KeyCode == 0x1B || KeyCode == 0x00)
				{
					// ESC Key pressed
					QuitPlay = true;
					NextPLCmd = 0xFF;
					break;
				}
				switch(KeyCode)
				{
				case 0x5B:
					// Cursor-Key Table
					//	Key		KeyCode
					//	Up		41
					//	Down	42
					//	Left	44
					//	Right	43
					// Cursor only: CursorKey
					// Ctrl: 0x31 + 0x3B + 0x35 + CursorKey
					// Alt: 0x31 + 0x3B + 0x33 + CursorKey
					
					// Page-Keys: PageKey + 0x7E
					//	PageUp		35
					//	PageDown	36
					KeyCode = _getch();	// Get 2nd Key
					// Convert Cursor Key Code from Linux to Windows
					switch(KeyCode)
					{
					case 0x31:	// Ctrl or Alt key
						KeyCode = _getch();
						if (KeyCode == 0x3B)
						{
							KeyCode = _getch();
							if (KeyCode == 0x35)
							{
								KeyCode = _getch();
								switch(KeyCode)
								{
								case 0x41:
									KeyCode = 0x8D;
									break;
								case 0x42:
									KeyCode = 0x91;
									break;
								case 0x43:
									KeyCode = 0x74;
									break;
								case 0x44:
									KeyCode = 0x73;
									break;
								default:
									KeyCode = 0x00;
									break;
								}
							}
						}
						
						if ((KeyCode & 0xF0) == 0x30)
							KeyCode = 0x00;
						break;
					case 0x35:
						KeyCode = 0x49;
						_getch();
						break;
					case 0x36:
						KeyCode = 0x51;
						_getch();
						break;
					case 0x41:
						KeyCode = 0x48;
						break;
					case 0x42:
						KeyCode = 0x50;
						break;
					case 0x43:
						KeyCode = 0x4D;
						break;
					case 0x44:
						KeyCode = 0x4B;
						break;
					default:
						KeyCode = 0x00;
						break;
					}
				}
				// At this point I have Windows-style keys.
#else	//#ifdef WIN32
			case 0xE0:	// Special Key
				// Cursor-Key Table
				// Shift + Cursor results in the usual value for the Cursor Key
				// Alt + Cursor results in 0x00 + (0x50 + CursorKey) (0x00 instead of 0xE0)
				//	Key		None	Ctrl
				//	Up		48		8D
				//	Down	50		91
				//	Left	4B		73
				//	Right	4D		74
				KeyCode = _getch();	// Get 2nd Key
#endif
				switch(KeyCode)
				{
				case 0x4B:	// Cursor Left
					PlaySmpl = -5;
					break;
				case 0x4D:	// Cursor Right
					PlaySmpl = 5;
					break;
				case 0x73:	// Ctrl + Cursor Left
					PlaySmpl = -60;
					break;
				case 0x74:	// Ctrl + Cursor Right
					PlaySmpl = 60;
					break;
				case 0x49:	// Page Up
					if (PLFileCount && /*! NextPLCmd &&*/ CurPLFile)
					{
						NextPLCmd = 0x01;
						QuitPlay = true;
					}
					PlaySmpl = 0;
					break;
				case 0x51:	// Page Down
					if (PLFileCount && /*! NextPLCmd &&*/ CurPLFile < PLFileCount - 0x01)
					{
						NextPLCmd = 0x00;
						QuitPlay = true;
					}
					PlaySmpl = 0;
					break;
				default:
					PlaySmpl = 0;
					break;
				}
				if (PlaySmpl)
				{
					SeekVGM(true, PlaySmpl * SampleRate);
					PosPrint = true;
				}
				break;
#ifdef WIN32
			case 0x1B:	// ESC
#endif
			case 'Q':
				QuitPlay = true;
				NextPLCmd = 0xFF;
				break;
			case ' ':
				PauseVGM(! PausePlay);
				PosPrint = true;
				break;
			case 'F':	// Fading
				FadeTime = FadeTimeN;
				FadePlay = true;
				break;
			case 'R':	// Restart
				RestartVGM();
				PosPrint = true;
				break;
			case 'B':	// Previous file (Back)
				if (PLFileCount && /*! NextPLCmd &&*/ CurPLFile)
				{
					NextPLCmd = 0x01;
					QuitPlay = true;
				}
				break;
			case 'N':	// Next file
				if (PLFileCount && /*! NextPLCmd &&*/ CurPLFile < PLFileCount - 0x01)
				{
					NextPLCmd = 0x00;
					QuitPlay = true;
				}
				break;
			}
