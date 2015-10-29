#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/bool.h"
#include "../headers/tokenizer.h"
#include "../headers/syntatic.h"

STRUCTURED_AUTOMATA SUBMACHINE_LIST[MAXAUTOMATA] = {
  [SUBMACHINE_PROGRAM] = {
    SUBMACHINE_PROGRAM,
    Q0,
    {
      [Q0] =  { { FALSE, { RESERVED_WORD, "program"   }, Q1, SUBMACHINE_NULL },
                EOR_TRANSITION },
      [Q1] =  { { FALSE, { RESERVED_WORD, "begin"   },   Q2, SUBMACHINE_NULL },
                EOR_TRANSITION },
      [Q2] =  { { FALSE, { RESERVED_WORD, "declare"   }, Q3, SUBMACHINE_NULL },
                { TRUE,  { TRIGGER_NULL },               Q4, SUBMACHINE_DEF_FUNCTION },
                EOR_TRANSITION },
      [Q3] =  { { TRUE, { TRIGGER_NULL },                Q2, SUBMACHINE_DECLARATION },
                EOR_TRANSITION },
      [Q4] =  { { FALSE, { RESERVED_WORD, "end"   },     QF, SUBMACHINE_NULL},
                { TRUE, { TRIGGER_NULL },                Q4, SUBMACHINE_DEF_FUNCTION},
                EOR_TRANSITION },
      [QF] =  { EOR_TRANSITION },
    }
  },
  [SUBMACHINE_DEF_FUNCTION] = {
    SUBMACHINE_DEF_FUNCTION,
    Q0,
    {
      [Q0] =  { { FALSE, { RESERVED_WORD, "def" },     Q1, SUBMACHINE_NULL },
                EOR_TRANSITION },
      [Q1] =  { { FALSE, { RESERVED_WORD, "string" },  Q2, SUBMACHINE_NULL },
                { FALSE, { RESERVED_WORD, "float" },   Q2, SUBMACHINE_NULL },
                { FALSE, { RESERVED_WORD, "integer" }, Q2, SUBMACHINE_NULL },
                { FALSE, { RESERVED_WORD, "boolean" }, Q2, SUBMACHINE_NULL },
                { FALSE, { RESERVED_WORD, "void" },    Q2, SUBMACHINE_NULL },
                EOR_TRANSITION },
      [Q2] =  { { FALSE, { IDENTIFIER, EMPTY_VALUE},   Q3, SUBMACHINE_NULL },
                EOR_TRANSITION },
      [Q3] =  { { FALSE, { SINGLE_SYMBOL, "(" },       Q4, SUBMACHINE_NULL },
                { FALSE, { RESERVED_WORD, "begin" },   Q5, SUBMACHINE_NULL },
                EOR_TRANSITION },
      [Q4] =  { { FALSE, { RESERVED_WORD, "string" },  Q8, SUBMACHINE_NULL },
                { FALSE, { RESERVED_WORD, "float" },   Q8, SUBMACHINE_NULL },
                { FALSE, { RESERVED_WORD, "integer" }, Q8, SUBMACHINE_NULL },
                { FALSE, { RESERVED_WORD, "boolean" }, Q8, SUBMACHINE_NULL },
                EOR_TRANSITION },
      [Q5] =  { { FALSE, { RESERVED_WORD, "declare" }, Q6, SUBMACHINE_NULL },
                { TRUE,  { TRIGGER_NULL },             Q7, SUBMACHINE_COMMANDS },
                EOR_TRANSITION },
      [Q6] =  { { TRUE,  { TRIGGER_NULL },             Q5, SUBMACHINE_DECLARATION },
                EOR_TRANSITION },
      [Q7] =  { { FALSE, { RESERVED_WORD, "end" },     QF, SUBMACHINE_NULL },
                EOR_TRANSITION },
      [Q8] =  { { FALSE, { VARIABLE, EMPTY_VALUE },    Q9, SUBMACHINE_NULL },
                EOR_TRANSITION },
      [Q9] =  { { FALSE, { SINGLE_SYMBOL, "," },       Q4, SUBMACHINE_NULL },
                { FALSE, { SINGLE_SYMBOL, ")" },       Q10, SUBMACHINE_NULL },
                EOR_TRANSITION },
      [Q10] =  { { FALSE, { RESERVED_WORD, "begin" },  Q5, SUBMACHINE_NULL },
                EOR_TRANSITION },
      [QF] =  { EOR_TRANSITION },
    }
  },
  [SUBMACHINE_DECLARATION] = {
    SUBMACHINE_DECLARATION,
    Q0,
    {
      [Q0] =  { { FALSE, { RESERVED_WORD, "string" },  Q1, SUBMACHINE_NULL },
                { FALSE, { RESERVED_WORD, "float" },   Q1, SUBMACHINE_NULL },
                { FALSE, { RESERVED_WORD, "integer" }, Q1, SUBMACHINE_NULL },
                { FALSE, { RESERVED_WORD, "boolean" }, Q1, SUBMACHINE_NULL },
                EOR_TRANSITION },
      [Q1] =  { { FALSE, { VARIABLE, EMPTY_VALUE },    Q2, SUBMACHINE_NULL },
                EOR_TRANSITION },
      [Q2] =  { { FALSE, { SINGLE_SYMBOL, "," },       Q3, SUBMACHINE_NULL },
                { FALSE, { SINGLE_SYMBOL, "[" },       Q4, SUBMACHINE_NULL },
                { FALSE, { SINGLE_SYMBOL, ";" },       QF, SUBMACHINE_NULL },
                EOR_TRANSITION },
      [Q3] =  { { FALSE, { VARIABLE, EMPTY_VALUE },    Q7, SUBMACHINE_NULL },
                EOR_TRANSITION },
      [Q4] =  { { FALSE, { INTEGER, EMPTY_VALUE },     Q5, SUBMACHINE_NULL },
                EOR_TRANSITION },
      [Q5] =  { { FALSE, { SINGLE_SYMBOL, "]" },       Q6, SUBMACHINE_NULL },
                EOR_TRANSITION },
      [Q6] =  { { FALSE, { SINGLE_SYMBOL, "," },       Q8, SUBMACHINE_NULL },
                { FALSE, { SINGLE_SYMBOL, ";" },       QF, SUBMACHINE_NULL },
                EOR_TRANSITION },
      [Q7] =  { { FALSE, { SINGLE_SYMBOL, "," },       Q3, SUBMACHINE_NULL },
                { FALSE, { SINGLE_SYMBOL, ";" },       QF, SUBMACHINE_NULL },
                EOR_TRANSITION },
      [Q8] =  { { FALSE, { VARIABLE, EMPTY_VALUE },    Q9, SUBMACHINE_NULL },
                EOR_TRANSITION },
      [Q9] =  { { FALSE, { SINGLE_SYMBOL, "[" },       Q4, SUBMACHINE_NULL },
                EOR_TRANSITION },
      [QF] =  { EOR_TRANSITION },
    }
  },
  [SUBMACHINE_COMMANDS] = {
    SUBMACHINE_COMMANDS,
    Q0,
    {
      [Q0] =  { { FALSE, { VARIABLE, EMPTY_VALUE },    Q1, SUBMACHINE_NULL },
                { FALSE, { RESERVED_WORD, "if" },      Q2, SUBMACHINE_NULL },
                { FALSE, { RESERVED_WORD, "while" },   Q3, SUBMACHINE_NULL },
                { FALSE, { RESERVED_WORD, "input" },   Q4, SUBMACHINE_NULL },
                { FALSE, { RESERVED_WORD, "output" },  Q5, SUBMACHINE_NULL },
                { FALSE, { IDENTIFIER, EMPTY_VALUE },  Q6, SUBMACHINE_NULL },
                { FALSE, { RESERVED_WORD, "return" },  Q7, SUBMACHINE_NULL },
                { FALSE, { RESERVED_WORD, "break" },   Q8, SUBMACHINE_NULL },
                EOR_TRANSITION },
      [Q1] =  { { FALSE, { SINGLE_SYMBOL, "=" },       Q9, SUBMACHINE_NULL },
                EOR_TRANSITION },
      [Q2] =  { { TRUE,  { TRIGGER_NULL },             QF, SUBMACHINE_CONDITIONAL },
                EOR_TRANSITION },
      [Q3] =  { { TRUE,  { TRIGGER_NULL },             QF, SUBMACHINE_ITERATION },
                EOR_TRANSITION },
      [Q4] =  { { FALSE, { VARIABLE, EMPTY_VALUE },    Q8, SUBMACHINE_NULL },
                EOR_TRANSITION },
      [Q5] =  { { TRUE,  { TRIGGER_NULL },             QF, SUBMACHINE_OUTPUT },
                EOR_TRANSITION },
      [Q6] =  { { FALSE, { SINGLE_SYMBOL, "(" },       Q10, SUBMACHINE_NULL },
                EOR_TRANSITION },
      [Q7] =  { { FALSE, { IDENTIFIER, EMPTY_VALUE },  Q6, SUBMACHINE_NULL },
                { FALSE, { VARIABLE, EMPTY_VALUE },    Q8, SUBMACHINE_NULL },
                { TRUE,  { TRIGGER_NULL },             Q8, SUBMACHINE_ARITH_EXP },
                EOR_TRANSITION },
      [Q8] =  { { FALSE, { SINGLE_SYMBOL, ";" },       QF, SUBMACHINE_NULL },
                EOR_TRANSITION },
      [Q9] =  { { TRUE,  { TRIGGER_NULL },             QF, SUBMACHINE_ATTRIBUTION },
                EOR_TRANSITION },
      [Q10] = { { FALSE, { VARIABLE, EMPTY_VALUE },    Q11, SUBMACHINE_NULL },
                { FALSE, { INTEGER, EMPTY_VALUE },     Q11, SUBMACHINE_NULL },
                { FALSE, { FLOAT, EMPTY_VALUE },       Q11, SUBMACHINE_NULL },
                { FALSE, { RESERVED_WORD, "FALSE" },   Q11, SUBMACHINE_NULL },
                { FALSE, { RESERVED_WORD, "TRUE" },    Q11, SUBMACHINE_NULL },
                { TRUE,  { TRIGGER_NULL },             Q11, SUBMACHINE_CALL_FUNCTION },
                EOR_TRANSITION },
      [Q11] = { { FALSE, { SINGLE_SYMBOL, "," },       Q10, SUBMACHINE_NULL },
                EOR_TRANSITION },
      [QF] =  { { FALSE, { VARIABLE, EMPTY_VALUE },    Q1, SUBMACHINE_NULL },
                { FALSE, { RESERVED_WORD, "if" },      Q2, SUBMACHINE_NULL },
                { FALSE, { RESERVED_WORD, "while" },   Q3, SUBMACHINE_NULL },
                { FALSE, { RESERVED_WORD, "input" },   Q4, SUBMACHINE_NULL },
                { FALSE, { RESERVED_WORD, "output" },  Q5, SUBMACHINE_NULL },
                { FALSE, { IDENTIFIER, EMPTY_VALUE },  Q6, SUBMACHINE_NULL },
                { FALSE, { RESERVED_WORD, "return" },  Q7, SUBMACHINE_NULL },
                { FALSE, { RESERVED_WORD, "break" },   Q8, SUBMACHINE_NULL },
                EOR_TRANSITION },
    }
  },
  [SUBMACHINE_ATTRIBUTION] = {
    SUBMACHINE_ATTRIBUTION,
    Q0,
    {
      [Q0] =  { { FALSE, { STRING, EMPTY_VALUE },      Q1, SUBMACHINE_NULL },
                { TRUE,  { TRIGGER_NULL },             Q1, SUBMACHINE_ARITH_EXP },
                EOR_TRANSITION },
      [Q1] =  { { FALSE, { SINGLE_SYMBOL, ";" },       QF, SUBMACHINE_NULL },
                EOR_TRANSITION },
      [QF] =  { EOR_TRANSITION },
    }
  },
  [SUBMACHINE_CALL_FUNCTION] = {
    SUBMACHINE_CALL_FUNCTION,
    Q0,
    {
      [Q0] =  { { FALSE, { IDENTIFIER, EMPTY_VALUE },  Q1, SUBMACHINE_NULL },
                EOR_TRANSITION },
      [Q1] =  { { FALSE, { SINGLE_SYMBOL, "(" },       Q2, SUBMACHINE_NULL },
                { TRUE,  { TRIGGER_NULL },             QF, SUBMACHINE_NULL },
                EOR_TRANSITION },
      [Q2] =  { { FALSE, { VARIABLE, EMPTY_VALUE },    Q3, SUBMACHINE_NULL },
                { FALSE, { INTEGER, EMPTY_VALUE },     Q3, SUBMACHINE_NULL },
                { FALSE, { FLOAT, EMPTY_VALUE },       Q3, SUBMACHINE_NULL },
                { FALSE, { RESERVED_WORD, "FALSE" },   Q3, SUBMACHINE_NULL },
                { FALSE, { RESERVED_WORD, "TRUE" },    Q3, SUBMACHINE_NULL },
                { TRUE,  { TRIGGER_NULL },             Q3, SUBMACHINE_CALL_FUNCTION },
                EOR_TRANSITION },
      [Q3] =  { { FALSE, { SINGLE_SYMBOL, "," },       Q2, SUBMACHINE_NULL },
                { FALSE, { SINGLE_SYMBOL, ")" },       Q4, SUBMACHINE_NULL },
                EOR_TRANSITION },
      [Q4] =  { { TRUE,  { TRIGGER_NULL },             QF, SUBMACHINE_NULL },
                EOR_TRANSITION },
      [QF] =  { { FALSE, { SINGLE_SYMBOL, "(" },       Q1, SUBMACHINE_NULL },
                EOR_TRANSITION },
    }
  },
  [SUBMACHINE_ARITH_EXP] = {
    SUBMACHINE_ARITH_EXP,
    Q0,
    {
      [Q0] =  { { FALSE, { SINGLE_SYMBOL, "(" },       Q1, SUBMACHINE_NULL },
                { TRUE,  { TRIGGER_NULL },             QF, SUBMACHINE_ARITH_EXP_SPEC },
                EOR_TRANSITION },
      [Q1] =  { { TRUE,  { TRIGGER_NULL },             Q2, SUBMACHINE_ARITH_EXP_SPEC },
                EOR_TRANSITION },
      [Q2] =  { { FALSE, { SINGLE_SYMBOL, ")" },       QF, SUBMACHINE_NULL },
                EOR_TRANSITION },
      [QF] =  { EOR_TRANSITION },
    }
  },
  [SUBMACHINE_ARITH_EXP_SPEC] = {
    SUBMACHINE_ARITH_EXP_SPEC,
    Q0,
    {
      [Q0] =  { { FALSE, { VARIABLE, EMPTY_VALUE },    Q2, SUBMACHINE_NULL },
                { FALSE, { INTEGER, EMPTY_VALUE },     Q2, SUBMACHINE_NULL },
                { FALSE, { FLOAT, EMPTY_VALUE },       Q2, SUBMACHINE_NULL },
                { FALSE, { IDENTIFIER, EMPTY_VALUE },  Q1, SUBMACHINE_NULL },
                { TRUE,  { TRIGGER_NULL },             Q2, SUBMACHINE_ARITH_EXP },
                EOR_TRANSITION },
      [Q1] =  { { FALSE, { SINGLE_SYMBOL, "-" },       Q4, SUBMACHINE_NULL },
                { FALSE, { SINGLE_SYMBOL, "+" },       Q4, SUBMACHINE_NULL },
                { FALSE, { SINGLE_SYMBOL, "/" },       Q4, SUBMACHINE_NULL },
                { FALSE, { SINGLE_SYMBOL, "%" },       Q4, SUBMACHINE_NULL },
                { FALSE, { SINGLE_SYMBOL, "*" },       Q4, SUBMACHINE_NULL },
                { FALSE, { SINGLE_SYMBOL, "(" },       Q3, SUBMACHINE_NULL },
                { TRUE,  { TRIGGER_NULL },             QF, SUBMACHINE_NULL },
                EOR_TRANSITION },
      [Q2] =  { { FALSE, { SINGLE_SYMBOL, "-" },       Q4, SUBMACHINE_NULL },
                { FALSE, { SINGLE_SYMBOL, "+" },       Q4, SUBMACHINE_NULL },
                { FALSE, { SINGLE_SYMBOL, "/" },       Q4, SUBMACHINE_NULL },
                { FALSE, { SINGLE_SYMBOL, "%" },       Q4, SUBMACHINE_NULL },
                { FALSE, { SINGLE_SYMBOL, "*" },       Q4, SUBMACHINE_NULL },
                { TRUE,  { TRIGGER_NULL },             QF, SUBMACHINE_NULL },
                EOR_TRANSITION },
      [Q3] =  { { FALSE, { VARIABLE, EMPTY_VALUE },    Q7, SUBMACHINE_NULL },
                { FALSE, { INTEGER, EMPTY_VALUE },     Q7, SUBMACHINE_NULL },
                { FALSE, { FLOAT, EMPTY_VALUE },       Q7, SUBMACHINE_NULL },
                { FALSE, { RESERVED_WORD, "FALSE" },   Q7, SUBMACHINE_NULL },
                { FALSE, { RESERVED_WORD, "TRUE" },    Q7, SUBMACHINE_NULL },
                { TRUE,  { TRIGGER_NULL },             Q7, SUBMACHINE_CALL_FUNCTION },
                EOR_TRANSITION },
      [Q4] =  { { FALSE, { VARIABLE, EMPTY_VALUE },    Q6, SUBMACHINE_NULL },
                { FALSE, { INTEGER, EMPTY_VALUE },     Q6, SUBMACHINE_NULL },
                { FALSE, { FLOAT, EMPTY_VALUE },       Q6, SUBMACHINE_NULL },
                { FALSE, { IDENTIFIER, EMPTY_VALUE },  Q5, SUBMACHINE_NULL },
                { TRUE,  { TRIGGER_NULL },             Q6, SUBMACHINE_ARITH_EXP },
                EOR_TRANSITION },
      [Q5] =  { { FALSE, { SINGLE_SYMBOL, "(" },       Q8, SUBMACHINE_NULL },
                { TRUE,  { TRIGGER_NULL },             QF, SUBMACHINE_NULL },
                EOR_TRANSITION },
      [Q6] =  { { TRUE,  { TRIGGER_NULL },             QF, SUBMACHINE_NULL },
                EOR_TRANSITION },
      [Q7] =  { { FALSE, { SINGLE_SYMBOL, ")" },       Q2, SUBMACHINE_NULL },
                { FALSE, { SINGLE_SYMBOL, "," },       Q3, SUBMACHINE_NULL },
                EOR_TRANSITION },
      [Q8] =  { { FALSE, { VARIABLE, EMPTY_VALUE },    Q9, SUBMACHINE_NULL },
                { FALSE, { INTEGER, EMPTY_VALUE },     Q9, SUBMACHINE_NULL },
                { FALSE, { FLOAT, EMPTY_VALUE },       Q9, SUBMACHINE_NULL },
                { FALSE, { RESERVED_WORD, "FALSE" },   Q9, SUBMACHINE_NULL },
                { FALSE, { RESERVED_WORD, "TRUE" },    Q9, SUBMACHINE_NULL },
                { TRUE,  { TRIGGER_NULL },             Q9, SUBMACHINE_CALL_FUNCTION },
                EOR_TRANSITION },
      [Q9] =  { { FALSE, { SINGLE_SYMBOL, ")" },       Q6, SUBMACHINE_NULL },
                { FALSE, { SINGLE_SYMBOL, "," },       Q8, SUBMACHINE_NULL },
                EOR_TRANSITION },
      [QF] =  { EOR_TRANSITION },
    }
  },
  [SUBMACHINE_BOOL_EXP] = {
    SUBMACHINE_BOOL_EXP,
    Q0,
    {
      [Q0] =  { { FALSE, { SINGLE_SYMBOL, "(" },       Q1, SUBMACHINE_NULL },
                { TRUE,  { TRIGGER_NULL },             QF, SUBMACHINE_BOOL_EXP_SPEC },
                EOR_TRANSITION },
      [Q1] =  { { TRUE,  { TRIGGER_NULL },             Q2, SUBMACHINE_BOOL_EXP_SPEC },
                EOR_TRANSITION },
      [Q2] =  { { FALSE, { SINGLE_SYMBOL, ")" },       QF, SUBMACHINE_NULL },
                EOR_TRANSITION },
      [QF] =  { EOR_TRANSITION },
    }
  },
  [SUBMACHINE_BOOL_EXP_SPEC] = {
    SUBMACHINE_BOOL_EXP_SPEC,
    Q0,
    {
      [Q0] =  { { FALSE, { VARIABLE, EMPTY_VALUE },    Q2, SUBMACHINE_NULL },
                { FALSE, { INTEGER, EMPTY_VALUE },     Q2, SUBMACHINE_NULL },
                { FALSE, { FLOAT, EMPTY_VALUE },       Q2, SUBMACHINE_NULL },
                { FALSE, { RESERVED_WORD, "FALSE" },   Q2, SUBMACHINE_NULL },
                { FALSE, { RESERVED_WORD, "TRUE" },    Q2, SUBMACHINE_NULL },
                { FALSE, { IDENTIFIER, EMPTY_VALUE },  Q1, SUBMACHINE_NULL },
                { TRUE,  { TRIGGER_NULL },             Q2, SUBMACHINE_ARITH_EXP },
                EOR_TRANSITION },
      [Q1] =  { { FALSE, { SINGLE_SYMBOL, "(" },       Q3, SUBMACHINE_NULL },
                { FALSE, { SINGLE_SYMBOL, "=" },       Q4, SUBMACHINE_NULL },
                { FALSE, { SINGLE_SYMBOL, "!" },       Q4, SUBMACHINE_NULL },
                { FALSE, { SINGLE_SYMBOL, ">" },       Q5, SUBMACHINE_NULL },
                { FALSE, { SINGLE_SYMBOL, "<" },       Q5, SUBMACHINE_NULL },
                { FALSE, { SINGLE_SYMBOL, "&" },       Q6, SUBMACHINE_NULL },
                { FALSE, { SINGLE_SYMBOL, "|" },       Q7, SUBMACHINE_NULL },
                EOR_TRANSITION },
      [Q2] =  { { FALSE, { SINGLE_SYMBOL, "(" },       Q3, SUBMACHINE_NULL },
                { FALSE, { SINGLE_SYMBOL, "=" },       Q4, SUBMACHINE_NULL },
                { FALSE, { SINGLE_SYMBOL, "!" },       Q4, SUBMACHINE_NULL },
                { FALSE, { SINGLE_SYMBOL, ">" },       Q5, SUBMACHINE_NULL },
                { FALSE, { SINGLE_SYMBOL, "<" },       Q5, SUBMACHINE_NULL },
                { FALSE, { SINGLE_SYMBOL, "&" },       Q6, SUBMACHINE_NULL },
                { FALSE, { SINGLE_SYMBOL, "|" },       Q7, SUBMACHINE_NULL },
                EOR_TRANSITION },
      [Q3] =  { { FALSE, { VARIABLE, EMPTY_VALUE },    Q11, SUBMACHINE_NULL },
                { FALSE, { INTEGER, EMPTY_VALUE },     Q11, SUBMACHINE_NULL },
                { FALSE, { FLOAT, EMPTY_VALUE },       Q11, SUBMACHINE_NULL },
                { FALSE, { RESERVED_WORD, "FALSE" },   Q11, SUBMACHINE_NULL },
                { FALSE, { RESERVED_WORD, "TRUE" },    Q11, SUBMACHINE_NULL },
                { TRUE,  { TRIGGER_NULL },             Q11, SUBMACHINE_CALL_FUNCTION },
                EOR_TRANSITION },
      [Q4] =  { { FALSE, { SINGLE_SYMBOL, "=" },       Q8, SUBMACHINE_NULL },
                EOR_TRANSITION },
      [Q5] =  { { FALSE, { SINGLE_SYMBOL, "=" },       Q8, SUBMACHINE_NULL },
                { FALSE, { VARIABLE, EMPTY_VALUE },    Q10, SUBMACHINE_NULL },
                { FALSE, { INTEGER, EMPTY_VALUE },     Q10, SUBMACHINE_NULL },
                { FALSE, { FLOAT, EMPTY_VALUE },       Q10, SUBMACHINE_NULL },
                { FALSE, { RESERVED_WORD, "FALSE" },   Q10, SUBMACHINE_NULL },
                { FALSE, { RESERVED_WORD, "TRUE" },    Q10, SUBMACHINE_NULL },
                { FALSE, { IDENTIFIER, EMPTY_VALUE },  Q9, SUBMACHINE_NULL },
                { TRUE,  { TRIGGER_NULL },             Q10, SUBMACHINE_ARITH_EXP },
                EOR_TRANSITION },
      [Q6] =  { { FALSE, { SINGLE_SYMBOL, "&" },       Q8, SUBMACHINE_NULL },
                EOR_TRANSITION },
      [Q7] =  { { FALSE, { SINGLE_SYMBOL, "|" },       Q8, SUBMACHINE_NULL },
                EOR_TRANSITION },
      [Q8] =  { { FALSE, { VARIABLE, EMPTY_VALUE },    Q10, SUBMACHINE_NULL },
                { FALSE, { INTEGER, EMPTY_VALUE },     Q10, SUBMACHINE_NULL },
                { FALSE, { FLOAT, EMPTY_VALUE },       Q10, SUBMACHINE_NULL },
                { FALSE, { RESERVED_WORD, "FALSE" },   Q10, SUBMACHINE_NULL },
                { FALSE, { RESERVED_WORD, "TRUE" },    Q10, SUBMACHINE_NULL },
                { FALSE, { IDENTIFIER, EMPTY_VALUE },  Q9, SUBMACHINE_NULL },
                { TRUE,  { TRIGGER_NULL },             Q10, SUBMACHINE_ARITH_EXP },
                EOR_TRANSITION },
      [Q9] =  { { FALSE, { SINGLE_SYMBOL, "(" },       Q12, SUBMACHINE_NULL },
                { TRUE,  { TRIGGER_NULL },             QF, SUBMACHINE_NULL },
                EOR_TRANSITION },
      [Q10] = { { TRUE,  { TRIGGER_NULL },             QF, SUBMACHINE_NULL },
                EOR_TRANSITION },
      [Q11] = { { FALSE, { SINGLE_SYMBOL, ")" },       Q2, SUBMACHINE_NULL },
                { FALSE, { SINGLE_SYMBOL, "," },       Q3, SUBMACHINE_NULL },
                EOR_TRANSITION },
      [Q12] = { { FALSE, { VARIABLE, EMPTY_VALUE },    Q13, SUBMACHINE_NULL },
                { FALSE, { INTEGER, EMPTY_VALUE },     Q13, SUBMACHINE_NULL },
                { FALSE, { FLOAT, EMPTY_VALUE },       Q13, SUBMACHINE_NULL },
                { FALSE, { RESERVED_WORD, "FALSE" },   Q13, SUBMACHINE_NULL },
                { FALSE, { RESERVED_WORD, "TRUE" },    Q13, SUBMACHINE_NULL },
                { TRUE,  { TRIGGER_NULL },             Q13, SUBMACHINE_CALL_FUNCTION },
                EOR_TRANSITION },
      [Q13] = { { FALSE, { SINGLE_SYMBOL, ")" },       Q10, SUBMACHINE_NULL },
                { FALSE, { SINGLE_SYMBOL, "," },       Q12, SUBMACHINE_NULL },
                EOR_TRANSITION },
      [QF] =  { EOR_TRANSITION },
    }
  },
  [SUBMACHINE_CONDITIONAL] = {
    SUBMACHINE_CONDITIONAL,
    Q0,
    {
      [Q0] =  { { TRUE,  { TRIGGER_NULL },             Q1, SUBMACHINE_CONDITION },
                EOR_TRANSITION },
      [Q1] =  { { FALSE, { RESERVED_WORD, "then" },    Q2, SUBMACHINE_NULL },
                EOR_TRANSITION },
      [Q2] =  { { TRUE,  { TRIGGER_NULL },             Q3, SUBMACHINE_COMMANDS },
                EOR_TRANSITION },
      [Q3] =  { { FALSE, { RESERVED_WORD, "else" },    Q4, SUBMACHINE_NULL },
                { FALSE, { RESERVED_WORD, "fend" },    QF, SUBMACHINE_NULL },
                EOR_TRANSITION },
      [Q4] =  { { TRUE,  { TRIGGER_NULL },             Q5, SUBMACHINE_COMMANDS },
                EOR_TRANSITION },
      [Q5] = { { FALSE, { RESERVED_WORD, "lend" },    Q6, SUBMACHINE_NULL },
                EOR_TRANSITION },
      [Q6] = { { FALSE, { RESERVED_WORD, "fend" },    QF, SUBMACHINE_NULL },
                EOR_TRANSITION },
      [QF] =  { EOR_TRANSITION },
    }
  },
  [SUBMACHINE_ITERATION] = {
    SUBMACHINE_ITERATION,
    Q0,
    {
      [Q0] =  { { TRUE,  { TRIGGER_NULL },             Q1, SUBMACHINE_CONDITION },
                EOR_TRANSITION },
      [Q1] =  { { FALSE, { RESERVED_WORD, "then" },    Q2, SUBMACHINE_NULL },
                EOR_TRANSITION },
      [Q2] =  { { TRUE,  { TRIGGER_NULL },             Q3, SUBMACHINE_COMMANDS },
                EOR_TRANSITION },
      [Q3] =  { { FALSE, { RESERVED_WORD, "wend" },    QF, SUBMACHINE_NULL },
                EOR_TRANSITION },
      [QF] =  { EOR_TRANSITION },
    }
  },
  [SUBMACHINE_CONDITION] = {
    SUBMACHINE_CONDITION,
    Q0,
    {
      [Q0] =  { { FALSE, { SINGLE_SYMBOL, "!" },       Q1, SUBMACHINE_NULL },
                { TRUE,  { TRIGGER_NULL },             QF, SUBMACHINE_BOOL_EXP },
                EOR_TRANSITION },
      [Q1] =  { { TRUE,  { TRIGGER_NULL },             QF, SUBMACHINE_BOOL_EXP },
                EOR_TRANSITION },
      [Q2] =  { { FALSE, { SINGLE_SYMBOL, "=" },       Q0, SUBMACHINE_NULL },
                EOR_TRANSITION },
      [Q3] =  { { FALSE, { SINGLE_SYMBOL, "=" },       Q0, SUBMACHINE_NULL },
                { FALSE, { SINGLE_SYMBOL, "!" },       Q1, SUBMACHINE_NULL },
                { TRUE,  { TRIGGER_NULL },             QF, SUBMACHINE_BOOL_EXP },
                EOR_TRANSITION },
      [Q4] =  { { FALSE, { SINGLE_SYMBOL, "&" },       Q0, SUBMACHINE_NULL },
                EOR_TRANSITION },
      [Q5] =  { { FALSE, { SINGLE_SYMBOL, "|" },       Q0, SUBMACHINE_NULL },
                EOR_TRANSITION },
      [QF] =  { { FALSE, { SINGLE_SYMBOL, "!" },       Q2, SUBMACHINE_NULL },
                { FALSE, { SINGLE_SYMBOL, "=" },       Q2, SUBMACHINE_NULL },
                { FALSE, { SINGLE_SYMBOL, ">" },       Q3, SUBMACHINE_NULL },
                { FALSE, { SINGLE_SYMBOL, "<" },       Q3, SUBMACHINE_NULL },
                { FALSE, { SINGLE_SYMBOL, "&" },       Q4, SUBMACHINE_NULL },
                { FALSE, { SINGLE_SYMBOL, "|" },       Q5, SUBMACHINE_NULL },
                EOR_TRANSITION },
    }
  },
  [SUBMACHINE_OUTPUT] = {
    SUBMACHINE_OUTPUT,
    Q0,
    {
      [Q0] =  { { FALSE, { VARIABLE, EMPTY_VALUE },    Q1, SUBMACHINE_NULL },
                { FALSE, { STRING, EMPTY_VALUE },      Q1, SUBMACHINE_NULL },
                { FALSE, { IDENTIFIER, EMPTY_VALUE },  Q2, SUBMACHINE_NULL },
                { TRUE,  { TRIGGER_NULL },             Q1, SUBMACHINE_ARITH_EXP },
                EOR_TRANSITION },
      [Q1] =  { { FALSE, { SINGLE_SYMBOL, "," },       Q0, SUBMACHINE_NULL },
                { FALSE, { SINGLE_SYMBOL, ";" },       QF, SUBMACHINE_NULL },
                EOR_TRANSITION },
      [Q2] =  { { FALSE, { SINGLE_SYMBOL, "," },       Q0, SUBMACHINE_NULL },
                { FALSE, { SINGLE_SYMBOL, ";" },       QF, SUBMACHINE_NULL },
                { FALSE, { SINGLE_SYMBOL, "(" },       Q3, SUBMACHINE_NULL },
                EOR_TRANSITION },
      [Q3] =  { { FALSE, { VARIABLE, EMPTY_VALUE },    Q4, SUBMACHINE_NULL },
                { FALSE, { INTEGER, EMPTY_VALUE },     Q4, SUBMACHINE_NULL },
                { FALSE, { FLOAT, EMPTY_VALUE },       Q4, SUBMACHINE_NULL },
                { FALSE, { RESERVED_WORD, "FALSE" },   Q4, SUBMACHINE_NULL },
                { FALSE, { RESERVED_WORD, "TRUE" },    Q4, SUBMACHINE_NULL },
                { TRUE,  { TRIGGER_NULL },             Q4, SUBMACHINE_CALL_FUNCTION },
                EOR_TRANSITION },
      [Q4] =  { { FALSE, { SINGLE_SYMBOL, "," },       Q3, SUBMACHINE_NULL },
                { FALSE, { SINGLE_SYMBOL, ")" },       Q1, SUBMACHINE_NULL },
                EOR_TRANSITION },
      [QF] =  { EOR_TRANSITION },
    }
  }
};

char submachine_debug_names[256][256] = {
  [SUBMACHINE_PROGRAM] = "Automata Program",
  [SUBMACHINE_DEF_FUNCTION] = "Automata Definition Function",
  [SUBMACHINE_DECLARATION] = "Automata Declaration",
  [SUBMACHINE_COMMANDS] = "Automata Commands",
  [SUBMACHINE_ATTRIBUTION] = "Automata Attribution",
  [SUBMACHINE_CALL_FUNCTION] = "Automata Call Function",
  [SUBMACHINE_CONDITIONAL] = "Automata Conditional",
  [SUBMACHINE_ITERATION] = "Automata Iteration",
  [SUBMACHINE_CONDITION] = "Automata Condition",
  [SUBMACHINE_ARITH_EXP] = "Automata Arithmetic Expression",
  [SUBMACHINE_BOOL_EXP] = "Automata Boolean Expression",
  [SUBMACHINE_OUTPUT] = "Automata Output",
};

BOOL tokenUsed = TRUE;

node * Stack_Get_node(sm_stack_pair sm_pair);
void Stack_Init(node **top);
void Stack_Push(sm_stack_pair sm_pair, node **top);
void Stack_Display(node **head);
sm_stack_pair Stack_Pop(node **top);
int Stack_Empty(node *temp);

void Stack_Init(node **top) {
  *top = NULL;
}

void Stack_Push(sm_stack_pair sm_pair, node **top) {
  node *New;
  node * Stack_Get_node(sm_stack_pair);
  New = Stack_Get_node(sm_pair);
  New->next = *top;
  *top = New;
}

node * Stack_Get_node(sm_stack_pair sm_pair) {
  node * temp;
  temp = (node *) malloc(sizeof(node));
  if (temp == NULL)
    printf("\nMemory Cannot be allocated");
  temp->sm_pair = sm_pair;
  temp->next = NULL;
  return (temp);
}

int Stack_Empty(node *temp) {
  if (temp == NULL)
    return 1;
  else
    return 0;
}

sm_stack_pair Stack_Pop(node **top) {
  sm_stack_pair sm_pair;
  node *temp;
  sm_pair = (*top)->sm_pair;
  temp = *top;
  *top = (*top)->next;
  free(temp);
  return sm_pair;
}

void Stack_Display(node **head) {
  node *temp;
  temp = *head;
  if (Stack_Empty(temp))
    printf("\nThe stack is empty!");
  else {
    while (temp != NULL) {
      printf("%d\n", temp->sm_pair.state);
      temp = temp->next;
    }
  }
}

void read_file(char* file_name) {

    FILE *input_file;
    input_file = fopen(file_name, "r");
    if (input_file == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return;
    }
    BOOL endOfProgram = FALSE;
    TOKEN token;
    BOOL wasTokenFound = FALSE;
    STRUCTURED_AUTOMATA *automata = &SUBMACHINE_LIST[SUBMACHINE_PROGRAM];

  Stack *stack;
  Stack_Init(&stack);

    while (!endOfProgram) {
      if (tokenUsed) {
        wasTokenFound = get_token(input_file, &token,  &endOfProgram);
        if (wasTokenFound) {
          print_token(token);
          tokenUsed = FALSE;
          if (run_automata(&automata, token, &stack) == FALSE) {
            #ifdef DEBUG
            printf("[DEBUG] Unexpected token!\n");
            #endif
            break;
          }
        } else {
          if (endOfProgram) {
            if(automata->current_state != QF) {
              printf("ERRO: Programa incompleto!\n");
            } else {
              printf("Program recognized! No errors occured!\n");
            }
          }
        }
      }
    }

    fclose(input_file);
}

// Receaves a automata and a token
// Calculate next state
BOOL run_automata (STRUCTURED_AUTOMATA **automata, TOKEN token, Stack **stack) {
  int state = (*automata)->current_state;
  for (int i = 0; (*automata)->transitions[state][i].next_state != EOR; i++) {
    STRUCTURED_AUTOMATA_TRANSITION transition = (*automata)->transitions[state][i];
    if (transition.is_submachine_transition == FALSE) {
      if (compare_token_values(transition.trigger, token)) {
        // this is a non-submachine transition
        tokenUsed = TRUE;
        #ifdef DEBUG
        printf("[DEBUG] Make transition from state: %d to %d (%s) \n\n\n", (*automata)->current_state, transition.next_state,
                                                                            submachine_debug_names[(*automata)->automata_id]);
        #endif
        (*automata)->current_state = transition.next_state;
        return TRUE;
      }
    } else {
      if(transition.next_submachine == SUBMACHINE_NULL) { //empty transition
        (*automata)->current_state = transition.next_state;
      } else {
        // this is a submachine transition
        sm_stack_pair pair;
        pair.sm = (*automata)->automata_id;
        pair.state = transition.next_state;

        #ifdef DEBUG
        printf("[DEBUG] Pushed to stack: ");
        print_stack_pair(pair);
        printf("[DEBUG] Chaging to automata: %s\n\n\n", submachine_debug_names[transition.next_submachine]);
        #endif

        Stack_Push(pair, stack);

        (*automata) = &SUBMACHINE_LIST[transition.next_submachine];
        (*automata)->current_state = Q0;
        run_automata(automata, token, stack);

        return TRUE;
      }
    }
  }
  // here, no transition was found
  // lets take a look at the stack

  if (Stack_Empty(*stack) == FALSE && (*automata)->current_state == QF) {
    //First we re-initialize the automata thay just finished
    (*automata)->current_state = Q0;
    // Lets get back to the stacked automata
    sm_stack_pair pair = Stack_Pop(stack);
    (*automata) = &SUBMACHINE_LIST[pair.sm];
    (*automata)->current_state = pair.state;

    #ifdef DEBUG
    printf("[DEBUG] Pop from stack: ");
    print_stack_pair(pair);
    printf("[DEBUG] Changing to automata: %s\n", submachine_debug_names[pair.sm]);
    printf("[DEBUG] Going into state: %d\n\n", pair.state);
    #endif
    run_automata(automata, token, stack);
    return TRUE;
  }
  // case it hits here
  // unespected token was found
  return FALSE;
}

// Used to compare two tokens
BOOL compare_token_values(STRUCTURED_AUTOMATA_TOKEN t1, TOKEN t2) {
  // some tokens can be compared only by class
  // others must be compared with class and value
  char *t2value = get_token_value(t2.token_class, t2.table_index);
  switch (t2.token_class)
  {
    case RESERVED_WORD:
    case SINGLE_SYMBOL:
      if (t2.token_class == t1.class
          && strcmp(t1.value, t2value) == 0)
        return TRUE;
      break;
    default:
      if (t2.token_class == t1.class)
        return TRUE;
      break;
  }
  return FALSE;
}

void print_stack_pair(sm_stack_pair pair) {
  printf("(%d,%d)\n", pair.sm, pair.state);
}