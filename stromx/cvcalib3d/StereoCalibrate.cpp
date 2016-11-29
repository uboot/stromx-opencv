#include "stromx/cvcalib3d/StereoCalibrate.h"

#include "stromx/cvcalib3d/Locale.h"
#include "stromx/cvcalib3d/Utility.h"
#include <stromx/cvsupport/Image.h>
#include <stromx/cvsupport/Matrix.h>
#include <stromx/cvsupport/Utilities.h>
#include <stromx/runtime/DataContainer.h>
#include <stromx/runtime/DataProvider.h>
#include <stromx/runtime/Id2DataComposite.h>
#include <stromx/runtime/Id2DataPair.h>
#include <stromx/runtime/ReadAccess.h>
#include <stromx/runtime/VariantComposite.h>
#include <stromx/runtime/WriteAccess.h>
#include <opencv2/calib3d/calib3d.hpp>

namespace stromx
{
    namespace cvcalib3d
    {
        const std::string StereoCalibrate::PACKAGE(STROMX_CVCALIB3D_PACKAGE_NAME);
        const runtime::Version StereoCalibrate::VERSION(STROMX_CVCALIB3D_VERSION_MAJOR, STROMX_CVCALIB3D_VERSION_MINOR, STROMX_CVCALIB3D_VERSION_PATCH);
        const std::string StereoCalibrate::TYPE("StereoCalibrate");
        
        StereoCalibrate::StereoCalibrate()
          : runtime::OperatorKernel(TYPE, PACKAGE, VERSION, setupInitParameters()),
            m_cameraMatrix1(cvsupport::Matrix::zeros(3, 3, runtime::Matrix::FLOAT_32)),
            m_cameraMatrix2(cvsupport::Matrix::zeros(3, 3, runtime::Matrix::FLOAT_32)),
            m_distCoeffs1(cvsupport::Matrix::zeros(1, 5, runtime::Matrix::FLOAT_32)),
            m_distCoeffs2(cvsupport::Matrix::zeros(1, 5, runtime::Matrix::FLOAT_32)),
            m_imageSizeX(640),
            m_imageSizeY(480),
            m_dataFlow()
        {
        }
        
        const runtime::DataRef StereoCalibrate::getParameter(unsigned int id) const
        {
            switch(id)
            {
            case PARAMETER_CAMERA_MATRIX_1:
                return m_cameraMatrix1;
            case PARAMETER_CAMERA_MATRIX_2:
                return m_cameraMatrix2;
            case PARAMETER_DIST_COEFFS_1:
                return m_distCoeffs1;
            case PARAMETER_DIST_COEFFS_2:
                return m_distCoeffs2;
            case PARAMETER_IMAGE_SIZE_X:
                return m_imageSizeX;
            case PARAMETER_IMAGE_SIZE_Y:
                return m_imageSizeY;
            case PARAMETER_DATA_FLOW:
                return m_dataFlow;
            default:
                throw runtime::WrongParameterId(id, *this);
            }
        }
        
        void StereoCalibrate::setParameter(unsigned int id, const runtime::Data& value)
        {
            try
            {
                switch(id)
                {
                case PARAMETER_CAMERA_MATRIX_1:
                    {
                        const runtime::Matrix & castedValue = runtime::data_cast<runtime::Matrix>(value);
                        if(! castedValue.variant().isVariant(runtime::Variant::FLOAT_MATRIX))
                        {
                            throw runtime::WrongParameterType(parameter(id), *this);
                        }
                        cvsupport::checkMatrixValue(castedValue, m_cameraMatrix1Parameter, *this);
                        m_cameraMatrix1 = castedValue;
                    }
                    break;
                case PARAMETER_CAMERA_MATRIX_2:
                    {
                        const runtime::Matrix & castedValue = runtime::data_cast<runtime::Matrix>(value);
                        if(! castedValue.variant().isVariant(runtime::Variant::FLOAT_MATRIX))
                        {
                            throw runtime::WrongParameterType(parameter(id), *this);
                        }
                        cvsupport::checkMatrixValue(castedValue, m_cameraMatrix2Parameter, *this);
                        m_cameraMatrix2 = castedValue;
                    }
                    break;
                case PARAMETER_DIST_COEFFS_1:
                    {
                        const runtime::Matrix & castedValue = runtime::data_cast<runtime::Matrix>(value);
                        if(! castedValue.variant().isVariant(runtime::Variant::FLOAT_MATRIX))
                        {
                            throw runtime::WrongParameterType(parameter(id), *this);
                        }
                        cvsupport::checkMatrixValue(castedValue, m_distCoeffs1Parameter, *this);
                        m_distCoeffs1 = castedValue;
                    }
                    break;
                case PARAMETER_DIST_COEFFS_2:
                    {
                        const runtime::Matrix & castedValue = runtime::data_cast<runtime::Matrix>(value);
                        if(! castedValue.variant().isVariant(runtime::Variant::FLOAT_MATRIX))
                        {
                            throw runtime::WrongParameterType(parameter(id), *this);
                        }
                        cvsupport::checkMatrixValue(castedValue, m_distCoeffs2Parameter, *this);
                        m_distCoeffs2 = castedValue;
                    }
                    break;
                case PARAMETER_IMAGE_SIZE_X:
                    {
                        const runtime::UInt32 & castedValue = runtime::data_cast<runtime::UInt32>(value);
                        if(! castedValue.variant().isVariant(runtime::Variant::UINT_32))
                        {
                            throw runtime::WrongParameterType(parameter(id), *this);
                        }
                        cvsupport::checkNumericValue(castedValue, m_imageSizeXParameter, *this);
                        m_imageSizeX = castedValue;
                    }
                    break;
                case PARAMETER_IMAGE_SIZE_Y:
                    {
                        const runtime::UInt32 & castedValue = runtime::data_cast<runtime::UInt32>(value);
                        if(! castedValue.variant().isVariant(runtime::Variant::UINT_32))
                        {
                            throw runtime::WrongParameterType(parameter(id), *this);
                        }
                        cvsupport::checkNumericValue(castedValue, m_imageSizeYParameter, *this);
                        m_imageSizeY = castedValue;
                    }
                    break;
                case PARAMETER_DATA_FLOW:
                    {
                        const runtime::Enum & castedValue = runtime::data_cast<runtime::Enum>(value);
                        if(! castedValue.variant().isVariant(runtime::Variant::ENUM))
                        {
                            throw runtime::WrongParameterType(parameter(id), *this);
                        }
                        cvsupport::checkEnumValue(castedValue, m_dataFlowParameter, *this);
                        m_dataFlow = castedValue;
                    }
                    break;
                default:
                    throw runtime::WrongParameterId(id, *this);
                }
            }
            catch(runtime::BadCast&)
            {
                throw runtime::WrongParameterType(parameter(id), *this);
            }
        }
        
        const std::vector<const runtime::Parameter*> StereoCalibrate::setupInitParameters()
        {
            std::vector<const runtime::Parameter*> parameters;
            
            m_dataFlowParameter = new runtime::EnumParameter(PARAMETER_DATA_FLOW);
            m_dataFlowParameter->setAccessMode(runtime::Parameter::NONE_WRITE);
            m_dataFlowParameter->setTitle(L_("Data flow"));
            m_dataFlowParameter->add(runtime::EnumDescription(runtime::Enum(EXTRINSICS), L_("Only extrinsics")));
            m_dataFlowParameter->add(runtime::EnumDescription(runtime::Enum(INTRINSICS), L_("Extrinsics and intrinsics")));
            parameters.push_back(m_dataFlowParameter);
            
            return parameters;
        }
        
        const std::vector<const runtime::Parameter*> StereoCalibrate::setupParameters()
        {
            std::vector<const runtime::Parameter*> parameters;
            
            switch(int(m_dataFlow))
            {
            case(EXTRINSICS):
                {
                    m_cameraMatrix1Parameter = new runtime::MatrixParameter(PARAMETER_CAMERA_MATRIX_1, runtime::Variant::FLOAT_MATRIX);
                    m_cameraMatrix1Parameter->setAccessMode(runtime::Parameter::ACTIVATED_WRITE);
                    m_cameraMatrix1Parameter->setTitle(L_("Camera matrix 1"));
                    m_cameraMatrix1Parameter->setRows(3);
                    m_cameraMatrix1Parameter->setCols(3);
                    parameters.push_back(m_cameraMatrix1Parameter);
                    
                    m_distCoeffs1Parameter = new runtime::MatrixParameter(PARAMETER_DIST_COEFFS_1, runtime::Variant::FLOAT_MATRIX);
                    m_distCoeffs1Parameter->setAccessMode(runtime::Parameter::ACTIVATED_WRITE);
                    m_distCoeffs1Parameter->setTitle(L_("Distortion coefficients 1"));
                    m_distCoeffs1Parameter->setRows(1);
                    m_distCoeffs1Parameter->setCols(5);
                    parameters.push_back(m_distCoeffs1Parameter);
                    
                    m_cameraMatrix2Parameter = new runtime::MatrixParameter(PARAMETER_CAMERA_MATRIX_2, runtime::Variant::FLOAT_MATRIX);
                    m_cameraMatrix2Parameter->setAccessMode(runtime::Parameter::ACTIVATED_WRITE);
                    m_cameraMatrix2Parameter->setTitle(L_("Camera matrix 2"));
                    m_cameraMatrix2Parameter->setRows(3);
                    m_cameraMatrix2Parameter->setCols(3);
                    parameters.push_back(m_cameraMatrix2Parameter);
                    
                    m_distCoeffs2Parameter = new runtime::MatrixParameter(PARAMETER_DIST_COEFFS_2, runtime::Variant::FLOAT_MATRIX);
                    m_distCoeffs2Parameter->setAccessMode(runtime::Parameter::ACTIVATED_WRITE);
                    m_distCoeffs2Parameter->setTitle(L_("Distortion coefficients 2"));
                    m_distCoeffs2Parameter->setRows(1);
                    m_distCoeffs2Parameter->setCols(5);
                    parameters.push_back(m_distCoeffs2Parameter);
                    
                    m_imageSizeXParameter = new runtime::NumericParameter<runtime::UInt32>(PARAMETER_IMAGE_SIZE_X);
                    m_imageSizeXParameter->setAccessMode(runtime::Parameter::ACTIVATED_WRITE);
                    m_imageSizeXParameter->setTitle(L_("Sensor size X"));
                    m_imageSizeXParameter->setMin(runtime::UInt32(1));
                    parameters.push_back(m_imageSizeXParameter);
                    
                    m_imageSizeYParameter = new runtime::NumericParameter<runtime::UInt32>(PARAMETER_IMAGE_SIZE_Y);
                    m_imageSizeYParameter->setAccessMode(runtime::Parameter::ACTIVATED_WRITE);
                    m_imageSizeYParameter->setTitle(L_("Sensor size Y"));
                    m_imageSizeYParameter->setMin(runtime::UInt32(1));
                    parameters.push_back(m_imageSizeYParameter);
                    
                }
                break;
            case(INTRINSICS):
                {
                    m_imageSizeXParameter = new runtime::NumericParameter<runtime::UInt32>(PARAMETER_IMAGE_SIZE_X);
                    m_imageSizeXParameter->setAccessMode(runtime::Parameter::ACTIVATED_WRITE);
                    m_imageSizeXParameter->setTitle(L_("Sensor size X"));
                    m_imageSizeXParameter->setMin(runtime::UInt32(1));
                    parameters.push_back(m_imageSizeXParameter);
                    
                    m_imageSizeYParameter = new runtime::NumericParameter<runtime::UInt32>(PARAMETER_IMAGE_SIZE_Y);
                    m_imageSizeYParameter->setAccessMode(runtime::Parameter::ACTIVATED_WRITE);
                    m_imageSizeYParameter->setTitle(L_("Sensor size Y"));
                    m_imageSizeYParameter->setMin(runtime::UInt32(1));
                    parameters.push_back(m_imageSizeYParameter);
                    
                }
                break;
            }
            
            return parameters;
        }
        
        const std::vector<const runtime::Input*> StereoCalibrate::setupInputs()
        {
            std::vector<const runtime::Input*> inputs;
            
            switch(int(m_dataFlow))
            {
            case(EXTRINSICS):
                {
                    m_objectPointsDescription = new runtime::Input(INPUT_OBJECT_POINTS, runtime::Variant::LIST);
                    m_objectPointsDescription->setTitle(L_("Object points"));
                    m_objectPointsDescription->setVisualization(runtime::Visualization::POINT);
                    inputs.push_back(m_objectPointsDescription);
                    
                    m_imagePoints1Description = new runtime::Input(INPUT_IMAGE_POINTS_1, runtime::Variant::LIST);
                    m_imagePoints1Description->setTitle(L_("Image points camera 1"));
                    m_imagePoints1Description->setVisualization(runtime::Visualization::POINT);
                    inputs.push_back(m_imagePoints1Description);
                    
                    m_imagePoints2Description = new runtime::Input(INPUT_IMAGE_POINTS_2, runtime::Variant::LIST);
                    m_imagePoints2Description->setTitle(L_("Image points 2"));
                    m_imagePoints2Description->setVisualization(runtime::Visualization::POINT);
                    inputs.push_back(m_imagePoints2Description);
                    
                }
                break;
            case(INTRINSICS):
                {
                    m_objectPointsDescription = new runtime::Input(INPUT_OBJECT_POINTS, runtime::Variant::LIST);
                    m_objectPointsDescription->setTitle(L_("Object points"));
                    m_objectPointsDescription->setVisualization(runtime::Visualization::POINT);
                    inputs.push_back(m_objectPointsDescription);
                    
                    m_imagePoints1Description = new runtime::Input(INPUT_IMAGE_POINTS_1, runtime::Variant::LIST);
                    m_imagePoints1Description->setTitle(L_("Image points camera 1"));
                    m_imagePoints1Description->setVisualization(runtime::Visualization::POINT);
                    inputs.push_back(m_imagePoints1Description);
                    
                    m_imagePoints2Description = new runtime::Input(INPUT_IMAGE_POINTS_2, runtime::Variant::LIST);
                    m_imagePoints2Description->setTitle(L_("Image points 2"));
                    m_imagePoints2Description->setVisualization(runtime::Visualization::POINT);
                    inputs.push_back(m_imagePoints2Description);
                    
                }
                break;
            }
            
            return inputs;
        }
        
        const std::vector<const runtime::Output*> StereoCalibrate::setupOutputs()
        {
            std::vector<const runtime::Output*> outputs;
            
            switch(int(m_dataFlow))
            {
            case(EXTRINSICS):
                {
                    runtime::Output* rvec = new runtime::Output(OUTPUT_RVEC, runtime::Variant::FLOAT_64_MATRIX);
                    rvec->setTitle(L_("Rotation"));
                    rvec->setRows(3);
                    rvec->setCols(1);
                    outputs.push_back(rvec);
                    
                    runtime::Output* tvec = new runtime::Output(OUTPUT_TVEC, runtime::Variant::FLOAT_64_MATRIX);
                    tvec->setTitle(L_("Translation"));
                    tvec->setRows(3);
                    tvec->setCols(1);
                    outputs.push_back(tvec);
                    
                }
                break;
            case(INTRINSICS):
                {
                    runtime::Output* cameraMatrix1Arg = new runtime::Output(OUTPUT_CAMERA_MATRIX_1_ARG, runtime::Variant::FLOAT_64_MATRIX);
                    cameraMatrix1Arg->setTitle(L_("Camera matrix 1"));
                    cameraMatrix1Arg->setRows(3);
                    cameraMatrix1Arg->setCols(3);
                    outputs.push_back(cameraMatrix1Arg);
                    
                    runtime::Output* distCoeffs1Arg = new runtime::Output(OUTPUT_DIST_COEFFS_1_ARG, runtime::Variant::FLOAT_64_MATRIX);
                    distCoeffs1Arg->setTitle(L_("Distortion coefficients 1"));
                    distCoeffs1Arg->setRows(1);
                    distCoeffs1Arg->setCols(5);
                    outputs.push_back(distCoeffs1Arg);
                    
                    runtime::Output* cameraMatrix2Arg = new runtime::Output(OUTPUT_CAMERA_MATRIX_2_ARG, runtime::Variant::FLOAT_64_MATRIX);
                    cameraMatrix2Arg->setTitle(L_("Camera matrix 2"));
                    cameraMatrix2Arg->setRows(3);
                    cameraMatrix2Arg->setCols(3);
                    outputs.push_back(cameraMatrix2Arg);
                    
                    runtime::Output* distCoeffs2Arg = new runtime::Output(OUTPUT_DIST_COEFFS_2_ARG, runtime::Variant::FLOAT_64_MATRIX);
                    distCoeffs2Arg->setTitle(L_("Distortion coefficients 2"));
                    distCoeffs2Arg->setRows(1);
                    distCoeffs2Arg->setCols(5);
                    outputs.push_back(distCoeffs2Arg);
                    
                    runtime::Output* rvec = new runtime::Output(OUTPUT_RVEC, runtime::Variant::FLOAT_64_MATRIX);
                    rvec->setTitle(L_("Rotation"));
                    rvec->setRows(3);
                    rvec->setCols(1);
                    outputs.push_back(rvec);
                    
                    runtime::Output* tvec = new runtime::Output(OUTPUT_TVEC, runtime::Variant::FLOAT_64_MATRIX);
                    tvec->setTitle(L_("Translation"));
                    tvec->setRows(3);
                    tvec->setCols(1);
                    outputs.push_back(tvec);
                    
                }
                break;
            }
            
            return outputs;
        }
        
        void StereoCalibrate::initialize()
        {
            runtime::OperatorKernel::initialize(setupInputs(), setupOutputs(), setupParameters());
        }
        
        void StereoCalibrate::execute(runtime::DataProvider & provider)
        {
            switch(int(m_dataFlow))
            {
            case(EXTRINSICS):
                {
                    runtime::Id2DataPair objectPointsInMapper(INPUT_OBJECT_POINTS);
                    runtime::Id2DataPair imagePoints1InMapper(INPUT_IMAGE_POINTS_1);
                    runtime::Id2DataPair imagePoints2InMapper(INPUT_IMAGE_POINTS_2);
                    
                    provider.receiveInputData(objectPointsInMapper && imagePoints1InMapper && imagePoints2InMapper);
                    
                    const runtime::Data* objectPointsData = 0;
                    const runtime::Data* imagePoints1Data = 0;
                    const runtime::Data* imagePoints2Data = 0;
                    
                    runtime::ReadAccess objectPointsReadAccess;
                    runtime::ReadAccess imagePoints1ReadAccess;
                    runtime::ReadAccess imagePoints2ReadAccess;
                    
                    objectPointsReadAccess = runtime::ReadAccess(objectPointsInMapper.data());
                    objectPointsData = &objectPointsReadAccess.get();
                    imagePoints1ReadAccess = runtime::ReadAccess(imagePoints1InMapper.data());
                    imagePoints1Data = &imagePoints1ReadAccess.get();
                    imagePoints2ReadAccess = runtime::ReadAccess(imagePoints2InMapper.data());
                    imagePoints2Data = &imagePoints2ReadAccess.get();
                    
                    if(! objectPointsData->variant().isVariant(m_objectPointsDescription->variant()))
                    {
                        throw runtime::InputError(INPUT_OBJECT_POINTS, *this, "Wrong input data variant.");
                    }
                    if(! imagePoints1Data->variant().isVariant(m_imagePoints1Description->variant()))
                    {
                        throw runtime::InputError(INPUT_IMAGE_POINTS_1, *this, "Wrong input data variant.");
                    }
                    if(! imagePoints2Data->variant().isVariant(m_imagePoints2Description->variant()))
                    {
                        throw runtime::InputError(INPUT_IMAGE_POINTS_2, *this, "Wrong input data variant.");
                    }
                    
                    const runtime::List* objectPointsCastedData = runtime::data_cast<runtime::List>(objectPointsData);
                    const runtime::List* imagePoints1CastedData = runtime::data_cast<runtime::List>(imagePoints1Data);
                    const runtime::List* imagePoints2CastedData = runtime::data_cast<runtime::List>(imagePoints2Data);
                    
                    if (objectPointsCastedData->content().size() != imagePoints1CastedData->content().size())
                    {
                        throw runtime::InputError(INPUT_OBJECT_POINTS, *this, "Object and image point (1) lists must have the same size.");
                    }
                    if (objectPointsCastedData->content().size() != imagePoints2CastedData->content().size())
                    {
                        throw runtime::InputError(INPUT_OBJECT_POINTS, *this, "Object and image point (2) lists must have the same size.");
                    }
                    
                    std::vector<cv::Mat> objectPointsCvData = cvsupport::getOpenCvMatVector(*objectPointsCastedData);
                    std::vector<cv::Mat> imagePoints1CvData = cvsupport::getOpenCvMatVector(*imagePoints1CastedData);
                    std::vector<cv::Mat> imagePoints2CvData = cvsupport::getOpenCvMatVector(*imagePoints2CastedData);
                    cv::Mat cameraMatrix1CvData = cvsupport::getOpenCvMat(m_cameraMatrix1);
                    cv::Mat distCoeffs1CvData = cvsupport::getOpenCvMat(m_distCoeffs1);
                    cv::Mat cameraMatrix2CvData = cvsupport::getOpenCvMat(m_cameraMatrix2);
                    cv::Mat distCoeffs2CvData = cvsupport::getOpenCvMat(m_distCoeffs2);
                    int imageSizeXCvData = int(m_imageSizeX);
                    int imageSizeYCvData = int(m_imageSizeY);
                    cv::Mat rvecCvData;
                    cv::Mat tvecCvData;
                    
                    cv::stereoCalibrate(objectPointsCvData, imagePoints1CvData, imagePoints2CvData, cameraMatrix1CvData, distCoeffs1CvData, cameraMatrix2CvData, distCoeffs2CvData, cv::Size(imageSizeXCvData, imageSizeYCvData), rvecCvData, tvecCvData, cv::Mat(3, 3, CV_64F), cv::Mat(3, 3, CV_64F));
                    
                    runtime::Matrix* rvecCastedData = new cvsupport::Matrix(rvecCvData);
                    runtime::DataContainer rvecOutContainer = runtime::DataContainer(rvecCastedData);
                    runtime::Id2DataPair rvecOutMapper(OUTPUT_RVEC, rvecOutContainer);
                    runtime::Matrix* tvecCastedData = new cvsupport::Matrix(tvecCvData);
                    runtime::DataContainer tvecOutContainer = runtime::DataContainer(tvecCastedData);
                    runtime::Id2DataPair tvecOutMapper(OUTPUT_TVEC, tvecOutContainer);
                    
                    provider.sendOutputData(rvecOutMapper && tvecOutMapper);
                }
                break;
            case(INTRINSICS):
                {
                    runtime::Id2DataPair objectPointsInMapper(INPUT_OBJECT_POINTS);
                    runtime::Id2DataPair imagePoints1InMapper(INPUT_IMAGE_POINTS_1);
                    runtime::Id2DataPair imagePoints2InMapper(INPUT_IMAGE_POINTS_2);
                    
                    provider.receiveInputData(objectPointsInMapper && imagePoints1InMapper && imagePoints2InMapper);
                    
                    const runtime::Data* objectPointsData = 0;
                    const runtime::Data* imagePoints1Data = 0;
                    const runtime::Data* imagePoints2Data = 0;
                    
                    runtime::ReadAccess objectPointsReadAccess;
                    runtime::ReadAccess imagePoints1ReadAccess;
                    runtime::ReadAccess imagePoints2ReadAccess;
                    
                    objectPointsReadAccess = runtime::ReadAccess(objectPointsInMapper.data());
                    objectPointsData = &objectPointsReadAccess.get();
                    imagePoints1ReadAccess = runtime::ReadAccess(imagePoints1InMapper.data());
                    imagePoints1Data = &imagePoints1ReadAccess.get();
                    imagePoints2ReadAccess = runtime::ReadAccess(imagePoints2InMapper.data());
                    imagePoints2Data = &imagePoints2ReadAccess.get();
                    
                    if(! objectPointsData->variant().isVariant(m_objectPointsDescription->variant()))
                    {
                        throw runtime::InputError(INPUT_OBJECT_POINTS, *this, "Wrong input data variant.");
                    }
                    if(! imagePoints1Data->variant().isVariant(m_imagePoints1Description->variant()))
                    {
                        throw runtime::InputError(INPUT_IMAGE_POINTS_1, *this, "Wrong input data variant.");
                    }
                    if(! imagePoints2Data->variant().isVariant(m_imagePoints2Description->variant()))
                    {
                        throw runtime::InputError(INPUT_IMAGE_POINTS_2, *this, "Wrong input data variant.");
                    }
                    
                    const runtime::List* objectPointsCastedData = runtime::data_cast<runtime::List>(objectPointsData);
                    const runtime::List* imagePoints1CastedData = runtime::data_cast<runtime::List>(imagePoints1Data);
                    const runtime::List* imagePoints2CastedData = runtime::data_cast<runtime::List>(imagePoints2Data);
                    
                    if (objectPointsCastedData->content().size() != imagePoints1CastedData->content().size())
                    {
                        throw runtime::InputError(INPUT_OBJECT_POINTS, *this, "Object and image point (1) lists must have the same size.");
                    }
                    if (objectPointsCastedData->content().size() != imagePoints2CastedData->content().size())
                    {
                        throw runtime::InputError(INPUT_OBJECT_POINTS, *this, "Object and image point (2) lists must have the same size.");
                    }
                    
                    std::vector<cv::Mat> objectPointsCvData = cvsupport::getOpenCvMatVector(*objectPointsCastedData);
                    std::vector<cv::Mat> imagePoints1CvData = cvsupport::getOpenCvMatVector(*imagePoints1CastedData);
                    std::vector<cv::Mat> imagePoints2CvData = cvsupport::getOpenCvMatVector(*imagePoints2CastedData);
                    cv::Mat cameraMatrix1ArgCvData;
                    cv::Mat distCoeffs1ArgCvData;
                    cv::Mat cameraMatrix2ArgCvData;
                    cv::Mat distCoeffs2ArgCvData;
                    int imageSizeXCvData = int(m_imageSizeX);
                    int imageSizeYCvData = int(m_imageSizeY);
                    cv::Mat rvecCvData;
                    cv::Mat tvecCvData;
                    
                    cv::stereoCalibrate(objectPointsCvData, imagePoints1CvData, imagePoints2CvData, cameraMatrix1ArgCvData, distCoeffs1ArgCvData, cameraMatrix2ArgCvData, distCoeffs2ArgCvData, cv::Size(imageSizeXCvData, imageSizeYCvData), rvecCvData, tvecCvData, cv::Mat(3, 3, CV_64F), cv::Mat(3, 3, CV_64F));
                    
                    runtime::Matrix* cameraMatrix1ArgCastedData = new cvsupport::Matrix(cameraMatrix1ArgCvData);
                    runtime::DataContainer cameraMatrix1ArgOutContainer = runtime::DataContainer(cameraMatrix1ArgCastedData);
                    runtime::Id2DataPair cameraMatrix1ArgOutMapper(OUTPUT_CAMERA_MATRIX_1_ARG, cameraMatrix1ArgOutContainer);
                    runtime::Matrix* distCoeffs1ArgCastedData = new cvsupport::Matrix(distCoeffs1ArgCvData);
                    runtime::DataContainer distCoeffs1ArgOutContainer = runtime::DataContainer(distCoeffs1ArgCastedData);
                    runtime::Id2DataPair distCoeffs1ArgOutMapper(OUTPUT_DIST_COEFFS_1_ARG, distCoeffs1ArgOutContainer);
                    runtime::Matrix* cameraMatrix2ArgCastedData = new cvsupport::Matrix(cameraMatrix2ArgCvData);
                    runtime::DataContainer cameraMatrix2ArgOutContainer = runtime::DataContainer(cameraMatrix2ArgCastedData);
                    runtime::Id2DataPair cameraMatrix2ArgOutMapper(OUTPUT_CAMERA_MATRIX_2_ARG, cameraMatrix2ArgOutContainer);
                    runtime::Matrix* distCoeffs2ArgCastedData = new cvsupport::Matrix(distCoeffs2ArgCvData);
                    runtime::DataContainer distCoeffs2ArgOutContainer = runtime::DataContainer(distCoeffs2ArgCastedData);
                    runtime::Id2DataPair distCoeffs2ArgOutMapper(OUTPUT_DIST_COEFFS_2_ARG, distCoeffs2ArgOutContainer);
                    runtime::Matrix* rvecCastedData = new cvsupport::Matrix(rvecCvData);
                    runtime::DataContainer rvecOutContainer = runtime::DataContainer(rvecCastedData);
                    runtime::Id2DataPair rvecOutMapper(OUTPUT_RVEC, rvecOutContainer);
                    runtime::Matrix* tvecCastedData = new cvsupport::Matrix(tvecCvData);
                    runtime::DataContainer tvecOutContainer = runtime::DataContainer(tvecCastedData);
                    runtime::Id2DataPair tvecOutMapper(OUTPUT_TVEC, tvecOutContainer);
                    
                    provider.sendOutputData(cameraMatrix1ArgOutMapper && distCoeffs1ArgOutMapper && cameraMatrix2ArgOutMapper && distCoeffs2ArgOutMapper && rvecOutMapper && tvecOutMapper);
                }
                break;
            }
        }
        
    } // cvcalib3d
} // stromx

