switch (type) {
  case NT_LIST:
  case NT_ALT:
    if (NTYPE(node) == NT_LIST)
      fprintf(f, "<list:%x>\n", (int )node);
    else
      fprintf(f, "<alt:%x>\n", (int )node);

    print_indent_tree(f, NCAR(node), indent + add);
    while (IS_NOT_NULL(node = NCDR(node))) {
      if (NTYPE(node) != type) {
	fprintf(f, "ERROR: list/alt right is not a cons. %d\n", NTYPE(node));
	exit(0);
      }
      print_indent_tree(f, NCAR(node), indent + add);
    }
    break;

  case NT_STR:
    fprintf(f, "<string%s:%x>",
	    (NSTRING_IS_RAW(node) ? "-raw" : ""), (int )node);
    for (p = NSTR(node)->s; p < NSTR(node)->end; p++) {
      if (*p >= 0x20 && *p < 0x7f)
	fputc(*p, f);
      else {
	fprintf(f, " 0x%02x", *p);
      }
    }
    break;

  case NT_CCLASS:
    fprintf(f, "<cclass:%x>", (int )node);
    if (IS_NCCLASS_NOT(NCCLASS(node))) fputs(" not", f);
    if (NCCLASS(node)->mbuf) {
      BBuf* bbuf = NCCLASS(node)->mbuf;
      for (i = 0; i < bbuf->used; i++) {
	if (i > 0) fprintf(f, ",");
	fprintf(f, "%0x", bbuf->p[i]);
      }
    }
    break;

  case NT_CTYPE:
    fprintf(f, "<ctype:%x> ", (int )node);
    switch (NCTYPE(node)->ctype) {
    case ONIGENC_CTYPE_WORD:
      if (NCTYPE(node)->not != 0)
	fputs("not word",       f);
      else
	fputs("word",           f);
      break;

    default:
      fprintf(f, "ERROR: undefined ctype.\n");
      exit(0);
    }
    break;

  case NT_CANY:
    fprintf(f, "<anychar:%x>", (int )node);
    break;

  case NT_ANCHOR:
    fprintf(f, "<anchor:%x> ", (int )node);
    switch (NANCHOR(node)->type) {
    case ANCHOR_BEGIN_BUF:      fputs("begin buf",      f); break;
    case ANCHOR_END_BUF:        fputs("end buf",        f); break;
    case ANCHOR_BEGIN_LINE:     fputs("begin line",     f); break;
    case ANCHOR_END_LINE:       fputs("end line",       f); break;
    case ANCHOR_SEMI_END_BUF:   fputs("semi end buf",   f); break;
    case ANCHOR_BEGIN_POSITION: fputs("begin position", f); break;

    case ANCHOR_WORD_BOUND:      fputs("word bound",     f); break;
    case ANCHOR_NOT_WORD_BOUND:  fputs("not word bound", f); break;
#ifdef USE_WORD_BEGIN_END
    case ANCHOR_WORD_BEGIN:      fputs("word begin", f);     break;
    case ANCHOR_WORD_END:        fputs("word end", f);       break;
#endif
    case ANCHOR_PREC_READ:       fputs("prec read",      f); break;
    case ANCHOR_PREC_READ_NOT:   fputs("prec read not",  f); break;
    case ANCHOR_LOOK_BEHIND:     fputs("look_behind",    f); break;
    case ANCHOR_LOOK_BEHIND_NOT: fputs("look_behind_not",f); break;

    default:
      fprintf(f, "ERROR: undefined anchor type.\n");
      break;
    }
    break;

  case NT_BREF:
    {
      int* p;
      BRefNode* br = NBREF(node);
      p = BACKREFS_P(br);
      fprintf(f, "<backref:%x>", (int )node);
      for (i = 0; i < br->back_num; i++) {
	if (i > 0) fputs(", ", f);
	fprintf(f, "%d", p[i]);
      }
    }
    break;

#ifdef USE_SUBEXP_CALL
  case NT_CALL:
    {
      CallNode* cn = NCALL(node);
      fprintf(f, "<call:%x>", (int )node);
      p_string(f, cn->name_end - cn->name, cn->name);
    }
    break;
#endif

  case NT_QTFR:
    fprintf(f, "<quantifier:%x>{%d,%d}%s\n", (int )node,
	    NQTFR(node)->lower, NQTFR(node)->upper,
	    (NQTFR(node)->greedy ? "" : "?"));
    print_indent_tree(f, NQTFR(node)->target, indent + add);
    break;

  case NT_ENCLOSE:
    fprintf(f, "<enclose:%x> ", (int )node);
    switch (NENCLOSE(node)->type) {
    case ENCLOSE_OPTION:
      fprintf(f, "option:%d\n", NENCLOSE(node)->option);
      print_indent_tree(f, NENCLOSE(node)->target, indent + add);
      break;
    case ENCLOSE_MEMORY:
      fprintf(f, "memory:%d", NENCLOSE(node)->regnum);
      break;
    case ENCLOSE_STOP_BACKTRACK:
      fprintf(f, "stop-bt");
      break;

    default:
      break;
    }
    fprintf(f, "\n");
    print_indent_tree(f, NENCLOSE(node)->target, indent + add);
    break;

  default:
    fprintf(f, "print_indent_tree: undefined node type %d\n", NTYPE(node));
    break;
  }
