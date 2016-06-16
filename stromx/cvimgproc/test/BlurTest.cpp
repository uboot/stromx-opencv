#include "stromx/cvimgproc/test/BlurTest.h"

#include <stromx/runtime/OperatorException.h>
#include <stromx/runtime/ReadAccess.h>
#include "stromx/cvsupport/Image.h"
#include "stromx/cvimgproc/Blur.h"

CPPUNIT_TEST_SUITE_REGISTRATION (stromx::cvimgproc::BlurTest);

namespace stromx
{
    namespace cvimgproc
    {
        void BlurTest::setUp()
        {
            m_operator = new stromx::runtime::OperatorTester(new Blur);
        }
        
        void BlurTest::tearDown()
        {
            delete m_operator;
        }
        
        void BlurTest::testManual0()
        {
            m_operator->setParameter(Blur::PARAMETER_DATA_FLOW, runtime::Enum(Blur::MANUAL));
            m_operator->initialize();
            m_operator->activate();
            
            runtime::DataContainer src(new cvsupport::Image("lenna.jpg"));
            runtime::DataContainer dst(new cvsupport::Image(1000000));
            runtime::UInt32 ksizex(3);
            runtime::UInt32 ksizey(4);
            
            m_operator->setInputData(Blur::INPUT_SRC, src);
            m_operator->setInputData(Blur::INPUT_DST, dst);
            m_operator->setParameter(Blur::PARAMETER_KSIZEX, ksizex);
            m_operator->setParameter(Blur::PARAMETER_KSIZEY, ksizey);
            
            runtime::DataContainer dstResult = m_operator->getOutputData(Blur::OUTPUT_DST);
            
            runtime::ReadAccess dstAccess(dstResult);
            cvsupport::Image::save("BlurTest_testManual0_dst.png", dstAccess.get<runtime::Image>());
        }
        
        void BlurTest::testManual1()
        {
            m_operator->setParameter(Blur::PARAMETER_DATA_FLOW, runtime::Enum(Blur::MANUAL));
            m_operator->initialize();
            m_operator->activate();
            
            runtime::DataContainer src(new cvsupport::Image("lenna.jpg", cvsupport::Image::GRAYSCALE));
            
            m_operator->setInputData(Blur::INPUT_SRC, src);
            m_operator->setInputData(Blur::INPUT_DST, src);
            
            runtime::DataContainer dstResult = m_operator->getOutputData(Blur::OUTPUT_DST);
            
            runtime::ReadAccess dstAccess(dstResult);
            cvsupport::Image::save("BlurTest_testManual1_dst.png", dstAccess.get<runtime::Image>());
        }
        
        void BlurTest::testAllocate0()
        {
            m_operator->setParameter(Blur::PARAMETER_DATA_FLOW, runtime::Enum(Blur::ALLOCATE));
            m_operator->initialize();
            m_operator->activate();
            
            runtime::DataContainer src(new cvsupport::Image("lenna.jpg"));
            
            m_operator->setInputData(Blur::INPUT_SRC, src);
            
            runtime::DataContainer dstResult = m_operator->getOutputData(Blur::OUTPUT_DST);
            
            runtime::ReadAccess dstAccess(dstResult);
            cvsupport::Image::save("BlurTest_testAllocate0_dst.png", dstAccess.get<runtime::Image>());
        }
        
        void BlurTest::testAllocate1()
        {
            m_operator->setParameter(Blur::PARAMETER_DATA_FLOW, runtime::Enum(Blur::ALLOCATE));
            m_operator->initialize();
            m_operator->activate();
            
            runtime::DataContainer src(new cvsupport::Image("lenna.jpg", cvsupport::Image::GRAYSCALE));
            
            m_operator->setInputData(Blur::INPUT_SRC, src);
            
            runtime::DataContainer dstResult = m_operator->getOutputData(Blur::OUTPUT_DST);
            
            runtime::ReadAccess dstAccess(dstResult);
            cvsupport::Image::save("BlurTest_testAllocate1_dst.png", dstAccess.get<runtime::Image>());
        }
        
        void BlurTest::testInPlace0()
        {
            m_operator->setParameter(Blur::PARAMETER_DATA_FLOW, runtime::Enum(Blur::IN_PLACE));
            m_operator->initialize();
            m_operator->activate();
            
            runtime::DataContainer src(new cvsupport::Image("lenna.jpg"));
            
            m_operator->setInputData(Blur::INPUT_SRC, src);
            
            runtime::DataContainer srcResult = m_operator->getOutputData(Blur::OUTPUT_SRC);
            
            runtime::ReadAccess srcAccess(srcResult);
            cvsupport::Image::save("BlurTest_testInPlace0_src.png", srcAccess.get<runtime::Image>());
        }
        
    } // cvimgproc
} // stromx

