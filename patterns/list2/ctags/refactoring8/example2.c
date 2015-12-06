static booleanOption BooleanOptions [] = {
	{ "append",         &Option.append,                 TRUE,  STAGE_ANY },
	{ "file-scope",     ((boolean *)XTAG_FILE_SCOPE),   FALSE, STAGE_ANY, redirectToXtag },
	{ "file-tags",      ((boolean *)XTAG_FILE_NAMES),   FALSE, STAGE_ANY, redirectToXtag },
	{ "filter",         &Option.filter,                 TRUE,  STAGE_ANY },
	{ "guess-language-eagerly", &Option.guessLanguageEagerly, FALSE, STAGE_ANY },
	{ "if0",            &Option.if0,                    FALSE, STAGE_ANY },
	{ "line-directives",&Option.lineDirectives,         FALSE, STAGE_ANY },
	{ "links",          &Option.followLinks,            FALSE, STAGE_ANY },
	{ "print-language", &Option.printLanguage,          TRUE,  STAGE_ANY },
	{ "quiet",          &Option.quiet,                  FALSE, STAGE_ANY },
#ifdef RECURSE_SUPPORTED
	{ "recurse",        &Option.recurse,                FALSE, STAGE_ANY },
#endif
	{ "tag-relative",   &Option.tagRelative,            TRUE,  STAGE_ANY },
	{ "totals",         &Option.printTotals,            TRUE,  STAGE_ANY },
	{ "verbose",        &Option.verbose,                FALSE, STAGE_ANY },
	{ "_allow-xcmd-in-homedir", &Option.allowXcmdInHomeDir, TRUE, ACCEPT(Etc)|ACCEPT(LocalEtc) },
	{ "_fatal-warnings",&Option.fatalWarnings,          FALSE, STAGE_ANY },
};
