#include "CppUTest/TestHarness.h"
#include "CppUTest/UtestMacros.h"
#include <cstring>

extern "C"
{
#include <RAM.h>
}
 
TEST_GROUP(RAM)
{
    int memory[MEMORY_SIZE]; 

    void setup() override
    {
        memset(memory, 0, sizeof(memory));
    }

    void teardown() override
    {
    }

};

TEST(RAM, readDefault)
{
    CHECK_EQUAL(0, RAM_read(memory, 0));   
    CHECK_EQUAL(0, RAM_read(memory, 50));   
    CHECK_EQUAL(0, RAM_read(memory, 99));   
}

TEST(RAM, readValue)
{
    memory[0] = 10;
    memory[50] = -4020;
    memory[99] = 9999;

    CHECK_EQUAL(10, RAM_read(memory, 0));   
    CHECK_EQUAL(-4020, RAM_read(memory, 50));   
    CHECK_EQUAL(9999, RAM_read(memory, 99));   

}

TEST(RAM, writeValue)
{
    CHECK_TEXT(RAM_write(memory, 0, 9999), "Should return true");
    CHECK_TEXT(RAM_write(memory, 50, 10), "Should return true");
    CHECK_TEXT(RAM_write(memory, 99, -4020), "Should return true");
    
    CHECK_EQUAL(9999, memory[0]);
    CHECK_EQUAL(10, memory[50]);
    CHECK_EQUAL(-4020, memory[99]);
}

TEST(RAM, writeAddressBoundaries)
{
    CHECK_FALSE_TEXT(RAM_write(memory, -1, 10), "Should return false");
    CHECK_FALSE_TEXT(RAM_write(memory, 100, 10), "Should return false");
}
