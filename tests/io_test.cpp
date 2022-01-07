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

TEST_GROUP(IO)
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

TEST(IO, IO_getValidDataWord_returnValidPositiveValue)
{
    mock().expectOneCall( "getDataWord");
    mock().setData("returnValue", 50);
    int resultActual = IO_getValidDataWord(outputFile);
    mock().checkExpectations();
    CHECK_EQUAL(50, resultActual);
}

TEST(IO, IO_getValidDataWord_returnValidNegativeValue)
{
    mock().expectOneCall( "getDataWord");
    mock().setData("returnValue", -50);
    int resultActual = IO_getValidDataWord(outputFile);
    mock().checkExpectations();
    CHECK_EQUAL(-50, resultActual);
}

TEST(IO, IO_getValidDataWord_returnValidBoundPositiveValue)
{
    mock().expectOneCall( "getDataWord");
    mock().setData("returnValue", 9999);
    int resultActual = IO_getValidDataWord(outputFile);
    mock().checkExpectations();
    CHECK_EQUAL(9999, resultActual);
}

TEST(IO, IO_getValidDataWord_returnValidBoundNegativeValue)
{
    mock().expectOneCall( "getDataWord");
    mock().setData("returnValue", -9999);
    int resultActual = IO_getValidDataWord(outputFile);
    mock().checkExpectations();
    CHECK_EQUAL(-9999, resultActual);
}

TEST(IO, IO_getValidDataWord_returnNotValidPositiveValue)
{
    mock().expectNCalls(2, "getDataWord");
    mock().setData("returnValue", 10000);
    mock().expectOneCall("printf");
    int resultActual = IO_getValidDataWord(outputFile);
    mock().checkExpectations();
    CHECK_EQUAL(50, resultActual);
}

TEST(IO, IO_getValidDataWord_returnNotValidNegativeValue)
{
    mock().expectNCalls(2, "getDataWord");
    mock().setData("returnValue", -10000);
    mock().expectOneCall("printf");
    int resultActual = IO_getValidDataWord(outputFile);
    mock().checkExpectations();
    CHECK_EQUAL(50, resultActual);
}

TEST(IO, IO_readProgram_failedToOpenFile)
{
    mock().setDataObject("testSmlFile", "FILE", NULL);
    mock().expectOneCall("openSourceFile");
    bool resultActual = IO_readProgram(memory, outputFile);
    mock().checkExpectations();
    CHECK_FALSE(resultActual);
}

TEST(IO, IO_readProgram_lessThanWordsize)
{
    FILE *testSml = fopen("tests/test_data/test_less_than_wordsize.sml","r");
    mock().setDataObject("testSmlFile", "FILE", testSml);
    mock().expectOneCall("openSourceFile");
    mock().expectOneCall("printf");
    bool resultActual = IO_readProgram(memory, outputFile);
    mock().checkExpectations();
    CHECK_FALSE(resultActual);
}

TEST(IO, IO_readProgram_moreThanWordsize)
{
    FILE *testSml = fopen("tests/test_data/test_more_than_wordsize.sml","r");
    mock().setDataObject("testSmlFile", "FILE", testSml);
    mock().expectOneCall("openSourceFile");
    mock().expectOneCall("printf");
    bool resultActual = IO_readProgram(memory, outputFile);
    mock().checkExpectations();
    CHECK_FALSE(resultActual);
}

TEST(IO, IO_readProgram_notNumber)
{
    FILE *testSml = fopen("tests/test_data/test_not_number.sml","r");
    mock().setDataObject("testSmlFile", "FILE", testSml);
    mock().expectOneCall("openSourceFile");
    mock().expectOneCall("printf");
    bool resultActual = IO_readProgram(memory, outputFile);
    mock().checkExpectations();
    CHECK_FALSE(resultActual);
}

TEST(IO, IO_readProgram_validData)
{
    FILE *testSml = fopen("tests/test_data/test_valid.sml","r");
    mock().setDataObject("testSmlFile", "FILE", testSml);
    mock().expectOneCall("openSourceFile");
    bool resultActual = IO_readProgram(memory, outputFile);
    mock().checkExpectations();
    CHECK(resultActual);
    CHECK_EQUAL(1234, memory[0]);
}
