#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab_11_2/Main.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		TEST_METHOD(TestCountPhysicsGrades)
		{
			const int N = 1;
			Student students[N];
			students[0].physics_grade = 4;
			students[0].math_grade = 5;
			students[0].additional_grade.programming = 3;

			Assert::AreEqual(1, CountPhysicsGrades(students, N, 4));
		}
	};
}
