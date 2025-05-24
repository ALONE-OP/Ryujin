#include <iostream>
#include "Ryujin.hh"

auto main() -> int {

    std::cout << "Hello World!\n";

    std::unique_ptr<Ryujin> ryujin = std::make_unique<Ryujin>("C:\\Users\\Keowu\\Documents\\GitHub\\MoFei\\x64\\Debug\\DemoObfuscation.exe", "C:\\Users\\Keowu\\Documents\\GitHub\\MoFei\\x64\\Debug\\DemoObfuscation.pdb", "C:\\Users\\Keowu\\Documents\\GitHub\\MoFei\\x64\\Debug\\DemoObfuscation2.exe");

    ryujin.get()->listRyujinProcedures();

    RyujinObfuscatorConfig config;
    config.m_isIgnoreOriginalCodeRemove = FALSE;
    config.m_isJunkCode = TRUE;
    config.m_isRandomSection = FALSE;
    config.m_isVirtualized = FALSE;
    std::vector<std::string> procsToObfuscate{
        "main"
    };
    config.m_strProceduresToObfuscate.assign(procsToObfuscate.begin(), procsToObfuscate.end());

    ryujin.get()->run(config);

    ryujin.reset();

    return 0;
}