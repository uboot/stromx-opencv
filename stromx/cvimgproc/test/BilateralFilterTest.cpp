#include "stromx/cvimgproc/test/BilateralFilterTest.h"

#include <stromx/runtime/OperatorException.h>
#include <stromx/runtime/ReadAccess.h>
#include "stromx/cvsupport/Image.h"
#include "stromx/cvimgproc/BilateralFilter.h"

CPPUNIT_TEST_SUITE_REGISTRATION (stromx::cvimgproc::BilateralFilterTest);

namespace stromx
{
    namespace cvimgproc
    {
        void BilateralFilterTest::setUp()
        {
            m_operator = new stromx::runtime::OperatorTester(new BilateralFilter);
        }
        
        void BilateralFilterTest::tearDown()
        {
            delete m_operator;
        }
        
        void BilateralFilterTest::testManual0()
        {
            m_operator->setParameter(BilateralFilter::PARAMETER_DATA_FLOW, runtime::Enum(BilateralFilter::MANUAL));
            m_operator->initialize();
            m_operator->activate();
            
            runtime::DataContainer src(new cvsupport::Image("lenna.jpg"));
            runtime::DataContainer dst(new cvsupport::Image(1000000));
            runtime::UInt32 d(9);
            runtime::Float64 sigmaColor(100);
            runtime::Float64 sigmaSpace(75);
            
            m_operator->setInputData(BilateralFilter::INPUT_SRC, src);
            m_operator->setInputData(BilateralFilter::INPUT_DST, dst);
            m_operator->setParameter(BilateralFilter::PARAMETER_D, d);
            m_operator->setParameter(BilateralFilter::PARAMETER_SIGMA_COLOR, sigmaColor);
            m_operator->setParameter(BilateralFilter::PARAMETER_SIGMA_SPACE, sigmaSpace);
            
            runtime::DataContainer dstResult = m_operator->getOutputData(BilateralFilter::OUTPUT_DST);
            
            runtime::ReadAccess dstAccess(dstResult);
            cvsupport::Image::save("BilateralFilterTest_testManual0_dst.png", dstAccess.get<runtime::Image>());
        }
        
        void BilateralFilterTest::testAllocate0()
        {
            m_operator->setParameter(BilateralFilter::PARAMETER_DATA_FLOW, runtime::Enum(BilateralFilter::ALLOCATE));
            m_operator->initialize();
            m_operator->activate();
            
            runtime::DataContainer src(new cvsupport::Image("lenna.jpg"));
            
            m_operator->setInputData(BilateralFilter::INPUT_SRC, src);
            
            runtime::DataContainer dstResult = m_operator->getOutputData(BilateralFilter::OUTPUT_DST);
            
            runtime::ReadAccess dstAccess(dstResult);
            cvsupport::Image::save("BilateralFilterTest_testAllocate0_dst.png", dstAccess.get<runtime::Image>());
        }
        
        void BilateralFilterTest::testAllocate1()
        {
            m_operator->setParameter(BilateralFilter::PARAMETER_DATA_FLOW, runtime::Enum(BilateralFilter::ALLOCATE));
            m_operator->initialize();
            m_operator->activate();
            
            runtime::DataContainer src(new cvsupport::Image("lenna.jpg", cvsupport::Image::GRAYSCALE));
            runtime::UInt32 d(9);
            runtime::Float64 sigmaColor(100);
            runtime::Float64 sigmaSpace(75);
            
            m_operator->setInputData(BilateralFilter::INPUT_SRC, src);
            m_operator->setParameter(BilateralFilter::PARAMETER_D, d);
            m_operator->setParameter(BilateralFilter::PARAMETER_SIGMA_COLOR, sigmaColor);
            m_operator->setParameter(BilateralFilter::PARAMETER_SIGMA_SPACE, sigmaSpace);
            
            runtime::DataContainer dstResult = m_operator->getOutputData(BilateralFilter::OUTPUT_DST);
            
            runtime::ReadAccess dstAccess(dstResult);
            cvsupport::Image::save("BilateralFilterTest_testAllocate1_dst.png", dstAccess.get<runtime::Image>());
        }
        
    } // cvimgproc
} // stromx

