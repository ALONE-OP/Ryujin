#pragma once
#include "RyujinInstruction.hh"

class RyujinBasicBlock {

public:
	std::vector<RyujinInstruction> instructions;
	std::vector<std::vector<ZyanU8>> opcodes;
	uintptr_t start_address;
	uintptr_t end_address;

};