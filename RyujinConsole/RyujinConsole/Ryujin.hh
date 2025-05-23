#pragma once
#include <iostream>
#include <memory>
#include "RyujinUtils.hh"

class Ryujin {

private:
	std::shared_ptr<unsigned char> m_mappedPE;
	const std::string& m_strInputFilePath;
	const std::string& m_strPdbFilePath;
	const std::string& m_strOutputFilePath;

public:
	Ryujin(const std::string& strInputFilePath, const std::string& strPdbFilePath, const std::string& strOutputFilePath);
	~Ryujin();

};

