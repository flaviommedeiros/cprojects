switch (remcomInBuffer[0]) {
			case 'g':
				/* Read registers: g
				   Success: Each byte of register data is described by two hex digits.
				   Registers are in the internal order for GDB, and the bytes
				   in a register  are in the same order the machine uses.
				   Failure: void. */
				
				{
#ifdef PROCESS_SUPPORT
					/* Use the special register content in the executing thread. */
					copy_registers (&reg_g, &reg, sizeof(registers));
					/* Replace the content available on the stack. */
					if (current_thread_g != executing_task) {
						copy_registers_from_stack (current_thread_g, &reg_g);
					}
					mem2hex ((unsigned char *)remcomOutBuffer, (unsigned char *)&reg_g, sizeof(registers));
#else
					mem2hex(remcomOutBuffer, (char *)&reg, sizeof(registers));
#endif
				}
				break;
				
			case 'G':
				/* Write registers. GXX..XX
				   Each byte of register data  is described by two hex digits.
				   Success: OK
				   Failure: void. */
#ifdef PROCESS_SUPPORT
				hex2mem ((unsigned char *)&reg_g, &remcomInBuffer[1], sizeof(registers));
				if (current_thread_g == executing_task) {
					copy_registers (&reg, &reg_g, sizeof(registers));
				}
				else {
					copy_registers_to_stack(current_thread_g, &reg_g);
				}
#else
				hex2mem((char *)&reg, &remcomInBuffer[1], sizeof(registers));
#endif
				gdb_cris_strcpy (remcomOutBuffer, "OK");
				break;
				
			case 'P':
				/* Write register. Pn...=r...
				   Write register n..., hex value without 0x, with value r...,
				   which contains a hex value without 0x and two hex digits
				   for each byte in the register (target byte order). P1f=11223344 means
				   set register 31 to 44332211.
				   Success: OK
				   Failure: E02, E05 */
				{
					char *suffix;
					int regno = gdb_cris_strtol (&remcomInBuffer[1], &suffix, 16);
					int status;
#ifdef PROCESS_SUPPORT
					if (current_thread_g != executing_task)
						status = write_stack_register (current_thread_g, regno, suffix+1);
					else
#endif
						status = write_register (regno, suffix+1);

					switch (status) {
						case E02:
							/* Do not support read-only registers. */
							gdb_cris_strcpy (remcomOutBuffer, error_message[E02]);
							break;
						case E05:
							/* Do not support non-existing registers. */
							gdb_cris_strcpy (remcomOutBuffer, error_message[E05]);
							break;
						case E07:
							/* Do not support non-existing registers on the stack. */
							gdb_cris_strcpy (remcomOutBuffer, error_message[E07]);
							break;
						default:
							/* Valid register number. */
							gdb_cris_strcpy (remcomOutBuffer, "OK");
							break;
					}
				}
				break;
				
			case 'm':
				/* Read from memory. mAA..AA,LLLL
				   AA..AA is the address and LLLL is the length.
				   Success: XX..XX is the memory content.  Can be fewer bytes than
				   requested if only part of the data may be read. m6000120a,6c means
				   retrieve 108 byte from base address 6000120a.
				   Failure: void. */
				{
                                        char *suffix;
					unsigned char *addr = (unsigned char *)gdb_cris_strtol(&remcomInBuffer[1],
                                                                                               &suffix, 16);                                        int length = gdb_cris_strtol(suffix+1, 0, 16);
                                        
                                        mem2hex(remcomOutBuffer, addr, length);
                                }
				break;
				
			case 'X':
				/* Write to memory. XAA..AA,LLLL:XX..XX
				   AA..AA is the start address,  LLLL is the number of bytes, and
				   XX..XX is the binary data.
				   Success: OK
				   Failure: void. */
			case 'M':
				/* Write to memory. MAA..AA,LLLL:XX..XX
				   AA..AA is the start address,  LLLL is the number of bytes, and
				   XX..XX is the hexadecimal data.
				   Success: OK
				   Failure: void. */
				{
					char *lenptr;
					char *dataptr;
					unsigned char *addr = (unsigned char *)gdb_cris_strtol(&remcomInBuffer[1],
										      &lenptr, 16);
					int length = gdb_cris_strtol(lenptr+1, &dataptr, 16);
					if (*lenptr == ',' && *dataptr == ':') {
						if (remcomInBuffer[0] == 'M') {
							hex2mem(addr, dataptr + 1, length);
						}
						else /* X */ {
							bin2mem(addr, dataptr + 1, length);
						}
						gdb_cris_strcpy (remcomOutBuffer, "OK");
					}
					else {
						gdb_cris_strcpy (remcomOutBuffer, error_message[E06]);
					}
				}
				break;
				
			case 'c':
				/* Continue execution. cAA..AA
				   AA..AA is the address where execution is resumed. If AA..AA is
				   omitted, resume at the present address.
				   Success: return to the executing thread.
				   Failure: will never know. */
				if (remcomInBuffer[1] != '\0') {
					reg.pc = gdb_cris_strtol (&remcomInBuffer[1], 0, 16);
				}
				enableDebugIRQ();
				return;
				
			case 's':
				/* Step. sAA..AA
				   AA..AA is the address where execution is resumed. If AA..AA is
				   omitted, resume at the present address. Success: return to the
				   executing thread. Failure: will never know.
				   
				   Should never be invoked. The single-step is implemented on
				   the host side. If ever invoked, it is an internal error E04. */
				gdb_cris_strcpy (remcomOutBuffer, error_message[E04]);
				putpacket (remcomOutBuffer);
				return;
				
			case '?':
				/* The last signal which caused a stop. ?
				   Success: SAA, where AA is the signal number.
				   Failure: void. */
				remcomOutBuffer[0] = 'S';
				remcomOutBuffer[1] = hex_asc_hi(sigval);
				remcomOutBuffer[2] = hex_asc_lo(sigval);
				remcomOutBuffer[3] = 0;
				break;
				
			case 'D':
				/* Detach from host. D
				   Success: OK, and return to the executing thread.
				   Failure: will never know */
				putpacket ("OK");
				return;
				
			case 'k':
			case 'r':
				/* kill request or reset request.
				   Success: restart of target.
				   Failure: will never know. */
				kill_restart ();
				break;
				
			case 'C':
			case 'S':
			case '!':
			case 'R':
			case 'd':
				/* Continue with signal sig. Csig;AA..AA
				   Step with signal sig. Ssig;AA..AA
				   Use the extended remote protocol. !
				   Restart the target system. R0
				   Toggle debug flag. d
				   Search backwards. tAA:PP,MM
				   Not supported: E04 */
				gdb_cris_strcpy (remcomOutBuffer, error_message[E04]);
				break;
#ifdef PROCESS_SUPPORT

			case 'T':
				/* Thread alive. TXX
				   Is thread XX alive?
				   Success: OK, thread XX is alive.
				   Failure: E03, thread XX is dead. */
				{
					int thread_id = (int)gdb_cris_strtol (&remcomInBuffer[1], 0, 16);
					/* Cannot tell whether it is alive or not. */
					if (thread_id >= 0 && thread_id < number_of_tasks)
						gdb_cris_strcpy (remcomOutBuffer, "OK");
				}
				break;
								
			case 'H':
				/* Set thread for subsequent operations: Hct
				   c = 'c' for thread used in step and continue;
				   t can be -1 for all threads.
				   c = 'g' for thread used in other  operations.
				   t = 0 means pick any thread.
				   Success: OK
				   Failure: E01 */
				{
					int thread_id = gdb_cris_strtol (&remcomInBuffer[2], 0, 16);
					if (remcomInBuffer[1] == 'c') {
						/* c = 'c' for thread used in step and continue */
						/* Do not change current_thread_c here. It would create a mess in
						   the scheduler. */
						gdb_cris_strcpy (remcomOutBuffer, "OK");
					}
					else if (remcomInBuffer[1] == 'g') {
						/* c = 'g' for thread used in other  operations.
						   t = 0 means pick any thread. Impossible since the scheduler does
						   not allow that. */
						if (thread_id >= 0 && thread_id < number_of_tasks) {
							current_thread_g = thread_id;
							gdb_cris_strcpy (remcomOutBuffer, "OK");
						}
						else {
							/* Not expected - send an error message. */
							gdb_cris_strcpy (remcomOutBuffer, error_message[E01]);
						}
					}
					else {
						/* Not expected - send an error message. */
						gdb_cris_strcpy (remcomOutBuffer, error_message[E01]);
					}
				}
				break;
				
			case 'q':
			case 'Q':
				/* Query of general interest. qXXXX
				   Set general value XXXX. QXXXX=yyyy */
				{
					int pos;
					int nextpos;
					int thread_id;
					
					switch (remcomInBuffer[1]) {
						case 'C':
							/* Identify the remote current thread. */
							gdb_cris_strcpy (&remcomOutBuffer[0], "QC");
							remcomOutBuffer[2] = hex_asc_hi(current_thread_c);
							remcomOutBuffer[3] = hex_asc_lo(current_thread_c);
							remcomOutBuffer[4] = '\0';
							break;
						case 'L':
							gdb_cris_strcpy (&remcomOutBuffer[0], "QM");
							/* Reply with number of threads. */
							if (os_is_started()) {
								remcomOutBuffer[2] = hex_asc_hi(number_of_tasks);
								remcomOutBuffer[3] = hex_asc_lo(number_of_tasks);
							}
							else {
								remcomOutBuffer[2] = hex_asc_hi(0);
								remcomOutBuffer[3] = hex_asc_lo(1);
							}
							/* Done with the reply. */
							remcomOutBuffer[4] = hex_asc_lo(1);
							pos = 5;
							/* Expects the argument thread id. */
							for (; pos < (5 + HEXCHARS_IN_THREAD_ID); pos++)
								remcomOutBuffer[pos] = remcomInBuffer[pos];
							/* Reply with the thread identifiers. */
							if (os_is_started()) {
								/* Store the thread identifiers of all tasks. */
								for (thread_id = 0; thread_id < number_of_tasks; thread_id++) {
									nextpos = pos + HEXCHARS_IN_THREAD_ID - 1;
									for (; pos < nextpos; pos ++)
										remcomOutBuffer[pos] = hex_asc_lo(0);
									remcomOutBuffer[pos++] = hex_asc_lo(thread_id);
								}
							}
							else {
								/* Store the thread identifier of the boot task. */
								nextpos = pos + HEXCHARS_IN_THREAD_ID - 1;
								for (; pos < nextpos; pos ++)
									remcomOutBuffer[pos] = hex_asc_lo(0);
								remcomOutBuffer[pos++] = hex_asc_lo(current_thread_c);
							}
							remcomOutBuffer[pos] = '\0';
							break;
						default:
							/* Not supported: "" */
							/* Request information about section offsets: qOffsets. */
							remcomOutBuffer[0] = 0;
							break;
					}
				}
				break;
#endif /* PROCESS_SUPPORT */
				
			default:
				/* The stub should ignore other request and send an empty
				   response ($#<checksum>). This way we can extend the protocol and GDB
				   can tell whether the stub it is talking to uses the old or the new. */
				remcomOutBuffer[0] = 0;
				break;
		}
