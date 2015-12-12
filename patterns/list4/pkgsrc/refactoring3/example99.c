switch (t->type) {
	  case TCOM:
		if (t->vars)
			for (w = t->vars; *w != NULL; )
				fptreef(shf, indent, "%S ", *w++);
		else
			fptreef(shf, indent, "#no-vars# ");
		if (t->args)
			for (w = t->args; *w != NULL; )
				fptreef(shf, indent, "%S ", *w++);
		else
			fptreef(shf, indent, "#no-args# ");
		break;
	  case TEXEC:
#if 0 /* ?not useful - can't be called? */
		/* Print original vars */
		if (t->left->vars)
			for (w = t->left->vars; *w != NULL; )
				fptreef(shf, indent, "%S ", *w++);
		else
			fptreef(shf, indent, "#no-vars# ");
		/* Print expanded vars */
		if (t->args)
			for (w = t->args; *w != NULL; )
				fptreef(shf, indent, "%s ", *w++);
		else
			fptreef(shf, indent, "#no-args# ");
		/* Print original io */
		t = t->left;
#else
		t = t->left;
		goto Chain;
#endif
	  case TPAREN:
		fptreef(shf, indent + 2, "( %T) ", t->left);
		break;
	  case TPIPE:
		fptreef(shf, indent, "%T| ", t->left);
		t = t->right;
		goto Chain;
	  case TLIST:
		fptreef(shf, indent, "%T%;", t->left);
		t = t->right;
		goto Chain;
	  case TOR:
	  case TAND:
		fptreef(shf, indent, "%T%s %T",
			t->left, (t->type==TOR) ? "||" : "&&", t->right);
		break;
	  case TBANG:
		fptreef(shf, indent, "! ");
		t = t->right;
		goto Chain;
	  case TDBRACKET:
	  {
		int i;

		fptreef(shf, indent, "[[");
		for (i = 0; t->args[i]; i++)
			fptreef(shf, indent, " %S", t->args[i]);
		fptreef(shf, indent, " ]] ");
		break;
	  }
#ifdef KSH
	  case TSELECT:
		fptreef(shf, indent, "select %s ", t->str);
		/* fall through */
#endif /* KSH */
	  case TFOR:
		if (t->type == TFOR)
			fptreef(shf, indent, "for %s ", t->str);
		if (t->vars != NULL) {
			fptreef(shf, indent, "in ");
			for (w = t->vars; *w; )
				fptreef(shf, indent, "%S ", *w++);
			fptreef(shf, indent, "%;");
		}
		fptreef(shf, indent + INDENT, "do%N%T", t->left);
		fptreef(shf, indent, "%;done ");
		break;
	  case TCASE:
		fptreef(shf, indent, "case %S in", t->str);
		for (t1 = t->left; t1 != NULL; t1 = t1->right) {
			fptreef(shf, indent, "%N(");
			for (w = t1->vars; *w != NULL; w++)
				fptreef(shf, indent, "%S%c", *w,
					(w[1] != NULL) ? '|' : ')');
			fptreef(shf, indent + INDENT, "%;%T%N;;", t1->left);
		}
		fptreef(shf, indent, "%Nesac ");
		break;
	  case TIF:
	  case TELIF:
		/* 3 == strlen("if ") */
		fptreef(shf, indent + 3, "if %T", t->left);
		for (;;) {
			t = t->right;
			if (t->left != NULL) {
				fptreef(shf, indent, "%;");
				fptreef(shf, indent + INDENT, "then%N%T",
					t->left);
			}
			if (t->right == NULL || t->right->type != TELIF)
				break;
			t = t->right;
			fptreef(shf, indent, "%;");
			/* 5 == strlen("elif ") */
			fptreef(shf, indent + 5, "elif %T", t->left);
		}
		if (t->right != NULL) {
			fptreef(shf, indent, "%;");
			fptreef(shf, indent + INDENT, "else%;%T", t->right);
		}
		fptreef(shf, indent, "%;fi ");
		break;
	  case TWHILE:
	  case TUNTIL:
		/* 6 == strlen("while"/"until") */
		fptreef(shf, indent + 6, "%s %T",
			(t->type==TWHILE) ? "while" : "until",
			t->left);
		fptreef(shf, indent, "%;do");
		fptreef(shf, indent + INDENT, "%;%T", t->right);
		fptreef(shf, indent, "%;done ");
		break;
	  case TBRACE:
		fptreef(shf, indent + INDENT, "{%;%T", t->left);
		fptreef(shf, indent, "%;} ");
		break;
	  case TCOPROC:
		fptreef(shf, indent, "%T|& ", t->left);
		break;
	  case TASYNC:
		fptreef(shf, indent, "%T& ", t->left);
		break;
	  case TFUNCT:
		fptreef(shf, indent,
			t->u.ksh_func ? "function %s %T" : "%s() %T",
				t->str, t->left);
		break;
	  case TTIME:
		fptreef(shf, indent, "time %T", t->left);
		break;
	  default:
		fptreef(shf, indent, "<botch>");
		break;
	}
