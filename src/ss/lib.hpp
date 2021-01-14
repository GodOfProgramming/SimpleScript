#pragma once

#include "cfg.hpp"
#include "code.hpp"
#include "datatypes.hpp"
#include <cinttypes>

namespace ss
{
  auto repl(VMConfig cfg = VMConfig::basic) -> int;
  class VM
  {
   public:
    VM(VMConfig cfg = VMConfig::basic);
    ~VM() = default;

    void run_script(std::string src);

    void test();

   private:
    using InstructionPointer = std::vector<Instruction>::iterator;

    VMConfig           config;
    Chunk*             chunk;
    InstructionPointer ip;

    void interpret(Chunk& chunk);
    void run();

    void disassemble_chunk(std::string name, Chunk& chunk) noexcept;
    void disassemble_instruction(Chunk& chunk, Instruction i, std::size_t offset) noexcept;

    void print_stack() noexcept;
  };
}  // namespace ss