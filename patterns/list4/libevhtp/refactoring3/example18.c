switch (type) {
  case NT_LIST:
    do {
      r = compile_tree(NCAR(node), reg);
    } while (r == 0 && IS_NOT_NULL(node = NCDR(node)));
    break;

  case NT_ALT:
    {
      Node* x = node;
      len = 0;
      do {
	len += compile_length_tree(NCAR(x), reg);
	if (NCDR(x) != NULL) {
	  len += SIZE_OP_PUSH + SIZE_OP_JUMP;
	}
      } while (IS_NOT_NULL(x = NCDR(x)));
      pos = reg->used + len;  /* goal position */

      do {
	len = compile_length_tree(NCAR(node), reg);
	if (IS_NOT_NULL(NCDR(node))) {
	  r = add_opcode_rel_addr(reg, OP_PUSH, len + SIZE_OP_JUMP);
	  if (r) break;
	}
	r = compile_tree(NCAR(node), reg);
	if (r) break;
	if (IS_NOT_NULL(NCDR(node))) {
	  len = pos - (reg->used + SIZE_OP_JUMP);
	  r = add_opcode_rel_addr(reg, OP_JUMP, len);
	  if (r) break;
	}
      } while (IS_NOT_NULL(node = NCDR(node)));
    }
    break;

  case NT_STR:
    if (NSTRING_IS_RAW(node))
      r = compile_string_raw_node(NSTR(node), reg);
    else
      r = compile_string_node(node, reg);
    break;

  case NT_CCLASS:
    r = compile_cclass_node(NCCLASS(node), reg);
    break;

  case NT_CTYPE:
    {
      int op;

      switch (NCTYPE(node)->ctype) {
      case ONIGENC_CTYPE_WORD:
	if (NCTYPE(node)->not != 0)  op = OP_NOT_WORD;
	else                         op = OP_WORD;
	break;
      default:
	return ONIGERR_TYPE_BUG;
	break;
      }
      r = add_opcode(reg, op);
    }
    break;

  case NT_CANY:
    if (IS_MULTILINE(reg->options))
      r = add_opcode(reg, OP_ANYCHAR_ML);
    else
      r = add_opcode(reg, OP_ANYCHAR);
    break;

  case NT_BREF:
    {
      BRefNode* br = NBREF(node);

#ifdef USE_BACKREF_WITH_LEVEL
      if (IS_BACKREF_NEST_LEVEL(br)) {
	r = add_opcode(reg, OP_BACKREF_WITH_LEVEL);
	if (r) return r;
	r = add_option(reg, (reg->options & ONIG_OPTION_IGNORECASE));
	if (r) return r;
	r = add_length(reg, br->nest_level);
	if (r) return r;

	goto add_bacref_mems;
      }
      else
#endif
      if (br->back_num == 1) {
	n = br->back_static[0];
	if (IS_IGNORECASE(reg->options)) {
	  r = add_opcode(reg, OP_BACKREFN_IC);
	  if (r) return r;
	  r = add_mem_num(reg, n);
	}
	else {
	  switch (n) {
	  case 1:  r = add_opcode(reg, OP_BACKREF1); break;
	  case 2:  r = add_opcode(reg, OP_BACKREF2); break;
	  default:
	    r = add_opcode(reg, OP_BACKREFN);
	    if (r) return r;
	    r = add_mem_num(reg, n);
	    break;
	  }
	}
      }
      else {
	int i;
	int* p;

        if (IS_IGNORECASE(reg->options)) {
          r = add_opcode(reg, OP_BACKREF_MULTI_IC);
        }
        else {
          r = add_opcode(reg, OP_BACKREF_MULTI);
        }
	if (r) return r;

#ifdef USE_BACKREF_WITH_LEVEL
      add_bacref_mems:
#endif
	r = add_length(reg, br->back_num);
	if (r) return r;
	p = BACKREFS_P(br);
	for (i = br->back_num - 1; i >= 0; i--) {
	  r = add_mem_num(reg, p[i]);
	  if (r) return r;
	}
      }
    }
    break;

#ifdef USE_SUBEXP_CALL
  case NT_CALL:
    r = compile_call(NCALL(node), reg);
    break;
#endif

  case NT_QTFR:
    r = compile_quantifier_node(NQTFR(node), reg);
    break;

  case NT_ENCLOSE:
    r = compile_enclose_node(NENCLOSE(node), reg);
    break;

  case NT_ANCHOR:
    r = compile_anchor_node(NANCHOR(node), reg);
    break;

  default:
#ifdef ONIG_DEBUG
    fprintf(stderr, "compile_tree: undefined node type %d\n", NTYPE(node));
#endif
    break;
  }
