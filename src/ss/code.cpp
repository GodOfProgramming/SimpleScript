#include "code.hpp"
#include "exceptions.hpp"
#include <sstream>

namespace ss
{
  Scanner::Scanner(std::string& src): source(src), current(source.begin()), line(1) {}

  auto Scanner::scan() -> std::vector<Token>
  {
    std::vector<Token> tokens;

    for (this->start = this->current; !this->is_at_end(); this->start = ++this->current) {
      this->skip_whitespace();
      char c = *this->start;
      switch (*this->start) {
        case '(': {
          tokens.push_back(this->make_token(TokenType::LEFT_PAREN));
        } break;
        case ')': {
          tokens.push_back(this->make_token(TokenType::RIGHT_PAREN));
        } break;
        case '{': {
          tokens.push_back(this->make_token(TokenType::LEFT_BRACE));
        } break;
        case '}': {
          tokens.push_back(this->make_token(TokenType::RIGHT_BRACE));
        } break;
        case ';': {
          tokens.push_back(this->make_token(TokenType::SEMICOLON));
        } break;
        case ',': {
          tokens.push_back(this->make_token(TokenType::COMMA));
        } break;
        case '.': {
          tokens.push_back(this->make_token(TokenType::DOT));
        } break;
        case '-': {
          tokens.push_back(this->make_token(TokenType::MINUS));
        } break;
        case '+': {
          tokens.push_back(this->make_token(TokenType::PLUS));
        } break;
        case '/': {
          tokens.push_back(this->make_token(TokenType::SLASH));
        } break;
        case '*': {
          tokens.push_back(this->make_token(TokenType::STAR));
        } break;
        case '!': {
          tokens.push_back(this->make_token(this->advance_if_match('=') ? TokenType::BANG_EQUAL : TokenType::BANG));
        } break;
        case '=': {
          tokens.push_back(this->make_token(this->advance_if_match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL));
        } break;
        case '<': {
          tokens.push_back(this->make_token(this->advance_if_match('=') ? TokenType::LESS_EQUAL : TokenType::LESS));
        } break;
        case '>': {
          tokens.push_back(this->make_token(this->advance_if_match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER));
        } break;
        case '"': {
          tokens.push_back(this->make_string());
        } break;
        default: {
          if (this->is_digit(c)) {
            tokens.push_back(this->make_number());
          } else if (this->is_alpha(c)) {
            tokens.push_back(this->make_identifier());
          } else {
            std::stringstream ss;
            ss << "invalid character '" << *this->start << "' on line " << this->line;
            THROW_COMPILETIME_ERROR(ss.str());
          }
        }
      }
    }

    tokens.push_back(this->make_token(TokenType::END_OF_FILE));

    return tokens;
  }

  auto Scanner::make_token(TokenType t) const noexcept -> Token
  {
    Token token;
    token.type   = t;
    token.lexeme = std::string_view(this->start.base(), this->current - this->start);
    token.line   = this->line;
  }

  auto Scanner::make_string() -> Token
  {
    while (!this->is_at_end() && this->peek() != '"') {
      if (this->peek() == '\n') {
        this->line++;
      }
      this->advance();
    }

    if (this->is_at_end()) {
      std::stringstream ss;
      ss << "unterminated string on line " << this->line;
      THROW_COMPILETIME_ERROR(ss.str());
    }

    // advance past the leading '"'
    this->start++;

    Token str = this->make_token(TokenType::STRING);

    // advance past the closing '"'
    this->advance();

    return str;
  }

  auto Scanner::make_number() -> Token
  {
    while (this->is_digit(this->peek())) {
      this->advance();
    }

    if (!this->is_at_end() && this->peek() == '.' && this->is_digit(this->peek_next())) {
      // advance past the "."
      this->advance();

      while (this->is_digit(this->peek())) {
        this->advance();
      }
    }

    return this->make_token(TokenType::NUMBER);
  }

  auto Scanner::is_at_end() const noexcept -> bool
  {
    return this->current >= this->source.end();
  }

  auto Scanner::peek() const noexcept -> char
  {
    return *this->current;
  }

  auto Scanner::peek_next() const noexcept -> char
  {
    return *(this->current + 1);
  }

  auto Scanner::advance() noexcept -> char
  {
    char c = *this->current;
    this->current++;
    return c;
  }

  auto Scanner::advance_if_match(char expected) noexcept -> bool
  {
    if (*this->current != expected || this->is_at_end()) {
      return false;
    }

    this->advance();
    return true;
  }

  void Scanner::skip_whitespace() noexcept
  {
    bool done = false;
    while (!done && !this->is_at_end()) {
      switch (this->peek()) {
        case ' ':
        case '\r':
        case '\t': {
          this->advance();
        } break;
        case '\n': {
          this->line++;
          this->advance();
        } break;
        case '#': {
          this->advance();
          while (!this->is_at_end() && this->advance() != '\n') {
          }
        } break;
        default: {
          done = true;
        }
      }
    }
  }

  auto Scanner::is_digit(char c) const noexcept -> bool
  {
    return !this->is_at_end() && c >= '0' && c <= '9';
  }

  Compiler::Compiler(std::string& src): source(src) {}

  void Compiler::compile()
  {
    Scanner scanner(this->source);
    auto    tokens = scanner.scan();

    for (auto iter = tokens.begin(); iter < tokens.end(); iter++) {
    }
  }
}  // namespace ss