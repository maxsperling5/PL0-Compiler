/************************/
/* Author: Max Sperling */
/************************/

#include "ILGen.hpp"

#include "CompEx.hpp"

namespace pl0compiler { namespace comp { namespace pl0tocl0 {

std::deque<char> ILGen::getBinary()
{
    return m_binary;
}

void ILGen::AddSymbol(void *tok)
{
    m_symbols.addSymbol(((Token*)tok)->getVal());
}

void ILGen::AddProcedure(void *tok)
{
    m_symbols.addProcedure();
}

void ILGen::RetProcedure(void *tok)
{
    m_symbols.retProcedure();
}

void ILGen::AddVariable(void *tok)
{
    m_symbols.addVariable();
}

void ILGen::AddConstant(void *tok)
{
    m_symbols.addConstant(stol(((Token*)tok)->getVal()));
}

void ILGen::CodeStart(void *tok)
{
    writeInt(0);
}

void ILGen::ProcedureStart(void *tok)
{
    m_procStartAddr.push(m_binary.size()+sizeof(char));
    std::vector<short> param;
    param.push_back(0);
    param.push_back(m_symbols.getCurProcIdx());
    param.push_back(m_symbols.getCurProcNumVar()*sizeof(int));
    writeCode(ByteCode::EntryProc, param);
}

void ILGen::ProcedureEnd(void *tok)
{
    writeCode(ByteCode::RetProc);
    short distProc = m_binary.size()+sizeof(char)-m_procStartAddr.top();
    writeShortToAddr(m_procStartAddr.top(), distProc);
    m_procStartAddr.pop();
}

void ILGen::BeforeAssignment(void *tok)
{
    if (!pushVarByName((Token*)tok, Addr))
    {
        throw CompEx((Token*)tok);
    }
}

void ILGen::AfterAssignment(void *tok)
{
    writeCode(ByteCode::StoreVal);
}

void ILGen::InputNumber(void *tok)
{
    if (!pushVarByName((Token*)tok, Addr))
    {
        throw CompEx((Token*)tok);
    }
    writeCode(ByteCode::GetVal);
}

void ILGen::OutputNumber(void *tok)
{
    writeCode(ByteCode::PutVal);
}

void ILGen::Negation(void *tok)
{
    writeCode(ByteCode::VzMinus);
}

void ILGen::Addition(void *tok)
{
    writeCode(ByteCode::OpAdd);
}

void ILGen::Subtraction(void *tok)
{
    writeCode(ByteCode::OpSub);
}

void ILGen::Multiplication(void *tok)
{
    writeCode(ByteCode::OpMult);
}

void ILGen::Division(void *tok)
{
    writeCode(ByteCode::OpDiv);
}

void ILGen::ConstByVal(void *tok)
{
    pushConstByVal((Token*)tok);
}

void ILGen::IdentByName(void *tok)
{
    if (pushVarByName((Token*)tok, Val)) return;
    if (pushConstByName((Token*)tok)) return;
    throw CompEx((Token*)tok);
}

void ILGen::Odd(void *tok)
{
    writeCode(ByteCode::OpOdd);
}

void ILGen::Equal(void *tok)
{
    m_cmpOp = ByteCode::CmpEq;
}

void ILGen::NotEqual(void *tok)
{
    m_cmpOp = ByteCode::CmpNe;
}

void ILGen::Smaller(void *tok)
{
    m_cmpOp = ByteCode::CmpLt;
}

void ILGen::Larger(void *tok)
{
    m_cmpOp = ByteCode::CmpGt;
}

void ILGen::LessOrEqual(void *tok)
{
    m_cmpOp = ByteCode::CmpLe;
}

void ILGen::GreaterOrEqual(void *tok)
{
    m_cmpOp = ByteCode::CmpGe;
}

void ILGen::Comparison(void *tok)
{
    writeCode((ByteCode)m_cmpOp);
}

void ILGen::Condition(void *tok)
{
    std::vector<short> param;
    param.push_back(0);
    writeCode(ByteCode::Jnot, param);
    m_jumpStartAddr.push(m_binary.size());
}

void ILGen::BranchEnd(void *tok)
{
    short jmpAddr = m_jumpStartAddr.top();
    m_jumpStartAddr.pop();

    short distFromCond = m_binary.size()-jmpAddr;
    writeShortToAddr(jmpAddr-sizeof(short), distFromCond);
}

void ILGen::While(void *tok)
{
    m_jumpStartAddr.push(m_binary.size());
}

void ILGen::LoopEnd(void *tok)
{
    short jmpAddrIf = m_jumpStartAddr.top();
    m_jumpStartAddr.pop();
    short jmpAddrWhile = m_jumpStartAddr.top();
    m_jumpStartAddr.pop();

    std::vector<short> param;
    param.push_back(0);
    writeCode(ByteCode::Jmp, param);
    short distToWhile = -(m_binary.size()-jmpAddrWhile);
    writeShortToAddr(m_binary.size()-sizeof(short), distToWhile);

    short distFromCond = m_binary.size()-jmpAddrIf;
    writeShortToAddr(jmpAddrIf-sizeof(short), distFromCond);
}

void ILGen::CallProcedure(void *tok)
{
    if (!pushProcByName((Token*)tok))
    {
        throw CompEx((Token*)tok);
    }
}

void ILGen::OutputString(void *tok)
{
    writeCode(ByteCode::PutStrg);
    writeString(((Token*)tok)->getVal());
}

void ILGen::CodeEnd(void *tok)
{
    for (auto &cons : m_symbols.m_vecConst)
    {
        writeInt(cons);
    }
    writeIntToAddr(0, m_symbols.m_numProc);
}

void ILGen::writeCode(ByteCode code, std::vector<short> param)
{
    m_binary.push_back(code);

    for (short par : param)
    {
        m_binary.push_back(par & 0xff);
        m_binary.push_back((par >> 8) & 0xff);
    }
}

void ILGen::writeString(std::string value)
{
    std::vector<char> vecVal(value.begin(), value.end());
    for (auto &val : vecVal)
    {
        m_binary.push_back(val);
    }
    m_binary.push_back(0);
}

void ILGen::writeInt(int value)
{
    m_binary.push_back(value & 0xff);
    m_binary.push_back((value >> 8) & 0xff);
    m_binary.push_back((value >> 16) & 0xff);
    m_binary.push_back((value >> 24) & 0xff);
}

void ILGen::writeShortToAddr(int startAddr, short value)
{
    m_binary.at(startAddr) = (value & 0xff);
    m_binary.at(startAddr+1) = ((value >> 8) & 0xff);
}

void ILGen::writeIntToAddr(int startAddr, int value)
{
    m_binary.at(startAddr) = (value & 0xff);
    m_binary.at(startAddr+1) = ((value >> 8) & 0xff);
    m_binary.at(startAddr+2) = ((value >> 16) & 0xff);
    m_binary.at(startAddr+3) = ((value >> 24) & 0xff);
}

bool ILGen::pushVarByName(Token *tok, AddrOrVal addrOrVal)
{
    Symbols::Symbol *symb = m_symbols.searchSymb(tok->getVal());
    if (symb == nullptr) return false;
    if (symb->m_object->getType() != Symbols::Object::Var) return false;

    std::vector<short> param;
    param.push_back((symb->m_object->m_index)*sizeof(int));

    if (symb->m_procIdx == m_symbols.getCurProcIdx())
    {
        switch (addrOrVal)
        {
        case Addr:
            writeCode(ByteCode::PuAdrVrLocl, param);
            break;
        case Val:
            writeCode(ByteCode::PuValVrLocl, param);
            break;
        }

    }
    else if (symb->m_procIdx == 0)
    {
        switch (addrOrVal)
        {
        case Addr:
            writeCode(ByteCode::PuAdrVrMain, param);
            break;
        case Val:
            writeCode(ByteCode::PuValVrMain, param);
            break;
        }
    }
    else
    {
        param.push_back(symb->m_procIdx);
        switch (addrOrVal)
        {
        case Addr:
            writeCode(ByteCode::PuAdrVrGlob, param);
            break;
        case Val:
            writeCode(ByteCode::PuValVrGlob, param);
            break;
        }
    }
    return true;
}

bool ILGen::pushConstByName(Token *tok)
{
    Symbols::Symbol *symb = m_symbols.searchSymb(tok->getVal());
    if (symb == nullptr) return false;
    if (symb->m_object->getType() != Symbols::Object::Cons) return false;

    std::vector<short> param;
    param.push_back(((Symbols::Constant*)symb->m_object)->m_value);
    writeCode(ByteCode::PuConst, param);
    return true;
}

bool ILGen::pushConstByVal(Token *tok)
{
    std::vector<short> param;

    for (unsigned int i=0; i<m_symbols.m_vecConst.size(); i++)
    {
        if (m_symbols.m_vecConst.at(i) == stol(tok->getVal()))
        {
            param.push_back(i);
            writeCode(ByteCode::PuConst, param);
            return true;
        }
    }

    param.push_back(m_symbols.m_vecConst.size());
    writeCode(ByteCode::PuConst, param);
    m_symbols.addConstNum(stol(tok->getVal()));
    return true;
}

 bool ILGen::pushProcByName(Token *tok)
 {
    Symbols::Symbol *symb = m_symbols.searchSymb(tok->getVal());
    if (symb == nullptr) return false;
    if (symb->m_object->getType() != Symbols::Object::Proc) return false;

    std::vector<short> param;
    param.push_back(symb->m_object->m_index);
    writeCode(ByteCode::Call, param);
    return true;
 }

} } }
