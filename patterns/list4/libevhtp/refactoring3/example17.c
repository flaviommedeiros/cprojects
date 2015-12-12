switch (type) {
  case NT_LIST:
    len = 0;
    do {
      r = compile_length_tree(NCAR(node), reg);
      if (r < 0) return r;
      len += r;
    } while (IS_NOT_NULL(node = NCDR(node)));
    r = len;
    break;

  case NT_ALT:
    {
      int n;

      n = r = 0;
      do {
	r += compile_length_tree(NCAR(node), reg);
	n++;
      } while (IS_NOT_NULL(node = NCDR(node)));
      r += (SIZE_OP_PUSH + SIZE_OP_JUMP) * (n - 1);
    }
    break;

  case NT_STR:
    if (NSTRING_IS_RAW(node))
      r = compile_length_string_raw_node(NSTR(node), reg);
    else
      r = compile_length_string_node(node, reg);
    break;

  case NT_CCLASS:
    r = compile_length_cclass_node(NCCLASS(node), reg);
    break;

  case NT_CTYPE:
  case NT_CANY:
    r = SIZE_OPCODE;
    break;

  case NT_BREF:
    {
      BRefNode* br = NBREF(node);

#ifdef USE_BACKREF_WITH_LEVEL
      if (IS_BACKREF_NEST_LEVEL(br)) {
        r = SIZE_OPCODE + SIZE_OPTION + SIZE_LENGTH +
            SIZE_LENGTH + (SIZE_MEMNUM * br->back_num);
      }
      else
#endif
      if (br->back_num == 1) {
	r = ((!IS_IGNORECASE(reg->options) && br->back_static[0] <= 2)
	     ? SIZE_OPCODE : (SIZE_OPCODE + SIZE_MEMNUM));
      }
      else {
	r = SIZE_OPCODE + SIZE_LENGTH + (SIZE_MEMNUM * br->back_num);
      }
    }
    break;

#ifdef USE_SUBEXP_CALL
  case NT_CALL:
    r = SIZE_OP_CALL;
    break;
#endif

  case NT_QTFR:
    r = compile_length_quantifier_node(NQTFR(node), reg);
    break;

  case NT_ENCLOSE:
    r = compile_length_enclose_node(NENCLOSE(node), reg);
    break;

  case NT_ANCHOR:
    r = compile_length_anchor_node(NANCHOR(node), reg);
    break;

  default:
    return ONIGERR_TYPE_BUG;
    break;
  }
