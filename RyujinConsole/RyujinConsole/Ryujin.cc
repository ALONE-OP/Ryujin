#include "Ryujin.hh"

Ryujin::Ryujin(const std::string& strInputFilePath, const std::string& strPdbFilePath, const std::string& strOutputFilePath) :
m_strInputFilePath(strInputFilePath), m_strOutputFilePath(strOutputFilePath), m_strPdbFilePath(strPdbFilePath) {

	RyujinUtils::MapPortableExecutableFileIntoMemory(m_strInputFilePath, m_mappedPE);

	std::printf("Goingggg :D\n0");

}

Ryujin::~Ryujin() {

}
