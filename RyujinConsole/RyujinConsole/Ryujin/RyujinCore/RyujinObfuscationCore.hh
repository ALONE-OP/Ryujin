#pragma once
#include <Windows.h>
#include <vector>
#include <set>
#include <asmjit/asmjit.h>
#include <Zydis/Zydis.h>
#include <Zydis/SharedTypes.h>
#include "../Models/RyujinProcedure.hh"
#include "../Models/RyujinObfuscatorConfig.hh"

class RyujinObfuscationCore {

private:
	std::vector<ZydisRegister> m_unusedRegisters;
	RyujinProcedure m_proc;
	BOOL extractUnusedRegisters();
	void addPaddingSpaces();

public:
	RyujinObfuscationCore(const RyujinObfuscatorConfig& config, const RyujinProcedure& proc);
	BOOL Run();
	RyujinProcedure getProcessedProc();
	~RyujinObfuscationCore();

};