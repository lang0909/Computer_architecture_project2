# Building a Simple MIPS Simulator 

## 개요

이 프로젝트는 MIPS instruction set의 subset의 emulator를 build 하는 것이다.

emulator는 MIPS binary file을 emulation 된 메모리에 로드하고 instruction을 실행한다.

instruction을 실행하면 레지스터와 메모리의 상태가 변경되고 그 변경 된 값을 output으로 보여준다.

## 사용된 환경 & version
- Ubuntu 18.04.1 LTS (64bit)
- gcc (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0


## 사용 시 주의사항

**object파일 생성 및 simulator 테스트**

```bash
make
make test
```

**생성 된 object파일 삭제**

```bash
make clean
```

**test option**
```bash
./sce212sim [-m addr1:addr2] [-d] [-n num_instr] inputBinary
```

- -m : addr1에서 addr2로 메모리 내용을 dump
- -d : 레지스터 파일 내용을 print. -m 옵션이 활성화 된 경우 메모리 내용도 print.
- -n : 시뮬레이션 된 instruction 수

## 기능 설명

- **States**
    - The emulator must maintain the system states, which consist of the necessary register set (R0-R31,
PC) and the memory. The register and memory must be created when the emulation begins.

- **Loading an input binary**
    - For a given input binary, the loader must identify the text and data section sizes. The text section must
be loaded to the emulated memory from the address 0x400000. The data section must be loaded to
the emulated memory from the address 0x10000000. In this project, the simple loader does not create
the stack region.

- **Initial states**
    - PC : The initial value of PC is 0x400000.
    - Registers : All values of register0 to 31 are set to zero.
    - Memory : You may assume all initial values are zero, except for the loaded text and data sections.

- **Instructio execution**
    - With the current PC, 4B from the memory is read. The emulator must parse the binary instruction and
identify what the instruction is and what are the operands. Based on the MIPS ISA, the emulator must
accurately mimic the execution, which will update either a PC, register, or memory.

- **Supported instruction set**

이미지


### 출력예시

- If you type the command line as below, the output file should show only PC and register values
like Figure 1.

```bash
./sce212sim –n 0 input.o
```

- If you type the command line as below, the output file should show memory contents of specific
memory region, PC and register values like Figure 2.

```bash
./sce212sim –m 0x400000:0x400010 –n 0 input.o
```

- The functions for printing the memory and register values are provided in the util.c, and
util.h files.

이미지