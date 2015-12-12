const ACPI_PREDEFINED_NAMES     AcpiGbl_PreDefinedNames[] =
{
    {"_GPE",    ACPI_TYPE_LOCAL_SCOPE,      NULL},
    {"_PR_",    ACPI_TYPE_LOCAL_SCOPE,      NULL},
    {"_SB_",    ACPI_TYPE_DEVICE,           NULL},
    {"_SI_",    ACPI_TYPE_LOCAL_SCOPE,      NULL},
    {"_TZ_",    ACPI_TYPE_DEVICE,           NULL},
    /*
     * March, 2015:
     * The _REV object is in the process of being deprecated, because
     * other ACPI implementations permanently return 2. Thus, it
     * has little or no value. Return 2 for compatibility with
     * other ACPI implementations.
     */
    {"_REV",    ACPI_TYPE_INTEGER,          ACPI_CAST_PTR (char, 2)},
    {"_OS_",    ACPI_TYPE_STRING,           ACPI_OS_NAME},
    {"_GL_",    ACPI_TYPE_MUTEX,            ACPI_CAST_PTR (char, 1)},

#if !defined (ACPI_NO_METHOD_EXECUTION) || defined (ACPI_CONSTANT_EVAL_ONLY)
    {"_OSI",    ACPI_TYPE_METHOD,           ACPI_CAST_PTR (char, 1)},
#endif

    /* Table terminator */

    {NULL,      ACPI_TYPE_ANY,              NULL}
};
