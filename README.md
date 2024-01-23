# Syntax-Directed Compiler
In this project, the front-end of a compiler is implemented from scratch. 

## Introduction
The compiler can read expressions from txt file and translate them into quadruples. It consists of three modules: lexical analysis module, syntax analysis module and semantic analysis module. The syntax analysis module is implemented with SLR(1) parser which achieves balance between performance and simplicity. S-attributed grammar is used in the semantic analysis module to enable one-pass analysis. 

## Workflow
The translation process is driven by the syntax analysis controller. It will perform advance action or reduction action based on the content of the syntax stack and the input. When an advance action is performed, the lexical analysis module is called and the identified token will be pushed into syntax stack. On the other hand, the semantic analysis module will be invoked by reduction actions to generate quadruples. 

## Language
C/C++

## Results
<img width="390" alt="2" src="https://github.com/Zixuan-Qiao/Compiler/assets/102449059/b608cbb8-b6bd-4b82-a782-f94039ff4e20">

## Author
Zixuan (Alex) Qiao
