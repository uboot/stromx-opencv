#include "stromx/cvimgproc/test/ScharrTest.h"

#include <stromx/runtime/OperatorException.h>
#include <stromx/runtime/ReadAccess.h>
#include "stromx/cvsupport/Image.h"
#include "stromx/cvimgproc/Scharr.h"

CPPUNIT_TEST_SUITE_REGISTRATION (stromx::cvimgproc::ScharrTest);

namespace stromx
{
    namespace cvimgproc
    {
        void ScharrTest::setUp()
        {
            m_operator = new stromx::runtime::OperatorTester(new Scharr);
        }
        
        void ScharrTest::tearDown()
        {
            delete m_operator;
        }
        
        void ScharrTest::testManual0()
        {
            m_operator->setParameter(Scharr::PARAMETER_DATA_FLOW, runtime::Enum(Scharr::MANUAL));
            m_operator->initialize();
            m_operator->activate();
            
            runtime::DataContainer src(new cvsupport::Image("lenna.jpg"));
            runtime::DataContainer dst(new cvsupport::Image(1000000));
            runtime::Enum ddepth(0);
            runtime::UInt32 dx(0);
            runtime::UInt32 dy(1);
            runtime::Float64 scale(1);
            runtime::Float64 delta(0);
            
            m_operator->setInputData(Scharr::INPUT_SRC, src);
            m_operator->setInputData(Scharr::INPUT_DST, dst);
            m_operator->setParameter(Scharr::PARAMETER_DDEPTH, ddepth);
            m_operator->setParameter(Scharr::PARAMETER_DX, dx);
            m_operator->setParameter(Scharr::PARAMETER_DY, dy);
            m_operator->setParameter(Scharr::PARAMETER_SCALE, scale);
            m_operator->setParameter(Scharr::PARAMETER_DELTA, delta);
            
            runtime::DataContainer dstResult = m_operator->getOutputData(Scharr::OUTPUT_DST);
            
            runtime::ReadAccess dstAccess(dstResult);
            cvsupport::Image::save("ScharrTest_testManual0_dst.png", dstAccess.get<runtime::Image>());
        }
        
        void ScharrTest::testManual1()
        {
            m_operator->setParameter(Scharr::PARAMETER_DATA_FLOW, runtime::Enum(Scharr::MANUAL));
            m_operator->initialize();
            m_operator->activate();
            
            runtime::DataContainer src(new cvsupport::Image("lenna.jpg", cvsupport::Image::GRAYSCALE));
            runtime::DataContainer dst(new cvsupport::Image(1000000));
            runtime::Enum ddepth(1);
            runtime::UInt32 dx(1);
            runtime::UInt32 dy(0);
            runtime::Float64 scale(1);
            runtime::Float64 delta(0);
            
            m_operator->setInputData(Scharr::INPUT_SRC, src);
            m_operator->setInputData(Scharr::INPUT_DST, dst);
            m_operator->setParameter(Scharr::PARAMETER_DDEPTH, ddepth);
            m_operator->setParameter(Scharr::PARAMETER_DX, dx);
            m_operator->setParameter(Scharr::PARAMETER_DY, dy);
            m_operator->setParameter(Scharr::PARAMETER_SCALE, scale);
            m_operator->setParameter(Scharr::PARAMETER_DELTA, delta);
            
            runtime::DataContainer dstResult = m_operator->getOutputData(Scharr::OUTPUT_DST);
            
            runtime::ReadAccess dstAccess(dstResult);
            cvsupport::Image::save("ScharrTest_testManual1_dst.png", dstAccess.get<runtime::Image>());
        }
        
        void ScharrTest::testAllocate0()
        {
            m_operator->setParameter(Scharr::PARAMETER_DATA_FLOW, runtime::Enum(Scharr::ALLOCATE));
            m_operator->initialize();
            m_operator->activate();
            
            runtime::DataContainer src(new cvsupport::Image("lenna.jpg"));
            runtime::Enum ddepth(0);
            runtime::Float64 scale(2);
            
            m_operator->setInputData(Scharr::INPUT_SRC, src);
            m_operator->setParameter(Scharr::PARAMETER_DDEPTH, ddepth);
            m_operator->setParameter(Scharr::PARAMETER_SCALE, scale);
            
            runtime::DataContainer dstResult = m_operator->getOutputData(Scharr::OUTPUT_DST);
            
            runtime::ReadAccess dstAccess(dstResult);
            cvsupport::Image::save("ScharrTest_testAllocate0_dst.png", dstAccess.get<runtime::Image>());
        }
        
        void ScharrTest::testAllocate1()
        {
            m_operator->setParameter(Scharr::PARAMETER_DATA_FLOW, runtime::Enum(Scharr::ALLOCATE));
            m_operator->initialize();
            m_operator->activate();
            
            runtime::DataContainer src(new cvsupport::Image("lenna.jpg", cvsupport::Image::GRAYSCALE));
            runtime::Enum ddepth(2);
            runtime::UInt32 dx(0);
            runtime::UInt32 dy(1);
            runtime::Float64 scale(100);
            
            m_operator->setInputData(Scharr::INPUT_SRC, src);
            m_operator->setParameter(Scharr::PARAMETER_DDEPTH, ddepth);
            m_operator->setParameter(Scharr::PARAMETER_DX, dx);
            m_operator->setParameter(Scharr::PARAMETER_DY, dy);
            m_operator->setParameter(Scharr::PARAMETER_SCALE, scale);
            
            runtime::DataContainer dstResult = m_operator->getOutputData(Scharr::OUTPUT_DST);
            
            runtime::ReadAccess dstAccess(dstResult);
            cvsupport::Image::save("ScharrTest_testAllocate1_dst.png", dstAccess.get<runtime::Image>());
        }
        
    } // cvimgproc
} // stromx

