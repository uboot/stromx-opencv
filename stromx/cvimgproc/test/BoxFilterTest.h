#ifndef STROMX_CVIMGPROC_BOXFILTERTEST_H
#define STROMX_CVIMGPROC_BOXFILTERTEST_H

#include "stromx/cvimgproc/Config.h"

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>

#include "stromx/runtime/OperatorTester.h"

namespace stromx
{
    namespace cvimgproc
    {
        class BoxFilterTest : public CPPUNIT_NS::TestFixture
        {
            CPPUNIT_TEST_SUITE(BoxFilterTest);
            CPPUNIT_TEST(testManual0);
            CPPUNIT_TEST(testManual1);
            CPPUNIT_TEST(testAllocate0);
            CPPUNIT_TEST(testInPlace0);
            CPPUNIT_TEST_SUITE_END();
            
        public:
            BoxFilterTest() : m_operator(0) {}
            void setUp();
            void tearDown();
            
        protected:
            void testManual0();
            void testManual1();
            void testAllocate0();
            void testInPlace0();
            
        private:
            runtime::OperatorTester* m_operator;
        };
    } // cvimgproc
} // stromx

#endif // STROMX_CVIMGPROC_BOXFILTERTEST_H
