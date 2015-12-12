switch (walk_state->op_info->type) {
#ifndef ACPI_NO_METHOD_EXECUTION

	case AML_TYPE_CREATE_FIELD:
		/*
		 * Create the field object, but the field buffer and index must
		 * be evaluated later during the execution phase
		 */
		status = acpi_ds_create_buffer_field(op, walk_state);
		break;

	case AML_TYPE_NAMED_FIELD:
		/*
		 * If we are executing a method, initialize the field
		 */
		if (walk_state->method_node) {
			status = acpi_ds_init_field_objects(op, walk_state);
		}

		switch (op->common.aml_opcode) {
		case AML_INDEX_FIELD_OP:

			status =
			    acpi_ds_create_index_field(op,
						       (acpi_handle) arg->
						       common.node, walk_state);
			break;

		case AML_BANK_FIELD_OP:

			status =
			    acpi_ds_create_bank_field(op, arg->common.node,
						      walk_state);
			break;

		case AML_FIELD_OP:

			status =
			    acpi_ds_create_field(op, arg->common.node,
						 walk_state);
			break;

		default:
			/* All NAMED_FIELD opcodes must be handled above */
			break;
		}
		break;

	case AML_TYPE_NAMED_SIMPLE:

		status = acpi_ds_create_operands(walk_state, arg);
		if (ACPI_FAILURE(status)) {
			goto cleanup;
		}

		switch (op->common.aml_opcode) {
		case AML_PROCESSOR_OP:

			status = acpi_ex_create_processor(walk_state);
			break;

		case AML_POWER_RES_OP:

			status = acpi_ex_create_power_resource(walk_state);
			break;

		case AML_MUTEX_OP:

			status = acpi_ex_create_mutex(walk_state);
			break;

		case AML_EVENT_OP:

			status = acpi_ex_create_event(walk_state);
			break;

		case AML_ALIAS_OP:

			status = acpi_ex_create_alias(walk_state);
			break;

		default:
			/* Unknown opcode */

			status = AE_OK;
			goto cleanup;
		}

		/* Delete operands */

		for (i = 1; i < walk_state->num_operands; i++) {
			acpi_ut_remove_reference(walk_state->operands[i]);
			walk_state->operands[i] = NULL;
		}

		break;
#endif				/* ACPI_NO_METHOD_EXECUTION */

	case AML_TYPE_NAMED_COMPLEX:

		switch (op->common.aml_opcode) {
#ifndef ACPI_NO_METHOD_EXECUTION
		case AML_REGION_OP:
		case AML_DATA_REGION_OP:

			if (op->common.aml_opcode == AML_REGION_OP) {
				region_space = (acpi_adr_space_type)
				    ((op->common.value.arg)->common.value.
				     integer);
			} else {
				region_space = ACPI_ADR_SPACE_DATA_TABLE;
			}

			/*
			 * The op_region is not fully parsed at this time. The only valid
			 * argument is the space_id. (We must save the address of the
			 * AML of the address and length operands)
			 *
			 * If we have a valid region, initialize it. The namespace is
			 * unlocked at this point.
			 *
			 * Need to unlock interpreter if it is locked (if we are running
			 * a control method), in order to allow _REG methods to be run
			 * during acpi_ev_initialize_region.
			 */
			if (walk_state->method_node) {
				/*
				 * Executing a method: initialize the region and unlock
				 * the interpreter
				 */
				status =
				    acpi_ex_create_region(op->named.data,
							  op->named.length,
							  region_space,
							  walk_state);
				if (ACPI_FAILURE(status)) {
					return_ACPI_STATUS(status);
				}

				acpi_ex_exit_interpreter();
			}

			status =
			    acpi_ev_initialize_region
			    (acpi_ns_get_attached_object(node), FALSE);
			if (walk_state->method_node) {
				acpi_ex_enter_interpreter();
			}

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
		break;

	case AML_CLASS_INTERNAL:

		/* case AML_INT_NAMEPATH_OP: */
		break;

	case AML_CLASS_METHOD_CALL:

		ACPI_DEBUG_PRINT((ACPI_DB_DISPATCH,
				  "RESOLVING-MethodCall: State=%p Op=%p NamedObj=%p\n",
				  walk_state, op, node));

		/*
		 * Lookup the method name and save the Node
		 */
		status =
		    acpi_ns_lookup(walk_state->scope_info,
				   arg->common.value.string, ACPI_TYPE_ANY,
				   ACPI_IMODE_LOAD_PASS2,
				   ACPI_NS_SEARCH_PARENT |
				   ACPI_NS_DONT_OPEN_SCOPE, walk_state,
				   &(new_node));
		if (ACPI_SUCCESS(status)) {
			/*
			 * Make sure that what we found is indeed a method
			 * We didn't search for a method on purpose, to see if the name
			 * would resolve
			 */
			if (new_node->type != ACPI_TYPE_METHOD) {
				status = AE_AML_OPERAND_TYPE;
			}

			/* We could put the returned object (Node) on the object stack for
			 * later, but for now, we will put it in the "op" object that the
			 * parser uses, so we can get it again at the end of this scope
			 */
			op->common.node = new_node;
		} else {
			ACPI_ERROR_NAMESPACE(arg->common.value.string, status);
		}
		break;

	default:
		break;
	}
