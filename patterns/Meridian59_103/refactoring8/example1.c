namespace owl {

// Generic definitions/compiler options (eg. alignment) preceeding the
// definition of classes
#include <owl/preclass.h>

/// \addtogroup utility
/// @{


//
/// \class TCmdLine
// ~~~~~ ~~~~~~~~
/// Command line argument processing class, processes in the form:
//
///  \<Name\> | {-/}\<Option\>[{:=}\<Value\>] ...
//
class _OWLCLASS TCmdLine {
  public:
    enum TKind {
      Start,   ///< No tokens have been parsed yet
      Name,    ///< Name type token, has no leading / or -
      Option,  ///< Option type token. Leading / or - skipped by Token
      Value,   ///< Value for name or option. Leading : or = skipped by Token
      Done     ///< No more tokens
    };
    TCmdLine(const tstring& cmdLine);
   ~TCmdLine();

    TKind   NextToken(bool removeCurrent=false);
    LPCTSTR GetLine() const {return Buffer;}
    void     Reset();

    tstring GetToken() const;
    TKind GetTokenKind() const;
    
#if defined(OWL5_COMPAT)
  public:
#else
  private:
#endif  
    TKind   Kind;       ///< Kind of current token
    LPTSTR   Token;     ///< Ptr to current token. (Not 0-terminated, use TokenLen)
    int     TokenLen;   ///< Length of current token

  private:
    LPTSTR Buffer;     ///< Command line buffer
    LPTSTR TokenStart; ///< Actual start of current token
};

/// @}

// Generic definitions/compiler options (eg. alignment) following the
// definition of classes
#include <owl/posclass.h>

inline TCmdLine::TKind TCmdLine::GetTokenKind() const
{
  return Kind;
}


}
