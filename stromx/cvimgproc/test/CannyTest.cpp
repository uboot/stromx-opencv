#include "stromx/cvimgproc/test/CannyTest.h"

#include <stromx/runtime/OperatorException.h>
#include <stromx/runtime/ReadAccess.h>
#include "stromx/cvsupport/Image.h"
#include "stromx/cvimgproc/Canny.h"

CPPUNIT_TEST_SUITE_REGISTRATION (stromx::cvimgproc::CannyTest);

namespace stromx
{
    namespace cvimgproc
    {
        void CannyTest::setUp()
        {
            m_operator = new stromx::runtime::OperatorTester(new Canny);
        }
        
        void CannyTest::tearDown()
        {
            delete m_operator;
        }
        
        void CannyTest::testManual0()
        {
            m_operator->setParameter(Canny::PARAMETER_DATA_FLOW, runtime::Enum(Canny::MANUAL));
            m_operator->initialize();
            m_operator->activate();
            
            runtime::DataContainer src(new cvsupport::Image("lenna.jpg", cvsupport::Image::GRAYSCALE));
            runtime::DataContainer dst(new cvsupport::Image(1000000));
            
            m_operator->setInputData(Canny::INPUT_SRC, src);
            m_operator->setInputData(Canny::INPUT_DST, dst);
            
            runtime::DataContainer dstResult = m_operator->getOutputData(Canny::OUTPUT_DST);
            
            runtime::ReadAccess dstAccess(dstResult);
            cvsupport::Image::save("CannyTest_testManual0_dst.png", dstAccess.get<runtime::Image>());
        }
        
        void CannyTest::testManual1()
        {
            m_operator->setParameter(Canny::PARAMETER_DATA_FLOW, runtime::Enum(Canny::MANUAL));
            m_operator->initialize();
            m_operator->activate();
            
            runtime::DataContainer src(new cvsupport::Image("lenna.jpg", cvsupport::Image::GRAYSCALE));
            runtime::Float64 threshold1(64);
            runtime::Float64 threshold2(128);
            
            m_operator->setInputData(Canny::INPUT_SRC, src);
            m_operator->setInputData(Canny::INPUT_DST, src);
            m_operator->setParameter(Canny::PARAMETER_THRESHOLD_1, threshold1);
            m_operator->setParameter(Canny::PARAMETER_THRESHOLD_2, threshold2);
            
            runtime::DataContainer dstResult = m_operator->getOutputData(Canny::OUTPUT_DST);
            
            runtime::ReadAccess dstAccess(dstResult);
            cvsupport::Image::save("CannyTest_testManual1_dst.png", dstAccess.get<runtime::Image>());
        }
        
        void CannyTest::testAllocate0()
        {
            m_operator->setParameter(Canny::PARAMETER_DATA_FLOW, runtime::Enum(Canny::ALLOCATE));
            m_operator->initialize();
            m_operator->activate();
            
            runtime::DataContainer src(new cvsupport::Image("lenna.jpg", cvsupport::Image::GRAYSCALE));
            
            m_operator->setInputData(Canny::INPUT_SRC, src);
            
            runtime::DataContainer dstResult = m_operator->getOutputData(Canny::OUTPUT_DST);
            
            runtime::ReadAccess dstAccess(dstResult);
            cvsupport::Image::save("CannyTest_testAllocate0_dst.png", dstAccess.get<runtime::Image>());
        }
        
        void CannyTest::testInPlace0()
        {
            m_operator->setParameter(Canny::PARAMETER_DATA_FLOW, runtime::Enum(Canny::IN_PLACE));
            m_operator->initialize();
            m_operator->activate();
            
            runtime::DataContainer src(new cvsupport::Image("lenna.jpg", cvsupport::Image::GRAYSCALE));
            
            m_operator->setInputData(Canny::INPUT_SRC, src);
            
            runtime::DataContainer srcResult = m_operator->getOutputData(Canny::OUTPUT_SRC);
            
            runtime::ReadAccess srcAccess(srcResult);
            cvsupport::Image::save("CannyTest_testInPlace0_src.png", srcAccess.get<runtime::Image>());
        }
        
    } // cvimgproc
} // stromx

