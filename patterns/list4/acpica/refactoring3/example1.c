switch (Op->Common.AmlOpcode)
    {
#ifdef ACPI_UNDER_DEVELOPMENT
    case AML_ADD_OP:

        ChildOp = Op->Common.Value.Arg;
        if ((ChildOp->Common.AmlOpcode == AML_INT_NAMEPATH_OP) &&
            !ChildOp->Common.Node)
        {
            AcpiNsExternalizeName (ACPI_UINT32_MAX, ChildOp->Common.Value.String,
                NULL, &Path);
            AcpiOsPrintf ("/* %-16s A-NAMEPATH: %s  */\n",
                Op->Common.AmlOpName, Path);
            ACPI_FREE (Path);

            NextOp = Op->Common.Next;
            if (!NextOp)
            {
                /* This NamePath has no args, assume it is an integer */

                AcpiDmAddOpToExternalList (ChildOp,
                    ChildOp->Common.Value.String, ACPI_TYPE_INTEGER, 0, 0);
                return (AE_OK);
            }

            ArgCount = AcpiDmInspectPossibleArgs (3, 1, NextOp);
            AcpiOsPrintf ("/* A-CHILDREN: %u Actual %u */\n",
                ArgCount, AcpiDmCountChildren (Op));

            if (ArgCount < 1)
            {
                /* One Arg means this is just a Store(Name,Target) */

                AcpiDmAddOpToExternalList (ChildOp,
                    ChildOp->Common.Value.String, ACPI_TYPE_INTEGER, 0, 0);
                return (AE_OK);
            }

            AcpiDmAddOpToExternalList (ChildOp,
                ChildOp->Common.Value.String, ACPI_TYPE_METHOD, ArgCount, 0);
        }
        break;
#endif

    case AML_STORE_OP:

        ChildOp = Op->Common.Value.Arg;
        if ((ChildOp->Common.AmlOpcode == AML_INT_NAMEPATH_OP) &&
            !ChildOp->Common.Node)
        {
            NextOp = Op->Common.Next;
            if (!NextOp)
            {
                /* This NamePath has no args, assume it is an integer */

                AcpiDmAddOpToExternalList (ChildOp,
                    ChildOp->Common.Value.String, ACPI_TYPE_INTEGER, 0, 0);
                return (AE_OK);
            }

            ArgCount = AcpiDmInspectPossibleArgs (2, 1, NextOp);
            if (ArgCount <= 1)
            {
                /* One Arg means this is just a Store(Name,Target) */

                AcpiDmAddOpToExternalList (ChildOp,
                    ChildOp->Common.Value.String, ACPI_TYPE_INTEGER, 0, 0);
                return (AE_OK);
            }

            AcpiDmAddOpToExternalList (ChildOp,
                ChildOp->Common.Value.String, ACPI_TYPE_METHOD, ArgCount, 0);
        }
        break;

    case AML_INT_NAMEPATH_OP:

        /* Must examine parent to see if this namepath is an argument */

        ParentOp = Op->Common.Parent;
        OpInfo = AcpiPsGetOpcodeInfo (ParentOp->Common.AmlOpcode);

        if ((OpInfo->Class != AML_CLASS_EXECUTE) &&
            (OpInfo->Class != AML_CLASS_CREATE) &&
            (OpInfo->ObjectType != ACPI_TYPE_LOCAL_ALIAS) &&
            (ParentOp->Common.AmlOpcode != AML_INT_METHODCALL_OP) &&
            !Op->Common.Node)
        {
            ArgCount = AcpiDmInspectPossibleArgs (0, 0, Op->Common.Next);

            /*
             * Check if namepath is a predicate for if/while or lone parameter to
             * a return.
             */
            if (ArgCount == 0)
            {
                if (((ParentOp->Common.AmlOpcode == AML_IF_OP) ||
                     (ParentOp->Common.AmlOpcode == AML_WHILE_OP) ||
                     (ParentOp->Common.AmlOpcode == AML_RETURN_OP)) &&

                     /* And namepath is the first argument */
                     (ParentOp->Common.Value.Arg == Op))
                {
                    AcpiDmAddOpToExternalList (Op,
                        Op->Common.Value.String, ACPI_TYPE_INTEGER, 0, 0);
                    break;
                }
            }

            /*
             * This is a standalone namestring (not a parameter to another
             * operator) - it *must* be a method invocation, nothing else is
             * grammatically possible.
             */
            AcpiDmAddOpToExternalList (Op,
                Op->Common.Value.String, ACPI_TYPE_METHOD, ArgCount, 0);
        }
        break;

    default:

        break;
    }
