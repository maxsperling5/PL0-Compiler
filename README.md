# PL0-Compiler

## Workflow
Sourcecode (PL0-Code) --Tokenizer--> Tokenlist --Generator--> Bytelist (CL0-Code) <br>

## Requirements
C/C++-Compiler <br>
CMake <br>

## Building
**Compiler:** cmake -Hsrc/PL0-Comp -Bbin/PL0-Comp -G \<Generator\> -DCMAKE_CXX_FLAGS=\<Compiler-Flags\> <br>
**VM:** cmake -Hres/Apps/PL0-VM -Bbin/PL0-VM -G \<Generator\> <br>

## Executing
**Compiler:** program \<PL0-File\> \<CL0-File\> <br>
**VM:** program \<CL0-File\> <br>
