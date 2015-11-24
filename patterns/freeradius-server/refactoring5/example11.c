#ifdef HAVE_REGEX
if (map->op == T_OP_REG_EQ) cast_type = PW_TYPE_STRING;
	else
#endif
	/*
	 *	If it's a pair comparison, data gets cast to the
	 *	type of the pair comparison attribute.
	 *
	 *	Magic attribute is always the LHS.
	 */
	if (c->pass2_fixup == PASS2_PAIRCOMPARE) {
		rad_assert(!c->cast);
		rad_assert(map->lhs->type == TMPL_TYPE_ATTR);
#ifndef NDEBUG
		/* expensive assert */
		rad_assert((map->rhs->type != TMPL_TYPE_ATTR) || !radius_find_compare(map->rhs->tmpl_da));
#endif
		cast = map->lhs->tmpl_da;
		cast_type = cast->type;

		EVAL_DEBUG("NORMALISATION TYPE %s (PAIRCMP TYPE)",
			   fr_int2str(dict_attr_types, cast->type, "<INVALID>"));
	/*
	 *	Otherwise we use the explicit cast, or implicit
	 *	cast (from an attribute reference).
	 *	We already have the data for the lhs, so we convert
	 *	it here.
	 */
	} else if (c->cast) {
		cast = c->cast;
		EVAL_DEBUG("NORMALISATION TYPE %s (EXPLICIT CAST)",
			   fr_int2str(dict_attr_types, cast->type, "<INVALID>"));
	} else if (map->lhs->type == TMPL_TYPE_ATTR) {
		cast = map->lhs->tmpl_da;
		EVAL_DEBUG("NORMALISATION TYPE %s (IMPLICIT FROM LHS REF)",
			   fr_int2str(dict_attr_types, cast->type, "<INVALID>"));
	} else if (map->rhs->type == TMPL_TYPE_ATTR) {
		cast = map->rhs->tmpl_da;
		EVAL_DEBUG("NORMALISATION TYPE %s (IMPLICIT FROM RHS REF)",
			   fr_int2str(dict_attr_types, cast->type, "<INVALID>"));
	} else if (map->lhs->type == TMPL_TYPE_DATA) {
		cast_type = map->lhs->tmpl_data_type;
		EVAL_DEBUG("NORMALISATION TYPE %s (IMPLICIT FROM LHS DATA)",
			   fr_int2str(dict_attr_types, cast_type, "<INVALID>"));
	} else if (map->rhs->type == TMPL_TYPE_DATA) {
		cast_type = map->rhs->tmpl_data_type;
		EVAL_DEBUG("NORMALISATION TYPE %s (IMPLICIT FROM RHS DATA)",
			   fr_int2str(dict_attr_types, cast_type, "<INVALID>"));
	}
