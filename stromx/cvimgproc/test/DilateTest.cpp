#include "stromx/cvimgproc/test/DilateTest.h"

#include <stromx/runtime/OperatorException.h>
#include <stromx/runtime/ReadAccess.h>
#include "stromx/cvsupport/Image.h"
#include "stromx/cvimgproc/Dilate.h"

CPPUNIT_TEST_SUITE_REGISTRATION (stromx::cvimgproc::DilateTest);

namespace stromx
{
    namespace cvimgproc
    {
        void DilateTest::setUp()
        {
            m_operator = new stromx::runtime::OperatorTester(new Dilate);
        }
        
        void DilateTest::tearDown()
        {
            delete m_operator;
        }
        
        void DilateTest::testManual0()
        {
            m_operator->setParameter(Dilate::PARAMETER_DATA_FLOW, runtime::Enum(Dilate::MANUAL));
            m_operator->initialize();
            m_operator->activate();
            
            runtime::DataContainer src(new cvsupport::Image("lenna.jpg"));
            runtime::DataContainer dst(new cvsupport::Image(1000000));
            runtime::UInt32 ksizex(3);
            runtime::UInt32 ksizey(4);
            runtime::Enum shape(1);
            runtime::UInt32 iterations(2);
            
            m_operator->setInputData(Dilate::INPUT_SRC, src);
            m_operator->setInputData(Dilate::INPUT_DST, dst);
            m_operator->setParameter(Dilate::PARAMETER_KSIZEX, ksizex);
            m_operator->setParameter(Dilate::PARAMETER_KSIZEY, ksizey);
            m_operator->setParameter(Dilate::PARAMETER_SHAPE, shape);
            m_operator->setParameter(Dilate::PARAMETER_ITERATIONS, iterations);
            
            runtime::DataContainer dstResult = m_operator->getOutputData(Dilate::OUTPUT_DST);
            
            runtime::ReadAccess dstAccess(dstResult);
            cvsupport::Image::save("DilateTest_testManual0_dst.png", dstAccess.get<runtime::Image>());
        }
        
        void DilateTest::testManual1()
        {
            m_operator->setParameter(Dilate::PARAMETER_DATA_FLOW, runtime::Enum(Dilate::MANUAL));
            m_operator->initialize();
            m_operator->activate();
            
            runtime::DataContainer src(new cvsupport::Image("lenna.jpg", cvsupport::Image::GRAYSCALE));
            runtime::DataContainer dst(new cvsupport::Image(1000000));
            
            m_operator->setInputData(Dilate::INPUT_SRC, src);
            m_operator->setInputData(Dilate::INPUT_DST, dst);
            
            runtime::DataContainer dstResult = m_operator->getOutputData(Dilate::OUTPUT_DST);
            
            runtime::ReadAccess dstAccess(dstResult);
            cvsupport::Image::save("DilateTest_testManual1_dst.png", dstAccess.get<runtime::Image>());
        }
        
        void DilateTest::testAllocate0()
        {
            m_operator->setParameter(Dilate::PARAMETER_DATA_FLOW, runtime::Enum(Dilate::ALLOCATE));
            m_operator->initialize();
            m_operator->activate();
            
            runtime::DataContainer src(new cvsupport::Image("lenna.jpg"));
            
            m_operator->setInputData(Dilate::INPUT_SRC, src);
            
            runtime::DataContainer dstResult = m_operator->getOutputData(Dilate::OUTPUT_DST);
            
            runtime::ReadAccess dstAccess(dstResult);
            cvsupport::Image::save("DilateTest_testAllocate0_dst.png", dstAccess.get<runtime::Image>());
        }
        
        void DilateTest::testInPlace0()
        {
            m_operator->setParameter(Dilate::PARAMETER_DATA_FLOW, runtime::Enum(Dilate::IN_PLACE));
            m_operator->initialize();
            m_operator->activate();
            
            runtime::DataContainer src(new cvsupport::Image("lenna.jpg", cvsupport::Image::GRAYSCALE));
            runtime::Enum shape(2);
            
            m_operator->setInputData(Dilate::INPUT_SRC, src);
            m_operator->setParameter(Dilate::PARAMETER_SHAPE, shape);
            
            runtime::DataContainer srcResult = m_operator->getOutputData(Dilate::OUTPUT_SRC);
            
            runtime::ReadAccess srcAccess(srcResult);
            cvsupport::Image::save("DilateTest_testInPlace0_src.png", srcAccess.get<runtime::Image>());
        }
        
    } // cvimgproc
} // stromx

