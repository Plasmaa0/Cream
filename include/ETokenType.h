#pragma once

typedef enum ETokenType
{
    NAME,
    SPACE,
    NUMBER,
    STRING,
    NEWLINE,
    INDENT,
    END,
    LB,           // (
    RB,           // )
    LSQB,         // [
    RSQB,         // ]
    LFIGB,        // {
    RFIGB,        // }
    COLON,        // :
    COMMA,        // ,
    SEMI,         // ;
    DOT,          // .
    PLUS,         // +
    MINUS,        // -
    STAR,         // *
    DOUBLESTAR,   // **
    CIRCUMFLEX,   // ^
    TILDE,        // ~
    SLASH,        // /
    DSLASH,       // //
    VBAR,         // |
    AMPER,        // &
    AT,           // @
    LESS,         // <
    GREATER,      // >
    EQUAL,        // =
    PERCENT,      // %
    EQEQ,         // ==
    EXCL,         //!
    NEQ,          // !=
    LEQUAL,       // <=
    GREQUAL,      // >=
    LSHIFT,       // <<
    RSHIFT,       // >>
    PLUSEQ,       // +=
    MINUSEQ,      // -=
    STAREQ,       // *=
    SLASHEQ,      // /=
    PERCENTEQ,    // %=
    AMPEREQ,      // &=
    VBAREQ,       // |=
    CIRCUMFLEXEQ, // ^=
    LSHIFTEQ,     // <<=
    RSHIFTEQ,     // >>=
    DOUBLESTAREQ, // **=
    DSLASHEQ,     // //=
    ATEQ,         // @=
    ELLIPSIS,     // ...
    COMMENT,      // #
    INCREMENT,    // ++
    DECREMENT,    // --
    FOR,          // for
    IF,           // if
    ELSE,         // else
    FUNCDECL,     // func
    RETURN,       // return
    IMPORT,       // import
    INVALID
} ETokenType;
