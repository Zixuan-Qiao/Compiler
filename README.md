# Syntax-Directed Compiler
In this project, the front-end of a compiler is implemented from scratch. 

## Introduction
The compiler can read expressions from txt file and translate them into quadruples. It consists of three modules: lexical analysis module, syntax analysis module and semantic analysis module. The syntax analysis module is implemented with SLR(1) parser which achieves balance between performance and simplicity. S-attributed grammar is used in the semantic analysis module to enable one-pass analysis. 

## Workflow
The translation process is driven by the syntax analysis controller. It will perform advance action or reduction action based on the content of the syntax stack and the input. When an advance action is performed, the lexical analysis module is called and the identified token will be pushed into syntax stack. On the other hand, the semantic analysis module will be invoked by reduction actions to generate quadruples. 

## Language
C/C++

## Results
<img width="324" alt="1" align="top" src="https://github.com/Zixuan-Qiao/Compiler/assets/102449059/1997efb8-d40b-43c9-bd42-5f79c0b05317">

<img width="265" alt="2" align="top" src="https://github.com/Zixuan-Qiao/Compiler/assets/102449059/5b98f23d-9bae-476e-87b7-4e4fe8170b35">

<img width="328" alt="3" align="top" src="https://github.com/Zixuan-Qiao/Compiler/assets/102449059/34aa362e-32a3-4d3b-85d1-d28033d2e903">

## Author
Zixuan (Alex) Qiao
