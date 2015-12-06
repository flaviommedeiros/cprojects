namespace google {

#if 1      // the C99 format
typedef int32_t int32;
typedef uint32_t uint32;
typedef int64_t int64;
typedef uint64_t uint64;
#elif 1   // the BSD format
typedef int32_t int32;
typedef u_int32_t uint32;
typedef int64_t int64;
typedef u_int64_t uint64;
#elif 0     // the windows (vc7) format
typedef __int32 int32;
typedef unsigned __int32 uint32;
typedef __int64 int64;
typedef unsigned __int64 uint64;
#else
#error Do not know how to define a 32-bit integer quantity on your system
#endif

// --------------------------------------------------------------------
// To actually define a flag in a file, use DEFINE_bool,
// DEFINE_string, etc. at the bottom of this file.  You may also find
// it useful to register a validator with the flag.  This ensures that
// when the flag is parsed from the commandline, or is later set via
// SetCommandLineOption, we call the validation function.
//
// The validation function should return true if the flag value is valid, and
// false otherwise. If the function returns false for the new setting of the
// flag, the flag will retain its current value. If it returns false for the
// default value, InitGoogle will die.
//
// This function is safe to call at global construct time (as in the
// example below).
//
// Example use:
//    static bool ValidatePort(const char* flagname, int32 value) {
//       if (value > 0 && value < 32768)   // value is ok
//         return true;
//       printf("Invalid value for --%s: %d\n", flagname, (int)value);
//       return false;
//    }
//    DEFINE_int32(port, 0, "What port to listen on");
//    static bool dummy = RegisterFlagValidator(&FLAGS_port, &ValidatePort);

// Returns true if successfully registered, false if not (because the
// first argument doesn't point to a command-line flag, or because a
// validator is already registered for this flag).
bool RegisterFlagValidator(const bool* flag,
                           bool (*validate_fn)(const char*, bool));
bool RegisterFlagValidator(const int32* flag,
                           bool (*validate_fn)(const char*, int32));
bool RegisterFlagValidator(const int64* flag,
                           bool (*validate_fn)(const char*, int64));
bool RegisterFlagValidator(const uint64* flag,
                           bool (*validate_fn)(const char*, uint64));
bool RegisterFlagValidator(const double* flag,
                           bool (*validate_fn)(const char*, double));
bool RegisterFlagValidator(const std::string* flag,
                           bool (*validate_fn)(const char*, const std::string&));


// --------------------------------------------------------------------
// These methods are the best way to get access to info about the
// list of commandline flags.  Note that these routines are pretty slow.
//   GetAllFlags: mostly-complete info about the list, sorted by file.
//   ShowUsageWithFlags: pretty-prints the list to stdout (what --help does)
//   ShowUsageWithFlagsRestrict: limit to filenames with restrict as a substr
//
// In addition to accessing flags, you can also access argv[0] (the program
// name) and argv (the entire commandline), which we sock away a copy of.
// These variables are static, so you should only set them once.

struct CommandLineFlagInfo {
  std::string name;           // the name of the flag
  std::string type;           // the type of the flag: int32, etc
  std::string description;    // the "help text" associated with the flag
  std::string current_value;  // the current value, as a string
  std::string default_value;  // the default value, as a string
  std::string filename;       // 'cleaned' version of filename holding the flag
  bool has_validator_fn;      // true if RegisterFlagValidator called on flag
  bool is_default;            // true if the flag has default value
};

extern void GetAllFlags(std::vector<CommandLineFlagInfo>* OUTPUT);
// These two are actually defined in commandlineflags_reporting.cc.
extern void ShowUsageWithFlags(const char *argv0);  // what --help does
extern void ShowUsageWithFlagsRestrict(const char *argv0, const char *restrict);

// Create a descriptive string for a flag.
// Goes to some trouble to make pretty line breaks.
extern std::string DescribeOneFlag(const CommandLineFlagInfo& flag);
