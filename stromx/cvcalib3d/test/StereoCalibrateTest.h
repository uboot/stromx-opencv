#ifndef STROMX_CVCALIB3D_STEREOCALIBRATETEST_H
#define STROMX_CVCALIB3D_STEREOCALIBRATETEST_H

#include "stromx/cvcalib3d/Config.h"

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/TestFixture.h>

#include "stromx/runtime/OperatorTester.h"

namespace stromx
{
    namespace cvcalib3d
    {
        class StereoCalibrateTest : public CPPUNIT_NS::TestFixture
        {
            CPPUNIT_TEST_SUITE(StereoCalibrateTest);
            CPPUNIT_TEST(testExtrinsics0);
            CPPUNIT_TEST(testIntrinsics0);
            CPPUNIT_TEST_SUITE_END();
            
        public:
            StereoCalibrateTest() : m_operator(0) {}
            void setUp();
            void tearDown();
            
        protected:
            void testExtrinsics0();
            void testIntrinsics0();
            
        private:
            runtime::OperatorTester* m_operator;
        };
    } // cvcalib3d
} // stromx

#endif // STROMX_CVCALIB3D_STEREOCALIBRATETEST_H
