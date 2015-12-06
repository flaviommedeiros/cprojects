switch (Typ->Base)
	{
		case TypeVoid:			PrintStr("void", Stream); break;
		case TypeInt:			PrintStr("int", Stream); break;
		case TypeShort:			PrintStr("short", Stream); break;
		case TypeChar:			PrintStr("char", Stream); break;
		case TypeLong:			PrintStr("long", Stream); break;
		case TypeUnsignedInt:	PrintStr("unsigned int", Stream); break;
		case TypeUnsignedShort:	PrintStr("unsigned short", Stream); break;
		case TypeUnsignedLong:	PrintStr("unsigned long", Stream); break;
		case TypeUnsignedChar:	PrintStr("unsigned char", Stream); break;
#ifndef NO_FP
		case TypeFP:			PrintStr("double", Stream); break;
#endif
		case TypeFunction:		PrintStr("function", Stream); break;
		case TypeMacro:			PrintStr("macro", Stream); break;
		case TypePointer:		if (Typ->FromType) PrintType(Typ->FromType, Stream); PrintCh('*', Stream); break;
		case TypeArray:			PrintType(Typ->FromType, Stream); PrintCh('[', Stream); if (Typ->ArraySize != 0) PrintSimpleInt(Typ->ArraySize, Stream); PrintCh(']', Stream); break;
		case TypeStruct:		PrintStr("struct ", Stream); PrintStr( Typ->Identifier, Stream); break;
		case TypeUnion:			PrintStr("union ", Stream); PrintStr(Typ->Identifier, Stream); break;
		case TypeEnum:			PrintStr("enum ", Stream); PrintStr(Typ->Identifier, Stream); break;
		case TypeGotoLabel:		PrintStr("goto label ", Stream); break;
		case Type_Type:			PrintStr("type ", Stream); break;
	}
