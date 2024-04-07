#include "pch.h"
#include "CppUnitTest.h"
#include "../Project1/Source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(FileManipulationTest) {
public:

    TEST_METHOD(CalculateAndWriteTest) {
        char filename[] = "testfile.txt";
        char ofilename[] = "outputfile.txt";

        
        std::ofstream file(filename);
        file << "1 2 3\n";
        file << "4 5 6\n";
        file.close();

        CalculateAndWrite(filename, ofilename);

        std::remove(filename);
        std::remove(ofilename);
    }
    };
}