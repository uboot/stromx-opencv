#include "stromx/cvcore/test/MergeTest.h"

#include <stromx/runtime/OperatorException.h>
#include <stromx/runtime/ReadAccess.h>
#include "stromx/cvsupport/Image.h"
#include "stromx/cvcore/Merge.h"

CPPUNIT_TEST_SUITE_REGISTRATION (stromx::cvcore::MergeTest);

namespace stromx
{
    namespace cvcore
    {
        void MergeTest::setUp()
        {
            m_operator = new stromx::runtime::OperatorTester(new Merge);
        }
        
        void MergeTest::tearDown()
        {
            delete m_operator;
        }
        
        void MergeTest::testManual0()
        {
            m_operator->setParameter(Merge::PARAMETER_DATA_FLOW, runtime::Enum(Merge::MANUAL));
            m_operator->initialize();
            m_operator->activate();
            
            runtime::DataContainer src1(new cvsupport::Matrix("column_32f.npy"));
            runtime::DataContainer src2(new cvsupport::Matrix("column_32f.npy"));
            runtime::DataContainer dst(new cvsupport::Image(5000000));
            
            m_operator->setInputData(Merge::INPUT_SRC_1, src1);
            m_operator->setInputData(Merge::INPUT_SRC_2, src2);
            m_operator->setInputData(Merge::INPUT_DST, dst);
            
            runtime::DataContainer dstResult = m_operator->getOutputData(Merge::OUTPUT_DST);
            
            runtime::ReadAccess dstAccess(dstResult);
            cvsupport::Matrix::save("MergeTest_testManual0_dst.npy", dstAccess.get<runtime::Matrix>());
        }
        
        void MergeTest::testManual1()
        {
            m_operator->setParameter(Merge::PARAMETER_DATA_FLOW, runtime::Enum(Merge::MANUAL));
            m_operator->initialize();
            m_operator->activate();
            
            runtime::DataContainer src1(new cvsupport::Matrix("row_64f.npy"));
            runtime::DataContainer src2(new cvsupport::Matrix("row_64f.npy"));
            runtime::DataContainer dst(new cvsupport::Image(5000000));
            
            m_operator->setInputData(Merge::INPUT_SRC_1, src1);
            m_operator->setInputData(Merge::INPUT_SRC_2, src2);
            m_operator->setInputData(Merge::INPUT_DST, dst);
            
            runtime::DataContainer dstResult = m_operator->getOutputData(Merge::OUTPUT_DST);
            
            runtime::ReadAccess dstAccess(dstResult);
            cvsupport::Matrix::save("MergeTest_testManual1_dst.npy", dstAccess.get<runtime::Matrix>());
        }
        
        void MergeTest::testAllocate0()
        {
            m_operator->setParameter(Merge::PARAMETER_DATA_FLOW, runtime::Enum(Merge::ALLOCATE));
            m_operator->initialize();
            m_operator->activate();
            
            runtime::DataContainer src1(new cvsupport::Matrix("column_64f.npy"));
            runtime::DataContainer src2(new cvsupport::Matrix("column_64f.npy"));
            runtime::DataContainer dst(new cvsupport::Image(5000000));
            
            m_operator->setInputData(Merge::INPUT_SRC_1, src1);
            m_operator->setInputData(Merge::INPUT_SRC_2, src2);
            m_operator->setInputData(Merge::INPUT_DST, dst);
            
            runtime::DataContainer dstResult = m_operator->getOutputData(Merge::OUTPUT_DST);
            
            runtime::ReadAccess dstAccess(dstResult);
            cvsupport::Matrix::save("MergeTest_testAllocate0_dst.npy", dstAccess.get<runtime::Matrix>());
        }
        
        void MergeTest::testAllocate1()
        {
            m_operator->setParameter(Merge::PARAMETER_DATA_FLOW, runtime::Enum(Merge::ALLOCATE));
            m_operator->initialize();
            m_operator->activate();
            
            runtime::DataContainer src1(new cvsupport::Matrix("row_32f.npy"));
            runtime::DataContainer src2(new cvsupport::Matrix("row_32f.npy"));
            runtime::DataContainer dst(new cvsupport::Image(5000000));
            
            m_operator->setInputData(Merge::INPUT_SRC_1, src1);
            m_operator->setInputData(Merge::INPUT_SRC_2, src2);
            m_operator->setInputData(Merge::INPUT_DST, dst);
            
            runtime::DataContainer dstResult = m_operator->getOutputData(Merge::OUTPUT_DST);
            
            runtime::ReadAccess dstAccess(dstResult);
            cvsupport::Matrix::save("MergeTest_testAllocate1_dst.npy", dstAccess.get<runtime::Matrix>());
        }
        
    } // cvcore
} // stromx

