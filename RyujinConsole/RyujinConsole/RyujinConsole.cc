#include <iostream>
#include "RyujinCore.hh"


auto main() -> int {

    std::cout << "Hello World!\n";

    RyujinObfuscatorConfig config;
    config.m_isIgnoreOriginalCodeRemove = FALSE;
    config.m_isJunkCode = TRUE;
    config.m_isRandomSection = FALSE;
    config.m_isVirtualized = TRUE;
    config.m_isIatObfuscation = TRUE;
    config.m_isEncryptObfuscatedCode = TRUE;
    std::vector<std::string> procsToObfuscate{

        "sum",
        "sub",
        "subadd",
        "main",
        "invoke_main"
        "__scrt_common_main",
        "j___security_init_cookie"
    
    };
    config.m_strProceduresToObfuscate.assign(procsToObfuscate.begin(), procsToObfuscate.end());

    auto bSuccess = config.RunRyujin("C:\\Users\\Keowu\\Documents\\GitHub\\Ryujin\\compiled\\release\\DemoObfuscation.exe", "C:\\Users\\Keowu\\Documents\\GitHub\\Ryujin\\compiled\\release\\DemoObfuscation.pdb", "C:\\Users\\Keowu\\Documents\\GitHub\\Ryujin\\compiled\\release\\DemoObfuscation.obfuscated.exe", config);

    std::printf("Ryujin core returned: %d\n", bSuccess);

    std::cin.get();

    return 0;
}