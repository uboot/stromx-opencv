#include "stromx/cvcalib3d/test/StereoCalibrateTest.h"

#include <stromx/runtime/OperatorException.h>
#include <stromx/runtime/ReadAccess.h>
#include "stromx/cvsupport/Image.h"
#include "stromx/cvcalib3d/StereoCalibrate.h"

CPPUNIT_TEST_SUITE_REGISTRATION (stromx::cvcalib3d::StereoCalibrateTest);

namespace stromx
{
    namespace cvcalib3d
    {
        void StereoCalibrateTest::setUp()
        {
            m_operator = new stromx::runtime::OperatorTester(new StereoCalibrate);
        }
        
        void StereoCalibrateTest::tearDown()
        {
            delete m_operator;
        }
        
        void StereoCalibrateTest::testExtrinsics0()
        {
            m_operator->setParameter(StereoCalibrate::PARAMETER_DATA_FLOW, runtime::Enum(StereoCalibrate::EXTRINSICS));
            m_operator->initialize();
            m_operator->activate();
            
            runtime::Data* objectPointsItem = 0;
            std::vector<runtime::Data*> objectPointsVector;
            objectPointsItem = new cvsupport::Matrix("chess_corners_3d.npy");
            objectPointsVector.push_back(objectPointsItem);
            objectPointsItem = new cvsupport::Matrix("chess_corners_3d.npy");
            objectPointsVector.push_back(objectPointsItem);
            objectPointsItem = new cvsupport::Matrix("chess_corners_3d.npy");
            objectPointsVector.push_back(objectPointsItem);
            objectPointsItem = new cvsupport::Matrix("chess_corners_3d.npy");
            objectPointsVector.push_back(objectPointsItem);
            objectPointsItem = new cvsupport::Matrix("chess_corners_3d.npy");
            objectPointsVector.push_back(objectPointsItem);
            objectPointsItem = new cvsupport::Matrix("chess_corners_3d.npy");
            objectPointsVector.push_back(objectPointsItem);
            objectPointsItem = new cvsupport::Matrix("chess_corners_3d.npy");
            objectPointsVector.push_back(objectPointsItem);
            runtime::DataContainer objectPoints(new runtime::List(objectPointsVector));
            
            runtime::Data* imagePoints1Item = 0;
            std::vector<runtime::Data*> imagePoints1Vector;
            imagePoints1Item = new cvsupport::Matrix("chess_corners_1.npy");
            imagePoints1Vector.push_back(imagePoints1Item);
            imagePoints1Item = new cvsupport::Matrix("chess_corners_2.npy");
            imagePoints1Vector.push_back(imagePoints1Item);
            imagePoints1Item = new cvsupport::Matrix("chess_corners_3.npy");
            imagePoints1Vector.push_back(imagePoints1Item);
            imagePoints1Item = new cvsupport::Matrix("chess_corners_4.npy");
            imagePoints1Vector.push_back(imagePoints1Item);
            imagePoints1Item = new cvsupport::Matrix("chess_corners_5.npy");
            imagePoints1Vector.push_back(imagePoints1Item);
            imagePoints1Item = new cvsupport::Matrix("chess_corners_6.npy");
            imagePoints1Vector.push_back(imagePoints1Item);
            imagePoints1Item = new cvsupport::Matrix("chess_corners_7.npy");
            imagePoints1Vector.push_back(imagePoints1Item);
            runtime::DataContainer imagePoints1(new runtime::List(imagePoints1Vector));
            
            runtime::Data* imagePoints2Item = 0;
            std::vector<runtime::Data*> imagePoints2Vector;
            imagePoints2Item = new cvsupport::Matrix("chess_corners_1.npy");
            imagePoints2Vector.push_back(imagePoints2Item);
            imagePoints2Item = new cvsupport::Matrix("chess_corners_2.npy");
            imagePoints2Vector.push_back(imagePoints2Item);
            imagePoints2Item = new cvsupport::Matrix("chess_corners_3.npy");
            imagePoints2Vector.push_back(imagePoints2Item);
            imagePoints2Item = new cvsupport::Matrix("chess_corners_4.npy");
            imagePoints2Vector.push_back(imagePoints2Item);
            imagePoints2Item = new cvsupport::Matrix("chess_corners_5.npy");
            imagePoints2Vector.push_back(imagePoints2Item);
            imagePoints2Item = new cvsupport::Matrix("chess_corners_6.npy");
            imagePoints2Vector.push_back(imagePoints2Item);
            imagePoints2Item = new cvsupport::Matrix("chess_corners_7.npy");
            imagePoints2Vector.push_back(imagePoints2Item);
            runtime::DataContainer imagePoints2(new runtime::List(imagePoints2Vector));
            
            cvsupport::Matrix cameraMatrix1("camera_matrix_32f.npy");
            cvsupport::Matrix distCoeffs1("dist_coeffs_32f.npy");
            cvsupport::Matrix cameraMatrix2("camera_matrix_32f.npy");
            cvsupport::Matrix distCoeffs2("dist_coeffs_32f.npy");
            runtime::UInt32 imageSizeX(320);
            runtime::UInt32 imageSizeY(240);
            
            m_operator->setInputData(StereoCalibrate::INPUT_OBJECT_POINTS, objectPoints);
            m_operator->setInputData(StereoCalibrate::INPUT_IMAGE_POINTS_1, imagePoints1);
            m_operator->setInputData(StereoCalibrate::INPUT_IMAGE_POINTS_2, imagePoints2);
            m_operator->setParameter(StereoCalibrate::PARAMETER_CAMERA_MATRIX_1, cameraMatrix1);
            m_operator->setParameter(StereoCalibrate::PARAMETER_DIST_COEFFS_1, distCoeffs1);
            m_operator->setParameter(StereoCalibrate::PARAMETER_CAMERA_MATRIX_2, cameraMatrix2);
            m_operator->setParameter(StereoCalibrate::PARAMETER_DIST_COEFFS_2, distCoeffs2);
            m_operator->setParameter(StereoCalibrate::PARAMETER_IMAGE_SIZE_X, imageSizeX);
            m_operator->setParameter(StereoCalibrate::PARAMETER_IMAGE_SIZE_Y, imageSizeY);
            
            runtime::DataContainer rvecResult = m_operator->getOutputData(StereoCalibrate::OUTPUT_RVEC);
            runtime::DataContainer tvecResult = m_operator->getOutputData(StereoCalibrate::OUTPUT_TVEC);
            
            runtime::ReadAccess rvecAccess(rvecResult);
            cvsupport::Matrix::save("StereoCalibrateTest_testExtrinsics0_rvec.npy", rvecAccess.get<runtime::Matrix>());
            runtime::ReadAccess tvecAccess(tvecResult);
            cvsupport::Matrix::save("StereoCalibrateTest_testExtrinsics0_tvec.npy", tvecAccess.get<runtime::Matrix>());
        }
        
        void StereoCalibrateTest::testIntrinsics0()
        {
            m_operator->setParameter(StereoCalibrate::PARAMETER_DATA_FLOW, runtime::Enum(StereoCalibrate::INTRINSICS));
            m_operator->initialize();
            m_operator->activate();
            
            runtime::Data* objectPointsItem = 0;
            std::vector<runtime::Data*> objectPointsVector;
            objectPointsItem = new cvsupport::Matrix("chess_corners_3d.npy");
            objectPointsVector.push_back(objectPointsItem);
            objectPointsItem = new cvsupport::Matrix("chess_corners_3d.npy");
            objectPointsVector.push_back(objectPointsItem);
            objectPointsItem = new cvsupport::Matrix("chess_corners_3d.npy");
            objectPointsVector.push_back(objectPointsItem);
            objectPointsItem = new cvsupport::Matrix("chess_corners_3d.npy");
            objectPointsVector.push_back(objectPointsItem);
            objectPointsItem = new cvsupport::Matrix("chess_corners_3d.npy");
            objectPointsVector.push_back(objectPointsItem);
            objectPointsItem = new cvsupport::Matrix("chess_corners_3d.npy");
            objectPointsVector.push_back(objectPointsItem);
            objectPointsItem = new cvsupport::Matrix("chess_corners_3d.npy");
            objectPointsVector.push_back(objectPointsItem);
            runtime::DataContainer objectPoints(new runtime::List(objectPointsVector));
            
            runtime::Data* imagePoints1Item = 0;
            std::vector<runtime::Data*> imagePoints1Vector;
            imagePoints1Item = new cvsupport::Matrix("chess_corners_1.npy");
            imagePoints1Vector.push_back(imagePoints1Item);
            imagePoints1Item = new cvsupport::Matrix("chess_corners_2.npy");
            imagePoints1Vector.push_back(imagePoints1Item);
            imagePoints1Item = new cvsupport::Matrix("chess_corners_3.npy");
            imagePoints1Vector.push_back(imagePoints1Item);
            imagePoints1Item = new cvsupport::Matrix("chess_corners_4.npy");
            imagePoints1Vector.push_back(imagePoints1Item);
            imagePoints1Item = new cvsupport::Matrix("chess_corners_5.npy");
            imagePoints1Vector.push_back(imagePoints1Item);
            imagePoints1Item = new cvsupport::Matrix("chess_corners_6.npy");
            imagePoints1Vector.push_back(imagePoints1Item);
            imagePoints1Item = new cvsupport::Matrix("chess_corners_7.npy");
            imagePoints1Vector.push_back(imagePoints1Item);
            runtime::DataContainer imagePoints1(new runtime::List(imagePoints1Vector));
            
            runtime::Data* imagePoints2Item = 0;
            std::vector<runtime::Data*> imagePoints2Vector;
            imagePoints2Item = new cvsupport::Matrix("chess_corners_1.npy");
            imagePoints2Vector.push_back(imagePoints2Item);
            imagePoints2Item = new cvsupport::Matrix("chess_corners_2.npy");
            imagePoints2Vector.push_back(imagePoints2Item);
            imagePoints2Item = new cvsupport::Matrix("chess_corners_3.npy");
            imagePoints2Vector.push_back(imagePoints2Item);
            imagePoints2Item = new cvsupport::Matrix("chess_corners_4.npy");
            imagePoints2Vector.push_back(imagePoints2Item);
            imagePoints2Item = new cvsupport::Matrix("chess_corners_5.npy");
            imagePoints2Vector.push_back(imagePoints2Item);
            imagePoints2Item = new cvsupport::Matrix("chess_corners_6.npy");
            imagePoints2Vector.push_back(imagePoints2Item);
            imagePoints2Item = new cvsupport::Matrix("chess_corners_7.npy");
            imagePoints2Vector.push_back(imagePoints2Item);
            runtime::DataContainer imagePoints2(new runtime::List(imagePoints2Vector));
            
            runtime::UInt32 imageSizeX(320);
            runtime::UInt32 imageSizeY(240);
            
            m_operator->setInputData(StereoCalibrate::INPUT_OBJECT_POINTS, objectPoints);
            m_operator->setInputData(StereoCalibrate::INPUT_IMAGE_POINTS_1, imagePoints1);
            m_operator->setInputData(StereoCalibrate::INPUT_IMAGE_POINTS_2, imagePoints2);
            m_operator->setParameter(StereoCalibrate::PARAMETER_IMAGE_SIZE_X, imageSizeX);
            m_operator->setParameter(StereoCalibrate::PARAMETER_IMAGE_SIZE_Y, imageSizeY);
            
            runtime::DataContainer cameraMatrix1ArgResult = m_operator->getOutputData(StereoCalibrate::OUTPUT_CAMERA_MATRIX_1_ARG);
            runtime::DataContainer distCoeffs1ArgResult = m_operator->getOutputData(StereoCalibrate::OUTPUT_DIST_COEFFS_1_ARG);
            runtime::DataContainer cameraMatrix2ArgResult = m_operator->getOutputData(StereoCalibrate::OUTPUT_CAMERA_MATRIX_2_ARG);
            runtime::DataContainer distCoeffs2ArgResult = m_operator->getOutputData(StereoCalibrate::OUTPUT_DIST_COEFFS_2_ARG);
            runtime::DataContainer rvecResult = m_operator->getOutputData(StereoCalibrate::OUTPUT_RVEC);
            runtime::DataContainer tvecResult = m_operator->getOutputData(StereoCalibrate::OUTPUT_TVEC);
            
            runtime::ReadAccess cameraMatrix1ArgAccess(cameraMatrix1ArgResult);
            cvsupport::Matrix::save("StereoCalibrateTest_testIntrinsics0_cameraMatrix1Arg.npy", cameraMatrix1ArgAccess.get<runtime::Matrix>());
            runtime::ReadAccess distCoeffs1ArgAccess(distCoeffs1ArgResult);
            cvsupport::Matrix::save("StereoCalibrateTest_testIntrinsics0_distCoeffs1Arg.npy", distCoeffs1ArgAccess.get<runtime::Matrix>());
            runtime::ReadAccess cameraMatrix2ArgAccess(cameraMatrix2ArgResult);
            cvsupport::Matrix::save("StereoCalibrateTest_testIntrinsics0_cameraMatrix2Arg.npy", cameraMatrix2ArgAccess.get<runtime::Matrix>());
            runtime::ReadAccess distCoeffs2ArgAccess(distCoeffs2ArgResult);
            cvsupport::Matrix::save("StereoCalibrateTest_testIntrinsics0_distCoeffs2Arg.npy", distCoeffs2ArgAccess.get<runtime::Matrix>());
            runtime::ReadAccess rvecAccess(rvecResult);
            cvsupport::Matrix::save("StereoCalibrateTest_testIntrinsics0_rvec.npy", rvecAccess.get<runtime::Matrix>());
            runtime::ReadAccess tvecAccess(tvecResult);
            cvsupport::Matrix::save("StereoCalibrateTest_testIntrinsics0_tvec.npy", tvecAccess.get<runtime::Matrix>());
        }
        
    } // cvcalib3d
} // stromx

