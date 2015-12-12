switch (WalkState->OpInfo->Type)
    {
#ifndef ACPI_NO_METHOD_EXECUTION

    case AML_TYPE_CREATE_FIELD:
        /*
         * Create the field object, but the field buffer and index must
         * be evaluated later during the execution phase
         */
        Status = AcpiDsCreateBufferField (Op, WalkState);
        break;

     case AML_TYPE_NAMED_FIELD:
        /*
         * If we are executing a method, initialize the field
         */
        if (WalkState->MethodNode)
        {
            Status = AcpiDsInitFieldObjects (Op, WalkState);
        }

        switch (Op->Common.AmlOpcode)
        {
        case AML_INDEX_FIELD_OP:

            Status = AcpiDsCreateIndexField (
                Op, (ACPI_HANDLE) Arg->Common.Node, WalkState);
            break;

        case AML_BANK_FIELD_OP:

            Status = AcpiDsCreateBankField (Op, Arg->Common.Node, WalkState);
            break;

        case AML_FIELD_OP:

            Status = AcpiDsCreateField (Op, Arg->Common.Node, WalkState);
            break;

        default:

            /* All NAMED_FIELD opcodes must be handled above */
            break;
        }
        break;

     case AML_TYPE_NAMED_SIMPLE:

        Status = AcpiDsCreateOperands (WalkState, Arg);
        if (ACPI_FAILURE (Status))
        {
            goto Cleanup;
        }

        switch (Op->Common.AmlOpcode)
        {
        case AML_PROCESSOR_OP:

            Status = AcpiExCreateProcessor (WalkState);
            break;

        case AML_POWER_RES_OP:

            Status = AcpiExCreatePowerResource (WalkState);
            break;

        case AML_MUTEX_OP:

            Status = AcpiExCreateMutex (WalkState);
            break;

        case AML_EVENT_OP:

            Status = AcpiExCreateEvent (WalkState);
            break;

        case AML_ALIAS_OP:

            Status = AcpiExCreateAlias (WalkState);
            break;

        default:

            /* Unknown opcode */

            Status = AE_OK;
            goto Cleanup;
        }

        /* Delete operands */

        for (i = 1; i < WalkState->NumOperands; i++)
        {
            AcpiUtRemoveReference (WalkState->Operands[i]);
            WalkState->Operands[i] = NULL;
        }

        break;
#endif /* ACPI_NO_METHOD_EXECUTION */

    case AML_TYPE_NAMED_COMPLEX:

        switch (Op->Common.AmlOpcode)
        {
#ifndef ACPI_NO_METHOD_EXECUTION
        case AML_REGION_OP:
        case AML_DATA_REGION_OP:

            if (Op->Common.AmlOpcode == AML_REGION_OP)
            {
                RegionSpace = (ACPI_ADR_SPACE_TYPE)
                    ((Op->Common.Value.Arg)->Common.Value.Integer);
            }
            else
            {
                RegionSpace = ACPI_ADR_SPACE_DATA_TABLE;
            }

            /*
             * The OpRegion is not fully parsed at this time. The only valid
             * argument is the SpaceId. (We must save the address of the
             * AML of the address and length operands)
             *
             * If we have a valid region, initialize it. The namespace is
             * unlocked at this point.
             *
             * Need to unlock interpreter if it is locked (if we are running
             * a control method), in order to allow _REG methods to be run
             * during AcpiEvInitializeRegion.
             */
            if (WalkState->MethodNode)
            {
                /*
                 * Executing a method: initialize the region and unlock
                 * the interpreter
                 */
                Status = AcpiExCreateRegion (Op->Named.Data,
                    Op->Named.Length, RegionSpace, WalkState);
                if (ACPI_FAILURE (Status))
                {
                    return_ACPI_STATUS (Status);
                }

                AcpiExExitInterpreter ();
            }

            Status = AcpiEvInitializeRegion (
                AcpiNsGetAttachedObject (Node), FALSE);
            if (WalkState->MethodNode)
            {
                AcpiExEnterInterpreter ();
            }

            if (ACPI_FAILURE (Status))
            {
                /*
                 *  If AE_NOT_EXIST is returned, it is not fatal
                 *  because many regions get created before a handler
                 *  is installed for said region.
                 */
                if (AE_NOT_EXIST == Status)
                {
                    Status = AE_OK;
                }
            }
            break;

        case AML_NAME_OP:

            Status = AcpiDsCreateNode (WalkState, Node, Op);
            break;

        case AML_METHOD_OP:
            /*
             * MethodOp PkgLength NameString MethodFlags TermList
             *
             * Note: We must create the method node/object pair as soon as we
             * see the method declaration. This allows later pass1 parsing
             * of invocations of the method (need to know the number of
             * arguments.)
             */
            ACPI_DEBUG_PRINT ((ACPI_DB_DISPATCH,
                "LOADING-Method: State=%p Op=%p NamedObj=%p\n",
                WalkState, Op, Op->Named.Node));

            if (!AcpiNsGetAttachedObject (Op->Named.Node))
            {
                WalkState->Operands[0] = ACPI_CAST_PTR (void, Op->Named.Node);
                WalkState->NumOperands = 1;

                Status = AcpiDsCreateOperands (
                    WalkState, Op->Common.Value.Arg);
                if (ACPI_SUCCESS (Status))
                {
                    Status = AcpiExCreateMethod (
                        Op->Named.Data, Op->Named.Length, WalkState);
                }

                WalkState->Operands[0] = NULL;
                WalkState->NumOperands = 0;

                if (ACPI_FAILURE (Status))
                {
                    return_ACPI_STATUS (Status);
                }
            }
            break;

#endif /* ACPI_NO_METHOD_EXECUTION */

        default:

            /* All NAMED_COMPLEX opcodes must be handled above */
            break;
        }
        break;

    case AML_CLASS_INTERNAL:

        /* case AML_INT_NAMEPATH_OP: */
        break;

    case AML_CLASS_METHOD_CALL:

        ACPI_DEBUG_PRINT ((ACPI_DB_DISPATCH,
            "RESOLVING-MethodCall: State=%p Op=%p NamedObj=%p\n",
            WalkState, Op, Node));

        /*
         * Lookup the method name and save the Node
         */
        Status = AcpiNsLookup (WalkState->ScopeInfo, Arg->Common.Value.String,
            ACPI_TYPE_ANY, ACPI_IMODE_LOAD_PASS2,
            ACPI_NS_SEARCH_PARENT | ACPI_NS_DONT_OPEN_SCOPE,
            WalkState, &(NewNode));
        if (ACPI_SUCCESS (Status))
        {
            /*
             * Make sure that what we found is indeed a method
             * We didn't search for a method on purpose, to see if the name
             * would resolve
             */
            if (NewNode->Type != ACPI_TYPE_METHOD)
            {
                Status = AE_AML_OPERAND_TYPE;
            }

            /* We could put the returned object (Node) on the object stack for
             * later, but for now, we will put it in the "op" object that the
             * parser uses, so we can get it again at the end of this scope
             */
            Op->Common.Node = NewNode;
        }
        else
        {
            ACPI_ERROR_NAMESPACE (Arg->Common.Value.String, Status);
        }
        break;


    default:

        break;
    }
