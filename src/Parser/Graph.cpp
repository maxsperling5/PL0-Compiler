/************************/
/* Author: Max Sperling */
/************************/

#ifndef GRAPH
#define GRAPH

#include "./Trans.cpp"
#include "../Lexer/Token.cpp"
#include "../Generator/Generator.cpp"
#include <vector>
using namespace std;

class Graph
{
public:
    Trans program[4];
    Trans block[21];
    Trans statement[26];
    Trans condition[11];
    Trans expression[8];
    Trans term[7];
    Trans factor[6];

    Graph() :
    program
    {
    /* 0*/ Trans(Trans::Nil,        nullptr, 1, 0, Generator::CodeStart),    /*(A)----------->(B)*/
    /* 1*/ Trans(Trans::GraphStart, &block,  2, 0, nullptr),                 /*(B)---BLOCK--->(C)*/
    /* 2*/ Trans(Trans::Symbol,     ".",     3, 0, Generator::ProcedureEnd), /*(C)----'.'---->(D)*/
    /* 3*/ Trans(Trans::GraphEnd,   nullptr, 0, 0, Generator::CodeEnd)       /*(D)----------(END)*/
    },
    block
    {
    /* 0*/ Trans(Trans::Symbol,     "CONST",                   2,  1, nullptr),                   /*(A)--->CONST--->(B)*/
    /* 1*/ Trans(Trans::Nil,        nullptr,                   7,  0, nullptr),                   /* +------------->(F)*/
    /* 2*/ Trans(Trans::Token,      (void*)Token::Identifier,  3,  0, Generator::AddSymbol),      /*(B)----ident--->(C)*/
    /* 3*/ Trans(Trans::Symbol,     "=",                       4,  0, nullptr),                   /*(C)-----'='-----(D)*/
    /* 4*/ Trans(Trans::Token,      (void*)Token::Number,      5,  0, Generator::AddConstant),    /*(D)--->number-->(E)*/
    /* 5*/ Trans(Trans::Symbol,     ",",                       2,  6, nullptr),                   /*(E)-----','-----(B)*/
    /* 6*/ Trans(Trans::Symbol,     ";",                       7,  0, nullptr),                   /* +------';'-----(F)*/
    /* 7*/ Trans(Trans::Symbol,     "VAR",                     9,  8, nullptr),                   /*(F)--->VAR----->(G)*/
    /* 8*/ Trans(Trans::Nil,        nullptr,                  12,  0, nullptr),                   /* +------------->(J)*/
    /* 9*/ Trans(Trans::Token,      (void*)Token::Identifier, 10,  0, Generator::AddSymbol),      /*(G)----ident--->(H)*/
    /*10*/ Trans(Trans::Symbol,     ",",                       9, 11, Generator::AddVariable),    /*(H)-----','-----(G)*/
    /*11*/ Trans(Trans::Symbol,     ";",                      12,  0, Generator::AddVariable),    /*(H)-----';'-----(I)*/
    /*12*/ Trans(Trans::Symbol,     "PROCEDURE",              14, 13, nullptr),                   /*(I)->PROCEDURE->(J)*/
    /*13*/ Trans(Trans::Nil,        nullptr,                  19,  0, Generator::ProcedureStart), /* +--------------(O)*/
    /*14*/ Trans(Trans::Token,      (void*)Token::Identifier, 15,  0, Generator::AddSymbol),      /*(J)----ident--->(K)*/
    /*15*/ Trans(Trans::Symbol,     ";",                      16,  0, Generator::AddProcedure),   /*(K)-----';'-----(L)*/
    /*16*/ Trans(Trans::GraphStart, &block,                   17,  0, nullptr),                   /*(L)----block----(M)*/
    /*17*/ Trans(Trans::Symbol,     ";",                      18,  0, Generator::ProcedureEnd),   /*(M)-----';'-----(N)*/
    /*18*/ Trans(Trans::Nil,        nullptr,                  12,  0, Generator::RetProcedure),   /*(N)------------>(I)*/
    /*19*/ Trans(Trans::GraphStart, &statement,               20,  0, nullptr),                   /*(O)--statement->(P)*/
    /*20*/ Trans(Trans::GraphEnd,   nullptr,                   0,  0, nullptr)                    /*(P)-----------(END)*/
    },
    statement
    {
    /* 0*/ Trans(Trans::Token,      (void*)Token::Identifier,  1,  3, Generator::BeforeAssignment), /*(A)----ident--->(B)*/
    /* 1*/ Trans(Trans::Symbol,     ":=",                      2,  0, nullptr),                     /*(B)-----':='----(C)*/
    /* 2*/ Trans(Trans::GraphStart, &expression,              25,  0, Generator::AfterAssignment),  /*(C)-expression->(Q)*/
    /* 3*/ Trans(Trans::Symbol,     "IF",                      4,  7, nullptr),                     /* +------IF------(D)*/
    /* 4*/ Trans(Trans::GraphStart, &condition,                5,  0, Generator::Condition),        /*(D)--condition->(E)*/
    /* 1*/ Trans(Trans::Symbol,     "THEN",                    6,  0, nullptr),                     /*(E)--->THEN---->(F)*/
    /* 2*/ Trans(Trans::GraphStart, &statement,               25,  0, Generator::BranchEnd),        /*(F)--statement->(Q)*/
    /* 7*/ Trans(Trans::Symbol,     "WHILE",                   8, 11, Generator::While),            /* +-----WHILE----(G)*/
    /* 8*/ Trans(Trans::GraphStart, &condition,                9,  0, Generator::Condition),        /*(G)--condition->(H)*/
    /* 9*/ Trans(Trans::Symbol,     "DO",                     10,  0, nullptr),                     /*(H)---->DO----->(I)*/
    /*10*/ Trans(Trans::GraphStart, &statement,               25,  0, Generator::LoopEnd),          /*(I)--statement->(Q)*/
    /*11*/ Trans(Trans::Symbol,     "BEGIN",                  12, 15, nullptr),                     /* +-----BEGIN----(J)*/
    /*12*/ Trans(Trans::GraphStart, &statement,               13,  0, nullptr),                     /*(J)--statement->(K)*/
    /*13*/ Trans(Trans::Symbol,     ";",                      12, 14, nullptr),                     /*(K)-----';'---->(J)*/
    /*14*/ Trans(Trans::Symbol,     "END",                    25,  0, nullptr),                     /*(K)-----END---->(Q)*/
    /*15*/ Trans(Trans::Symbol,     "CALL",                   16, 17, nullptr),                     /* +-----CALL-----(L)*/
    /*16*/ Trans(Trans::Token,      (void*)Token::Identifier, 25,  0, Generator::CallPrecedure),    /*(L)----ident--->(Q)*/
    /*17*/ Trans(Trans::Symbol,     "?",                      18, 19, nullptr),                     /* +------'?'-----(M)*/
    /*18*/ Trans(Trans::Token,      (void*)Token::Identifier, 25,  0, Generator::InputNumber),      /*(M)----ident--->(Q)*/
    /*19*/ Trans(Trans::Symbol,     "!",                      20, 24, nullptr),                     /* +------'!'-----(N)*/
    /*20*/ Trans(Trans::Symbol,     "\"",                     21, 23, nullptr),                     /*(N)-----'"'---->(O)*/
    /*21*/ Trans(Trans::Token,      (void*)Token::String,     22,  0, Generator::OutputString),    /*(O)---string--->(P)*/
    /*22*/ Trans(Trans::Symbol,     "\"",                     25,  0, nullptr),                     /*(P)-----'"'---->(Q)*/
    /*23*/ Trans(Trans::GraphStart, &expression,              25,  0, Generator::OutputNumber),     /* +--expression->(Q)*/
    /*24*/ Trans(Trans::Nil,        nullptr,                  25,  0, nullptr),                     /* +--------------(Q)*/
    /*25*/ Trans(Trans::GraphEnd,   nullptr,                   0,  0, nullptr)                      /*(Q)-----------(END)*/
    },
    condition
    {
    /* 0*/ Trans(Trans::Symbol,     "ODD",        1, 2, nullptr),                   /*(A)----ODD----->(D)*/
    /* 1*/ Trans(Trans::GraphStart, &expression, 10, 0, Generator::NotEqual),       /*(B)---express-->(E)*/
    /* 2*/ Trans(Trans::GraphStart, &expression,  3, 0, nullptr),                   /* +----express-->(C)*/
    /* 3*/ Trans(Trans::Symbol,     "=",          9, 4, Generator::Equal),          /*(C)----'='----->(D)*/
    /* 4*/ Trans(Trans::Symbol,     "#",          9, 5, Generator::NotEqual),       /* +-----'#'----->(D)*/
    /* 5*/ Trans(Trans::Symbol,     "<",          9, 6, Generator::Smaller),        /* +-----'<'----->(D)*/
    /* 6*/ Trans(Trans::Symbol,     "<=",         9, 7, Generator::LessOrEqual),    /* +-----'<='---->(D)*/
    /* 7*/ Trans(Trans::Symbol,     ">",          9, 8, Generator::Larger),         /* +-----'>'----->(D)*/
    /* 8*/ Trans(Trans::Symbol,     ">=",         9, 0, Generator::GreaterOrEqual), /* +-----'>='---->(D)*/
    /* 9*/ Trans(Trans::GraphStart, &expression, 10, 0, Generator::Comparison),     /*(D)---express-->(E)*/
    /*10*/ Trans(Trans::GraphEnd,   nullptr,      0, 0, nullptr)                    /*(E)-----------(END)*/
    },
    expression
    {
    /* 0*/ Trans(Trans::Symbol,     "-",     2,  1, Generator::Negation),    /*(A)----'-'----->(B)*/
    /* 1*/ Trans(Trans::Nil,        nullptr, 2,  0, nullptr),                /* +------------->(B)*/
    /* 2*/ Trans(Trans::GraphStart, &term,   3,  0, nullptr),                /*(B)----term---->(C)*/
    /* 3*/ Trans(Trans::Symbol,     "+",     4,  5, nullptr),                /*(C)-----'+'---->(D)*/
    /* 4*/ Trans(Trans::GraphStart, &term,   3,  0, Generator::Addition),    /*(D)----term---->(C)*/
    /* 5*/ Trans(Trans::Symbol,     "-",     6,  7, nullptr),                /* +------'-'---->(E)*/
    /* 6*/ Trans(Trans::GraphStart, &term,   3,  0, Generator::Subtraction), /*(E)----term---->(C)*/
    /* 7*/ Trans(Trans::GraphEnd,   nullptr, 0,  0, nullptr)                 /* +------------(END)*/
    },
    term
    {
    /* 0*/ Trans(Trans::GraphStart, &factor, 1, 0, nullptr),                   /*(A)---faktor--->(B)*/
    /* 1*/ Trans(Trans::Nil,        nullptr, 2, 0, nullptr),                   /*(B)------------>(C)*/
    /* 2*/ Trans(Trans::Symbol,     "*",     3, 4, nullptr),                   /*(C)----'*'----->(D)*/
    /* 3*/ Trans(Trans::GraphStart, &factor, 1, 0, Generator::Multiplication), /*(D)---faktor--->(B)*/
    /* 4*/ Trans(Trans::Symbol,     "/",     5, 6, nullptr),                   /* +-----'/'----->(E)*/
    /* 5*/ Trans(Trans::GraphStart, &factor, 1, 0, Generator::Division),       /*(E)---faktor--->(B)*/
    /* 6*/ Trans(Trans::GraphEnd,   nullptr, 0, 0, nullptr)                    /* +------------(END)*/
    },
    factor
    {
    /* 0*/ Trans(Trans::Token,      (void*)Token::Number,     5, 1, Generator::ConstByVal),  /*(A)---number--->(D)*/
    /* 1*/ Trans(Trans::Symbol,     "(",                      2, 4, nullptr),                /* +-----'('----->(B)*/
    /* 2*/ Trans(Trans::GraphStart, &expression,              3, 0, nullptr),                /*(B)---express-->(C)*/
    /* 3*/ Trans(Trans::Symbol,     ")",                      5, 0, nullptr),                /*(C)----')'----->(D)*/
    /* 4*/ Trans(Trans::Token,      (void*)Token::Identifier, 5, 0, Generator::IdentByName), /* +----ident---->(D)*/
    /* 5*/ Trans(Trans::GraphEnd,   nullptr,                  0, 0, nullptr)                 /*(D)-----------(END)*/
    }
    {}
};

#endif
