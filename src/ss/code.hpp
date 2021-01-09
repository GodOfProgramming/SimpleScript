#pragma once

#include <cinttypes>
#include <string>
#include <vector>

namespace ss
{
  enum class OpCode : std::uint8_t
  {
    NO_OP,
    CONSTANT,
    ADD,
    SUB,
    MUL,
    DIV,
    NEGATE,
    RETURN,
  };

  struct Instruction
  {
    OpCode      major_opcode   = OpCode::NO_OP;
    std::size_t modifying_bits = 0;
  };

  constexpr auto to_string(OpCode op) noexcept -> const char*
  {
    switch (op) {
      case OpCode::NO_OP: {
        return "NOOP";
      }
      case OpCode::CONSTANT: {
        return "CONSTANT";
      }
      case OpCode::ADD: {
        return "ADD";
      } break;
      case OpCode::SUB: {
        return "SUB";
      } break;
      case OpCode::MUL: {
        return "MUL";
      } break;
      case OpCode::DIV: {
        return "DIV";
      } break;
      case OpCode::NEGATE: {
        return "NEGATE";
      }
      case OpCode::RETURN: {
        return "RETURN";
      }
      default: {
        return "UNKNOWN";
      }
    }
  }

  enum class TokenType
  {
    // Single-character tokens.
    LEFT_PAREN,
    RIGHT_PAREN,
    LEFT_BRACE,
    RIGHT_BRACE,
    COMMA,
    DOT,
    MINUS,
    PLUS,
    SEMICOLON,
    SLASH,
    STAR,

    // One or two character tokens.
    BANG,
    BANG_EQUAL,
    EQUAL,
    EQUAL_EQUAL,
    GREATER,
    GREATER_EQUAL,
    LESS,
    LESS_EQUAL,

    // Literals.
    IDENTIFIER,
    STRING,
    NUMBER,

    // Keywords.
    AND,
    CLASS,
    ELSE,
    FALSE,
    FOR,
    FN,
    IF,
    NIL,
    OR,
    PRINT,
    RETURN,
    SUPER,
    THIS,
    TRUE,
    LET,
    WHILE,

    ERROR,
    END_OF_FILE,
  };

  struct Token
  {
    TokenType        type;
    std::string_view lexeme;
    std::size_t      line;
  };

  class Scanner
  {
   public:
    Scanner(std::string& src) noexcept;
    ~Scanner() = default;

    auto scan() -> std::vector<Token>;

   private:
    std::string&          source;
    std::string::iterator start;
    std::string::iterator current;
    std::size_t           line;

    auto make_token(TokenType t) const noexcept -> Token;
    auto make_string() -> Token;
    auto make_number() -> Token;
    auto is_at_end() const noexcept -> bool;
    auto peek() const noexcept -> char;
    auto peek_next() const noexcept -> char;
    auto advance() noexcept -> char;
    auto advance_if_match(char expected) -> bool;
    void skip_whitespace() noexcept;
    auto is_digit(char c) const noexcept -> bool;
  };

  class Compiler
  {
   public:
    Compiler(std::string& src) noexcept;
    ~Compiler() = default;

    void compile();

   private:
    std::string& source;
  };
}  // namespace ss