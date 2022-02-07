//
// Created by xhy on 2021/2/5.
//

#ifndef MOD_I18NMANAGER_H
#define MOD_I18NMANAGER_H

#include <set>
#include <unordered_map>

#include "tools/json.hpp"

namespace trapdoor {

    using json = nlohmann::json;

    namespace lang {
        std::string getSystemLang();
        bool tryChangeLang(const std::string &);
        void initialize();
        std::string getAllLanguages();
        std::string get(const std::string &);
    }  // namespace lang

    // class I18nManager {
    //     std::string current_lang = "zh_cn";
    //     std::set<std::string> languages;
    //     std::unordered_map<std::string,
    //                        std::unordered_map<std::string, std::string>>
    //         strings;

    //     void findLanguageFile();

    //     void readLanguageFile(const std::string &langName);

    //     void getSystemLangAndSet();

    //    public:
    //     std::string get(const std::string &id);

    //     bool tryChangeLanguage(const std::string &language);

    //     std::string getAllLanguages() {
    //         std::string s;
    //         for (const auto &lang : this->languages) s += lang + "\n";
    //         return s;
    //     }

    //     inline void initialize() {}
    //     //{

    //     //读取语言文件
    //     //  this->findLanguageFile();
    //     // this->getSystemLangAndSet();
    //     // }
    // };

    std::string LANG(const std::string &l);
}  // namespace trapdoor

std::string operator""_i18(const char *key, unsigned long long);

#endif  // MOD_I18NMANAGER_H
