#pragma once

#include <cstdint>


union [[gnu::packed]] rv_Instruction32 {
	struct [[gnu::packed]] {
		unsigned int opcode : 7;
		unsigned int rd : 5;
		unsigned int funct3 : 3;
		unsigned int rs1 : 5;
		unsigned int rs2 : 5;
		unsigned int funct7 : 7;

		int32_t imm() {
			return 0;
		}
	} R;

	struct [[gnu::packed]] {
		unsigned int opcode : 7;
		unsigned int rd : 5;
		unsigned int funct3 : 3;
		unsigned int rs1 : 5;
		signed int   imm11_0 : 12;

		int32_t imm() {
			return imm11_0;
		}
	} I;

	struct [[gnu::packed]] {
		unsigned int opcode : 7;
		unsigned int imm4_0 : 5;
		unsigned int funct3 : 3;
		unsigned int rs1 : 5;
		unsigned int rs2 : 5;
		signed int   imm11_5 : 7;

		int32_t imm() {
			return (imm11_5 << 5) + imm4_0;
		}
	} S;

	struct [[gnu::packed]] {
		unsigned int opcode : 7;
		unsigned int imm11 : 1;
		unsigned int imm4_1 : 4;
		unsigned int funct3 : 3;
		unsigned int rs1 : 5;
		unsigned int rs2 : 5;
		unsigned int imm10_5 : 6;
		signed int   imm12 : 1;

		// branch offsets in multiples of 2
		int32_t imm() {
			return (imm12 << 12) + (imm11 << 11) + (imm10_5 << 5) + (imm4_1 << 1);
		}
	} B;

	struct [[gnu::packed]] {
		unsigned int opcode : 7;
		unsigned int rd : 5;
		signed int   imm31_12 : 20;

		int32_t imm() {
			return imm31_12 << 12;
		}
	} U;

	struct [[gnu::packed]] {
		unsigned int opcode : 7;
		unsigned int rd : 5;

		unsigned int imm19_12 : 8;
		unsigned int imm11 : 1;
		unsigned int imm10_1 : 10;
		signed int   imm20 : 1;

		int32_t imm() {
			return (imm20 << 20) + (imm19_12 << 12) + (imm11 << 11) + (imm10_1 << 1);
		}
	} J;
};

static_assert(sizeof(rv_Instruction32) == 4, "rv_Instruction32 must be 32-bit long");
