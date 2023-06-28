#pragma once

#include <cstdint>


enum rv_Opcode {
	LOAD     = 0b0000011,
	LOAD_FP  = 0b0000111,
	Custom_0 = 0b0001011,
	MISC_MEM = 0b0001111,
	OP_IMM   = 0b0010011,
	AUIPC    = 0b0010111,
	OP_IMM32 = 0b0011011,

	STORE    = 0b0100011,
	STORE_FP = 0b0100111,
	Custom_1 = 0b0101011,
	AMO      = 0b0101111,
	OP       = 0b0110011,
	LUI      = 0b0110111,
	OP_32    = 0b0111011,

	MADD          = 0b1000011,
	MSUB          = 0b1000111,
	NMSUB         = 0b1001011,
	NMADD         = 0b1001111,
	OP_FP         = 0b1010011,
	Reserved10101 = 0b1010111,
	Custom_2      = 0b1011011,

	BRANCH        = 0b1100011,
	JALR          = 0b1100111,
	Reserved11010 = 0b1101011,
	JAL           = 0b1101111,
	SYSTEM        = 0b1110011,
	Reserved11101 = 0b1110111,
	Custom_3      = 0b1111011,
};

enum rv_EncodingType {
	R,
	I,
	S,
	B,
	U,
	J,
};

struct rv_InstructionType {
	const char     *name;
	rv_Opcode       opcode;
	rv_EncodingType type;

	int funct3, funct7;
};

const rv_InstructionType rv_Instructions[] = {
	// RV32I
	{"LUI", LUI, U},
	{"AUIPC", AUIPC, U},
	{"JAL", JAL, J},
	{"JALR", JALR, I},

	{"BEQ", BRANCH, B, 0b000},
	{"BNE", BRANCH, B, 0b001},
	{"BLT", BRANCH, B, 0b100},
	{"BGE", BRANCH, B, 0b101},
	{"BLTU", BRANCH, B, 0b110},
	{"BGEU", BRANCH, B, 0b111},

	{"LB", LOAD, I, 0b000},
	{"LH", LOAD, I, 0b001},
	{"LW", LOAD, I, 0b010},
	{"LBU", LOAD, I, 0b100},
	{"LHU", LOAD, I, 0b101},

	{"SB", STORE, S, 0b000},
	{"SH", STORE, S, 0b001},
	{"SW", STORE, S, 0b010},

	{"ADDI", OP_IMM, I, 0b000},
	{"SLTI", OP_IMM, I, 0b010},
	{"SLTIU", OP_IMM, I, 0b011},

	{"XORI", OP_IMM, I, 0b100},
	{"ORI", OP_IMM, I, 0b110},
	{"ANDI", OP_IMM, I, 0b111},

	{"SLLI", OP_IMM, I, 0b001},
	{"SRLI", OP_IMM, I, 0b101},
	{"SRAI", OP_IMM, I, -1}, // Only set by special case

	{"ADD", OP, R, 0b000, 0b0000000},
	{"SUB", OP, R, 0b000, 0b0100000},
	{"SLL", OP, R, 0b001},
	{"SLT", OP, R, 0b010},
	{"SLTU", OP, R, 0b011},
	{"XOR", OP, R, 0b100},
	{"SRL", OP, R, 0b101, 0b0000000},
	{"SRA", OP, R, 0b101, 0b0100000},
	{"OR", OP, R, 0b110},
	{"AND", OP, R, 0b111},

	{"FENCE", MISC_MEM, I, 0b000},
	{"ECALL", SYSTEM, U, 0b000},
	{"EBREAK", SYSTEM, U, -1}, // Only set by special case

	// RV64I
	{"LWU", LOAD, I, 0b110},
	{"LD", LOAD, I, 0b11},
	{"SD", STORE, S, 0b11},
	//{"SLLI", OP_IMM, I, 0b1},
	//{"SRLI", OP_IMM, I, 0b101},
	//{"SRAI", OP_IMM, I, -1},
	{"ADDIW", OP_IMM32, I, 0b0},
	{"SLLIW", OP_IMM32, R, 0b1},
	{"SRLIW", OP_IMM32, R, 0b101, 0b0000000},
	{"SRAIW", OP_IMM32, R, 0b101, 0b0100000},
	{"ADDW", OP_32, R, 0b0, 0b0000000},
	{"SUBW", OP_32, R, 0b0, 0b0100000},
	{"SLLW", OP_32, R, 0b1, 0b0000000},
	{"SRLW", OP_32, R, 0b101, 0b0000000},
	{"SRAW", OP_32, R, 0b101, 0b0100000},

	// Zifenci
	{"FENCE.I", MISC_MEM, I, 0b001},

	// Zicsr
	{"CSRRW", SYSTEM, I, 0b001},
	{"CSRRS", SYSTEM, I, 0b010},
	{"CSRRC", SYSTEM, I, 0b011},
	{"CSRRWI", SYSTEM, I, 0b101},
	{"CSRRSI", SYSTEM, I, 0b110},
	{"CSRRCI", SYSTEM, I, 0b111},

	// RV32M
	{"MUL", OP, R, 0b000, 0b0000001},
	{"MULH", OP, R, 0b001, 0b0000001},
	{"MULHSU", OP, R, 0b010, 0b0000001},
	{"MULHU", OP, R, 0b011, 0b0000001},
	{"DIV", OP, R, 0b100, 0b0000001},
	{"DIVU", OP, R, 0b101, 0b0000001},
	{"REM", OP, R, 0b110, 0b0000001},
	{"REMU", OP, R, 0b111, 0b0000001},

	// RV64M
	{"MULW", OP_32, R, 0b000, 0b0000001},
	{"DIVW", OP_32, R, 0b100, 0b0000001},
	{"DIVUW", OP_32, R, 0b101, 0b0000001},
	{"REMW", OP_32, R, 0b110, 0b0000001},
	{"REMUW", OP_32, R, 0b111, 0b0000001},


};


enum class rv_Funct3 : int {

	// OP-IMM
	ADDI  = 0b000,
	SLTI  = 0b010,
	SLTIU = 0b011,

	ANDI = 0b111,
	ORI  = 0b110,
	XORI = 0b100,

	SLLI = 0b001,
	SRLI = 0b101,
	SRAI = 0b101,

	// OP
	ADD  = 0b000,
	SUB  = 0b000,
	SLL  = 0b001,
	SLT  = 0b010,
	SLTU = 0b011,

	XOR = 0b100,
	SRL = 0b101,
	SRA = 0b101,
	OR  = 0b110,
	AND = 0b111,


};
