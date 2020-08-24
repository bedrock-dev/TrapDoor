#include "pch.h"
#include "mod.h"
#include "SymHook.h"
#include<cctype>
#include <string>
#include<ctime>
#include<map>
#include <sstream>
#include<vector>

using namespace SymHook;
/**——————————————————————————————————————**
 |              MOD C++文件               |
 **——————————————————————————————————————**
说明：
该cpp文件的目的是包含MOD功能主要代码，请将主要部分代码写在这个文件内！
“T”开头的系列Hook宏在模块加载的时候调用，使用方法请参考MCMrARM的modloader。
地址：https://github.com/minecraft-linux/server-modloader/wiki
请注意：使用方法略有不同，本文件的函数符号用的是PDB工具生成的C++变量，而不是字符串字面量！
另外，该文件包含两个函数mod_init和mod_exit，分别在该模块加载或退出时调用。
本模块例子：
THook(void,							// 函数返回类型
	MSSYM_XXXXXXXXXXXXXXXXXXXXX,	// 函数符号名对应的C++变量（位于SymHook.h）
	__int64 a1, __int64 a2) {		// 函数参数类型列表（假设存在参数a1与a2）
	std::cout << "Hello world!" << std::endl;
	original(a1, a2);				// 调用该函数Hook前的原始函数
}
*/

// 此处开始编写MOD代码
// 下面两个函数不是必要的，你可以使用，也可以不使用。
void mod_init() {
    const char *banner = "\n"
                         "  _______                  _                   \n"
                         " |__   __|                | |                  \n"
                         "    | |_ __ __ _ _ __   __| | ___   ___  _ __  \n"
                         "    | | '__/ _` | '_ \\ / _` |/ _ \\ / _ \\| '__| \n"
                         "    | | | | (_| | |_) | (_| | (_) | (_) | |    \n"
                         "    |_|_|  \\__,_| .__/ \\__,_|\\___/ \\___/|_|    \n"
                         "                | |                            \n"
                         "                |_|                            ";
    printf("%s\nTrapdoor V0.1.4\ngithub:https://github.com/hhhxiao/MCBEtoolSet\nLicense: MIT\n", banner);
    // 此处填写模块加载时候的操作
}

void mod_exit() {
    // 此处填写模块卸载时候的操作
}
