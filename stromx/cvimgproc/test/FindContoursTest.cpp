#include "stromx/cvimgproc/test/FindContoursTest.h"

#include <stromx/runtime/OperatorException.h>
#include <stromx/runtime/ReadAccess.h>
#include "stromx/cvsupport/Image.h"
#include "stromx/cvimgproc/FindContours.h"

CPPUNIT_TEST_SUITE_REGISTRATION (stromx::cvimgproc::FindContoursTest);

namespace stromx
{
    namespace cvimgproc
    {
        void FindContoursTest::setUp()
        {
            m_operator = new stromx::runtime::OperatorTester(new FindContours);
        }
        
        void FindContoursTest::tearDown()
        {
            delete m_operator;
        }
        
        void FindContoursTest::testAllocate0()
        {
            m_operator->initialize();
            m_operator->activate();
            
            runtime::DataContainer src(new cvsupport::Image("contours.png", cvsupport::Image::GRAYSCALE));
            
            m_operator->setInputData(FindContours::INPUT_SRC, src);
            
            runtime::DataContainer dstResult = m_operator->getOutputData(FindContours::OUTPUT_DST);
            
            std::size_t index = 0;
            runtime::ReadAccess dstAccess(dstResult);
            const std::vector<const runtime::Data*> & content = dstAccess.get<runtime::List>().content();
            for (std::vector<const runtime::Data*>::const_iterator iter = content.begin(); iter != content.end(); ++iter)
            {
                const runtime::Matrix* matrix = runtime::data_cast<runtime::Matrix>(*iter);
                std::string fileName = "FindContoursTest_testAllocate0_dst_" + std::to_string(index) + ".npy";
                cvsupport::Matrix::save(fileName, *matrix);
                ++index;
            }
        }
        
        void FindContoursTest::testAllocate1()
        {
            m_operator->initialize();
            m_operator->activate();
            
            runtime::DataContainer src(new cvsupport::Image("contours.png", cvsupport::Image::GRAYSCALE));
            runtime::Enum method(1);
            
            m_operator->setInputData(FindContours::INPUT_SRC, src);
            m_operator->setParameter(FindContours::PARAMETER_METHOD, method);
            
            runtime::DataContainer dstResult = m_operator->getOutputData(FindContours::OUTPUT_DST);
            
            std::size_t index = 0;
            runtime::ReadAccess dstAccess(dstResult);
            const std::vector<const runtime::Data*> & content = dstAccess.get<runtime::List>().content();
            for (std::vector<const runtime::Data*>::const_iterator iter = content.begin(); iter != content.end(); ++iter)
            {
                const runtime::Matrix* matrix = runtime::data_cast<runtime::Matrix>(*iter);
                std::string fileName = "FindContoursTest_testAllocate1_dst_" + std::to_string(index) + ".npy";
                cvsupport::Matrix::save(fileName, *matrix);
                ++index;
            }
        }
        
    } // cvimgproc
} // stromx

