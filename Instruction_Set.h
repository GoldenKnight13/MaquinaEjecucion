#pragma once
#include <unordered_map>
#include <string>
#include <iostream>

namespace InstructionSet {

    //Listado de instrucciones validas
    enum class KEYWORD {
        HALT,
        IN, OUT,
        ADD, SUB, MUL, DIV,
        LD, LDA, LDC, ST,
        JLT, JLE, JGT, JGE, JEQ, JNE,
        UNKNOWN
    };

    // Tokenizador de strings a instrucciones
    inline const std::unordered_map<std::string, KEYWORD> TRANSLATOR = {
        {"HALT", KEYWORD::HALT},
        {"IN", KEYWORD::IN}, {"OUT", KEYWORD::OUT},
        {"ADD", KEYWORD::ADD}, {"SUB", KEYWORD::SUB}, {"MUL", KEYWORD::MUL}, {"DIV", KEYWORD::DIV},
        {"LD", KEYWORD::LD}, {"LDA", KEYWORD::LDA}, {"LDC", KEYWORD::LDC}, {"ST", KEYWORD::ST},
        {"JLT", KEYWORD::JLT}, {"JLE", KEYWORD::JLE}, {"JGT", KEYWORD::JGT}, {"JGE", KEYWORD::JGE}, {"JEQ", KEYWORD::JEQ}, {"JNE", KEYWORD::JNE}
    };

    // Permite obtener un string de los comandos
    inline const std::unordered_map<KEYWORD, std::string> INVERSOR = {
        {KEYWORD::HALT, "HALT"},
        {KEYWORD::IN, "IN"}, {KEYWORD::OUT, "OUT"},
        {KEYWORD::ADD, "ADD"}, {KEYWORD::SUB, "SUB"}, {KEYWORD::MUL, "MUL"}, {KEYWORD::DIV, "DIV"},
        {KEYWORD::LD, "LD"}, {KEYWORD::LDA, "LDA"}, {KEYWORD::LDC, "LDC"}, {KEYWORD::ST, "ST"},
        {KEYWORD::JLT, "JLT"}, {KEYWORD::JLE, "JLE"}, {KEYWORD::JGT, "JGT"}, {KEYWORD::JGE, "JGE"}, {KEYWORD::JEQ, "JEQ"}, {KEYWORD::JNE, "JNE"}
    };

    //Permite usar cout para imprimir la instruccion guardada
    inline std::ostream& operator <<(std::ostream& os, const KEYWORD instruction) {

        auto it = INVERSOR.find(instruction);
        if (it != INVERSOR.end()) os << it->second;
        else os << "UNKNOWN";

        return os;
    };

}