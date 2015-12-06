switch (*FPos)
			{
			case 's':
				FormatType = pc->CharPtrType;
				break;
			case 'd':
			case 'u':
			case 'x':
			case 'c':
				FormatType = &pc->IntType;
				break;
#ifndef NO_FP
			case 'f':
				FormatType = &pc->FPType;
				break;
#endif
			case '%':
				PrintCh('%', Stream);
				FormatType = NULL;
				break;
			case '\0':
				FPos--;
				FormatType = NULL;
				break;
			default:
				PrintCh(*FPos, Stream);
				FormatType = NULL;
			}
