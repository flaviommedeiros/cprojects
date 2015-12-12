switch (op->common.aml_opcode) {
#ifndef ACPI_NO_METHOD_EXECUTION
		case AML_REGION_OP:
		case AML_DATA_REGION_OP:

			if (op->common.aml_opcode == AML_REGION_OP) {
				region_space = (acpi_adr_space_type)
				    ((op->common.value.arg)->common.value.
				     integer);
			} else {
				region_space = REGION_DATA_TABLE;
			}

			/*
			 * If we are executing a method, initialize the region
			 */
			if (walk_state->method_node) {
				status =
				    acpi_ex_create_region(op->named.data,
							  op->named.length,
							  region_space,
							  walk_state);
				if (ACPI_FAILURE(status)) {
					return (status);
				}
			}

			/*
			 * The op_region is not fully parsed at this time. Only valid
			 * argument is the space_id. (We must save the address of the
			 * AML of the address and length operands)
			 */

			/*
			 * If we have a valid region, initialize it
			 * Namespace is NOT locked at this point.
			 */
			status =
			    acpi_ev_initialize_region
			    (acpi_ns_get_attached_object(node), FALSE);
			if (ACPI_FAILURE(status)) {
				/*
				 *  If AE_NOT_EXIST is returned, it is not fatal
				 *  because many regions get created before a handler
				 *  is installed for said region.
				 */
				if (AE_NOT_EXIST == status) {
					status = AE_OK;
				}
			}
			break;

		case AML_NAME_OP:

			status = acpi_ds_create_node(walk_state, node, op);
			break;

		case AML_METHOD_OP:
			/*
			 * method_op pkg_length name_string method_flags term_list
			 *
			 * Note: We must create the method node/object pair as soon as we
			 * see the method declaration. This allows later pass1 parsing
			 * of invocations of the method (need to know the number of
			 * arguments.)
			 */
			ACPI_DEBUG_PRINT((ACPI_DB_DISPATCH,
					  "LOADING-Method: State=%p Op=%p NamedObj=%p\n",
					  walk_state, op, op->named.node));

			if (!acpi_ns_get_attached_object(op->named.node)) {
				walk_state->operands[0] =
				    ACPI_CAST_PTR(void, op->named.node);
				walk_state->num_operands = 1;

				status =
				    acpi_ds_create_operands(walk_state,
							    op->common.value.
							    arg);
				if (ACPI_SUCCESS(status)) {
					status =
					    acpi_ex_create_method(op->named.
								  data,
								  op->named.
								  length,
								  walk_state);
				}
				walk_state->operands[0] = NULL;
				walk_state->num_operands = 0;

				if (ACPI_FAILURE(status)) {
					return_ACPI_STATUS(status);
				}
			}
			break;

#endif				/* ACPI_NO_METHOD_EXECUTION */

		default:
			/* All NAMED_COMPLEX opcodes must be handled above */
			break;
		}
