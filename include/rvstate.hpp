#pragma once

#include <cstdint>


template<typename Word>
struct rv_HartState {
	Word reg[32];
	Word pc;
};

typedef rv_HartState<uint32_t> rv32_HartState;
typedef rv_HartState<uint64_t> rv64_HartState;
