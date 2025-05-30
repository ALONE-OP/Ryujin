#include "RyujinObfuscationCore.hh"

RyujinObfuscationCore::RyujinObfuscationCore(const RyujinObfuscatorConfig& config, const RyujinProcedure& proc) {

	m_proc = proc;

	if (!extractUnusedRegisters())
		throw std::exception("No registers avaliable for obfuscation...");



}

RyujinProcedure RyujinObfuscationCore::getProcessedProc() {

	return this->m_proc;
}

BOOL RyujinObfuscationCore::extractUnusedRegisters() {

	std::vector<ZydisRegister> candidateRegs = {

			ZYDIS_REGISTER_RAX,
			ZYDIS_REGISTER_RCX,
			ZYDIS_REGISTER_RDX,
			ZYDIS_REGISTER_RBX,
			ZYDIS_REGISTER_RSP,
			ZYDIS_REGISTER_RBP,
			ZYDIS_REGISTER_RSI,
			ZYDIS_REGISTER_RDI,
			ZYDIS_REGISTER_R8,
			ZYDIS_REGISTER_R9,
			ZYDIS_REGISTER_R10,
			ZYDIS_REGISTER_R11,
			ZYDIS_REGISTER_R12,
			ZYDIS_REGISTER_R13,
			ZYDIS_REGISTER_R14,
			ZYDIS_REGISTER_R15,

	};

	std::set<ZydisRegister> usedRegs;

	for (auto blocks : m_proc.basic_blocks) {

		for (auto instr : blocks.instructions) {

			for (auto i = 0; i < instr.instruction.info.operand_count; ++i) {

				const ZydisDecodedOperand& op = instr.instruction.operands[i];

				if (op.type == ZYDIS_OPERAND_TYPE_REGISTER) usedRegs.insert(op.reg.value);
				else if (op.type == ZYDIS_OPERAND_TYPE_POINTER) {
				
					if (op.mem.base != ZYDIS_REGISTER_NONE) usedRegs.insert(op.mem.base);
					if (op.mem.index != ZYDIS_REGISTER_NONE) usedRegs.insert(op.mem.index);
				
				}

			}

		}

	}

	ZydisRegister freeReg = ZYDIS_REGISTER_NONE;
	for (auto reg : candidateRegs)
		if (usedRegs.count(reg) == 0) m_unusedRegisters.push_back(reg);

	return m_unusedRegisters.size() >= 2; //Theres unused regs for be used by us ?
}

void RyujinObfuscationCore::addPaddingSpaces() {

	asmjit::JitRuntime runtime;

	for (auto& block : m_proc.basic_blocks) {

		std::vector<std::vector<ZyanU8>> new_instructions;

		for (auto& opcode : block.opcodes) {

			std::vector<ZyanU8> new_opcodes;

			for (auto individual_opcode : opcode) {

				new_opcodes.push_back(individual_opcode);

			}

			new_instructions.push_back(new_opcodes);

			//Inserindo junkcode
			std::vector<ZyanU8> gen_opcodes;

			asmjit::CodeHolder code;
			code.init(runtime.environment());
			asmjit::x86::Assembler a(&code);

			for (auto i = 0; i < 50; i++) {
				a.nop();
			}

			code.flatten();

			auto section = code.sectionById(0);
			const uint8_t* buf = section->buffer().data();
			size_t size = section->buffer().size();

			for (size_t i = 0; i < size; ++i) {
				gen_opcodes.push_back(buf[i]);
			}

			new_instructions.push_back(gen_opcodes);

		}

		//Overrite the original opcodes with new ones
		block.opcodes.clear();
		block.opcodes.assign(new_instructions.begin(), new_instructions.end());

	}

}

BOOL RyujinObfuscationCore::Run() {

	//Add padding spaces
	addPaddingSpaces();

	/*
	if (config.m_isIatObfuscation) todoAction();

	if (config.m_isVirtualized) todoAction();
	if (config.m_isJunkCode) todoAction();
	*/

	return TRUE;
}

RyujinObfuscationCore::~RyujinObfuscationCore() {

}