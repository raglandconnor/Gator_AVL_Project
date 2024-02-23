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
    SECTION("Left rotation test 1") {
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

    SECTION("Right rotation 1") {
        AVLTree myAVL;

        std::ostringstream oss;
        std::streambuf* p_cout_streambuf = std::cout.rdbuf();
        std::cout.rdbuf(oss.rdbuf());

        myAVL.command("insert \"Five\" 50000000");
        myAVL.command("insert \"Four\" 40000000");
        myAVL.command("insert \"Three\" 30000000");
        myAVL.command("printInorder");
        myAVL.command("printPreorder");
        myAVL.command("printPostorder");

        std::string output = oss.str();

        std::cout.rdbuf(p_cout_streambuf); // Restore cout

        // Check if output matches expected result
        REQUIRE(output == "successful\nsuccessful\nsuccessful\nThree, Four, Five\nFour, Three, Five\nThree, Five, Four\n");
    }

    SECTION("Left-Right rotation 1") {
        AVLTree myAVL;

        std::ostringstream oss;
        std::streambuf* p_cout_streambuf = std::cout.rdbuf();
        std::cout.rdbuf(oss.rdbuf());

        myAVL.command("insert \"Five\" 50000000");
        myAVL.command("insert \"Three\" 30000000");
        myAVL.command("insert \"Four\" 40000000");
        myAVL.command("printInorder");
        myAVL.command("printPreorder");
        myAVL.command("printPostorder");

        std::string output = oss.str();

        std::cout.rdbuf(p_cout_streambuf); // Restore cout

        // Check if output matches expected result
        REQUIRE(output == "successful\nsuccessful\nsuccessful\nThree, Four, Five\nFour, Three, Five\nThree, Five, Four\n");
    }

    SECTION("Right-Left rotation 1") {
        AVLTree myAVL;

        std::ostringstream oss;
        std::streambuf* p_cout_streambuf = std::cout.rdbuf();
        std::cout.rdbuf(oss.rdbuf());

        myAVL.command("insert \"Five\" 50000000");
        myAVL.command("insert \"Seven\" 70000000");
        myAVL.command("insert \"Six\" 60000000");
        myAVL.command("printInorder");
        myAVL.command("printPreorder");
        myAVL.command("printPostorder");

        std::string output = oss.str();

        std::cout.rdbuf(p_cout_streambuf); // Restore cout

        // Check if output matches expected result
        REQUIRE(output == "successful\nsuccessful\nsuccessful\nFive, Six, Seven\nSix, Five, Seven\nFive, Seven, Six\n");
    }

    SECTION("Right rotation 2: rotation with parents") {
        AVLTree myAVL;

        std::ostringstream oss;
        std::streambuf* p_cout_streambuf = std::cout.rdbuf();
        std::cout.rdbuf(oss.rdbuf());

        myAVL.command("insert \"Five\" 50000000");
        myAVL.command("insert \"Four\" 40000000");
        myAVL.command("insert \"Six\" 60000000");
        myAVL.command("insert \"Three\" 30000000");
        myAVL.command("insert \"One\" 10000000");
        myAVL.command("printInorder");
        myAVL.command("printPreorder");
        myAVL.command("printPostorder");

        std::string output = oss.str();

        std::cout.rdbuf(p_cout_streambuf); // Restore cout

        // Check if output matches expected result
        REQUIRE(output == "successful\nsuccessful\nsuccessful\nsuccessful\nsuccessful\nOne, Three, Four, Five, Six\nFive, Three, One, Four, Six\nOne, Four, Three, Six, Five\n");
    }
}

TEST_CASE("Test deletion cases", "[fourth]") {
    SECTION("No children deletion case") {
        AVLTree myAVL;

        std::ostringstream oss;
        std::streambuf* p_cout_streambuf = std::cout.rdbuf();
        std::cout.rdbuf(oss.rdbuf());

        myAVL.command("insert \"Five\" 50000000");
        myAVL.command("insert \"Six\" 60000000");
        myAVL.command("remove 60000000");
        myAVL.command("printInorder");
        myAVL.command("printPreorder");
        myAVL.command("printPostorder");
        myAVL.command("remove 50000000");
        myAVL.command("printInorder");
        myAVL.command("printPreorder");
        myAVL.command("printPostorder");

        std::string output = oss.str();

        std::cout.rdbuf(p_cout_streambuf); // Restore cout

        // Check if output matches expected result
        REQUIRE(output == "successful\nsuccessful\nsuccessful\nFive\nFive\nFive\nsuccessful\n\n\n\n");
    }

    SECTION("One child deletion case") {
        AVLTree myAVL;

        std::ostringstream oss;
        std::streambuf* p_cout_streambuf = std::cout.rdbuf();
        std::cout.rdbuf(oss.rdbuf());

        myAVL.command("insert \"Five\" 50000000");
        myAVL.command("insert \"Four\" 40000000");
        myAVL.command("insert \"Six\" 60000000");
        myAVL.command("insert \"Seven\" 70000000");
        myAVL.command("remove 60000000");
        myAVL.command("printInorder");
        myAVL.command("printPreorder");
        myAVL.command("printPostorder");
        myAVL.command("insert \"Eight\" 80000000");
        myAVL.command("remove 70000000");
        myAVL.command("printInorder");
        myAVL.command("printPreorder");
        myAVL.command("printPostorder");

        std::string output = oss.str();

        std::cout.rdbuf(p_cout_streambuf); // Restore cout

        // Check if output matches expected result
        REQUIRE(output == "successful\nsuccessful\nsuccessful\nsuccessful\nsuccessful\nFour, Five, Seven\nFive, Four, Seven\nFour, Seven, Five\nsuccessful\nsuccessful\nFour, Five, Eight\nFive, Four, Eight\nFour, Eight, Five\n");
    }

    SECTION("Two children deletion case at the root") {
        AVLTree myAVL;

        std::ostringstream oss;
        std::streambuf* p_cout_streambuf = std::cout.rdbuf();
        std::cout.rdbuf(oss.rdbuf());

        myAVL.command("insert \"Five\" 50000000");
        myAVL.command("insert \"Four\" 40000000");
        myAVL.command("insert \"Six\" 60000000");
        myAVL.command("remove 50000000");
        myAVL.command("printInorder");
        myAVL.command("printPreorder");
        myAVL.command("printPostorder");

        std::string output = oss.str();

        std::cout.rdbuf(p_cout_streambuf); // Restore cout

        // Check if output matches expected result
        REQUIRE(output == "successful\nsuccessful\nsuccessful\nsuccessful\nFour, Six\nSix, Four\nFour, Six\n");
    }

    SECTION("Two children deletion case (not root)") {
        AVLTree myAVL;

        std::ostringstream oss;
        std::streambuf* p_cout_streambuf = std::cout.rdbuf();
        std::cout.rdbuf(oss.rdbuf());

        myAVL.command("insert \"Five\" 50000000");
        myAVL.command("insert \"Eight\" 80000000");
        myAVL.command("insert \"Two\" 20000000");
        myAVL.command("insert \"Nine\" 90000000");
        myAVL.command("insert \"Four\" 40000000");
        myAVL.command("insert \"One\" 10000000");
        myAVL.command("insert \"Three\" 30000000");
        myAVL.command("printPostorder");
        myAVL.command("remove 20000000");
        myAVL.command("printPostorder");

        std::string output = oss.str();

        std::cout.rdbuf(p_cout_streambuf); // Restore cout

        // Check if output matches expected result
        REQUIRE(output == "successful\nsuccessful\nsuccessful\nsuccessful\nsuccessful\nsuccessful\nsuccessful\nOne, Three, Four, Two, Nine, Eight, Five\nsuccessful\nOne, Four, Three, Nine, Eight, Five\n");
    }

    SECTION("Two children deletion case three+ children and a child on the successor") {
        AVLTree myAVL;

        std::ostringstream oss;
        std::streambuf* p_cout_streambuf = std::cout.rdbuf();
        std::cout.rdbuf(oss.rdbuf());

        myAVL.command("insert \"Five\" 50000000");
        myAVL.command("insert \"Eight\" 80000000");
        myAVL.command("insert \"Two\" 20000000");
        myAVL.command("insert \"Nine\" 90000000");
        myAVL.command("insert \"Four\" 40000000");
        myAVL.command("insert \"One\" 10000000");
        myAVL.command("insert \"Three\" 30000000");
        myAVL.command("insert \"Six\" 60000000");
        myAVL.command("insert \"Seven\" 70000000");
        myAVL.command("printPostorder");
        myAVL.command("remove 50000000");
        myAVL.command("printPostorder");

        std::string output = oss.str();

        std::cout.rdbuf(p_cout_streambuf); // Restore cout

        // Check if output matches expected result
        REQUIRE(output == "successful\nsuccessful\nsuccessful\nsuccessful\nsuccessful\nsuccessful\nsuccessful\nsuccessful\nsuccessful\nOne, Three, Four, Two, Seven, Six, Nine, Eight, Five\nsuccessful\nOne, Three, Four, Two, Seven, Nine, Eight, Six\n");
    }
}

TEST_CASE("Height updating", "[extra]") {
    AVLTree myAVL;

    std::ostringstream oss;
    std::streambuf* p_cout_streambuf = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());

    myAVL.command("insert \"Five\" 50000000");
    myAVL.command("insert \"Eight\" 80000000");
    myAVL.command("insert \"Two\" 20000000");
    myAVL.command("insert \"Nine\" 90000000");
    myAVL.command("insert \"Four\" 40000000");
    myAVL.command("insert \"One\" 10000000");
    myAVL.command("insert \"Three\" 30000000");
    myAVL.command("insert \"Six\" 60000000");
    myAVL.command("insert \"Seven\" 70000000");
    myAVL.command("printLevelCount");
    myAVL.command("printPostorder");
    myAVL.command("remove 30000000");
    myAVL.command("remove 70000000");
    myAVL.command("printPostorder");
    myAVL.command("printLevelCount");

    std::string output = oss.str();

    std::cout.rdbuf(p_cout_streambuf); // Restore cout

    // Check if output matches expected result
    REQUIRE(output == "successful\nsuccessful\nsuccessful\nsuccessful\nsuccessful\nsuccessful\nsuccessful\nsuccessful\nsuccessful\n4\nOne, Three, Four, Two, Seven, Six, Nine, Eight, Five\nsuccessful\nsuccessful\nOne, Four, Two, Six, Nine, Eight, Five\n3\n");
}
