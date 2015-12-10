switch(c) {
			case C_EOL:
				if( stack->defsp > stack->sp )
					ShowError("script:run_script_main: unexpected stack position (defsp=%d sp=%d). please report this!!!\n", stack->defsp, stack->sp);
				else
					script->pop_stack(st, stack->defsp, stack->sp);// pop unused stack data. (unused return value)
				break;
			case C_INT:
				script->push_val(stack,C_INT,script->get_num(st->script->script_buf,&st->pos),NULL);
				break;
			case C_POS:
			case C_NAME:
				script->push_val(stack,c,GETVALUE(st->script->script_buf,st->pos),NULL);
				st->pos+=3;
				break;
			case C_ARG:
				script->push_val(stack,c,0,NULL);
				break;
			case C_STR:
				script->push_str(stack,C_CONSTSTR,(char*)(st->script->script_buf+st->pos));
				while(st->script->script_buf[st->pos++]);
				break;
			case C_LSTR:
			{
				int string_id = *((int *)(&st->script->script_buf[st->pos]));
				uint8 translations = *((uint8 *)(&st->script->script_buf[st->pos+sizeof(int)]));
				struct map_session_data *lsd = NULL;

				st->pos += sizeof(int) + sizeof(uint8);

				if( (!st->rid || !(lsd = map->id2sd(st->rid)) || !lsd->lang_id) && !map->default_lang_id )
					script->push_str(stack,C_CONSTSTR,script->string_list+string_id);
				else {
					uint8 k, wlang_id = lsd ? lsd->lang_id : map->default_lang_id;
					int offset = st->pos;

					for(k = 0; k < translations; k++) {
						uint8 lang_id = *(uint8 *)(&st->script->script_buf[offset]);
						offset += sizeof(uint8);
						if( lang_id == wlang_id )
							break;
						offset += sizeof(char*);
					}
					script->push_str(stack,C_CONSTSTR,
							( k == translations ) ? script->string_list+string_id : *(char**)(&st->script->script_buf[offset]) );
				}
				st->pos += ( ( sizeof(char*) + sizeof(uint8) ) * translations );
			}
				break;
			case C_FUNC:
				script->run_func(st);
				if(st->state==GOTO) {
					st->state = RUN;
					if( !st->freeloop && gotocount>0 && (--gotocount)<=0 ) {
						ShowError("run_script: infinity loop !\n");
						script->reportsrc(st);
						st->state=END;
					}
				}
				break;

			case C_REF:
				st->op2ref = 1;
				break;

			case C_NEG:
			case C_NOT:
			case C_LNOT:
				script->op_1(st ,c);
				break;

			case C_ADD:
			case C_SUB:
			case C_MUL:
			case C_DIV:
			case C_MOD:
			case C_EQ:
			case C_NE:
			case C_GT:
			case C_GE:
			case C_LT:
			case C_LE:
			case C_AND:
			case C_OR:
			case C_XOR:
			case C_LAND:
			case C_LOR:
			case C_R_SHIFT:
			case C_L_SHIFT:
#ifdef PCRE_SUPPORT
			case C_RE_EQ:
			case C_RE_NE:
#endif // PCRE_SUPPORT
				script->op_2(st, c);
				break;

			case C_OP3:
				script->op_3(st, c);
				break;

			case C_NOP:
				st->state=END;
				break;

			default:
				ShowError("unknown command : %d @ %d\n",c,st->pos);
				st->state=END;
				break;
		}
