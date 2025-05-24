#pragma once
#include "RyujinBasicBlock.hh"

class RyujinProcedure {

public:
    std::string name;
    uintptr_t imagebase;
    uintptr_t address;
    uintptr_t size;
    std::vector<RyujinBasicBlock> basic_blocks;

};