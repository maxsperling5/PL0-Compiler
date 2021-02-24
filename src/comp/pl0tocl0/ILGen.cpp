/************************/
/* Author: Max Sperling */
/************************/

#include "ILGen.hpp"

#include "CompEx.hpp"

using namespace std;

deque<char>
pl0compiler::comp::pl0tocl0::ILGen::getBinary()
{
    return m_binary;
}

void
pl0compiler::comp::pl0tocl0::ILGen::AddSymbol(void *tok)
{
    m_symbols.addSymbol(((Token*)tok)->getVal());
}

void
pl0compiler::comp::pl0tocl0::ILGen::AddProcedure(void *tok)
{
    m_symbols.addProcedure();
}

void
pl0compiler::comp::pl0tocl0::ILGen::RetProcedure(void *tok)
{
    m_symbols.retProcedure();
}

void
pl0compiler::comp::pl0tocl0::ILGen::AddVariable(void *tok)
{
    m_symbols.addVariable();
}

void
pl0compiler::comp::pl0tocl0::ILGen::AddConstant(void *tok)
{
    m_symbols.addConstant(stol(((Token*)tok)->getVal()));
}

void
pl0compiler::comp::pl0tocl0::ILGen::CodeStart(void *tok)
{
    writeInt(0);
}

void
pl0compiler::comp::pl0tocl0::ILGen::ProcedureStart(void *tok)
{
    m_procStartAddr.push(m_binary.size()+sizeof(char));
    vector<short> param;
    param.push_back(0);
    param.push_back(m_symbols.getCurProcIdx());
    param.push_back(m_symbols.getCurProcNumVar()*sizeof(int));
    writeCode(Bytecode::EntryProc, param);
}

void
pl0compiler::comp::pl0tocl0::ILGen::ProcedureEnd(void *tok)
{
    writeCode(Bytecode::RetProc);
    short distProc = m_binary.size()+sizeof(char)-m_procStartAddr.top();
    writeShortToAddr(m_procStartAddr.top(), distProc);
    m_procStartAddr.pop();
}

void
pl0compiler::comp::pl0tocl0::ILGen::BeforeAssignment(void *tok)
{
    if(!pushVarByName((Token*)tok, Addr))
        throw CompEx((Token*)tok);
}

void
pl0compiler::comp::pl0tocl0::ILGen::AfterAssignment(void *tok)
{
    writeCode(Bytecode::StoreVal);
}

void
pl0compiler::comp::pl0tocl0::ILGen::InputNumber(void *tok)
{
    if(!pushVarByName((Token*)tok, Addr))
        throw CompEx((Token*)tok);
    writeCode(Bytecode::GetVal);
}

void
pl0compiler::comp::pl0tocl0::ILGen::OutputNumber(void *tok)
{
    writeCode(Bytecode::PutVal);
}

void
pl0compiler::comp::pl0tocl0::ILGen::Negation(void *tok)
{
    writeCode(Bytecode::VzMinus);
}

void
pl0compiler::comp::pl0tocl0::ILGen::Addition(void *tok)
{
    writeCode(Bytecode::OpAdd);
}

void
pl0compiler::comp::pl0tocl0::ILGen::Subtraction(void *tok)
{
    writeCode(Bytecode::OpSub);
}

void
pl0compiler::comp::pl0tocl0::ILGen::Multiplication(void *tok)
{
    writeCode(Bytecode::OpMult);
}

void
pl0compiler::comp::pl0tocl0::ILGen::Division(void *tok)
{
    writeCode(Bytecode::OpDiv);
}

void
pl0compiler::comp::pl0tocl0::ILGen::ConstByVal(void *tok)
{
    pushConstByVal((Token*)tok);
}

void
pl0compiler::comp::pl0tocl0::ILGen::IdentByName(void *tok)
{
    if(pushVarByName((Token*)tok, Val)) return;
    if(pushConstByName((Token*)tok)) return;
    throw CompEx((Token*)tok);
}

void
pl0compiler::comp::pl0tocl0::ILGen::Odd(void *tok)
{
    writeCode(Bytecode::OpOdd);
}

void
pl0compiler::comp::pl0tocl0::ILGen::Equal(void *tok)
{
    m_cmpOp = Bytecode::CmpEq;
}

void
pl0compiler::comp::pl0tocl0::ILGen::NotEqual(void *tok)
{
    m_cmpOp = Bytecode::CmpNe;
}

void
pl0compiler::comp::pl0tocl0::ILGen::Smaller(void *tok)
{
    m_cmpOp = Bytecode::CmpLt;
}

void
pl0compiler::comp::pl0tocl0::ILGen::Larger(void *tok)
{
    m_cmpOp = Bytecode::CmpGt;
}

void
pl0compiler::comp::pl0tocl0::ILGen::LessOrEqual(void *tok)
{
    m_cmpOp = Bytecode::CmpLe;
}

void
pl0compiler::comp::pl0tocl0::ILGen::GreaterOrEqual(void *tok)
{
    m_cmpOp = Bytecode::CmpGe;
}

void
pl0compiler::comp::pl0tocl0::ILGen::Comparison(void *tok)
{
    writeCode((Bytecode)m_cmpOp);
}

void
pl0compiler::comp::pl0tocl0::ILGen::Condition(void *tok)
{
    vector<short> param;
    param.push_back(0);
    writeCode(Bytecode::Jnot, param);
    m_jumpStartAddr.push(m_binary.size());
}

void
pl0compiler::comp::pl0tocl0::ILGen::BranchEnd(void *tok)
{
    short jmpAddr = m_jumpStartAddr.top();
    m_jumpStartAddr.pop();

    short distFromCond = m_binary.size()-jmpAddr;
    writeShortToAddr(jmpAddr-sizeof(short), distFromCond);
}

void
pl0compiler::comp::pl0tocl0::ILGen::While(void *tok)
{
    m_jumpStartAddr.push(m_binary.size());
}

void
pl0compiler::comp::pl0tocl0::ILGen::LoopEnd(void *tok)
{
    short jmpAddrIf = m_jumpStartAddr.top();
    m_jumpStartAddr.pop();
    short jmpAddrWhile = m_jumpStartAddr.top();
    m_jumpStartAddr.pop();

    vector<short> param;
    param.push_back(0);
    writeCode(Bytecode::Jmp, param);
    short distToWhile = -(m_binary.size()-jmpAddrWhile);
    writeShortToAddr(m_binary.size()-sizeof(short), distToWhile);

    short distFromCond = m_binary.size()-jmpAddrIf;
    writeShortToAddr(jmpAddrIf-sizeof(short), distFromCond);
}

void
pl0compiler::comp::pl0tocl0::ILGen::CallProcedure(void *tok)
{
    if(!pushProcByName((Token*)tok))
        throw CompEx((Token*)tok);
}

void
pl0compiler::comp::pl0tocl0::ILGen::OutputString(void *tok)
{
    writeCode(Bytecode::PutStrg);
    writeString(((Token*)tok)->getVal());
}

void
pl0compiler::comp::pl0tocl0::ILGen::CodeEnd(void *tok)
{
    for(auto &cons : m_symbols.m_vecConst)
    {
        writeInt(cons);
    }
    writeIntToAddr(0, m_symbols.m_numProc);
}

void
pl0compiler::comp::pl0tocl0::ILGen::writeCode(Bytecode code, vector<short> param)
{
    m_binary.push_back(code);

    for(short par : param)
    {
        m_binary.push_back(par & 0xff);
        m_binary.push_back((par >> 8) & 0xff);
    }
}

void
pl0compiler::comp::pl0tocl0::ILGen::writeString(string value)
{
    vector<char> vecVal(value.begin(), value.end());
    for(auto &val : vecVal)
    {
        m_binary.push_back(val);
    }
    m_binary.push_back(0);
}

void
pl0compiler::comp::pl0tocl0::ILGen::writeInt(int value)
{
    m_binary.push_back(value & 0xff);
    m_binary.push_back((value >> 8) & 0xff);
    m_binary.push_back((value >> 16) & 0xff);
    m_binary.push_back((value >> 24) & 0xff);
}

void
pl0compiler::comp::pl0tocl0::ILGen::writeShortToAddr(int startAddr, short value)
{
    m_binary.at(startAddr) = (value & 0xff);
    m_binary.at(startAddr+1) = ((value >> 8) & 0xff);
}

void
pl0compiler::comp::pl0tocl0::ILGen::writeIntToAddr(int startAddr, int value)
{
    m_binary.at(startAddr) = (value & 0xff);
    m_binary.at(startAddr+1) = ((value >> 8) & 0xff);
    m_binary.at(startAddr+2) = ((value >> 16) & 0xff);
    m_binary.at(startAddr+3) = ((value >> 24) & 0xff);
}

bool
pl0compiler::comp::pl0tocl0::ILGen::pushVarByName(Token *tok, AddrOrVal addrOrVal)
{
    Symbols::Symbol *symb = m_symbols.searchSymb(tok->getVal());
    if(symb == nullptr) return false;
    if(symb->m_object->getType() != Symbols::Object::Var) return false;

    vector<short> param;
    param.push_back((symb->m_object->m_index)*sizeof(int));

    if(symb->m_procIdx == m_symbols.getCurProcIdx())
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
    else if(symb->m_procIdx == 0)
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
        param.push_back(symb->m_procIdx);
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

bool
pl0compiler::comp::pl0tocl0::ILGen::pushConstByName(Token *tok)
{
    Symbols::Symbol *symb = m_symbols.searchSymb(tok->getVal());
    if(symb == nullptr) return false;
    if(symb->m_object->getType() != Symbols::Object::Cons) return false;

    vector<short> param;
    param.push_back(((Symbols::Constant*)symb->m_object)->m_value);
    writeCode(Bytecode::PuConst, param);
    return true;
}

bool
pl0compiler::comp::pl0tocl0::ILGen::pushConstByVal(Token *tok)
{
    vector<short> param;

    for(unsigned int i=0; i<m_symbols.m_vecConst.size(); i++)
    {
        if(m_symbols.m_vecConst.at(i) == stol(tok->getVal()))
        {
            param.push_back(i);
            writeCode(Bytecode::PuConst, param);
            return true;
        }
    }

    param.push_back(m_symbols.m_vecConst.size());
    writeCode(Bytecode::PuConst, param);
    m_symbols.addConstNum(stol(tok->getVal()));
    return true;
}

 bool
 pl0compiler::comp::pl0tocl0::ILGen::pushProcByName(Token *tok)
 {
    Symbols::Symbol *symb = m_symbols.searchSymb(tok->getVal());
    if(symb == nullptr) return false;
    if(symb->m_object->getType() != Symbols::Object::Proc) return false;

    vector<short> param;
    param.push_back(symb->m_object->m_index);
    writeCode(Bytecode::Call, param);
    return true;
 }
