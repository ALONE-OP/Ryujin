
class RyujinObfuscatorConfig {

public:
	bool m_isRandomSection; // Randomize the name of the new section with the processed code -> Ryujin standard
	bool m_isVirtualized; // Virtualize the code [Try as much as possible]
	bool m_isJunkCode; // Insert junk code to confuse
	bool m_isIgnoreOriginalCodeRemove; // Do not remove the original code after processing (replace the original instructions with NOPs)
	std::vector<std::string> m_strProceduresToObfuscate; // Names of the procedures to obfuscate
	// todo: passes

};