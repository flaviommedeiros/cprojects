switch (DestValue->Typ->Base)
    {
        case TypeInt:           DestValue->Val->Integer = ExpressionCoerceInteger(SourceValue); break;
        case TypeShort:         DestValue->Val->ShortInteger = (short)ExpressionCoerceInteger(SourceValue); break;
        case TypeChar:          DestValue->Val->Character = (char)ExpressionCoerceInteger(SourceValue); break;
        case TypeLong:          DestValue->Val->LongInteger = ExpressionCoerceInteger(SourceValue); break;
        case TypeUnsignedInt:   DestValue->Val->UnsignedInteger = ExpressionCoerceUnsignedInteger(SourceValue); break;
        case TypeUnsignedShort: DestValue->Val->UnsignedShortInteger = (unsigned short)ExpressionCoerceUnsignedInteger(SourceValue); break;
        case TypeUnsignedLong:  DestValue->Val->UnsignedLongInteger = ExpressionCoerceUnsignedInteger(SourceValue); break;
        case TypeUnsignedChar:  DestValue->Val->UnsignedCharacter = (unsigned char)ExpressionCoerceUnsignedInteger(SourceValue); break;

#ifndef NO_FP
        case TypeFP:
            if (!IS_NUMERIC_COERCIBLE_PLUS_POINTERS(SourceValue, AllowPointerCoercion)) 
                AssignFail(Parser, "%t from %t", DestValue->Typ, SourceValue->Typ, 0, 0, FuncName, ParamNo); 
            
            DestValue->Val->FP = ExpressionCoerceFP(SourceValue);
            break;
#endif
        case TypePointer:
            ExpressionAssignToPointer(Parser, DestValue, SourceValue, FuncName, ParamNo, AllowPointerCoercion);
            break;
        
        case TypeArray:
            if (SourceValue->Typ->Base == TypeArray && DestValue->Typ->FromType == DestValue->Typ->FromType && DestValue->Typ->ArraySize == 0)
            {
                /* destination array is unsized - need to resize the destination array to the same size as the source array */
                DestValue->Typ = SourceValue->Typ;
                VariableRealloc(Parser, DestValue, TypeSizeValue(DestValue, FALSE));
                
                if (DestValue->LValueFrom != NULL)
                {
                    /* copy the resized value back to the LValue */
                    DestValue->LValueFrom->Val = DestValue->Val;
                    DestValue->LValueFrom->AnyValOnHeap = DestValue->AnyValOnHeap;
                }
            }

            /* char array = "abcd" */
            if (DestValue->Typ->FromType->Base == TypeChar && SourceValue->Typ->Base == TypePointer && SourceValue->Typ->FromType->Base == TypeChar)
            {
                if (DestValue->Typ->ArraySize == 0) /* char x[] = "abcd", x is unsized */
                {
                    int Size = strlen(SourceValue->Val->Pointer) + 1;
                    #ifdef DEBUG_ARRAY_INITIALIZER
                    PRINT_SOURCE_POS;
                    fprintf(stderr, "str size: %d\n", Size);
                    #endif
                    DestValue->Typ = TypeGetMatching(Parser->pc, Parser, DestValue->Typ->FromType, DestValue->Typ->Base, Size, DestValue->Typ->Identifier, TRUE);
                    VariableRealloc(Parser, DestValue, TypeSizeValue(DestValue, FALSE));
                }
                /* else, it's char x[10] = "abcd" */

                #ifdef DEBUG_ARRAY_INITIALIZER
                PRINT_SOURCE_POS;
                fprintf(stderr, "char[%d] from char* (len=%d)\n", DestValue->Typ->ArraySize, strlen(SourceValue->Val->Pointer));
                #endif
                memcpy((void *)DestValue->Val, SourceValue->Val->Pointer, TypeSizeValue(DestValue, FALSE));
                break;
            }

            if (DestValue->Typ != SourceValue->Typ)
                AssignFail(Parser, "%t from %t", DestValue->Typ, SourceValue->Typ, 0, 0, FuncName, ParamNo); 
            
            if (DestValue->Typ->ArraySize != SourceValue->Typ->ArraySize)
                AssignFail(Parser, "from an array of size %d to one of size %d", NULL, NULL, DestValue->Typ->ArraySize, SourceValue->Typ->ArraySize, FuncName, ParamNo);
            
            memcpy((void *)DestValue->Val, (void *)SourceValue->Val, TypeSizeValue(DestValue, FALSE));
            break;
        
        case TypeStruct:
        case TypeUnion:
            if (DestValue->Typ != SourceValue->Typ)
                AssignFail(Parser, "%t from %t", DestValue->Typ, SourceValue->Typ, 0, 0, FuncName, ParamNo); 
            
            memcpy((void *)DestValue->Val, (void *)SourceValue->Val, TypeSizeValue(SourceValue, FALSE));
            break;
        
        default:
            AssignFail(Parser, "%t", DestValue->Typ, NULL, 0, 0, FuncName, ParamNo); 
            break;
    }
