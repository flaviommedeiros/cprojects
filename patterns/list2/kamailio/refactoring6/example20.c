if (!strncmp(sig, "F", 1)
#if defined(JAVA_INV_SUPP_TYPE_OBJECTS) && defined(JAVA_INV_SUPP_TYPE_FLOAT)
	|| !strcmp(sig, "Ljava/lang/Float;")
#endif
	) {
	    sfptr = (float)strtof(pval, &endptr);
	    if ((sfptr == 0 && errno != 0) || (pval == endptr))
	    {
		LM_ERR("%s: Can't cast '%s' to type '%s'. Error: %s.\n", APP_NAME, pval, sig, get_conv_err_str(errno));
		pkg_free(ret);
                return NULL;
	    }
            if (sfptr < FLT_MIN || sfptr > FLT_MAX)	// overflow
	    {
		LM_ERR("%s: Can't cast '%s' to type '%s'. Reason: overflow.", APP_NAME, pval, sig);
		pkg_free(ret);
                return NULL;
	    }

	    (*ret).f = (jfloat)sfptr;
	    return ret;
    }
    else
    // integer
    if (!strncmp(sig, "I", 1)
#if defined(JAVA_INV_SUPP_TYPE_OBJECTS) && defined(JAVA_INV_SUPP_TYPE_INTEGER)
	|| !strcmp(sig, "Ljava/lang/Integer;")
#endif
	) {
	    slptr = strtol(pval, &endptr, 10);
	    if ((slptr == 0 && errno != 0) || (pval == endptr))
	    {
		LM_ERR("%s: Can't cast '%s' to type '%s'. Error: %s.\n", APP_NAME, pval, sig, get_conv_err_str(errno));
		pkg_free(ret);
                return NULL;
	    }
	    if (slptr < INT_MIN || slptr > INT_MAX)	// overflow
	    {
		LM_ERR("%s: Can't cast '%s' to type '%s'. Reason: overflow.", APP_NAME, pval, sig);
		pkg_free(ret);
                return NULL;
	    }

	    (*ret).i = (jint)slptr;
	    return ret;
    }
    else
    // long
    if (!strncmp(sig, "J", 1)
#if defined(JAVA_INV_SUPP_TYPE_OBJECTS) && defined(JAVA_INV_SUPP_TYPE_LONG)
	|| !strcmp(sig, "Ljava/lang/Long;")
#endif
	) {
	    slptr = (long)strtol(pval, &endptr, 10);
	    if ((slptr == 0 && errno != 0) || (pval == endptr))
	    {
		LM_ERR("%s: Can't cast '%s' to type '%s'. Error: %s.\n", APP_NAME, pval, sig, get_conv_err_str(errno));
		pkg_free(ret);
                return NULL;
	    }
	    if (slptr < LONG_MIN || slptr > LONG_MAX)	// overflow
	    {
		LM_ERR("%s: Can't cast '%s' to type '%s'. Reason: overflow.", APP_NAME, pval, sig);
		pkg_free(ret);
                return NULL;
	    }

	    (*ret).j = (jlong)slptr;
	    return ret;
    }
    else
    // short
    if (!strncmp(sig, "S", 1)
#if defined(JAVA_INV_SUPP_TYPE_OBJECTS) && defined(JAVA_INV_SUPP_TYPE_SHORT)
	|| !strcmp(sig, "Ljava/lang/Short;")
#endif
	) {
	    ssptr = (short)strtod(pval, &endptr);
	    if ((ssptr == 0 && errno != 0) || (pval == endptr))
	    {
		LM_ERR("%s: Can't cast '%s' to type '%s'. Error: %s.\n", APP_NAME, pval, sig, get_conv_err_str(errno));
		pkg_free(ret);
                return NULL;
	    }
	    if (ssptr < SHRT_MIN || ssptr > SHRT_MAX)	// overflow
	    {
		LM_ERR("%s: Can't cast '%s' to type '%s'. Reason: overflow.", APP_NAME, pval, sig);
		pkg_free(ret);
                return NULL;
	    }

	    (*ret).s = (jshort)ssptr;
	    return ret;
    }
    // String (object)
#if defined(JAVA_INV_SUPP_TYPE_OBJECTS) && defined(JAVA_INV_SUPP_TYPE_STRING)
    else
    if (!strcmp(sig, "Ljava/lang/String;"))
    {
	    sjptr = (*env)->NewStringUTF(env, pval);
	    if ((*env)->ExceptionCheck(env))
	    {
		pkg_free(ret);
		handle_exception();
		return NULL;
	    }
/*
	    if (pval != NULL && sjptr == NULL)
	    {
		pkg_free(ret);
                return NULL;
	    }
*/
	    (*ret).l = (jstring)sjptr;
	    return ret;
    }
#endif
#ifdef JAVA_INV_SUPP_TYPE_VOID
    else
    if (!strncmp(sig, "V", 1))
    {
	pkg_free(ret);
	return NULL;
    }
#endif
    else
    {
	// unknown sig
	LM_ERR("%s: Can't cast '%s' to signature '%s'\n", APP_NAME, pval, sig);
	pkg_free(ret);
	return NULL;
    }
