#include "Ryujin.hh"

Ryujin::Ryujin(const std::string& strInputFilePath, const std::string& strPdbFilePath, const std::string& strOutputFilePath) :
m_strInputFilePath(strInputFilePath), m_strOutputFilePath(strOutputFilePath), m_strPdbFilePath(strPdbFilePath) {

	auto mappedInfo = RyujinUtils::MapPortableExecutableFileIntoMemory(m_strInputFilePath, m_mappedPE);

	m_szFile = mappedInfo.second;
	m_isInitialized = mappedInfo.first;

	if (!m_isInitialized) {

		OutputDebugStringA("Ryujin::Ryujin: failed to initilize.\n");

	}

}

bool Ryujin::run() {

	auto imgDos = reinterpret_cast<PIMAGE_DOS_HEADER>(m_mappedPE.get());

	if (imgDos->e_magic != IMAGE_DOS_SIGNATURE) {

		OutputDebugStringA(
			
			_In_ "Ryujin::run: Invalid PE File.\n"
		
		);

		return FALSE;
	}

	auto imgNt = reinterpret_cast<PIMAGE_NT_HEADERS>(m_mappedPE.get() + imgDos->e_lfanew);

	if (imgNt->Signature != IMAGE_NT_SIGNATURE) {

		OutputDebugStringA(
			
			_In_ "Ryujin::run: Invalid NT headers for the input PE File.\n"
		
		);

		return FALSE;
	}

	if (!m_isInitialized) {

		OutputDebugStringA(
			
			_In_ "Ryujin::Ryujin: not initilized.\n"
		
		);

		return FALSE;
	}

	auto syms = RyujinPdbParsing::ExtractProceduresFromPdb(
		
		reinterpret_cast<uintptr_t>(m_mappedPE.get()),
		m_szFile,
		m_strInputFilePath,
		m_strPdbFilePath
	
	);

}

Ryujin::~Ryujin() {

}
