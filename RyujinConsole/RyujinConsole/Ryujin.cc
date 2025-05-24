#include "Ryujin.hh"

Ryujin::Ryujin(const std::string& strInputFilePath, const std::string& strPdbFilePath, const std::string& strOutputFilePath) :
m_strInputFilePath(strInputFilePath), m_strOutputFilePath(strOutputFilePath), m_strPdbFilePath(strPdbFilePath) {

	auto mappedInfo = RyujinUtils::MapPortableExecutableFileIntoMemory(m_strInputFilePath, m_mappedPE);

	m_szFile = mappedInfo.second;
	m_isInitialized = mappedInfo.first;

	if (!m_isInitialized) {

		::OutputDebugStringA(
			
			_In_ "Ryujin::Ryujin: failed to initilize.\n"
		
		);

	}

	m_ryujinProcedures = RyujinPdbParsing::ExtractProceduresFromPdb(

		reinterpret_cast<uintptr_t>(m_mappedPE.get()),
		m_szFile,
		m_strInputFilePath,
		m_strPdbFilePath

	);

	if (m_ryujinProcedures.size() == 0) {

		m_isInitialized = FALSE;

		::OutputDebugStringA(

			_In_ "Ryujin::Ryujin: No Associate PDB file found for the input binary.."

		);

	}

}

bool Ryujin::run(const RyujinObfuscatorConfig& config) {

	auto imgDos = reinterpret_cast<PIMAGE_DOS_HEADER>(m_mappedPE.get());

	if (imgDos->e_magic != IMAGE_DOS_SIGNATURE) {

		::OutputDebugStringA(
			
			_In_ "Ryujin::run: Invalid PE File.\n"
		
		);

		return FALSE;
	}

	auto imgNt = reinterpret_cast<PIMAGE_NT_HEADERS>(m_mappedPE.get() + imgDos->e_lfanew);

	if (imgNt->Signature != IMAGE_NT_SIGNATURE) {

		::OutputDebugStringA(
			
			_In_ "Ryujin::run: Invalid NT headers for the input PE File.\n"
		
		);

		return FALSE;
	}

	if (!m_isInitialized) {

		::OutputDebugStringA(
			
			_In_ "Ryujin::Ryujin: not initilized.\n"
		
		);

		return FALSE;
	}

	if (config.m_strProceduresToObfuscate.size() == 0) {

		::OutputDebugStringA(

			_In_ "Ryujin::Ryujin: not provided functions to obfuscate.\n"

		);

		return FALSE;
	}

	for (const auto& proc : m_ryujinProcedures) {

		auto it = std::find(config.m_strProceduresToObfuscate.begin(), config.m_strProceduresToObfuscate.end(), proc.name);

		if (it == config.m_strProceduresToObfuscate.end()) continue;

		std::printf("[WORKING ON]: %s\n", proc.name);

		// Is a valid procedure ?
		if (proc.size == 0) {

			::OutputDebugStringA(

				_In_ "Ryujin::Ryujin: The candidate is a ghost function cannot obfuscate this..\n"

			);

			continue;
		}

		//Create basic blocks


	}

}

void Ryujin::listRyujinProcedures() {

	if (!m_isInitialized) {

		::OutputDebugStringA(
			
			_In_ "Ryujin::listRyujinProcedures: not initialized.\n"
		
		);

		return;
	}

	std::printf("=== Ryujin Procedures ===\n");

	for (const auto& procedure : m_ryujinProcedures) {

		std::printf(
			"Name: %-30s | Address: 0x%016llx | Size: 0x%llx\n",
			procedure.name.c_str(),
			procedure.address,
			procedure.size
		);

	}

	std::printf("==========================\n");

}

Ryujin::~Ryujin() {

}
