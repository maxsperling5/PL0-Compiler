/************************/
/* Author: Max Sperling */
/************************/

#ifndef GENERATOR
#define GENERATOR

#include "../Lexer/Token.cpp"
#include "./SymbolTab.cpp"
#include <vector>
#include <stack>
#include <cstdint>
#include <string>
#include <typeinfo>
#include <iostream>
using namespace std;

class Generator
{
private:
    vector<unsigned char> binary;
    SymbolTab symbolTab;
    stack<unsigned int> procStartAddr;
    unsigned char cmpOp;
    stack<unsigned int> jumpStartAddr;

public:
    Generator(){}

    vector<unsigned char> getBinary()
    {
        return binary;
    }

private:
    enum Bytecode
    {
        /*--- Stack instructions ---*/
        PuValVrLocl,    /*00 (short Displ)  [Kellern Wert lokale  Variable]             */
        PuValVrMain,    /*01 (short Displ)  [Kellern Wert Main    Variable]             */
        PuValVrGlob,    /*02 (short Displ,short Proc)  [Kellern Wert globale Variable]  */
        PuAdrVrLocl,    /*03 (short Displ)  [Kellern Adresse lokale  Variable]          */
        PuAdrVrMain,    /*04 (short Displ)  [Kellern Adresse Main    Variable]          */
        PuAdrVrGlob,    /*05 (short Displ,short Proc) [Kellern Adresse globale Variable]*/
        PuConst,        /*06 (short Index)  [Kellern einer Konstanten]                  */
        StoreVal,       /*07 ()           [Speichern Wert -> Adresse, beides aus Keller]*/
        PutVal,         /*08 ()           [Ausgabe eines Wertes aus Keller nach stdout] */
        GetVal,         /*09 ()           [Eingabe eines Wertes von  stdin -> Keller ]  */
        /*--- Arithmetic instructions ---*/
        VzMinus,        /*0A ()           [Vorzeichen -]                                */
        OpOdd,          /*0B ()           [ungerade -> 0/1]                             */
        OpAdd,          /*0C ()           [Addition]                                    */
        OpSub,          /*0D ()           [Subtraktion ]                                */
        OpMult,         /*0E ()           [Multiplikation ]                             */
        OpDiv,          /*0F ()           [Division ]                                   */
        CmpEq,          /*10 ()           [Vergleich = -> 0/1]                          */
        CmpNe,          /*11 ()           [Vergleich # -> 0/1]                          */
        CmpLt,          /*12 ()           [Vergleich < -> 0/1]                          */
        CmpGt,          /*13 ()           [Vergleich > -> 0/1]                          */
        CmpLe,          /*14 ()           [Vergleich <=-> 0/1]                          */
        CmpGe,          /*15 ()           [Vergleich >=-> 0/1]                          */
        /*--- Jump instructions ---*/
        Call,           /*16 (short ProzNr) [Prozeduraufruf]                            */
        RetProc,        /*17 ()           [Ruecksprung]                                 */
        Jmp,            /*18 (short RelAdr) [SPZZ innerhalb der Funktion]               */
        Jnot,           /*19 (short RelAdr) [SPZZ innerhalb der Funkt.,Beding.aus Keller]*/
        EntryProc,      /*1A (short lenCode,short ProcIdx,lenVar)                       */
        /*--- Additional instructions ---*/
        PutStrg,        /*1B (char[])                                                   */
        Pop,            /*1C               Entfernt einen Wert aus dem Stack            */
        Swap,           /*1D               Austausch Adressse gegen Wert                */
    };

public:
    void AddSymbol(void *tok)
    {
        symbolTab.addSymbol(((Token*)tok)->getVal());
    }

    void AddProcedure(void *tok)
    {
        symbolTab.addProcedure();
    }

    void RetProcedure(void *tok)
    {
        symbolTab.retProcedure();
    }

    void AddVariable(void *tok)
    {
        symbolTab.addVariable();
    }

    void AddConstant(void *tok)
    {
        symbolTab.addConstant(stol(((Token*)tok)->getVal()));
    }

    void CodeStart(void *tok)
    {
        writeInt(0);
    }

    void ProcedureStart(void *tok)
    {
        procStartAddr.push(binary.size()+sizeof(unsigned char));
        vector<unsigned short> param;
        param.push_back(0);
        param.push_back(symbolTab.getCurProcIdx());
        param.push_back(symbolTab.getCurProcNumVar()*sizeof(int));
        writeCode(Bytecode::EntryProc, param);
    }

    void ProcedureEnd(void *tok)
    {
        unsigned short distProc = binary.size()-procStartAddr.top();
        writeShortToAddr(procStartAddr.top(), distProc);
        procStartAddr.pop();
        writeCode(Bytecode::RetProc);
    }

    void BeforeAssignment(void *tok)
    {
        pushVarByName((Token*)tok, Addr);
    }

    void AfterAssignment(void *tok)
    {
        writeCode(Bytecode::StoreVal);
    }

    void InputNumber(void *tok)
    {
        pushVarByName((Token*)tok, Addr);
        writeCode(Bytecode::GetVal);
    }

    void OutputNumber(void *tok)
    {
        writeCode(Bytecode::PutVal);
    }

    void Negation(void *tok)
    {
        writeCode(Bytecode::VzMinus);
    }

    void Addition(void *tok)
    {
        writeCode(Bytecode::OpAdd);
    }

    void Subtraction(void *tok)
    {
        writeCode(Bytecode::OpSub);
    }

    void Multiplication(void *tok)
    {
        writeCode(Bytecode::OpMult);
    }

    void Division(void *tok)
    {
        writeCode(Bytecode::OpDiv);
    }

    void ConstByVal(void *tok)
    {
        pushConstByVal((Token*)tok);
    }

    void IdentByName(void *tok)
    {
        pushVarByName((Token*)tok, Val);
        pushConstByName((Token*)tok);
    }

    void Odd(void *tok)
    {
        writeCode(Bytecode::OpOdd);
    }

    void Equal(void *tok)
    {
        cmpOp = Bytecode::CmpEq;
    }

    void NotEqual(void *tok)
    {
        cmpOp = Bytecode::CmpNe;
    }

    void Smaller(void *tok)
    {
        cmpOp = Bytecode::CmpLt;
    }

    void Larger(void *tok)
    {
        cmpOp = Bytecode::CmpGt;
    }

    void LessOrEqual(void *tok)
    {
        cmpOp = Bytecode::CmpLe;
    }

    void GreaterOrEqual(void *tok)
    {
        cmpOp = Bytecode::CmpGe;
    }

    void Comparison(void *tok)
    {
        writeCode((Bytecode)cmpOp);
    }

    void Condition(void *tok)
    {
        vector<unsigned short> param;
        param.push_back(0);
        writeCode(Bytecode::Jnot, param);
        jumpStartAddr.push(binary.size());
    }

    void BranchEnd(void *tok)
    {
        unsigned short distCond = binary.size()-jumpStartAddr.top();
        writeShortToAddr(jumpStartAddr.top(), distCond);
        jumpStartAddr.pop();
    }

    void While(void *tok)
    {
        jumpStartAddr.push(binary.size());
    }

    void LoopEnd(void *tok)
    {
        unsigned short distCond = binary.size()-jumpStartAddr.top()+sizeof(unsigned char)+sizeof(short);
        writeShortToAddr(jumpStartAddr.top()-sizeof(short), distCond);
        jumpStartAddr.pop();

        unsigned short distWhile = jumpStartAddr.top()-binary.size()-sizeof(short);
        vector<unsigned short> param;
        param.push_back(distWhile);
        writeCode(Bytecode::Jmp, param);
        jumpStartAddr.pop();
    }

    void CallPrecedure(void *tok)
    {
        SymbolTab::Symbol *symb = symbolTab.searchSymb(((Token*)tok)->getVal());
        if(symb == nullptr)
            return;
        // check type

        vector<unsigned short> param;
        param.push_back(symb->object->index);
        writeCode(Bytecode::Call, param);
    }

    void OutputString(void *tok)
    {
        writeCode(Bytecode::PutStrg);
        writeString(((Token*)tok)->getVal());
    }

    void CodeEnd(void *tok)
    {
        for(auto &cons : symbolTab.vecConst)
        {
            writeInt(cons);
        }
        writeIntToAddr(0, symbolTab.numProc);
    }

private:
    void writeCode(Bytecode code, vector<unsigned short> param = vector<unsigned short>())
    {
        binary.push_back(code);

        for(unsigned short par : param)
        {
            binary.push_back(par & 0xff);
            binary.push_back((par >> 8) & 0xff);
        }
    }

    void writeString(string value)
    {
        vector<unsigned char> vecVal(value.begin(), value.end());
        for(auto &val : vecVal)
        {
            binary.push_back(val);
        }
        binary.push_back(0);
    }

    void writeInt(int value)
    {
        binary.push_back(value & 0xff);
        binary.push_back((value >> 8) & 0xff);
        binary.push_back((value >> 16) & 0xff);
        binary.push_back((value >> 24) & 0xff);
    }

    void writeShortToAddr(unsigned int startAddr, unsigned short value)
    {
        binary.at(startAddr) = (value & 0xff);
        binary.at(startAddr+1) = ((value >> 8) & 0xff);
    }

    void writeIntToAddr(unsigned int startAddr, unsigned int value)
    {
        binary.at(startAddr) = (value & 0xff);
        binary.at(startAddr+1) = ((value >> 8) & 0xff);
        binary.at(startAddr+2) = ((value >> 16) & 0xff);
        binary.at(startAddr+3) = ((value >> 24) & 0xff);
    }

    enum AddrOrVal
    {
        Addr,
        Val
    };

    bool pushVarByName(Token *tok, AddrOrVal addrOrVal)
    {
        SymbolTab::Symbol *symb = symbolTab.searchSymb(tok->getVal());
        if(symb == nullptr)
            return false;
        // check type

        vector<unsigned short> param;
        param.push_back((symb->object->index)*sizeof(int));

        if(symb->procIdx == symbolTab.getCurProcIdx())
        {
            switch(addrOrVal)
            {
            case Addr:
                writeCode(Bytecode::PuAdrVrLocl, param);
                break;
            case Val:
                writeCode(Bytecode::PuValVrLocl, param);
                break;
            }

        }
        else if(symb->procIdx == 0)
        {
            switch(addrOrVal)
            {
            case Addr:
                writeCode(Bytecode::PuAdrVrMain, param);
                break;
            case Val:
                writeCode(Bytecode::PuValVrMain, param);
                break;
            }
        }
        else
        {
            param.push_back(symb->procIdx);
            switch(addrOrVal)
            {
            case Addr:
                writeCode(Bytecode::PuAdrVrGlob, param);
                break;
            case Val:
                writeCode(Bytecode::PuValVrGlob, param);
                break;
            }
        }
        return true;
    }

    bool pushConstByName(Token *tok)
    {
        SymbolTab::Symbol *symb = symbolTab.searchSymb(tok->getVal());
        if(symb == nullptr)
            return false;
        // check type

        vector<unsigned short> param;
        param.push_back(((SymbolTab::Constant*)symb->object)->value);
        writeCode(Bytecode::PuConst, param);
        return true;
    }

    bool pushConstByVal(Token *tok)
    {
        vector<unsigned short> param;

        for(unsigned int i=0; i<symbolTab.vecConst.size(); i++)
        {
            if(symbolTab.vecConst.at(i) == stol(tok->getVal()))
            {
                param.push_back(i);
                writeCode(Bytecode::PuConst, param);
                return true;
            }
        }

        param.push_back(symbolTab.vecConst.size());
        writeCode(Bytecode::PuConst, param);
        symbolTab.addConstNum(stol(tok->getVal()));
        return true;
    }
};

#endif
