#include "stromx/cvimgproc/test/IntegralTest.h"

#include <stromx/runtime/OperatorException.h>
#include <stromx/runtime/ReadAccess.h>
#include "stromx/cvsupport/Image.h"
#include "stromx/cvimgproc/Integral.h"

CPPUNIT_TEST_SUITE_REGISTRATION (stromx::cvimgproc::IntegralTest);

namespace stromx
{
    namespace cvimgproc
    {
        void IntegralTest::setUp()
        {
            m_operator = new stromx::runtime::OperatorTester(new Integral);
        }
        
        void IntegralTest::tearDown()
        {
            delete m_operator;
        }
        
        void IntegralTest::testManual0()
        {
            m_operator->setParameter(Integral::PARAMETER_DATA_FLOW, runtime::Enum(Integral::MANUAL));
            m_operator->initialize();
            m_operator->activate();
            
            runtime::DataContainer src(new cvsupport::Image("lenna.jpg", cvsupport::Image::GRAYSCALE));
            runtime::DataContainer dst(new cvsupport::Image(10000000));
            
            m_operator->setInputData(Integral::INPUT_SRC, src);
            m_operator->setInputData(Integral::INPUT_DST, dst);
            
            runtime::DataContainer dstResult = m_operator->getOutputData(Integral::OUTPUT_DST);
            
            runtime::ReadAccess dstAccess(dstResult);
            cvsupport::Matrix::save("IntegralTest_testManual0_dst.npy", dstAccess.get<runtime::Matrix>());
        }
        
        void IntegralTest::testAllocate0()
        {
            m_operator->setParameter(Integral::PARAMETER_DATA_FLOW, runtime::Enum(Integral::ALLOCATE));
            m_operator->initialize();
            m_operator->activate();
            
            runtime::DataContainer src(new cvsupport::Image("circle.png", cvsupport::Image::GRAYSCALE));
            
            m_operator->setInputData(Integral::INPUT_SRC, src);
            
            runtime::DataContainer dstResult = m_operator->getOutputData(Integral::OUTPUT_DST);
            
            runtime::ReadAccess dstAccess(dstResult);
            cvsupport::Matrix::save("IntegralTest_testAllocate0_dst.npy", dstAccess.get<runtime::Matrix>());
        }
        
    } // cvimgproc
} // stromx

