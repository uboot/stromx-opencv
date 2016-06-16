#include "stromx/cvimgproc/test/PyrDownTest.h"

#include <stromx/runtime/OperatorException.h>
#include <stromx/runtime/ReadAccess.h>
#include "stromx/cvsupport/Image.h"
#include "stromx/cvimgproc/PyrDown.h"

CPPUNIT_TEST_SUITE_REGISTRATION (stromx::cvimgproc::PyrDownTest);

namespace stromx
{
    namespace cvimgproc
    {
        void PyrDownTest::setUp()
        {
            m_operator = new stromx::runtime::OperatorTester(new PyrDown);
        }
        
        void PyrDownTest::tearDown()
        {
            delete m_operator;
        }
        
        void PyrDownTest::testManual0()
        {
            m_operator->setParameter(PyrDown::PARAMETER_DATA_FLOW, runtime::Enum(PyrDown::MANUAL));
            m_operator->initialize();
            m_operator->activate();
            
            runtime::DataContainer src(new cvsupport::Image("lenna.jpg"));
            runtime::DataContainer dst(new cvsupport::Image(1000000));
            
            m_operator->setInputData(PyrDown::INPUT_SRC, src);
            m_operator->setInputData(PyrDown::INPUT_DST, dst);
            
            runtime::DataContainer dstResult = m_operator->getOutputData(PyrDown::OUTPUT_DST);
            
            runtime::ReadAccess dstAccess(dstResult);
            cvsupport::Image::save("PyrDownTest_testManual0_dst.png", dstAccess.get<runtime::Image>());
        }
        
        void PyrDownTest::testAllocate0()
        {
            m_operator->setParameter(PyrDown::PARAMETER_DATA_FLOW, runtime::Enum(PyrDown::ALLOCATE));
            m_operator->initialize();
            m_operator->activate();
            
            runtime::DataContainer src(new cvsupport::Image("lenna.jpg", cvsupport::Image::GRAYSCALE));
            
            m_operator->setInputData(PyrDown::INPUT_SRC, src);
            
            runtime::DataContainer dstResult = m_operator->getOutputData(PyrDown::OUTPUT_DST);
            
            runtime::ReadAccess dstAccess(dstResult);
            cvsupport::Image::save("PyrDownTest_testAllocate0_dst.png", dstAccess.get<runtime::Image>());
        }
        
    } // cvimgproc
} // stromx

