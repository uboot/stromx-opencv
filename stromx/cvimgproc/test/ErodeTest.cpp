#include "stromx/cvimgproc/test/ErodeTest.h"

#include <stromx/runtime/OperatorException.h>
#include <stromx/runtime/ReadAccess.h>
#include "stromx/cvsupport/Image.h"
#include "stromx/cvimgproc/Erode.h"

CPPUNIT_TEST_SUITE_REGISTRATION (stromx::cvimgproc::ErodeTest);

namespace stromx
{
    namespace cvimgproc
    {
        void ErodeTest::setUp()
        {
            m_operator = new stromx::runtime::OperatorTester(new Erode);
        }
        
        void ErodeTest::tearDown()
        {
            delete m_operator;
        }
        
        void ErodeTest::testManual0()
        {
            m_operator->setParameter(Erode::PARAMETER_DATA_FLOW, runtime::Enum(Erode::MANUAL));
            m_operator->initialize();
            m_operator->activate();
            
            runtime::DataContainer src(new cvsupport::Image("lenna.jpg"));
            runtime::DataContainer dst(new cvsupport::Image(1000000));
            runtime::UInt32 ksizex(3);
            runtime::UInt32 ksizey(4);
            runtime::Enum shape(1);
            runtime::UInt32 iterations(2);
            
            m_operator->setInputData(Erode::INPUT_SRC, src);
            m_operator->setInputData(Erode::INPUT_DST, dst);
            m_operator->setParameter(Erode::PARAMETER_KSIZEX, ksizex);
            m_operator->setParameter(Erode::PARAMETER_KSIZEY, ksizey);
            m_operator->setParameter(Erode::PARAMETER_SHAPE, shape);
            m_operator->setParameter(Erode::PARAMETER_ITERATIONS, iterations);
            
            runtime::DataContainer dstResult = m_operator->getOutputData(Erode::OUTPUT_DST);
            
            runtime::ReadAccess dstAccess(dstResult);
            cvsupport::Image::save("ErodeTest_testManual0_dst.png", dstAccess.get<runtime::Image>());
        }
        
        void ErodeTest::testManual1()
        {
            m_operator->setParameter(Erode::PARAMETER_DATA_FLOW, runtime::Enum(Erode::MANUAL));
            m_operator->initialize();
            m_operator->activate();
            
            runtime::DataContainer src(new cvsupport::Image("lenna.jpg", cvsupport::Image::GRAYSCALE));
            runtime::DataContainer dst(new cvsupport::Image(1000000));
            
            m_operator->setInputData(Erode::INPUT_SRC, src);
            m_operator->setInputData(Erode::INPUT_DST, dst);
            
            runtime::DataContainer dstResult = m_operator->getOutputData(Erode::OUTPUT_DST);
            
            runtime::ReadAccess dstAccess(dstResult);
            cvsupport::Image::save("ErodeTest_testManual1_dst.png", dstAccess.get<runtime::Image>());
        }
        
        void ErodeTest::testAllocate0()
        {
            m_operator->setParameter(Erode::PARAMETER_DATA_FLOW, runtime::Enum(Erode::ALLOCATE));
            m_operator->initialize();
            m_operator->activate();
            
            runtime::DataContainer src(new cvsupport::Image("lenna.jpg"));
            
            m_operator->setInputData(Erode::INPUT_SRC, src);
            
            runtime::DataContainer dstResult = m_operator->getOutputData(Erode::OUTPUT_DST);
            
            runtime::ReadAccess dstAccess(dstResult);
            cvsupport::Image::save("ErodeTest_testAllocate0_dst.png", dstAccess.get<runtime::Image>());
        }
        
        void ErodeTest::testInPlace0()
        {
            m_operator->setParameter(Erode::PARAMETER_DATA_FLOW, runtime::Enum(Erode::IN_PLACE));
            m_operator->initialize();
            m_operator->activate();
            
            runtime::DataContainer src(new cvsupport::Image("lenna.jpg", cvsupport::Image::GRAYSCALE));
            runtime::Enum shape(2);
            
            m_operator->setInputData(Erode::INPUT_SRC, src);
            m_operator->setParameter(Erode::PARAMETER_SHAPE, shape);
            
            runtime::DataContainer srcResult = m_operator->getOutputData(Erode::OUTPUT_SRC);
            
            runtime::ReadAccess srcAccess(srcResult);
            cvsupport::Image::save("ErodeTest_testInPlace0_src.png", srcAccess.get<runtime::Image>());
        }
        
    } // cvimgproc
} // stromx

