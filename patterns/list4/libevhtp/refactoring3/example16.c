switch (node->type) {
  case ANCHOR_BEGIN_BUF:      r = add_opcode(reg, OP_BEGIN_BUF);      break;
  case ANCHOR_END_BUF:        r = add_opcode(reg, OP_END_BUF);        break;
  case ANCHOR_BEGIN_LINE:     r = add_opcode(reg, OP_BEGIN_LINE);     break;
  case ANCHOR_END_LINE:       r = add_opcode(reg, OP_END_LINE);       break;
  case ANCHOR_SEMI_END_BUF:   r = add_opcode(reg, OP_SEMI_END_BUF);   break;
  case ANCHOR_BEGIN_POSITION: r = add_opcode(reg, OP_BEGIN_POSITION); break;

  case ANCHOR_WORD_BOUND:     r = add_opcode(reg, OP_WORD_BOUND);     break;
  case ANCHOR_NOT_WORD_BOUND: r = add_opcode(reg, OP_NOT_WORD_BOUND); break;
#ifdef USE_WORD_BEGIN_END
  case ANCHOR_WORD_BEGIN:     r = add_opcode(reg, OP_WORD_BEGIN);     break;
  case ANCHOR_WORD_END:       r = add_opcode(reg, OP_WORD_END);       break;
#endif

  case ANCHOR_PREC_READ:
    r = add_opcode(reg, OP_PUSH_POS);
    if (r) return r;
    r = compile_tree(node->target, reg);
    if (r) return r;
    r = add_opcode(reg, OP_POP_POS);
    break;

  case ANCHOR_PREC_READ_NOT:
    len = compile_length_tree(node->target, reg);
    if (len < 0) return len;
    r = add_opcode_rel_addr(reg, OP_PUSH_POS_NOT, len + SIZE_OP_FAIL_POS);
    if (r) return r;
    r = compile_tree(node->target, reg);
    if (r) return r;
    r = add_opcode(reg, OP_FAIL_POS);
    break;

  case ANCHOR_LOOK_BEHIND:
    {
      int n;
      r = add_opcode(reg, OP_LOOK_BEHIND);
      if (r) return r;
      if (node->char_len < 0) {
	r = get_char_length_tree(node->target, reg, &n);
	if (r) return ONIGERR_INVALID_LOOK_BEHIND_PATTERN;
      }
      else
	n = node->char_len;
      r = add_length(reg, n);
      if (r) return r;
      r = compile_tree(node->target, reg);
    }
    break;

  case ANCHOR_LOOK_BEHIND_NOT:
    {
      int n;
      len = compile_length_tree(node->target, reg);
      r = add_opcode_rel_addr(reg, OP_PUSH_LOOK_BEHIND_NOT,
			   len + SIZE_OP_FAIL_LOOK_BEHIND_NOT);
      if (r) return r;
      if (node->char_len < 0) {
	r = get_char_length_tree(node->target, reg, &n);
	if (r) return ONIGERR_INVALID_LOOK_BEHIND_PATTERN;
      }
      else
	n = node->char_len;
      r = add_length(reg, n);
      if (r) return r;
      r = compile_tree(node->target, reg);
      if (r) return r;
      r = add_opcode(reg, OP_FAIL_LOOK_BEHIND_NOT);
    }
    break;

  default:
    return ONIGERR_TYPE_BUG;
    break;
  }
