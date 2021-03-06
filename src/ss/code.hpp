#pragma once

#include "cfg.hpp"
#include "datatypes.hpp"
#include "exceptions.hpp"

#include <cinttypes>
#include <functional>
#include <string>
#include <vector>

/**
 * @brief Case statement for any to_string() enum function
 *
 * @return The string representation for the given enum
 */
#define SS_ENUM_TO_STR_CASE(enum, name)                                                                                        \
  case enum ::name: {                                                                                                          \
    return #name;                                                                                                              \
  }

namespace ss
{
  enum class OpCode : std::uint8_t
  {
    /**
     * @brief No operation instruction
     */
    NO_OP,
    /**
     * @brief Looks up a constant value. The index is specified by the modifying bits
     */
    CONSTANT,
    /**
     * @brief Pushes a nil value on to the stack
     */
    NIL,
    /**
     * @brief Pushes a true value on to the stack
     */
    TRUE,
    /**
     * @brief Pushes a false value on to the stack
     */
    FALSE,
    /**
     * @brief Pops a value off the stack
     */
    POP,
    /**
     * @brief Pops N values off the stack. N is specified by the modifying bits
     */
    POP_N,
    /**
     * @brief Looks up a local variable. . The index in the stack is specified by the modifying bits
     */
    LOOKUP_LOCAL,
    /**
     * @brief Assigns a value to the local variable. The value comes off the top of the stack
     */
    ASSIGN_LOCAL,
    /**
     * @brief Looks up a global variable. The name is stored in the constant list. The index to then name is specified by the
     * modifying bits
     */
    LOOKUP_GLOBAL,
    /**
     * @brief Defines a new global variable. The name is stored in the constant list. The index to then name is specified by the
     * modifying bits
     */
    DEFINE_GLOBAL,
    /**
     * @brief Assigns a value to the global variable. The value comes off the top of the stack
     */
    ASSIGN_GLOBAL,
    /**
     * @brief Pops two values off the stack, compares, then pushes the result back on
     */
    EQUAL,
    /**
     * @brief Pops two values off the stack, compares, then pushes the result back on
     */
    NOT_EQUAL,
    /**
     * @brief Pops two values off the stack, compares, then pushes the result back on
     */
    GREATER,
    /**
     * @brief Pops two values off the stack, compares, then pushes the result back on
     */
    GREATER_EQUAL,
    /**
     * @brief Pops two values off the stack, compares, then pushes the result back on
     */
    LESS,
    /**
     * @brief Pops two values off the stack, compares, then pushes the result back on
     */
    LESS_EQUAL,
    /**
     * @brief Pops a value off the stack, and compars it with the peeked value, pushing the new value on
     */
    CHECK,
    /**
     * @brief Pops two values off the stack, calculates the sum, then pushes the result back on
     */
    ADD,
    /**
     * @brief Pops two values off the stack, calculates the difference, then pushes the result back on
     */
    SUB,
    /**
     * @brief Pops two values off the stack, calculates the product, then pushes the result back on
     */
    MUL,
    /**
     * @brief Pops two values off the stack, calculates the quotient, then pushes the result back on
     */
    DIV,
    /**
     * @brief Pops two values off the stack, calculates the remainder, then pushes the result back on
     */
    MOD,
    /**
     * @brief Pops a value off the stack, inverts its truthy value, then pushes that back on
     */
    NOT,
    /**
     * @brief Pops a value off the stack, inverts its numarical value, then pushes that back on
     */
    NEGATE,
    /**
     * @brief Pops a value off the stack and prints it to the screen
     */
    PRINT,
    /**
     * @brief Swaps the top two values on the stack.
     */
    SWAP,
    /**
     * @brief Moves, or rather shifts, the top value in the stack down N slots, specified by the modifying bits.
     */
    MOVE,
    /**
     * @brief Jumps to a code location indicated by the modifying bits
     */
    JUMP,
    /**
     * @brief Jumps to a code location indicated by the modifying bits
     */
    JUMP_IF_FALSE,
    /**
     * @brief Jumps the instruction pointer backwards N instructions. N specified by the modifying bits
     */
    LOOP,
    /**
     * @brief Peeks at the stack, if the top value is true short circuts to the instruction pointed to by the modifying bit
     */
    OR,
    /**
     * @brief Peeks at the stack, if the top value is false short circuts to the instruction pointed to by the modifying bit
     */
    AND,
    /**
     * @brief Pushes the stack pointer onto the stack
     */
    PUSH_SP,
    /** @brief Calls the instruction on the stack. Number of arguments is specified by the modifying bits */
    CALL,
    /** @brief TODO */
    RETURN,
    /** @brief TODO */
    END,
  };

  struct Instruction
  {
    OpCode major_opcode = OpCode::NO_OP;
    // TODO set this up to be a union { struct { uint8_t, uint16_t, & uint32_t }; /* other combinations */ };
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
      SS_ENUM_TO_STR_CASE(OpCode, POP_N)
      SS_ENUM_TO_STR_CASE(OpCode, LOOKUP_LOCAL)
      SS_ENUM_TO_STR_CASE(OpCode, ASSIGN_LOCAL)
      SS_ENUM_TO_STR_CASE(OpCode, LOOKUP_GLOBAL)
      SS_ENUM_TO_STR_CASE(OpCode, DEFINE_GLOBAL)
      SS_ENUM_TO_STR_CASE(OpCode, ASSIGN_GLOBAL)
      SS_ENUM_TO_STR_CASE(OpCode, EQUAL)
      SS_ENUM_TO_STR_CASE(OpCode, NOT_EQUAL)
      SS_ENUM_TO_STR_CASE(OpCode, GREATER)
      SS_ENUM_TO_STR_CASE(OpCode, GREATER_EQUAL)
      SS_ENUM_TO_STR_CASE(OpCode, LESS)
      SS_ENUM_TO_STR_CASE(OpCode, LESS_EQUAL)
      SS_ENUM_TO_STR_CASE(OpCode, CHECK)
      SS_ENUM_TO_STR_CASE(OpCode, ADD)
      SS_ENUM_TO_STR_CASE(OpCode, SUB)
      SS_ENUM_TO_STR_CASE(OpCode, MUL)
      SS_ENUM_TO_STR_CASE(OpCode, DIV)
      SS_ENUM_TO_STR_CASE(OpCode, MOD)
      SS_ENUM_TO_STR_CASE(OpCode, NOT)
      SS_ENUM_TO_STR_CASE(OpCode, NEGATE)
      SS_ENUM_TO_STR_CASE(OpCode, PRINT)
      SS_ENUM_TO_STR_CASE(OpCode, SWAP)
      SS_ENUM_TO_STR_CASE(OpCode, MOVE)
      SS_ENUM_TO_STR_CASE(OpCode, JUMP)
      SS_ENUM_TO_STR_CASE(OpCode, JUMP_IF_FALSE)
      SS_ENUM_TO_STR_CASE(OpCode, LOOP)
      SS_ENUM_TO_STR_CASE(OpCode, OR)
      SS_ENUM_TO_STR_CASE(OpCode, AND)
      SS_ENUM_TO_STR_CASE(OpCode, PUSH_SP)
      SS_ENUM_TO_STR_CASE(OpCode, CALL)
      SS_ENUM_TO_STR_CASE(OpCode, RETURN)
      SS_ENUM_TO_STR_CASE(OpCode, END)
      default: {
        return "UNKNOWN";
      }
    }
  }

  auto operator<<(std::ostream& ostream, const OpCode& code) -> std::ostream&;

  /**
   * @brief Structure representing scanned tokens
   */
  struct Token
  {
    /**
     * @brief Enumeration representing types of tokens
     */
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
      ARROW,

      // Literals.
      IDENTIFIER,
      STRING,
      NUMBER,

      // Keywords.
      AND,
      BREAK,
      CLASS,
      CONTINUE,
      ELSE,
      END,
      FALSE,
      FOR,
      FN,
      IF,
      LET,
      LOAD,
      LOADR,
      LOOP,
      MATCH,
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

    Type type;
    std::string_view lexeme;
    std::size_t line;
    std::size_t column;

    auto operator==(const Token& other) const noexcept -> bool;
  };

  constexpr auto to_string(Token::Type type) noexcept -> const char*
  {
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
      SS_ENUM_TO_STR_CASE(Token::Type, BREAK)
      SS_ENUM_TO_STR_CASE(Token::Type, CLASS)
      SS_ENUM_TO_STR_CASE(Token::Type, CONTINUE)
      SS_ENUM_TO_STR_CASE(Token::Type, ELSE)
      SS_ENUM_TO_STR_CASE(Token::Type, FALSE)
      SS_ENUM_TO_STR_CASE(Token::Type, FOR)
      SS_ENUM_TO_STR_CASE(Token::Type, FN)
      SS_ENUM_TO_STR_CASE(Token::Type, IF)
      SS_ENUM_TO_STR_CASE(Token::Type, LET)
      SS_ENUM_TO_STR_CASE(Token::Type, LOAD)
      SS_ENUM_TO_STR_CASE(Token::Type, LOADR)
      SS_ENUM_TO_STR_CASE(Token::Type, LOOP)
      SS_ENUM_TO_STR_CASE(Token::Type, NIL)
      SS_ENUM_TO_STR_CASE(Token::Type, OR)
      SS_ENUM_TO_STR_CASE(Token::Type, PRINT)
      SS_ENUM_TO_STR_CASE(Token::Type, RETURN)
      SS_ENUM_TO_STR_CASE(Token::Type, TRUE)
      SS_ENUM_TO_STR_CASE(Token::Type, WHILE)
      SS_ENUM_TO_STR_CASE(Token::Type, MATCH)
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

  class BytecodeChunk
  {
   public:
    using Instructions        = std::vector<Instruction>;
    using InstructionIterator = Instructions::iterator;

    using GlobalMap            = std::unordered_map<Value::StringType, Value>;
    using LocalCache           = std::unordered_map<std::size_t, std::string>;
    using IdentifierCache      = std::unordered_map<std::string_view, std::size_t>;
    using IdentifierCacheEntry = IdentifierCache::const_iterator;

    /**
     * @brief Prepares the chunk for a new script, however globals remain intact
     */
    void prepare() noexcept;

    /**
     * @brief Writes the instruction and tags it with the line
     */
    void write(Instruction, std::size_t line) noexcept;

    /**
     * @brief Writes a constant instruction and tags the instruction with the line
     */
    void write_constant(Value v, std::size_t line) noexcept;

    /**
     * @brief Writes a constant to the constant buffer
     *
     * @return The offset of the newly inserted constant
     */
    auto insert_constant(Value v) noexcept -> std::size_t;

    /**
     * @brief Acquires the constant at the given index
     *
     * @return The value at the offset
     */
    auto constant_at(std::size_t offset) const noexcept -> Value;

    /**
     * @brief Pushes a new value onto the stack
     */
    void push_stack(Value v) noexcept;

    /**
     * @brief Pops a value off the stack
     *
     * @return The value popped off the stack
     */
    auto pop_stack() noexcept -> Value;

    /**
     * @brief Pops values off the stack N times
     */
    void pop_stack_n(std::size_t n);

    /**
     * @brief Check if the stack is empty
     *
     * @return True if the stack is empty, false otherwise
     */
    auto stack_empty() const noexcept -> bool;

    /**
     * @brief Access values on the stack by index. Index 0 being the hightest part
     *
     * @return The value accessed by the index. If the index is out of bounds, behavior is undefined
     */
    auto peek_stack(std::size_t index = 0) const noexcept -> Value;

    /**
     * @brief Access values on the stack directly by index. Indexing behaves as normal
     *
     * @return The value accessed by the index. If the index is out of bounds, behavior is undefined
     */
    auto index_stack(std::size_t index) const noexcept -> Value;

    /**
     * @brief Access values on the stack directly by index. Indexing behaves as normal
     *
     * @return A mutable reference to the value accessed by the index. If the index is out of bounds, behavior is undefined
     */
    auto index_stack_mut(std::size_t index) noexcept -> Value&;

    /**
     * @brief Get the number of items on the stack
     *
     * @return The number of items on the stack
     */
    auto stack_size() const noexcept -> std::size_t;

    /**
     * @brief Grabs the line at the given offset
     *
     * @return The line number
     */
    auto line_at(std::size_t offset) const noexcept -> std::size_t;

    auto instruction_count() const noexcept -> std::size_t;

    auto index_code_mut(std::size_t index) -> InstructionIterator;

    auto find_ident(std::string_view name) const noexcept -> IdentifierCacheEntry;
    auto is_entry_found(IdentifierCacheEntry entry) const noexcept -> bool;

    /**
     * @brief Adds the identifier to the cache
     *
     * @return The index in the list of constants
     */
    auto add_ident(std::string_view name) noexcept -> std::size_t;

    void set_global(Value::StringType&& name, Value value) noexcept;

    auto find_global(Value::StringType name) noexcept -> GlobalMap::iterator;

    auto is_global_found(GlobalMap::iterator it) const noexcept -> bool;

    auto begin() noexcept -> InstructionIterator;

    auto end() noexcept -> InstructionIterator;

    /**
     * @brief Prints the stack to the given output stream
     */
    void print_stack(VMConfig& cfg) const noexcept;

    void print_constants(VMConfig& cfg) const noexcept;

   private:
    Instructions code;
    std::vector<Value> constants;
    std::vector<Value> stack;
    std::vector<std::size_t> lines;
    std::size_t last_line            = 0;
    std::size_t instructions_on_line = 0;
    GlobalMap globals;
    IdentifierCache identifier_cache;

    void add_line(std::size_t line) noexcept;
  };

  class Scanner
  {
   public:
    Scanner(std::string&& src) noexcept;
    ~Scanner() = default;

    auto scan() -> std::vector<Token>;

   private:
    std::string&& source;
    std::string::iterator starting_char;
    std::string::iterator current_char;
    std::size_t line;
    std::size_t column;

    template <typename... Args>
    void error(Args&&... args) const
    {
      CompiletimeError::throw_err(this->line, ":", this->column, " -> ", args...);
    }

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

  struct Local
  {
    Token name;
    std::size_t depth;
    bool initialized;
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

    constexpr auto to_string(Precedence p) noexcept -> const char*
    {
      switch (p) {
        SS_ENUM_TO_STR_CASE(Precedence, NONE)
        SS_ENUM_TO_STR_CASE(Precedence, ASSIGNMENT)
        SS_ENUM_TO_STR_CASE(Precedence, OR)
        SS_ENUM_TO_STR_CASE(Precedence, AND)
        SS_ENUM_TO_STR_CASE(Precedence, EQUALITY)
        SS_ENUM_TO_STR_CASE(Precedence, COMPARISON)
        SS_ENUM_TO_STR_CASE(Precedence, TERM)
        SS_ENUM_TO_STR_CASE(Precedence, FACTOR)
        SS_ENUM_TO_STR_CASE(Precedence, UNARY)
        SS_ENUM_TO_STR_CASE(Precedence, CALL)
        SS_ENUM_TO_STR_CASE(Precedence, PRIMARY)
        default: {
          return "UNKNOWN";
        }
      };
    }
    using ParseFn = std::function<void(Parser*, bool)>;

    struct ParseRule
    {
      ParseFn prefix;
      ParseFn infix;
      Precedence precedence;
    };

    struct VarLookup
    {
      enum class Type
      {
        LOCAL,
        GLOBAL,
      };

      Type type;
      std::size_t index;
    };

    enum class FnType
    {
      FUNCTION,
    };

   public:
    Parser(TokenList&& tokens, BytecodeChunk& chunk, std::string current_file) noexcept;
    ~Parser() = default;

    void parse();

   private:
    TokenList tokens;
    TokenIterator iter;
    BytecodeChunk& chunk;
    std::string current_file;
    std::vector<Local> locals;

    /**
     * @brief Current scope depth. 0 is the global namespace, depth > 0 creates local variables
     */
    std::size_t scope_depth;

    /**
     * @brief True if inside some kind of loop, false otherwise
     */
    bool in_loop;

    /**
     * @brief Jump instruction to the beginning of the current loop
     */
    std::size_t continue_jmp;

    /**
     * @brief Depth level at beginning of the loop
     */
    std::size_t loop_depth;

    /**
     * @brief Jump instructions to patch after loop end
     */
    std::vector<std::size_t> breaks;

    /**
     * @brief True if inside some kind of function, false otherwise
     */
    bool in_function;

    /**
     * @brief Number of parameters to deallocate upon returning from the last function
     */
    std::size_t locals_in_function;

    /**
     * @brief Depth level at beginning of the last function
     */
    std::size_t function_depth;

    template <typename... Args>
    void error(TokenIterator tok, Args&&... args) const
    {
      CompiletimeError::throw_err(tok->line, ":", tok->column, " -> ", args...);
    }

    void write_instruction(Instruction i);
    auto previous() const -> TokenIterator;
    void advance() noexcept;
    void consume(Token::Type type, std::string err);
    void emit_instruction(Instruction i);
    void emit_constant(Value v);
    auto emit_jump(Instruction i) -> std::size_t;
    void patch_jump(std::size_t jump_loc);
    /**
     * @brief Prepares for a new scope. Used for functions or control flow
     */
    void wrap_scope(auto f);
    /**
     * @brief Cleans up after a typical code block. Writes a POP_N instruction after to take care of local vars
     */
    void wrap_block(auto f);
    /**
     * @brief Calls a function after preparing for a call instruction sequence.
     *
     * @param f The function or lambda to call
     */
    void wrap_call_frame(auto f);
    /**
     * @brief Calls a function after preparing for a function block.
     *
     * @param f The function or lambda to call
     */
    void wrap_call_block(std::size_t arg_count, auto f);
    /**
     * @brief Calls a function after preparing for a loop sequence. Then after the function restors old state
     *
     * @param cont_jmp The instruction to jump to from a continue
     * @param f The function or lambda to call
     */
    void wrap_loop(std::size_t cont_jmp, auto f);

    auto rule_for(Token::Type t) const noexcept -> const ParseRule&;
    void parse_precedence(Precedence p);
    void make_number(bool can_assign);
    void make_string(bool can_assign);
    void make_variable(bool assign);
    void make_function(std::string name);
    void named_variable(TokenIterator name, bool assign);
    auto parse_variable(std::string err_msg) -> std::size_t;
    auto parse_arg_list() -> std::size_t;
    /**
     * @brief Defines a new variable.
     *
     * @param global The index of the global variable in the chunk's constants. When defining a local variable, this will be 0
     */
    void define_variable(std::size_t global);
    void declare_variable();
    auto identifier_constant(TokenIterator name) -> std::size_t;
    auto check(Token::Type type) -> bool;
    auto advance_if_matches(Token::Type type) -> bool;
    void add_local(TokenIterator token) noexcept;
    auto resolve_local(TokenIterator token) const -> VarLookup;
    auto reduce_locals_to_depth(std::size_t depth) -> std::size_t;

    void expression();
    void grouping_expr(bool);
    void unary_expr(bool);
    void binary_expr(bool);
    void literal_expr(bool);
    void and_expr(bool);
    void or_expr(bool);
    void call_expr(bool);

    void declaration();

    void statement();
    void print_stmt();
    void expression_stmt();
    void let_stmt();
    void block_stmt();
    void fn_block_stmt();
    void if_stmt();
    void loop_stmt();
    void while_stmt();
    void for_stmt();
    void break_stmt();
    void continue_stmt();
    void return_stmt();
    void end_stmt();
    void match_stmt();
    void load_stmt();
    void loadr_stmt();
    void fn_stmt();
  };

  class Compiler
  {
   public:
    Compiler() = default;
    void compile(std::string&& src, BytecodeChunk& chunk, std::string current_file);
  };

}  // namespace ss