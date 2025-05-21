#include "pch.h"
#include "CppUnitTest.h"
#include "../laba8po/processing.h"
#include "../laba8po/processing.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace unittestproject
{
	TEST_CLASS(unittestproject)
	{
	public:
        // ���� ��� ���������� ������
        TEST_METHOD(TestAverageCost)
        {
            std::vector<CallRecord> records = {
                {"123", "456", "01.11.2021", "12:00", "00:02:30", "���������", 2.0},
                {"789", "012", "02.11.2021", "13:00", "00:05:00", "���������", 1.5}
            };
            double expected = ((2.0 * 2.5) + (1.5 * 5)) / (2 * 60 + 30 + 5 * 60);
            Assert::AreEqual(expected, calculateAverageCostPerSecond(records), 0.001);
        }

        // ���� �� ���������� ������ (������ ������)
        TEST_METHOD(TestEmptyRecords)
        {
            std::vector<CallRecord> records;
            try {
                calculateAverageCostPerSecond(records);
                Assert::Fail(L"��������� ���������� invalid_argument");
            }
            catch (const std::invalid_argument&) {
                // ���������� �������, ���� ������� ��������
            }
        }

        // ���� �� ������� ����������������� ����������
        TEST_METHOD(TestZeroDuration)
        {
            std::vector<CallRecord> records = {
                {"123", "456", "01.11.2021", "12:00", "00:00:00", "���������", 2.0}
            };
            try {
                calculateAverageCostPerSecond(records);
                Assert::Fail(L"��������� ���������� invalid_argument");
            }
            catch (const std::invalid_argument&) {
                // ���������� �������, ���� ������� ��������
            }
        }
    };
}
