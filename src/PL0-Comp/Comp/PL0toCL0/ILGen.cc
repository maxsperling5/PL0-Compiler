/************************/
/* Author: Max Sperling */
/************************/

#include "ILGen.hh"

#include "CompEx.hh"

using namespace std;

deque<char> ILGen::getBinary()
{
    return binary;
}

void ILGen::AddSymbol(void *tok)
{
    symbols.addSymbol(((Token*)tok)->getVal());
}

void ILGen::AddProcedure(void *tok)
{
    symbols.addProcedure();
}

void ILGen::RetProcedure(void *tok)
{
    symbols.retProcedure();
}

void ILGen::AddVariable(void *tok)
{
    symbols.addVariable();
}

void ILGen::AddConstant(void *tok)
{
    symbols.addConstant(stol(((Token*)tok)->getVal()));
}

void ILGen::CodeStart(void *tok)
{
    writeInt(0);
}

void ILGen::ProcedureStart(void *tok)
{
    procStartAddr.push(binary.size()+sizeof(char));
    vector<short> param;
    param.push_back(0);
    param.push_back(symbols.getCurProcIdx());
    param.push_back(symbols.getCurProcNumVar()*sizeof(int));
    writeCode(Bytecode::EntryProc, param);
}

void ILGen::ProcedureEnd(void *tok)
{
    writeCode(Bytecode::RetProc);
    short distProc = binary.size()+sizeof(char)-procStartAddr.top();
    writeShortToAddr(procStartAddr.top(), distProc);
    procStartAddr.pop();
}

void ILGen::BeforeAssignment(void *tok)
{
    if(!pushVarByName((Token*)tok, Addr))
        throw CompEx((Token*)tok);
}

void ILGen::AfterAssignment(void *tok)
{
    writeCode(Bytecode::StoreVal);
}

void ILGen::InputNumber(void *tok)
{
    if(!pushVarByName((Token*)tok, Addr))
        throw CompEx((Token*)tok);
    writeCode(Bytecode::GetVal);
}

void ILGen::OutputNumber(void *tok)
{
    writeCode(Bytecode::PutVal);
}

void ILGen::Negation(void *tok)
{
    writeCode(Bytecode::VzMinus);
}

void ILGen::Addition(void *tok)
{
    writeCode(Bytecode::OpAdd);
}

void ILGen::Subtraction(void *tok)
{
    writeCode(Bytecode::OpSub);
}

void ILGen::Multiplication(void *tok)
{
    writeCode(Bytecode::OpMult);
}

void ILGen::Division(void *tok)
{
    writeCode(Bytecode::OpDiv);
}

void ILGen::ConstByVal(void *tok)
{
    pushConstByVal((Token*)tok);
}

void ILGen::IdentByName(void *tok)
{
    if(pushVarByName((Token*)tok, Val)) return;
    if(pushConstByName((Token*)tok)) return;
    throw CompEx((Token*)tok);
}

void ILGen::Odd(void *tok)
{
    writeCode(Bytecode::OpOdd);
}

void ILGen::Equal(void *tok)
{
    cmpOp = Bytecode::CmpEq;
}

void ILGen::NotEqual(void *tok)
{
    cmpOp = Bytecode::CmpNe;
}

void ILGen::Smaller(void *tok)
{
    cmpOp = Bytecode::CmpLt;
}

void ILGen::Larger(void *tok)
{
    cmpOp = Bytecode::CmpGt;
}

void ILGen::LessOrEqual(void *tok)
{
    cmpOp = Bytecode::CmpLe;
}

void ILGen::GreaterOrEqual(void *tok)
{
    cmpOp = Bytecode::CmpGe;
}

void ILGen::Comparison(void *tok)
{
    writeCode((Bytecode)cmpOp);
}

void ILGen::Condition(void *tok)
{
    vector<short> param;
    param.push_back(0);
    writeCode(Bytecode::Jnot, param);
    jumpStartAddr.push(binary.size());
}

void ILGen::BranchEnd(void *tok)
{
    short jmpAddr = jumpStartAddr.top();
    jumpStartAddr.pop();

    short distFromCond = binary.size()-jmpAddr;
    writeShortToAddr(jmpAddr-sizeof(short), distFromCond);
}

void ILGen::While(void *tok)
{
    jumpStartAddr.push(binary.size());
}

void ILGen::LoopEnd(void *tok)
{
    short jmpAddrIf = jumpStartAddr.top();
    jumpStartAddr.pop();
    short jmpAddrWhile = jumpStartAddr.top();
    jumpStartAddr.pop();

    vector<short> param;
    param.push_back(0);
    writeCode(Bytecode::Jmp, param);
    short distToWhile = -(binary.size()-jmpAddrWhile);
    writeShortToAddr(binary.size()-sizeof(short), distToWhile);

    short distFromCond = binary.size()-jmpAddrIf;
    writeShortToAddr(jmpAddrIf-sizeof(short), distFromCond);
}

void ILGen::CallProcedure(void *tok)
{
    if(!pushProcByName((Token*)tok))
        throw CompEx((Token*)tok);
}

void ILGen::OutputString(void *tok)
{
    writeCode(Bytecode::PutStrg);
    writeString(((Token*)tok)->getVal());
}

void ILGen::CodeEnd(void *tok)
{
    for(auto &cons : symbols.vecConst)
    {
        writeInt(cons);
    }
    writeIntToAddr(0, symbols.numProc);
}

void ILGen::writeCode(Bytecode code, vector<short> param)
{
    binary.push_back(code);

    for(short par : param)
    {
        binary.push_back(par & 0xff);
        binary.push_back((par >> 8) & 0xff);
    }
}

void ILGen::writeString(string value)
{
    vector<char> vecVal(value.begin(), value.end());
    for(auto &val : vecVal)
    {
        binary.push_back(val);
    }
    binary.push_back(0);
}

void ILGen::writeInt(int value)
{
    binary.push_back(value & 0xff);
    binary.push_back((value >> 8) & 0xff);
    binary.push_back((value >> 16) & 0xff);
    binary.push_back((value >> 24) & 0xff);
}

void ILGen::writeShortToAddr(int startAddr, short value)
{
    binary.at(startAddr) = (value & 0xff);
    binary.at(startAddr+1) = ((value >> 8) & 0xff);
}

void ILGen::writeIntToAddr(int startAddr, int value)
{
    binary.at(startAddr) = (value & 0xff);
    binary.at(startAddr+1) = ((value >> 8) & 0xff);
    binary.at(startAddr+2) = ((value >> 16) & 0xff);
    binary.at(startAddr+3) = ((value >> 24) & 0xff);
}

bool ILGen::pushVarByName(Token *tok, AddrOrVal addrOrVal)
{
    Symbols::Symbol *symb = symbols.searchSymb(tok->getVal());
    if(symb == nullptr) return false;
    if(symb->object->getType() != Symbols::Object::Var) return false;

    vector<short> param;
    param.push_back((symb->object->index)*sizeof(int));

    if(symb->procIdx == symbols.getCurProcIdx())
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

bool ILGen::pushConstByName(Token *tok)
{
    Symbols::Symbol *symb = symbols.searchSymb(tok->getVal());
    if(symb == nullptr) return false;
    if(symb->object->getType() != Symbols::Object::Cons) return false;

    vector<short> param;
    param.push_back(((Symbols::Constant*)symb->object)->value);
    writeCode(Bytecode::PuConst, param);
    return true;
}

bool ILGen::pushConstByVal(Token *tok)
{
    vector<short> param;

    for(unsigned int i=0; i<symbols.vecConst.size(); i++)
    {
        if(symbols.vecConst.at(i) == stol(tok->getVal()))
        {
            param.push_back(i);
            writeCode(Bytecode::PuConst, param);
            return true;
        }
    }

    param.push_back(symbols.vecConst.size());
    writeCode(Bytecode::PuConst, param);
    symbols.addConstNum(stol(tok->getVal()));
    return true;
}

 bool ILGen::pushProcByName(Token *tok)
 {
    Symbols::Symbol *symb = symbols.searchSymb(tok->getVal());
    if(symb == nullptr) return false;
    if(symb->object->getType() != Symbols::Object::Proc) return false;

    vector<short> param;
    param.push_back(symb->object->index);
    writeCode(Bytecode::Call, param);
    return true;
 }
