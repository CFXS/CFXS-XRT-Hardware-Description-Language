#include "Token.hpp"
#include <Log/Logger.hpp>
#include <StringUtils.hpp>

namespace XRT {

    static std::string TokenTypeToString(TokenType t) {
        switch (t) {
            case TokenType::KEYWORD: return "KEYWORD";
            case TokenType::IDENTIFIER: return "IDENTIFIER";
            case TokenType::INVALID_IDENTIFIER: return "INVALID_IDENTIFIER";
            case TokenType::LITERAL: return "LITERAL";
            case TokenType::INVALID_LITERAL: return "INVALID_LITERAL";
            case TokenType::OPERATOR: return "OPERATOR";
            case TokenType::PUNCTUATOR: return "PUNCTUATOR";
            case TokenType::COMMENT: return "COMMENT";
            default: return "???";
        }
    }

    Token::Token(const std::wstring& currentValue,
                 TokenType type,
                 size_t entrySize,
                 size_t line,
                 size_t column,
                 const std::filesystem::path* filePath) :
        m_FilePath(filePath), m_Value(currentValue), m_Type(type), m_EntrySize(entrySize), m_Line(line), m_Column(column) {
    }

    Token::~Token() {
    }

    std::string Token::GetValue_utf8() {
        return StringUtils::utf16_to_utf8(m_Value);
    }

    void Token::Print() {
        LOG_TRACE("[Token]");
        LOG_TRACE("    | '{}'", GetValue_utf8());
        LOG_TRACE("    | '{}'", TokenTypeToString(m_Type));
        LOG_TRACE("    | '{}'", GetEntrySize());
        LOG_TRACE("    | \"{}:{}:{}\"", m_FilePath->string(), GetLine(), GetColumn());
    }

    std::string Token::PrintToString() {
        std::stringstream ss;
        fmt::print(ss, "    | '{}'\n", GetValue_utf8());
        fmt::print(ss, "    | '{}'\n", TokenTypeToString(m_Type));
        fmt::print(ss, "    | '{}'\n", GetEntrySize());
        fmt::print(ss, "    | \"{}:{}:{}\"", m_FilePath->string(), GetLine(), GetColumn());
        return ss.str();
    }

} // namespace XRT
