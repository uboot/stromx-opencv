#include "stromx/cvimgproc/test/WarpPerspectiveTest.h"

#include <stromx/runtime/OperatorException.h>
#include <stromx/runtime/ReadAccess.h>
#include "stromx/cvsupport/Image.h"
#include "stromx/cvimgproc/WarpPerspective.h"

CPPUNIT_TEST_SUITE_REGISTRATION (stromx::cvimgproc::WarpPerspectiveTest);

namespace stromx
{
    namespace cvimgproc
    {
        void WarpPerspectiveTest::setUp()
        {
            m_operator = new stromx::runtime::OperatorTester(new WarpPerspective);
        }
        
        void WarpPerspectiveTest::tearDown()
        {
            delete m_operator;
        }
        
        void WarpPerspectiveTest::testManual0()
        {
            m_operator->setParameter(WarpPerspective::PARAMETER_DATA_FLOW, runtime::Enum(WarpPerspective::MANUAL));
            m_operator->initialize();
            m_operator->activate();
            
            runtime::DataContainer src(new cvsupport::Image("lenna.jpg", cvsupport::Image::GRAYSCALE));
            runtime::DataContainer dst(new cvsupport::Image(1000000));
            cvsupport::Matrix affineM("perspective.npy");
            runtime::UInt32 dsizex(400);
            runtime::UInt32 dsizey(500);
            
            m_operator->setInputData(WarpPerspective::INPUT_SRC, src);
            m_operator->setInputData(WarpPerspective::INPUT_DST, dst);
            m_operator->setParameter(WarpPerspective::PARAMETER_AFFINE_M, affineM);
            m_operator->setParameter(WarpPerspective::PARAMETER_DSIZEX, dsizex);
            m_operator->setParameter(WarpPerspective::PARAMETER_DSIZEY, dsizey);
            
            runtime::DataContainer dstResult = m_operator->getOutputData(WarpPerspective::OUTPUT_DST);
            
            runtime::ReadAccess dstAccess(dstResult);
            cvsupport::Image::save("WarpPerspectiveTest_testManual0_dst.png", dstAccess.get<runtime::Image>());
        }
        
        void WarpPerspectiveTest::testManual1()
        {
            m_operator->setParameter(WarpPerspective::PARAMETER_DATA_FLOW, runtime::Enum(WarpPerspective::MANUAL));
            m_operator->initialize();
            m_operator->activate();
            
            runtime::DataContainer src(new cvsupport::Image("lenna.jpg"));
            runtime::DataContainer dst(new cvsupport::Image(1000000));
            runtime::UInt32 dsizex(400);
            runtime::UInt32 dsizey(500);
            
            m_operator->setInputData(WarpPerspective::INPUT_SRC, src);
            m_operator->setInputData(WarpPerspective::INPUT_DST, dst);
            m_operator->setParameter(WarpPerspective::PARAMETER_DSIZEX, dsizex);
            m_operator->setParameter(WarpPerspective::PARAMETER_DSIZEY, dsizey);
            
            runtime::DataContainer dstResult = m_operator->getOutputData(WarpPerspective::OUTPUT_DST);
            
            runtime::ReadAccess dstAccess(dstResult);
            cvsupport::Image::save("WarpPerspectiveTest_testManual1_dst.png", dstAccess.get<runtime::Image>());
        }
        
        void WarpPerspectiveTest::testAllocate0()
        {
            m_operator->setParameter(WarpPerspective::PARAMETER_DATA_FLOW, runtime::Enum(WarpPerspective::ALLOCATE));
            m_operator->initialize();
            m_operator->activate();
            
            runtime::DataContainer src(new cvsupport::Image("lenna.jpg"));
            cvsupport::Matrix affineM("perspective.npy");
            runtime::UInt32 dsizex(400);
            runtime::UInt32 dsizey(500);
            
            m_operator->setInputData(WarpPerspective::INPUT_SRC, src);
            m_operator->setParameter(WarpPerspective::PARAMETER_AFFINE_M, affineM);
            m_operator->setParameter(WarpPerspective::PARAMETER_DSIZEX, dsizex);
            m_operator->setParameter(WarpPerspective::PARAMETER_DSIZEY, dsizey);
            
            runtime::DataContainer dstResult = m_operator->getOutputData(WarpPerspective::OUTPUT_DST);
            
            runtime::ReadAccess dstAccess(dstResult);
            cvsupport::Image::save("WarpPerspectiveTest_testAllocate0_dst.png", dstAccess.get<runtime::Image>());
        }
        
    } // cvimgproc
} // stromx

