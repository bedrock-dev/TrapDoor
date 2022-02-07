//
// Created by xhy on 2021/2/5.
//

#include "I18nManager.h"

#include <filesystem>
#include <fstream>
#include <iostream>

#include "BDSMod.h"
#include "tools/DirtyLogger.h"

namespace trapdoor {
    namespace lang {
        namespace {

            std::string &currentLang() {
                static std::string cur_lang = "zh_cn";
                return cur_lang;
            }

            std::unordered_map<std::string,
                               std::unordered_map<std::string, std::string>>
                &LangStrings() {
                static std::unordered_map<
                    std::string, std::unordered_map<std::string, std::string>>
                    strings;
                return strings;
            }

            void parseLangString(const char *name, const char *strings) {
                try {
                    auto j = json::parse(strings);
                    for (auto &[key, value] : j.items()) {
                        LangStrings()[name][key] = value.get<std::string>();
                    }
                } catch (std::exception &e) {
                    L_ERROR("can not read lang [%s]", name);
                }
            }

        }  // namespace

        void initialize() {
            const char *lang_en_us =
#include "lang/en_us"
                ;
            const char *lang_zh_cn =
#include "lang/zh_cn"
                ;
            parseLangString("zh_cn", lang_zh_cn);
            parseLangString("en_us", lang_en_us);
            tryChangeLang(getSystemLang());
        }

        std::string get(const std::string &id) {
            auto iter = LangStrings()[currentLang()].find(id);
            if (iter != LangStrings()[currentLang()].end()) {
                return iter->second;
            }
            return id;
        }

        std::string getSystemLang() {
            LCID localeID = GetUserDefaultUILanguage();
            unsigned short lang = localeID & 0xFF;
            if (lang == LANG_CHINESE) {
                return "zh_cn";
            } else {
                return "en_us";
            }
        }
        bool tryChangeLang(const std::string &name) {
            L_INFO("set language to %s", name.c_str());
            auto iter = LangStrings().find(name);
            if (iter != LangStrings().end()) {
                currentLang() = name;
                return true;
            } else {
                return false;
            }
        }

        std::string getAllLanguages() {
            std::string res;
            for (auto &kv : LangStrings()) {
                res += kv.first + "\n";
            }
            return res;
        }
    }  // namespace lang

    // void I18nManager::findLanguageFile() {
    //     namespace fs = std::filesystem;
    //     fs::path path("plugins/trapdoor/lang");
    //     if (!fs::exists(path)) {
    //         L_WARNING("can't find the language dictionary");
    //         return;
    //     }
    //     fs::directory_entry entry(path);  //文件入口
    //     if (entry.status().type() == fs::file_type::directory) {
    //         for (const auto &iter : fs::directory_iterator(path)) {
    //             if (fs::is_regular_file(iter.path())) {
    //                 readLanguageFile(iter.path().string());
    //             }
    //         }
    //     }
    // }

    // void I18nManager::readLanguageFile(const std::string &path) {
    //     if (path.size() < 10) {
    //         return;
    //     }
    //     auto langName = path.substr(path.find_last_of('\\') + 1,
    //                                 path.size() - path.find_last_of('.'));
    //     json langJson;
    //     try {
    //         std::ifstream i(path);
    //         i >> langJson;
    //     } catch (std::exception &e) {
    //         L_ERROR("can not read config file %s with reason:\n[%s] ",
    //                 path.c_str(), e.what());
    //         return;
    //     }

    //     this->languages.insert(langName);
    //     try {
    //         for (auto &[key, value] : langJson.items()) {
    //             this->strings[langName][key] = value.get<std::string>();
    //         }
    //     } catch (std::exception &e) {
    //         L_ERROR("can not read config file %s with reasion:\n[%s]",
    //                 path.c_str(), e.what());
    //     }
    // }

    // bool I18nManager::tryChangeLanguage(const std::string &language) {
    //     auto iter = this->languages.find(language);
    //     if (iter == this->languages.end()) return false;
    //     L_INFO("set language to %s", language.c_str());
    //     this->current_lang = language;
    //     return true;
    // }

    // std::string I18nManager::get(const std::string &id) {
    //     //找不到就按照原样返回
    //     auto iter = this->strings[current_lang].find(id);
    //     if (iter != this->strings[current_lang].end()) {
    //         return iter->second;
    //     }
    //     return id;
    // }

    // void I18nManager::getSystemLangAndSet() {
    //     LCID localeID = GetUserDefaultLCID();
    //     unsigned short lang = localeID & 0xFF;
    //     if (lang == LANG_CHINESE) {
    //         this->tryChangeLanguage("zh_cn");
    //     } else {
    //         this->tryChangeLanguage("en_us");
    //     }
    // }

    std::string LANG(const std::string &l) {
        return lang::get(l);
        // return trapdoor::bdsMod->getI18NManager().get(l);
    }
}  // namespace trapdoor

std::string operator""_i18(const char *key, unsigned long long) {
    return trapdoor::LANG(key);
}
