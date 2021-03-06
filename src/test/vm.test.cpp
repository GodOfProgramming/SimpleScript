#include "ss/vm.hpp"

#include "helpers.hpp"

#include <gtest/gtest.h>

#define TEST_SCRIPT(src) #src

using ss::NativeFunction;
using ss::Value;
using ss::VM;
using ss::VMConfig;

class TestVM: public testing::Test
{
 public:
  void SetUp() override

  {
    this->ostream = std::make_shared<std::ostringstream>();
    this->vm      = std::make_shared<VM>(VMConfig(&std::cin, this->ostream.get()));
  }

 protected:
  std::shared_ptr<std::ostringstream> ostream;
  std::shared_ptr<VM> vm;
};

TEST_F(TestVM, prints_correctly)
{
  const char* script = {
#include "scripts/print_script.ss"
  };

  this->vm->run_script(script);

  ASSERT_EQ(this->ostream->str(), "true\nhello world\n");
}

TEST_F(TestVM, setting_and_getting_vars)
{
  const char* script = {
#include "scripts/var_script.ss"
  };

  this->vm->set_var("value", Value("test"));
  this->vm->run_script(script);

  EXPECT_EQ(this->ostream->str(), "test\n");
  EXPECT_EQ(this->vm->get_var("value"), Value(true));
}

TEST_F(TestVM, blocks)
{
  const char* script = {
#include "scripts/block_script.ss"
  };

  this->vm->run_script(script);

  EXPECT_EQ(this->ostream->str(), "string\n");
}

TEST_F(TestVM, if_statements)
{
  const char* script = {
#include "scripts/if_script.ss"
  };

  this->vm->run_script(script);

  EXPECT_EQ(this->ostream->str(), "true\nafter\n");
}

TEST_F(TestVM, if_else_statements)
{
  const char* script = {
#include "scripts/if_else_script.ss"
  };

  this->vm->run_script(script);

  EXPECT_EQ(this->ostream->str(), "true\nfalse\ny\nor\n");
}

TEST_F(TestVM, ands_and_ors)
{
  this->vm->run_script("print true or false and true;");
  EXPECT_EQ(this->ostream->str(), "true\n");
}

TEST_F(TestVM, while_stmt)
{
  const char* script = {
#include "scripts/while_script.ss"
  };

  this->vm->run_script(script);

  EXPECT_EQ(this->ostream->str(), "0\n1\n2\n");
}

TEST_F(TestVM, for_stmt)
{
  const char* script = {
#include "scripts/for_script.ss"
  };

  this->vm->run_script(script);

  EXPECT_EQ(this->ostream->str(), "0\n1\n2\n");
}

TEST_F(TestVM, match_stmt)
{
  const char* script = {
#include "scripts/match_script.ss"
  };

  this->vm->run_script(script);

  EXPECT_EQ(this->ostream->str(), "at hello\n");
}

TEST_F(TestVM, breaks_continues)
{
  const char* script = {
#include "scripts/break_continue_script.ss"
  };

  this->vm->run_script(script);

  EXPECT_EQ(this->ostream->str(), "0\n1\n2\n3\n4\n");
}

TEST_F(TestVM, loops)
{
  const char* script = {
#include "scripts/loop_script.ss"
  };

  this->vm->run_script(script);

  EXPECT_EQ(this->ostream->str(), "0\n1\n2\n3\n4\n");
}

TEST_F(TestVM, complex)
{
  const char* script = {
#include "scripts/complex_script.ss"
  };

  this->vm->run_script(script);

  EXPECT_EQ(this->ostream->str(), "1\n2\n3\n4\n5\n");
}

TEST_F(TestVM, fn)
{
  const char* script = {
#include "scripts/fn_script.ss"
  };

  this->vm->run_script(script);

  EXPECT_EQ(this->ostream->str(), "-4\n");
}

TEST_F(TestVM, native)
{
  const char* script = {
#include "scripts/native_script.ss"
  };

  std::string name = "test";
  this->vm->set_var(
   name, Value(std::make_shared<NativeFunction>(name, 0, [](NativeFunction::Args&&) { return Value("test"); })));
  this->vm->run_script(script);

  EXPECT_EQ(this->ostream->str(), "test\n");
}
