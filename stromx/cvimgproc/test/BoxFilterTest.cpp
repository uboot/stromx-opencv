#include "stromx/cvimgproc/test/BoxFilterTest.h"

#include <stromx/runtime/OperatorException.h>
#include <stromx/runtime/ReadAccess.h>
#include "stromx/cvsupport/Image.h"
#include "stromx/cvimgproc/BoxFilter.h"

CPPUNIT_TEST_SUITE_REGISTRATION (stromx::cvimgproc::BoxFilterTest);

namespace stromx
{
    namespace cvimgproc
    {
        void BoxFilterTest::setUp()
        {
            m_operator = new stromx::runtime::OperatorTester(new BoxFilter);
        }
        
        void BoxFilterTest::tearDown()
        {
            delete m_operator;
        }
        
        void BoxFilterTest::testManual0()
        {
            m_operator->setParameter(BoxFilter::PARAMETER_DATA_FLOW, runtime::Enum(BoxFilter::MANUAL));
            m_operator->initialize();
            m_operator->activate();
            
            runtime::DataContainer src(new cvsupport::Image("lenna.jpg"));
            runtime::DataContainer dst(new cvsupport::Image(1000000));
            runtime::UInt32 ksizex(5);
            runtime::UInt32 ksizey(4);
            
            m_operator->setInputData(BoxFilter::INPUT_SRC, src);
            m_operator->setInputData(BoxFilter::INPUT_DST, dst);
            m_operator->setParameter(BoxFilter::PARAMETER_KSIZEX, ksizex);
            m_operator->setParameter(BoxFilter::PARAMETER_KSIZEY, ksizey);
            
            runtime::DataContainer dstResult = m_operator->getOutputData(BoxFilter::OUTPUT_DST);
            
            runtime::ReadAccess dstAccess(dstResult);
            cvsupport::Image::save("BoxFilterTest_testManual0_dst.png", dstAccess.get<runtime::Image>());
        }
        
        void BoxFilterTest::testManual1()
        {
            m_operator->setParameter(BoxFilter::PARAMETER_DATA_FLOW, runtime::Enum(BoxFilter::MANUAL));
            m_operator->initialize();
            m_operator->activate();
            
            runtime::DataContainer src(new cvsupport::Image("lenna.jpg"));
            
            m_operator->setInputData(BoxFilter::INPUT_SRC, src);
            m_operator->setInputData(BoxFilter::INPUT_DST, src);
            
            runtime::DataContainer dstResult = m_operator->getOutputData(BoxFilter::OUTPUT_DST);
            
            runtime::ReadAccess dstAccess(dstResult);
            cvsupport::Image::save("BoxFilterTest_testManual1_dst.png", dstAccess.get<runtime::Image>());
        }
        
        void BoxFilterTest::testAllocate0()
        {
            m_operator->setParameter(BoxFilter::PARAMETER_DATA_FLOW, runtime::Enum(BoxFilter::ALLOCATE));
            m_operator->initialize();
            m_operator->activate();
            
            runtime::DataContainer src(new cvsupport::Image("lenna.jpg", cvsupport::Image::GRAYSCALE));
            runtime::UInt32 ksizex(4);
            runtime::UInt32 ksizey(5);
            
            m_operator->setInputData(BoxFilter::INPUT_SRC, src);
            m_operator->setParameter(BoxFilter::PARAMETER_KSIZEX, ksizex);
            m_operator->setParameter(BoxFilter::PARAMETER_KSIZEY, ksizey);
            
            runtime::DataContainer dstResult = m_operator->getOutputData(BoxFilter::OUTPUT_DST);
            
            runtime::ReadAccess dstAccess(dstResult);
            cvsupport::Image::save("BoxFilterTest_testAllocate0_dst.png", dstAccess.get<runtime::Image>());
        }
        
        void BoxFilterTest::testInPlace0()
        {
            m_operator->setParameter(BoxFilter::PARAMETER_DATA_FLOW, runtime::Enum(BoxFilter::IN_PLACE));
            m_operator->initialize();
            m_operator->activate();
            
            runtime::DataContainer src(new cvsupport::Image("lenna.jpg"));
            
            m_operator->setInputData(BoxFilter::INPUT_SRC, src);
            
            runtime::DataContainer srcResult = m_operator->getOutputData(BoxFilter::OUTPUT_SRC);
            
            runtime::ReadAccess srcAccess(srcResult);
            cvsupport::Image::save("BoxFilterTest_testInPlace0_src.png", srcAccess.get<runtime::Image>());
        }
        
    } // cvimgproc
} // stromx

