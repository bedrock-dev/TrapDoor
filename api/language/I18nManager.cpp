//
// Created by xhy on 2021/2/5.
//

#include "I18nManager.h"
#include "BDSMod.h"
#include "tools/DirtyLogger.h"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace trapdoor {
void I18nManager::findLanguageFile() {
    namespace fs = std::filesystem;
    fs::path path("plugins/trapdoor/lang");
    if (!fs::exists(path)) {
        L_WARNING("can't find the language dictionary");
        return;
    }
    fs::directory_entry entry(path); //文件入口
    if (entry.status().type() == fs::file_type::directory) {
        for (const auto &iter : fs::directory_iterator(path)) {
            if (fs::is_regular_file(iter.path())) {
                readLanguageFile(iter.path().string());
            }
        }
    }
}

void I18nManager::readLanguageFile(const std::string &path) {
    if (path.size() < 10) {
        return;
    }
    // auto langName = path.substr(5, path.size() - 10);
    auto langName = path.substr(path.find_last_of('\\') + 1,
                                path.size() - path.find_last_of('.'));
    //  L_WARNING("find language file [%s]", langName.c_str());
    json langJson;
    try {
        std::ifstream i(path);
        i >> langJson;
    } catch (std::exception &e) {
        L_ERROR("can not read config file %s ", path.c_str());
        return;
    }

    this->languages.insert(langName);
    try {
        for (auto &[key, value] : langJson.items()) {
            this->strings[langName][key] = value.get<std::string>();
        }
    } catch (std::exception &e) {
        L_ERROR("can not read config file %s ", path.c_str());
    }
}

bool I18nManager::tryChangeLanguage(const std::string &language) {
    auto iter = this->languages.find(language);
    if (iter == this->languages.end())
        return false;
    this->current_lang = language;
    return true;
}

std::string I18nManager::get(const std::string &id) {
    //找不到就按照原样返回
    auto iter = this->strings[current_lang].find(id);
    if (iter != this->strings[current_lang].end()) {
        return iter->second;
    }
    return id;
}

void I18nManager::getSystemLangAndSet() {
    LCID localeID = GetUserDefaultLCID();
    unsigned short lang = localeID & 0xFF;
    if (lang == LANG_CHINESE) {
        this->tryChangeLanguage("zh_cn");
    } else {
        this->tryChangeLanguage("en_us");
    }
}

std::string LANG(const std::string &l) {
    return trapdoor::bdsMod->getI18NManager().get(l);
}

} // namespace trapdoor

std::string operator""_i18(const char *key, unsigned long long) {
    return trapdoor::LANG(key);
}
