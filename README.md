# PL0-Compiler

## Building
Compiler: cmake -Hsrc/PL0-Comp -Bbin/PL0-Comp -G \<Generator\> -DCMAKE_CXX_FLAGS=\<Compiler-Flags\>
VM: cmake -Hsrc/PL0-VM -Bbin/PL0-VM -G \<Generator\>

## Workflow
General: Sourcecode -> Compiler -> IL-Code
Detailed: Sourcecode --Tokenizer--> Tokenlist --Generator--> Bytelist