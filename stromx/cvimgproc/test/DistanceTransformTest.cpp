#include "stromx/cvimgproc/test/DistanceTransformTest.h"

#include <stromx/runtime/OperatorException.h>
#include <stromx/runtime/ReadAccess.h>
#include "stromx/cvsupport/Image.h"
#include "stromx/cvimgproc/DistanceTransform.h"

CPPUNIT_TEST_SUITE_REGISTRATION (stromx::cvimgproc::DistanceTransformTest);

namespace stromx
{
    namespace cvimgproc
    {
        void DistanceTransformTest::setUp()
        {
            m_operator = new stromx::runtime::OperatorTester(new DistanceTransform);
        }
        
        void DistanceTransformTest::tearDown()
        {
            delete m_operator;
        }
        
        void DistanceTransformTest::testManual0()
        {
            m_operator->setParameter(DistanceTransform::PARAMETER_DATA_FLOW, runtime::Enum(DistanceTransform::MANUAL));
            m_operator->initialize();
            m_operator->activate();
            
            runtime::DataContainer src(new cvsupport::Image("circle.png", cvsupport::Image::GRAYSCALE));
            runtime::DataContainer dst(new cvsupport::Image(1000000));
            
            m_operator->setInputData(DistanceTransform::INPUT_SRC, src);
            m_operator->setInputData(DistanceTransform::INPUT_DST, dst);
            
            runtime::DataContainer dstResult = m_operator->getOutputData(DistanceTransform::OUTPUT_DST);
            
            runtime::ReadAccess dstAccess(dstResult);
            cvsupport::Matrix::save("DistanceTransformTest_testManual0_dst.npy", dstAccess.get<runtime::Matrix>());
        }
        
        void DistanceTransformTest::testAllocate0()
        {
            m_operator->setParameter(DistanceTransform::PARAMETER_DATA_FLOW, runtime::Enum(DistanceTransform::ALLOCATE));
            m_operator->initialize();
            m_operator->activate();
            
            runtime::DataContainer src(new cvsupport::Image("circle.png", cvsupport::Image::GRAYSCALE));
            runtime::Enum distanceType(2);
            runtime::Enum maskSize(0);
            
            m_operator->setInputData(DistanceTransform::INPUT_SRC, src);
            m_operator->setParameter(DistanceTransform::PARAMETER_DISTANCE_TYPE, distanceType);
            m_operator->setParameter(DistanceTransform::PARAMETER_MASK_SIZE, maskSize);
            
            runtime::DataContainer dstResult = m_operator->getOutputData(DistanceTransform::OUTPUT_DST);
            
            runtime::ReadAccess dstAccess(dstResult);
            cvsupport::Matrix::save("DistanceTransformTest_testAllocate0_dst.npy", dstAccess.get<runtime::Matrix>());
        }
        
        void DistanceTransformTest::testAllocate1()
        {
            m_operator->setParameter(DistanceTransform::PARAMETER_DATA_FLOW, runtime::Enum(DistanceTransform::ALLOCATE));
            m_operator->initialize();
            m_operator->activate();
            
            runtime::DataContainer src(new cvsupport::Image("circle.png", cvsupport::Image::GRAYSCALE));
            runtime::Enum distanceType(1);
            runtime::Enum maskSize(1);
            
            m_operator->setInputData(DistanceTransform::INPUT_SRC, src);
            m_operator->setParameter(DistanceTransform::PARAMETER_DISTANCE_TYPE, distanceType);
            m_operator->setParameter(DistanceTransform::PARAMETER_MASK_SIZE, maskSize);
            
            runtime::DataContainer dstResult = m_operator->getOutputData(DistanceTransform::OUTPUT_DST);
            
            runtime::ReadAccess dstAccess(dstResult);
            cvsupport::Matrix::save("DistanceTransformTest_testAllocate1_dst.npy", dstAccess.get<runtime::Matrix>());
        }
        
        void DistanceTransformTest::testAllocate2()
        {
            m_operator->setParameter(DistanceTransform::PARAMETER_DATA_FLOW, runtime::Enum(DistanceTransform::ALLOCATE));
            m_operator->initialize();
            m_operator->activate();
            
            runtime::DataContainer src(new cvsupport::Image("circle.png", cvsupport::Image::GRAYSCALE));
            runtime::Enum distanceType(0);
            runtime::Enum maskSize(2);
            
            m_operator->setInputData(DistanceTransform::INPUT_SRC, src);
            m_operator->setParameter(DistanceTransform::PARAMETER_DISTANCE_TYPE, distanceType);
            m_operator->setParameter(DistanceTransform::PARAMETER_MASK_SIZE, maskSize);
            
            runtime::DataContainer dstResult = m_operator->getOutputData(DistanceTransform::OUTPUT_DST);
            
            runtime::ReadAccess dstAccess(dstResult);
            cvsupport::Matrix::save("DistanceTransformTest_testAllocate2_dst.npy", dstAccess.get<runtime::Matrix>());
        }
        
    } // cvimgproc
} // stromx

