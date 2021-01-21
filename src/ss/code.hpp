#pragma once

#include "datatypes.hpp"
#include <cinttypes>
#include <string>
#include <vector>
#include <functional>

#define SS_ENUM_TO_STR_CASE(enum, name) \
  case enum::name: {            \
    return #name;                 \
  }

namespace ss
{
  enum class OpCode : std::uint8_t
  {
    NO_OP,
    CONSTANT,
    NIL,
    TRUE,
    FALSE,
    POP,
    LOOKUP_GLOBAL,
    DEFINE_GLOBAL,
    EQUAL,
    NOT_EQUAL,
    GREATER,
    GREATER_EQUAL,
    LESS,
    LESS_EQUAL,
    ADD,
    SUB,
    MUL,
    DIV,
    MOD,
    NOT,
    NEGATE,
    PRINT,
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
      SS_ENUM_TO_STR_CASE(OpCode, NO_OP)
      SS_ENUM_TO_STR_CASE(OpCode, CONSTANT)
      SS_ENUM_TO_STR_CASE(OpCode, NIL)
      SS_ENUM_TO_STR_CASE(OpCode, TRUE)
      SS_ENUM_TO_STR_CASE(OpCode, FALSE)
      SS_ENUM_TO_STR_CASE(OpCode, POP)
      SS_ENUM_TO_STR_CASE(OpCode, LOOKUP_GLOBAL)
      SS_ENUM_TO_STR_CASE(OpCode, DEFINE_GLOBAL)
      SS_ENUM_TO_STR_CASE(OpCode, EQUAL)
      SS_ENUM_TO_STR_CASE(OpCode, NOT_EQUAL)
      SS_ENUM_TO_STR_CASE(OpCode, GREATER)
      SS_ENUM_TO_STR_CASE(OpCode, GREATER_EQUAL)
      SS_ENUM_TO_STR_CASE(OpCode, LESS)
      SS_ENUM_TO_STR_CASE(OpCode, LESS_EQUAL)
      SS_ENUM_TO_STR_CASE(OpCode, ADD)
      SS_ENUM_TO_STR_CASE(OpCode, SUB)
      SS_ENUM_TO_STR_CASE(OpCode, MUL)
      SS_ENUM_TO_STR_CASE(OpCode, DIV)
      SS_ENUM_TO_STR_CASE(OpCode, MOD)
      SS_ENUM_TO_STR_CASE(OpCode, NOT)
      SS_ENUM_TO_STR_CASE(OpCode, NEGATE)
      SS_ENUM_TO_STR_CASE(OpCode, PRINT)
      SS_ENUM_TO_STR_CASE(OpCode, RETURN)
      default: {
        return "UNKNOWN";
      }
    }
  }

  auto operator<<(std::ostream& ostream, const OpCode& code) -> std::ostream&;

  struct Token
  {
    enum class Type
    {
      // Single-character tokens.
      LEFT_PAREN,
      RIGHT_PAREN,
      LEFT_BRACE,
      RIGHT_BRACE,
      COMMA,
      DOT,
      SEMICOLON,
      PLUS,
      MINUS,
      STAR,
      SLASH,
      MODULUS,

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
      LET,
      NIL,
      OR,
      PRINT,
      RETURN,
      TRUE,
      WHILE,

      ERROR,
      END_OF_FILE,
      LAST,
    };

    Type             type;
    std::string_view lexeme;
    std::size_t      line;
    std::size_t      column;

    auto operator==(const Token& other) const noexcept -> bool;
  };

  constexpr auto to_string(Token::Type type) noexcept -> const char* {
    switch (type) {
      SS_ENUM_TO_STR_CASE(Token::Type, LEFT_PAREN)
      SS_ENUM_TO_STR_CASE(Token::Type, RIGHT_PAREN)
      SS_ENUM_TO_STR_CASE(Token::Type, LEFT_BRACE)
      SS_ENUM_TO_STR_CASE(Token::Type, RIGHT_BRACE)
      SS_ENUM_TO_STR_CASE(Token::Type, COMMA)
      SS_ENUM_TO_STR_CASE(Token::Type, DOT)
      SS_ENUM_TO_STR_CASE(Token::Type, SEMICOLON)
      SS_ENUM_TO_STR_CASE(Token::Type, PLUS)
      SS_ENUM_TO_STR_CASE(Token::Type, MINUS)
      SS_ENUM_TO_STR_CASE(Token::Type, STAR)
      SS_ENUM_TO_STR_CASE(Token::Type, SLASH)
      SS_ENUM_TO_STR_CASE(Token::Type, MODULUS)
      SS_ENUM_TO_STR_CASE(Token::Type, BANG)
      SS_ENUM_TO_STR_CASE(Token::Type, BANG_EQUAL)
      SS_ENUM_TO_STR_CASE(Token::Type, EQUAL)
      SS_ENUM_TO_STR_CASE(Token::Type, EQUAL_EQUAL)
      SS_ENUM_TO_STR_CASE(Token::Type, GREATER)
      SS_ENUM_TO_STR_CASE(Token::Type, GREATER_EQUAL)
      SS_ENUM_TO_STR_CASE(Token::Type, LESS)
      SS_ENUM_TO_STR_CASE(Token::Type, LESS_EQUAL)
      SS_ENUM_TO_STR_CASE(Token::Type, IDENTIFIER)
      SS_ENUM_TO_STR_CASE(Token::Type, STRING)
      SS_ENUM_TO_STR_CASE(Token::Type, NUMBER)
      SS_ENUM_TO_STR_CASE(Token::Type, AND)
      SS_ENUM_TO_STR_CASE(Token::Type, CLASS)
      SS_ENUM_TO_STR_CASE(Token::Type, ELSE)
      SS_ENUM_TO_STR_CASE(Token::Type, FALSE)
      SS_ENUM_TO_STR_CASE(Token::Type, FOR)
      SS_ENUM_TO_STR_CASE(Token::Type, FN)
      SS_ENUM_TO_STR_CASE(Token::Type, IF)
      SS_ENUM_TO_STR_CASE(Token::Type, LET)
      SS_ENUM_TO_STR_CASE(Token::Type, NIL)
      SS_ENUM_TO_STR_CASE(Token::Type, OR)
      SS_ENUM_TO_STR_CASE(Token::Type, PRINT)
      SS_ENUM_TO_STR_CASE(Token::Type, RETURN)
      SS_ENUM_TO_STR_CASE(Token::Type, TRUE)
      SS_ENUM_TO_STR_CASE(Token::Type, WHILE)
      SS_ENUM_TO_STR_CASE(Token::Type, ERROR)
      SS_ENUM_TO_STR_CASE(Token::Type, END_OF_FILE)
      SS_ENUM_TO_STR_CASE(Token::Type, LAST)
      default: {
        return "UNKNOWN";
      }
    }
  }

  auto operator<<(std::ostream& ostream, const Token::Type& type) -> std::ostream&;
  auto operator<<(std::ostream& ostream, const Token& token) -> std::ostream&;

  class Chunk
  {
   public:
    void write(Instruction, std::size_t line);
    void write_constant(Value v, std::size_t line);
    auto insert_constant(Value v) -> std::size_t;

    auto constant_at(std::size_t offset) -> Value;

    void push_stack(Value v);
    auto pop_stack() -> Value;
    auto stack_empty() -> bool;

    auto line_at(std::size_t offset) const noexcept -> std::size_t;

    std::vector<Instruction> code;
    std::vector<Value>       constants;
    std::vector<Value>       stack;

   private:
    std::vector<std::size_t> lines;
    std::size_t              last_line            = 0;
    std::size_t              instructions_on_line = 0;

    void add_line(std::size_t line) noexcept;
  };

  void compile(std::string& src, Chunk& chunk);

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
    std::size_t           column;

    void error(std::string msg) const;
    auto make_token(Token::Type t) const noexcept -> Token;
    auto make_string() -> Token;
    auto make_number() -> Token;
    auto make_identifier() -> Token;
    auto identifier() -> Token::Type;
    auto check_keyword(std::size_t start, std::size_t len, const char* rest, Token::Type type) const noexcept -> Token::Type;
    auto is_at_end() const noexcept -> bool;
    auto peek() const noexcept -> char;
    auto peek_next() const noexcept -> char;
    auto advance() noexcept -> char;
    auto advance_if_match(char expected) noexcept -> bool;
    void skip_whitespace() noexcept;
    auto is_digit(char c) const noexcept -> bool;
    auto is_alpha(char c) const noexcept -> bool;
  };

  class Parser
  {
    using TokenList     = std::vector<Token>;
    using TokenIterator = TokenList::iterator;

    enum class Precedence
    {
      NONE,
      ASSIGNMENT,  // =
      OR,          // or
      AND,         // and
      EQUALITY,    // == !=
      COMPARISON,  // < > <= >=
      TERM,        // + -
      FACTOR,      // / *
      UNARY,       // - !
      CALL,        // . ()
      PRIMARY,
    };

    using ParseFn = std::function<void(Parser*)>;

    struct ParseRule
    {
      ParseFn    prefix;
      ParseFn    infix;
      Precedence precedence;
    };

   public:
    Parser(TokenList&& tokens, Chunk& chunk) noexcept;
    ~Parser() = default;

    void parse();

   private:
    TokenList     tokens;
    TokenIterator iter;
    Chunk&        chunk;

    void write_instruction(Instruction i);

    auto previous() const -> TokenIterator;
    void advance() noexcept;
    void consume(Token::Type type, std::string err);
    void error(TokenIterator tok, std::string msg) const;
    void emit_instruction(Instruction i);

    auto rule_for(Token::Type t) const noexcept -> const ParseRule&;
    void parse_precedence(Precedence p);
    void make_number();
    void make_string();
    void make_variable();
    void named_variable(TokenIterator name);
    auto parse_variable(std::string err_msg) -> std::size_t;
    void define_variable(std::size_t global);
    auto identifier_constant(TokenIterator name) -> std::size_t;
    auto check(Token::Type type) -> bool;
    auto advance_if_matches(Token::Type type) -> bool;

    void expression();
    void grouping();
    void unary();
    void binary();
    void literal();

    void declaration();

    void statement();
    void print_statement();
    void expression_statement();
    void let_statement();
  };
}  // namespace ss