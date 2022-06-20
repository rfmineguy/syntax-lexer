#include <regex>
#include <fstream>
#include <sstream>
#include <utility>
#include <vector>
#include <iostream>
#include <map>

void searchLine(std::string source, std::string regex);

int main() {
    std::fstream fs("res/main.rf");

    std::vector<std::string> lines;
    std::string fullCode;
    std::string s;
    while (getline(fs, s)) {
        s.erase(std::remove(s.begin(), s.end(), ' '), s.end());
        lines.push_back(s);
        fullCode.append(s + "\n");
    }

    std::vector<std::regex> reg_vec;

    // the order of this vector is the order the files will be lexed
    std::vector<std::pair<std::string, std::string>> vec;
    vec.push_back(std::make_pair("byte|word|dword|qword", "TYPE "));
    vec.push_back(std::make_pair("fun",         "FUNC "));
    vec.push_back(std::make_pair("ret",         "RET "));
    vec.push_back(std::make_pair("for",         "FOR "));
    vec.push_back(std::make_pair("(or|\\|\\|)", "OR "));
    vec.push_back(std::make_pair("(and|\\&\\&)","AND "));
    vec.push_back(std::make_pair("if",          "IF "));
    vec.push_back(std::make_pair("0b[0-1]+",    "BLITERAL "));
    vec.push_back(std::make_pair("0x[0-9]+",    "HLITERAL "));
    vec.push_back(std::make_pair("[0-9]+",      "DLITERAL "));
    vec.push_back(std::make_pair("[a-z]+",      "ID "));
    vec.push_back(std::make_pair(",",           "COMMA "));
    vec.push_back(std::make_pair("\\(",         "OPEN_PAREN "));
    vec.push_back(std::make_pair("\\)",         "CLOSE_PAREN "));
    vec.push_back(std::make_pair("\\{",         "OPEN_BRACE "));
    vec.push_back(std::make_pair("\\}",         "CLOSE_BRACE "));
    vec.push_back(std::make_pair("->",          "ARROW "));
    vec.push_back(std::make_pair(";",           "SEMI "));
    vec.push_back(std::make_pair("<=",          "LESSTHAN_EQ "));
    vec.push_back(std::make_pair("<",           "LESSTHAN "));
    vec.push_back(std::make_pair("=>",          "GREATERTHAN_EQ "));
    vec.push_back(std::make_pair(">",           "GREATERTHAN "));
    vec.push_back(std::make_pair("==",          "TEST_EQ "));
    vec.push_back(std::make_pair("=",           "ASSIGN "));
    vec.push_back(std::make_pair("\\+",         "PLUS "));
    vec.push_back(std::make_pair("\\-",         "MINUS "));
    vec.push_back(std::make_pair("\\*",         "MUL "));
    vec.push_back(std::make_pair("\\/",         "DIV "));

    for (auto& pair : vec) {
        try {
            fullCode = std::regex_replace(fullCode, std::regex(pair.first), pair.second.c_str());
        } catch (std::regex_error e) {
            printf("\033[31mERROR: Regex Error in [%s]\n", pair.first.c_str());
            printf("%s", e.what());
            printf("\033[39m\n");
        }
    }
    printf("Lexed source code written to %s\n", "res/main.lex");
    fs.close();
    fs.open("res/main.lex", std::ios::out);
    fs.write(fullCode.c_str(), fullCode.size());
    fs.close();
}
