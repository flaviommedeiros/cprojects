#ifndef NO_FP
if (TopValue->Typ == &Parser->pc->FPType)
            {
                /* floating point prefix arithmetic */
                double ResultFP = 0.0;
                
                switch (Op)
                {
                    case TokenPlus:         ResultFP = TopValue->Val->FP; break;
                    case TokenMinus:        ResultFP = -TopValue->Val->FP; break;
                    case TokenIncrement:    ResultFP = ExpressionAssignFP(Parser, TopValue, TopValue->Val->FP+1); break;
                    case TokenDecrement:    ResultFP = ExpressionAssignFP(Parser, TopValue, TopValue->Val->FP-1); break;
                    case TokenUnaryNot:     ResultFP = !TopValue->Val->FP; break;
                    default:                ProgramFail(Parser, "invalid operation"); break;
                }
                
                ExpressionPushFP(Parser, StackTop, ResultFP);
            }
            else 
#endif
            if (IS_NUMERIC_COERCIBLE(TopValue))
            {
                /* integer prefix arithmetic */
                long ResultInt = 0;
                long TopInt = ExpressionCoerceInteger(TopValue);
                switch (Op)
                {
                    case TokenPlus:         ResultInt = TopInt; break;
                    case TokenMinus:        ResultInt = -TopInt; break;
                    case TokenIncrement:    ResultInt = ExpressionAssignInt(Parser, TopValue, TopInt+1, FALSE); break;
                    case TokenDecrement:    ResultInt = ExpressionAssignInt(Parser, TopValue, TopInt-1, FALSE); break;
                    case TokenUnaryNot:     ResultInt = !TopInt; break;
                    case TokenUnaryExor:    ResultInt = ~TopInt; break;
                    default:                ProgramFail(Parser, "invalid operation"); break;
                }

                ExpressionPushInt(Parser, StackTop, ResultInt);
            }
            else if (TopValue->Typ->Base == TypePointer)
            {
                /* pointer prefix arithmetic */
                int Size = TypeSize(TopValue->Typ->FromType, 0, TRUE);
                struct Value *StackValue;
                void *ResultPtr;

                if (TopValue->Val->Pointer == NULL)
                    ProgramFail(Parser, "invalid use of a NULL pointer");
                
                if (!TopValue->IsLValue) 
                    ProgramFail(Parser, "can't assign to this"); 
                    
                switch (Op)
                {
                    case TokenIncrement:    TopValue->Val->Pointer = (void *)((char *)TopValue->Val->Pointer + Size); break;
                    case TokenDecrement:    TopValue->Val->Pointer = (void *)((char *)TopValue->Val->Pointer - Size); break;
                    default:                ProgramFail(Parser, "invalid operation"); break;
                }

                ResultPtr = TopValue->Val->Pointer;
                StackValue = ExpressionStackPushValueByType(Parser, StackTop, TopValue->Typ);
                StackValue->Val->Pointer = ResultPtr;
            }
            else
                ProgramFail(Parser, "invalid operation");
