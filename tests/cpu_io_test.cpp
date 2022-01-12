#include "CppUTest/TestHarness.h"
#include "CppUTest/UtestMacros.h"
#include "CppUTestExt/MockSupport.h"
#include <cstdio>
#include <cstring>

extern "C"
{
#include <IO.h>
#include <IO_openSourceFile.h>
#include <IO_getDataWord.h>
#include <IO_showDataWord.h>
#include <IO_showAccumulatorOverflowMessage.h>
#include <IO_showDivideByZeroMessage.h>
#include <CPU.h>
}

static int counter;

int getDataWord()
{
    int returnValue = mock().getData("returnValue").getIntValue();

    mock().actualCall("getDataWord");
    
    if (counter++ == 0)
    {
        return mock().returnIntValueOrDefault(returnValue);
    }
    else
    {
        return mock().returnIntValueOrDefault(50);
    }
}

FILE *openSourceFile(FILE *outputFile)
{
     mock().actualCall("openSourceFile");
    
     FILE * resultFilePointer = (FILE *) mock().getData("testSmlFile").getObjectPointer();

     return resultFilePointer;
}

int printf( const char * format, ... )
{
    mock().actualCall("printf");
    return mock().intReturnValue();
}


void IO_showDataWord(int dataWord, FILE *outputFile)
{
    mock().actualCall("IO_showDataWord")
        .withParameter("dataWord", dataWord);
}

void IO_showAccumulatorOverflowMessage(FILE *outputFile)
{
    mock().actualCall("IO_showAccumulatorOverflowMessage");
}

void IO_showDivideByZeroMessage(FILE *outputFile)
{

    mock().actualCall("IO_showDivideByZeroMessage");
}

TEST_GROUP(IO_and_CPU)
{
    FILE *outputFile;
    int memory[100];

    void setup() override
    {
        outputFile = fopen("tests/test_data/test_output.txt", "w");
        counter = 0;
        memset(memory, 0, sizeof(memory));
    }

    void teardown() override
    {
        mock().clear();
    }

};

TEST(IO_and_CPU, IO_getValidDataWord_returnValidPositiveValue)
{
    mock().expectOneCall( "getDataWord");
    mock().setData("returnValue", 50);
    int resultActual = IO_getValidDataWord(outputFile);
    mock().checkExpectations();
    CHECK_EQUAL(50, resultActual);
}

TEST(IO_and_CPU, IO_getValidDataWord_returnValidNegativeValue)
{
    mock().expectOneCall( "getDataWord");
    mock().setData("returnValue", -50);
    int resultActual = IO_getValidDataWord(outputFile);
    mock().checkExpectations();
    CHECK_EQUAL(-50, resultActual);
}

TEST(IO_and_CPU, IO_getValidDataWord_returnValidBoundPositiveValue)
{
    mock().expectOneCall( "getDataWord");
    mock().setData("returnValue", 9999);
    int resultActual = IO_getValidDataWord(outputFile);
    mock().checkExpectations();
    CHECK_EQUAL(9999, resultActual);
}

TEST(IO_and_CPU, IO_getValidDataWord_returnValidBoundNegativeValue)
{
    mock().expectOneCall( "getDataWord");
    mock().setData("returnValue", -9999);
    int resultActual = IO_getValidDataWord(outputFile);
    mock().checkExpectations();
    CHECK_EQUAL(-9999, resultActual);
}

TEST(IO_and_CPU, IO_getValidDataWord_returnNotValidPositiveValue)
{
    mock().expectNCalls(2, "getDataWord");
    mock().setData("returnValue", 10000);
    mock().expectOneCall("printf");
    int resultActual = IO_getValidDataWord(outputFile);
    mock().checkExpectations();
    CHECK_EQUAL(50, resultActual);
}

TEST(IO_and_CPU, IO_getValidDataWord_returnNotValidNegativeValue)
{
    mock().expectNCalls(2, "getDataWord");
    mock().setData("returnValue", -10000);
    mock().expectOneCall("printf");
    int resultActual = IO_getValidDataWord(outputFile);
    mock().checkExpectations();
    CHECK_EQUAL(50, resultActual);
}

TEST(IO_and_CPU, IO_readProgram_failedToOpenFile)
{
    mock().setDataObject("testSmlFile", "FILE", NULL);
    mock().expectOneCall("openSourceFile");
    bool resultActual = IO_readProgram(memory, outputFile);
    mock().checkExpectations();
    CHECK_FALSE(resultActual);
}

TEST(IO_and_CPU, IO_readProgram_lessThanWordsize)
{
    FILE *testSml = fopen("tests/test_data/test_less_than_wordsize.sml","r");
    mock().setDataObject("testSmlFile", "FILE", testSml);
    mock().expectOneCall("openSourceFile");
    mock().expectOneCall("printf");
    bool resultActual = IO_readProgram(memory, outputFile);
    mock().checkExpectations();
    CHECK_FALSE(resultActual);
}

TEST(IO_and_CPU, IO_readProgram_moreThanWordsize)
{
    FILE *testSml = fopen("tests/test_data/test_more_than_wordsize.sml","r");
    mock().setDataObject("testSmlFile", "FILE", testSml);
    mock().expectOneCall("openSourceFile");
    mock().expectOneCall("printf");
    bool resultActual = IO_readProgram(memory, outputFile);
    mock().checkExpectations();
    CHECK_FALSE(resultActual);
}

TEST(IO_and_CPU, IO_readProgram_notNumber)
{
    FILE *testSml = fopen("tests/test_data/test_not_number.sml","r");
    mock().setDataObject("testSmlFile", "FILE", testSml);
    mock().expectOneCall("openSourceFile");
    mock().expectOneCall("printf");
    bool resultActual = IO_readProgram(memory, outputFile);
    mock().checkExpectations();
    CHECK_FALSE(resultActual);
}

TEST(IO_and_CPU, IO_readProgram_validData)
{
    FILE *testSml = fopen("tests/test_data/test_valid.sml","r");
    mock().setDataObject("testSmlFile", "FILE", testSml);
    mock().expectOneCall("openSourceFile");
    bool resultActual = IO_readProgram(memory, outputFile);
    mock().checkExpectations();
    CHECK(resultActual);
    CHECK_EQUAL(1234, memory[0]);
}

TEST(IO_and_CPU, CPU_read_command)
{
    memory[0] = 1002;
    memory[1] = 4300;
    mock().setData("returnValue", 55);
    mock().expectOneCall("printf");
    mock().expectOneCall("getDataWord");
    CPU_executeProgram(memory, outputFile);
    mock().checkExpectations();
    CHECK_EQUAL(55, memory[2]);
}

TEST(IO_and_CPU, CPU_write_command)
{
    memory[0] = 1102;
    memory[1] = 4300;
    memory[2] = 55;
    mock().expectOneCall("IO_showDataWord")
        .withParameter("dataWord", 55);
    CPU_executeProgram(memory, outputFile);
    mock().checkExpectations();
}

TEST(IO_and_CPU, CPU_load_command)
{
   memory[0] = 2002;
   memory[1] = 4300;
   memory[2] = 55;
   CPU_executeProgram(memory, outputFile);
   CHECK_EQUAL(55, CPU_getAccumulator());
}

TEST(IO_and_CPU, CPU_store_command)
{
    memory[0] = 2003;
    memory[1] = 2104;
    memory[2] = 4300;
    memory[3] = 55;
    CPU_executeProgram(memory, outputFile);
    CHECK_EQUAL(55, memory[4]);
}

TEST(IO_and_CPU, CPU_add_command)
{
    memory[0] = 2003;
    memory[1] = 3004;
    memory[2] = 4300;
    memory[3] = 50;
    memory[4] = 5;
    mock().expectNoCall("IO_showAccumulatorOverflowMessage");
    CPU_executeProgram(memory, outputFile);
    mock().checkExpectations();
    CHECK_EQUAL(55, CPU_getAccumulator());
}

TEST(IO_and_CPU, CPU_add_command_overflow)
{
    memory[0] = 2003;
    memory[1] = 3004;
    memory[2] = 4300;
    memory[3] = 9999;
    memory[4] = 5;
    mock().expectOneCall("IO_showAccumulatorOverflowMessage");
    CPU_executeProgram(memory, outputFile);
    mock().checkExpectations();
}

TEST(IO_and_CPU, CPU_substract_command)
{
    memory[0] = 2003;
    memory[1] = 3104;
    memory[2] = 4300;
    memory[3] = 50;
    memory[4] = 5;
    mock().expectNoCall("IO_showAccumulatorOverflowMessage");
    CPU_executeProgram(memory, outputFile);
    mock().checkExpectations();
    CHECK_EQUAL(45, CPU_getAccumulator());
}

TEST(IO_and_CPU, CPU_substract_command_overflow)
{
    memory[0] = 2003;
    memory[1] = 3104;
    memory[2] = 4300;
    memory[3] = -9999;
    memory[4] = 5;
    mock().expectOneCall("IO_showAccumulatorOverflowMessage");
    CPU_executeProgram(memory, outputFile);
    mock().checkExpectations();
}

TEST(IO_and_CPU, CPU_divide_command)
{
    memory[0] = 2003;
    memory[1] = 3204;
    memory[2] = 4300;
    memory[3] = 50;
    memory[4] = 5;
    mock().expectNoCall("IO_showAccumulatorOverflowMessage");
    mock().expectNoCall("IO_showDivideByZeroMessage");
    CPU_executeProgram(memory, outputFile);
    mock().checkExpectations();
    CHECK_EQUAL(10, CPU_getAccumulator());
}

TEST(IO_and_CPU, CPU_divide_command_overflow)
{
    memory[0] = 2003;
    memory[1] = 3204;
    memory[2] = 4300;
    memory[3] = 50;
    memory[4] = 0;
    mock().expectOneCall("IO_showDivideByZeroMessage");
    CPU_executeProgram(memory, outputFile);
    mock().checkExpectations();
}

TEST(IO_and_CPU, CPU_multiply_command)
{
    memory[0] = 2003;
    memory[1] = 3304;
    memory[2] = 4300;
    memory[3] = 50;
    memory[4] = 5;
    mock().expectNoCall("IO_showAccumulatorOverflowMessage");
    mock().expectNoCall("IO_showDivideByZeroMessage");
    CPU_executeProgram(memory, outputFile);
    mock().checkExpectations();
    CHECK_EQUAL(250, CPU_getAccumulator());
}

TEST(IO_and_CPU, CPU_multiply_command_overflow)
{
    memory[0] = 2003;
    memory[1] = 3304;
    memory[2] = 4300;
    memory[3] = 9000;
    memory[4] = 5;
    mock().expectOneCall("IO_showAccumulatorOverflowMessage");
    CPU_executeProgram(memory, outputFile);
    mock().checkExpectations();
}

TEST(IO_and_CPU, CPU_branch_command)
{
    memory[0] = 4055;
    memory[55] = 4300;
    CPU_executeProgram(memory,outputFile);
    CHECK_EQUAL(55, CPU_getInstructionCounter());
}

TEST(IO_and_CPU, CPU_branchneg_command_true)
{
    memory[0] = 2003;
    memory[1] = 4155;
    memory[2] = 4300;
    memory[3] = -25;
    memory[55] = 4300;
    CPU_executeProgram(memory,outputFile);
    CHECK_EQUAL(55, CPU_getInstructionCounter());
}
TEST(IO_and_CPU, CPU_branchneg_command_false)
{
    memory[0] = 2003;
    memory[1] = 4155;
    memory[2] = 4300;
    memory[3] = 25;
    memory[55] = 4300;
    CPU_executeProgram(memory,outputFile);
    CHECK_EQUAL(2, CPU_getInstructionCounter());
}

TEST(IO_and_CPU, CPU_branchzero_command_true)
{
    memory[0] = 2003;
    memory[1] = 4255;
    memory[2] = 4300;
    memory[3] = 0;
    memory[55] = 4300;
    CPU_executeProgram(memory,outputFile);
    CHECK_EQUAL(55, CPU_getInstructionCounter());
}
TEST(IO_and_CPU, CPU_branchzero_command_false)
{
    memory[0] = 2003;
    memory[1] = 4255;
    memory[2] = 4300;
    memory[3] = 25;
    memory[55] = 4300;
    CPU_executeProgram(memory,outputFile);
    CHECK_EQUAL(2, CPU_getInstructionCounter());
}
