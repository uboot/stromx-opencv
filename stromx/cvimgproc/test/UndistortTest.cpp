#include "stromx/cvimgproc/test/UndistortTest.h"

#include <stromx/runtime/OperatorException.h>
#include <stromx/runtime/ReadAccess.h>
#include "stromx/cvsupport/Image.h"
#include "stromx/cvimgproc/Undistort.h"

CPPUNIT_TEST_SUITE_REGISTRATION (stromx::cvimgproc::UndistortTest);

namespace stromx
{
    namespace cvimgproc
    {
        void UndistortTest::setUp()
        {
            m_operator = new stromx::runtime::OperatorTester(new Undistort);
        }
        
        void UndistortTest::tearDown()
        {
            delete m_operator;
        }
        
        void UndistortTest::testManual0()
        {
            m_operator->setParameter(Undistort::PARAMETER_DATA_FLOW, runtime::Enum(Undistort::MANUAL));
            m_operator->initialize();
            m_operator->activate();
            
            runtime::DataContainer src(new cvsupport::Image("lenna.jpg", cvsupport::Image::GRAYSCALE));
            runtime::DataContainer dst(new cvsupport::Image(1000000));
            cvsupport::Matrix cameraMatrix("camera_matrix.npy");
            cvsupport::Matrix distCoeffs("dist_coeffs.npy");
            
            m_operator->setInputData(Undistort::INPUT_SRC, src);
            m_operator->setInputData(Undistort::INPUT_DST, dst);
            m_operator->setParameter(Undistort::PARAMETER_CAMERA_MATRIX, cameraMatrix);
            m_operator->setParameter(Undistort::PARAMETER_DIST_COEFFS, distCoeffs);
            
            runtime::DataContainer dstResult = m_operator->getOutputData(Undistort::OUTPUT_DST);
            
            runtime::ReadAccess dstAccess(dstResult);
            cvsupport::Image::save("UndistortTest_testManual0_dst.png", dstAccess.get<runtime::Image>());
        }
        
        void UndistortTest::testManual1()
        {
            m_operator->setParameter(Undistort::PARAMETER_DATA_FLOW, runtime::Enum(Undistort::MANUAL));
            m_operator->initialize();
            m_operator->activate();
            
            runtime::DataContainer src(new cvsupport::Image("lenna.jpg"));
            runtime::DataContainer dst(new cvsupport::Image(1000000));
            
            m_operator->setInputData(Undistort::INPUT_SRC, src);
            m_operator->setInputData(Undistort::INPUT_DST, dst);
            
            runtime::DataContainer dstResult = m_operator->getOutputData(Undistort::OUTPUT_DST);
            
            runtime::ReadAccess dstAccess(dstResult);
            cvsupport::Image::save("UndistortTest_testManual1_dst.png", dstAccess.get<runtime::Image>());
        }
        
        void UndistortTest::testAllocate0()
        {
            m_operator->setParameter(Undistort::PARAMETER_DATA_FLOW, runtime::Enum(Undistort::ALLOCATE));
            m_operator->initialize();
            m_operator->activate();
            
            runtime::DataContainer src(new cvsupport::Image("lenna.jpg"));
            cvsupport::Matrix cameraMatrix("camera_matrix.npy");
            cvsupport::Matrix distCoeffs("dist_coeffs.npy");
            
            m_operator->setInputData(Undistort::INPUT_SRC, src);
            m_operator->setParameter(Undistort::PARAMETER_CAMERA_MATRIX, cameraMatrix);
            m_operator->setParameter(Undistort::PARAMETER_DIST_COEFFS, distCoeffs);
            
            runtime::DataContainer dstResult = m_operator->getOutputData(Undistort::OUTPUT_DST);
            
            runtime::ReadAccess dstAccess(dstResult);
            cvsupport::Image::save("UndistortTest_testAllocate0_dst.png", dstAccess.get<runtime::Image>());
        }
        
    } // cvimgproc
} // stromx

