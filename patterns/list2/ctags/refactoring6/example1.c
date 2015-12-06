if (startsWith (line, "#include")
	     || startsWith (line, "#import")
	     || startsWith (line, "#define ")
	     || startsWith (line, "#ifdef "))
	return TR_OBJC;
    else if (startsWith (line, "@interface ")
	     || startsWith (line, "@implementation ")
	     || startsWith (line, "@protocol "))
	return TR_OBJC;
    else if (startsWith (line, "struct ")
	     || startsWith (line, "union ")
	     || startsWith (line, "typedef "))
	return TR_OBJC;
    else {
	if (startsWith (line, "function ")) {
	    const char *p = line + strlen ("function ");
	    while (isspace(*p))
		p++;
	    if (*p != '\0' && *p != '(')
		return TR_MATLAB;
	}
    }
