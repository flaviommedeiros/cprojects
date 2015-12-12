const struct acpi_predefined_names acpi_gbl_pre_defined_names[] = {
	{"_GPE", ACPI_TYPE_LOCAL_SCOPE, NULL},
	{"_PR_", ACPI_TYPE_LOCAL_SCOPE, NULL},
	{"_SB_", ACPI_TYPE_DEVICE, NULL},
	{"_SI_", ACPI_TYPE_LOCAL_SCOPE, NULL},
	{"_TZ_", ACPI_TYPE_DEVICE, NULL},
	{"_REV", ACPI_TYPE_INTEGER, (char *)ACPI_CA_SUPPORT_LEVEL},
	{"_OS_", ACPI_TYPE_STRING, ACPI_OS_NAME},
	{"_GL_", ACPI_TYPE_MUTEX, (char *)1},

#if !defined (ACPI_NO_METHOD_EXECUTION) || defined (ACPI_CONSTANT_EVAL_ONLY)
	{"_OSI", ACPI_TYPE_METHOD, (char *)1},
#endif

	/* Table terminator */

	{NULL, ACPI_TYPE_ANY, NULL}
};
