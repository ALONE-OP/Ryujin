#pragma once
#include <string>
#include "RyujinBasicBlock.hh"

class RyujinProcedure {

public:
    std::string name;
    uintptr_t imagebase;
    uintptr_t address;
    uintptr_t size;
    std::vector<RyujinBasicBlock> basic_blocks;

    std::vector<ZyanU8> getUpdateOpcodes() {

		std::vector<unsigned char> result;

		for (auto& block : basic_blocks) {

			auto& blocks = block.opcodes;

			for (size_t i = 0; i < blocks.size(); ++i) {
				const auto& block = blocks[i];
				if (!block.empty()) {
					for (const auto& byte : block) {
						result.emplace_back(byte);
					}
				}
			}

		}

		return result;
    }

};