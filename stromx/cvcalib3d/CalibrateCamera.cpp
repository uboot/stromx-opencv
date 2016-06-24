#include "stromx/cvcalib3d/CalibrateCamera.h"

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
        const std::string CalibrateCamera::PACKAGE(STROMX_CVCALIB3D_PACKAGE_NAME);
        const runtime::Version CalibrateCamera::VERSION(STROMX_CVCALIB3D_VERSION_MAJOR, STROMX_CVCALIB3D_VERSION_MINOR, STROMX_CVCALIB3D_VERSION_PATCH);
        const std::string CalibrateCamera::TYPE("CalibrateCamera");
        
        CalibrateCamera::CalibrateCamera()
          : runtime::OperatorKernel(TYPE, PACKAGE, VERSION, setupInitParameters()),
            m_imageSizeX(640),
            m_imageSizeY(480),
            m_dataFlow()
        {
        }
        
        const runtime::DataRef CalibrateCamera::getParameter(unsigned int id) const
        {
            switch(id)
            {
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
        
        void CalibrateCamera::setParameter(unsigned int id, const runtime::Data& value)
        {
            try
            {
                switch(id)
                {
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
        
        const std::vector<const runtime::Parameter*> CalibrateCamera::setupInitParameters()
        {
            std::vector<const runtime::Parameter*> parameters;
            
            return parameters;
        }
        
        const std::vector<const runtime::Parameter*> CalibrateCamera::setupParameters()
        {
            std::vector<const runtime::Parameter*> parameters;
            
            switch(int(m_dataFlow))
            {
            case(ALLOCATE):
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
        
        const std::vector<const runtime::Input*> CalibrateCamera::setupInputs()
        {
            std::vector<const runtime::Input*> inputs;
            
            switch(int(m_dataFlow))
            {
            case(ALLOCATE):
                {
                    m_objectPointsDescription = new runtime::Input(INPUT_OBJECT_POINTS, runtime::Variant::LIST);
                    m_objectPointsDescription->setTitle(L_("Object points"));
                    m_objectPointsDescription->setVisualization(runtime::Visualization::POINT);
                    inputs.push_back(m_objectPointsDescription);
                    
                    m_imagePointsDescription = new runtime::Input(INPUT_IMAGE_POINTS, runtime::Variant::LIST);
                    m_imagePointsDescription->setTitle(L_("Image points"));
                    m_imagePointsDescription->setVisualization(runtime::Visualization::POINT);
                    inputs.push_back(m_imagePointsDescription);
                    
                }
                break;
            }
            
            return inputs;
        }
        
        const std::vector<const runtime::Output*> CalibrateCamera::setupOutputs()
        {
            std::vector<const runtime::Output*> outputs;
            
            switch(int(m_dataFlow))
            {
            case(ALLOCATE):
                {
                    runtime::Output* cameraMatrix = new runtime::Output(OUTPUT_CAMERA_MATRIX, runtime::Variant::FLOAT_64_MATRIX);
                    cameraMatrix->setTitle(L_("Camera matrix"));
                    cameraMatrix->setRows(3);
                    cameraMatrix->setCols(3);
                    outputs.push_back(cameraMatrix);
                    
                    runtime::Output* distCoeffs = new runtime::Output(OUTPUT_DIST_COEFFS, runtime::Variant::FLOAT_64_MATRIX);
                    distCoeffs->setTitle(L_("Distortion coefficients"));
                    distCoeffs->setRows(1);
                    distCoeffs->setCols(5);
                    outputs.push_back(distCoeffs);
                    
                }
                break;
            }
            
            return outputs;
        }
        
        void CalibrateCamera::initialize()
        {
            runtime::OperatorKernel::initialize(setupInputs(), setupOutputs(), setupParameters());
        }
        
        void CalibrateCamera::execute(runtime::DataProvider & provider)
        {
            switch(int(m_dataFlow))
            {
            case(ALLOCATE):
                {
                    runtime::Id2DataPair objectPointsInMapper(INPUT_OBJECT_POINTS);
                    runtime::Id2DataPair imagePointsInMapper(INPUT_IMAGE_POINTS);
                    
                    provider.receiveInputData(objectPointsInMapper && imagePointsInMapper);
                    
                    const runtime::Data* objectPointsData = 0;
                    const runtime::Data* imagePointsData = 0;
                    
                    runtime::ReadAccess objectPointsReadAccess;
                    runtime::ReadAccess imagePointsReadAccess;
                    
                    objectPointsReadAccess = runtime::ReadAccess(objectPointsInMapper.data());
                    objectPointsData = &objectPointsReadAccess.get();
                    imagePointsReadAccess = runtime::ReadAccess(imagePointsInMapper.data());
                    imagePointsData = &imagePointsReadAccess.get();
                    
                    if(! objectPointsData->variant().isVariant(m_objectPointsDescription->variant()))
                    {
                        throw runtime::InputError(INPUT_OBJECT_POINTS, *this, "Wrong input data variant.");
                    }
                    if(! imagePointsData->variant().isVariant(m_imagePointsDescription->variant()))
                    {
                        throw runtime::InputError(INPUT_IMAGE_POINTS, *this, "Wrong input data variant.");
                    }
                    
                    const runtime::List* objectPointsCastedData = runtime::data_cast<runtime::List>(objectPointsData);
                    const runtime::List* imagePointsCastedData = runtime::data_cast<runtime::List>(imagePointsData);
                    
                    if (objectPointsCastedData->content().size() != imagePointsCastedData->content().size())
                    {
                        throw runtime::InputError(INPUT_OBJECT_POINTS, *this, "Object and image point lists must have the same size.");
                    }
                    
                    std::vector<cv::Mat> rvecs(objectPointsCastedData->content().size());
                    std::fill(rvecs.begin(), rvecs.end(), cv::Mat());
                    std::vector<cv::Mat> tvecs(objectPointsCastedData->content().size());
                    std::fill(tvecs.begin(), tvecs.end(), cv::Mat());
                    
                    std::vector<cv::Mat> objectPointsCvData = cvsupport::getOpenCvMatVector(*objectPointsCastedData);
                    std::vector<cv::Mat> imagePointsCvData = cvsupport::getOpenCvMatVector(*imagePointsCastedData);
                    int imageSizeXCvData = int(m_imageSizeX);
                    int imageSizeYCvData = int(m_imageSizeY);
                    cv::Mat cameraMatrixCvData;
                    cv::Mat distCoeffsCvData;
                    
                    cv::calibrateCamera(objectPointsCvData, imagePointsCvData, cv::Size(imageSizeXCvData, imageSizeYCvData), cameraMatrixCvData, distCoeffsCvData, rvecs, tvecs);
                    
                    runtime::Matrix* cameraMatrixCastedData = new cvsupport::Matrix(cameraMatrixCvData);
                    runtime::DataContainer cameraMatrixOutContainer = runtime::DataContainer(cameraMatrixCastedData);
                    runtime::Id2DataPair cameraMatrixOutMapper(OUTPUT_CAMERA_MATRIX, cameraMatrixOutContainer);
                    runtime::Matrix* distCoeffsCastedData = new cvsupport::Matrix(distCoeffsCvData);
                    runtime::DataContainer distCoeffsOutContainer = runtime::DataContainer(distCoeffsCastedData);
                    runtime::Id2DataPair distCoeffsOutMapper(OUTPUT_DIST_COEFFS, distCoeffsOutContainer);
                    
                    provider.sendOutputData(cameraMatrixOutMapper && distCoeffsOutMapper);
                }
                break;
            }
        }
        
    } // cvcalib3d
} // stromx

