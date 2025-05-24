#pragma once
#include "RyujinProcedure.hh"
//#include <dbghelp.h>

//#pragma comment(lib, "DbgHelp.lib")

class RyujinPdbParsing {

public:


	static std::vector<RyujinProcedure> ExtractProceduresFromPdb(uintptr_t mappedPebase, uintptr_t m_szFile, const std::string& m_strInputFilePath, const std::string& m_strPdbFilePath) {

		std::vector<RyujinProcedure> procs;

		return procs;
	}

};