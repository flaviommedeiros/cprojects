switch (*FPos)
						{
						case 's':
							{
								char *Str;
								if (NextArg->Typ->Base == TypePointer)
									Str = NextArg->Val->Pointer;
								else
									Str = &NextArg->Val->ArrayMem[0];
								if (Str == NULL)
									PrintStr("NULL", Stream);
								else
									PrintStr(Str, Stream); 
							}
							break;
						case 'd':
							PrintInt(ExpressionCoerceInteger(NextArg), FieldWidth, ZeroPad, LeftJustify, Stream);
							break;
						case 'u':
							PrintUnsigned(ExpressionCoerceUnsignedInteger(NextArg), 10, FieldWidth, ZeroPad, LeftJustify, Stream);
							break;
						case 'x':
							PrintUnsigned(ExpressionCoerceUnsignedInteger(NextArg), 16, FieldWidth, ZeroPad, LeftJustify, Stream);
							break;
						case 'c':
							PrintCh(ExpressionCoerceUnsignedInteger(NextArg), Stream);
							break;
#ifndef NO_FP
						case 'f':
							PrintFP(ExpressionCoerceFP(NextArg), Stream);
							break;
#endif
						}
