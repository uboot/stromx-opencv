#include "stromx/cvimgproc/test/UndistortPointsTest.h"

#include <stromx/runtime/OperatorException.h>
#include <stromx/runtime/ReadAccess.h>
#include "stromx/cvsupport/Image.h"
#include "stromx/cvimgproc/UndistortPoints.h"

CPPUNIT_TEST_SUITE_REGISTRATION (stromx::cvimgproc::UndistortPointsTest);

namespace stromx
{
    namespace cvimgproc
    {
        void UndistortPointsTest::setUp()
        {
            m_operator = new stromx::runtime::OperatorTester(new UndistortPoints);
        }
        
        void UndistortPointsTest::tearDown()
        {
            delete m_operator;
        }
        
        void UndistortPointsTest::testAllocate0()
        {
            m_operator->initialize();
            m_operator->activate();
            
            runtime::DataContainer src(new cvsupport::Matrix("points_f32.npy"));
            cvsupport::Matrix cameraMatrix("camera_matrix.npy");
            cvsupport::Matrix distCoeffs("dist_coeffs.npy");
            
            m_operator->setInputData(UndistortPoints::INPUT_SRC, src);
            m_operator->setParameter(UndistortPoints::PARAMETER_CAMERA_MATRIX, cameraMatrix);
            m_operator->setParameter(UndistortPoints::PARAMETER_DIST_COEFFS, distCoeffs);
            
            runtime::DataContainer dstResult = m_operator->getOutputData(UndistortPoints::OUTPUT_DST);
            
            runtime::ReadAccess dstAccess(dstResult);
            cvsupport::Matrix::save("UndistortPointsTest_testAllocate0_dst.npy", dstAccess.get<runtime::Matrix>());
        }
        
        void UndistortPointsTest::testAllocate1()
        {
            m_operator->initialize();
            m_operator->activate();
            
            runtime::DataContainer src(new cvsupport::Matrix("points_f32.npy"));
            
            m_operator->setInputData(UndistortPoints::INPUT_SRC, src);
            
            runtime::DataContainer dstResult = m_operator->getOutputData(UndistortPoints::OUTPUT_DST);
            
            runtime::ReadAccess dstAccess(dstResult);
            cvsupport::Matrix::save("UndistortPointsTest_testAllocate1_dst.npy", dstAccess.get<runtime::Matrix>());
        }
        
    } // cvimgproc
} // stromx

