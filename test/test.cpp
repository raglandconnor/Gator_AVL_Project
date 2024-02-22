#include <catch2/catch_test_macros.hpp>
#include "AVL.h"
#include <iostream>
#include <sstream>

#define private public

using namespace std;

/*
 * Referencing the cout capturing from here
 * https://stackoverflow.com/questions/4191089/how-to-unit-test-function-writing-to-stdout-stdcout
 */

// the syntax for defining a test is below. It is important for the name to be unique, but you can group multiple tests with [tags]. A test can have [multiple][tags] using that syntax.
TEST_CASE("Test invalid commands", "[first]") {

    SECTION("Test invalid commands 1") {
        AVLTree myAVL;
        std::ostringstream oss;
        std::streambuf* p_cout_streambuf = std::cout.rdbuf();
        std::cout.rdbuf(oss.rdbuf());

        myAVL.command("insert Joe 12345678");
        myAVL.command("insert \"joe\" 1234567");
        myAVL.command("insert \"joe\" 123456789");
        myAVL.command("invalidCommand");
        myAVL.command("insert \"Invalid nam3\" 12345678");
        myAVL.command("insert \"ID too big\" 123456789");
        myAVL.command("insert \"ID too small\" 1234567");

        std::string output = oss.str();

        std::cout.rdbuf(p_cout_streambuf); // Restore cout

        // Check if output matches expected result
        REQUIRE(output == "unsuccessful\nunsuccessful\nunsuccessful\nunsuccessful\nunsuccessful\nunsuccessful\nunsuccessful\n");
    }


}

TEST_CASE("Test edge cases", "[second]") {
    SECTION("Test edge cases 1") {
        AVLTree myAVL;

        std::ostringstream oss;
        std::streambuf* p_cout_streambuf = std::cout.rdbuf();
        std::cout.rdbuf(oss.rdbuf());

        myAVL.command("removeInorder 0");
        myAVL.command("removeInorder -5");
        myAVL.command("removeInorder 5");
        myAVL.command("search 78506999");
        myAVL.command("remove 78506999");
        myAVL.command("search \"Connor Ragland\"");

        std::string output = oss.str();

        std::cout.rdbuf(p_cout_streambuf); // Restore cout

        // Check if output matches expected result
        REQUIRE(output == "unsuccessful\nunsuccessful\nunsuccessful\nunsuccessful\nunsuccessful\nunsuccessful\n");
    }
}

TEST_CASE("Test rotations", "[third]") {
    SECTION("Left rotation test") {
        AVLTree myAVL;

        std::ostringstream oss;
        std::streambuf* p_cout_streambuf = std::cout.rdbuf();
        std::cout.rdbuf(oss.rdbuf());

        myAVL.command("insert \"Five\" 50000000");
        myAVL.command("insert \"Six\" 60000000");
        myAVL.command("insert \"Seven\" 70000000");
        myAVL.command("printInorder");
        myAVL.command("printPreorder");
        myAVL.command("printPostorder");

        std::string output = oss.str();

        std::cout.rdbuf(p_cout_streambuf); // Restore cout

        // Check if output matches expected result
        REQUIRE(output == "successful\nsuccessful\nsuccessful\nFive, Six, Seven\nSix, Five, Seven\nFive, Seven, Six\n");
    }

    SECTION("Right rotation") {

    }

    SECTION("Left-Right rotation") {

    }

    SECTION("Right-Left rotation") {

    }
}

//TEST_CASE("Test 2", "[flag]"){
//	// you can also use "sections" to share setup code between tests, for example:
////	int one = 1;
////
////	SECTION("num is 2") {
////		int num = one + 1;
////		REQUIRE(num == 2);
////	};
////
////	SECTION("num is 3") {
////		int num = one + 2;
////		REQUIRE(num == 3);
//	};
//
//	// each section runs the setup code independently to ensure that they don't affect each other
////}
//
//// you must write 5 unique, meaningful tests for credit on the testing portion of this project!
//
//// the provided test from the template is below.
//
//TEST_CASE("Example BST Insert", "[flag]"){
//	/*
//		MyAVLTree tree;   // Create a Tree object
//		tree.insert(3);
//		tree.insert(2);
//		tree.insert(1);
//		std::vector<int> actualOutput = tree.inorder();
//		std::vector<int> expectedOutput = {1, 2, 3};
//		REQUIRE(expectedOutput.size() == actualOutput.size());
//		REQUIRE(actualOutput == expectedOutput);
//	*/
//}
