#include "pch.h"
#include "CppUnitTest.h"
#include"../Flow.h"
#include <fstream>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestFlowPushRelabel
{
	TEST_CLASS(UnitTestFlowPushRelabel)
	{
	public:

		TEST_METHOD(TestMethod_Ñorrect_output_for_6_vertexes)
		{
			ifstream input("C:\\Users\\ROG\\source\\repos\\Flow_Push_Relabel\\UnitTestFlow_Push_Relabel\\Input1.txt");
			Flow flow(input);
			Assert::AreEqual(flow.max_flow(), 5);
		}
		TEST_METHOD(TestMethod_Exception_entering_the_first_character) {
			try {
				ifstream input("C:\\Users\\ROG\\source\\repos\\Flow_Push_Relabel\\UnitTestFlow_Push_Relabel\\Input2.txt");
				Flow flow(input);
			}
			catch (exception & ex) {
				Assert::AreEqual(ex.what(),"Error entering the first character in the string or missing a space after it. Check the correctness of the input in the file and correct these errors in the line under the number: 2");
			}
		}
		TEST_METHOD(TestMethod_Exception_entering_the_second_character) {
			try {
				ifstream input("C:\\Users\\ROG\\source\\repos\\Flow_Push_Relabel\\UnitTestFlow_Push_Relabel\\Input3.txt");
				Flow flow(input);
			}
			catch (exception & ex) {
				Assert::AreEqual(ex.what(), "Error entering the second character in the string or missing a space after it. Check the correctness of the input in the file and correct these errors in the line under the number: 2");
			}
		}
		TEST_METHOD(TestMethod_Exception_entering_the_third_number_flow) {
			try {
				ifstream input("C:\\Users\\ROG\\source\\repos\\Flow_Push_Relabel\\UnitTestFlow_Push_Relabel\\Input4.txt");
				Flow flow(input);
			}
			catch (exception & ex) {
				Assert::AreEqual(ex.what(), "Error entering the third character (bandwidth) in the string or the presence of a space after it.Please note that the bandwidth cannot be negative. Check that you entered the file correctly and correct these errors in the line number: 2");
			}
		}
		TEST_METHOD(TestMethod_Exception_empty_string) {
			try {
				ifstream input("C:\\Users\\ROG\\source\\repos\\Flow_Push_Relabel\\UnitTestFlow_Push_Relabel\\Input5.txt");
				Flow flow(input);
			}
			catch (exception & ex) {
				Assert::AreEqual(ex.what(), "A data-entry error. Check the correctness of the input in the file and correct these errors in the line under the number: 2");
			}
		}
		TEST_METHOD(TestMethod_Ñorrect_output_for_6_vertexes_and_edge_from_source_to_sink)
		{
			ifstream input("C:\\Users\\ROG\\source\\repos\\Flow_Push_Relabel\\UnitTestFlow_Push_Relabel\\Input6.txt");
			Flow flow(input);
			Assert::AreEqual(flow.max_flow(), 25);
		}
		TEST_METHOD(TestMethod_Ñorrect_output_for_2_vertexes_edges_from_source_to_sink)
		{
			ifstream input("C:\\Users\\ROG\\source\\repos\\Flow_Push_Relabel\\UnitTestFlow_Push_Relabel\\Input7.txt");
			Flow flow(input);
			Assert::AreEqual(flow.max_flow(), 20);
		}
		TEST_METHOD(TestMethod_Exception_there_is_a_path_from_the_vertex_to_itself) {
			try {
				ifstream input("C:\\Users\\ROG\\source\\repos\\Flow_Push_Relabel\\UnitTestFlow_Push_Relabel\\Input8.txt");
				Flow flow(input);
			}
			catch (exception & ex) {
				Assert::AreEqual(ex.what(), "The path from the vertex to itself is impossible in the string under the number: 2");
			}
		}
		TEST_METHOD(TestMethod_Ñorrect_output_for_20_vertexes)
		{
			ifstream input("C:\\Users\\ROG\\source\\repos\\Flow_Push_Relabel\\UnitTestFlow_Push_Relabel\\Input9.txt");
			Flow flow(input);
			Assert::AreEqual(flow.max_flow(), 19);
		}

	};
}
