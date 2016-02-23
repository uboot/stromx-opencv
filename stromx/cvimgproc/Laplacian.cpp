#include "stromx/cvimgproc/Laplacian.h"

#include "stromx/cvimgproc/Locale.h"
#include "stromx/cvimgproc/Utility.h"
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
#include <opencv2/imgproc/imgproc.hpp>

namespace stromx
{
    namespace cvimgproc
    {
        const std::string Laplacian::PACKAGE(STROMX_CVIMGPROC_PACKAGE_NAME);
        const runtime::Version Laplacian::VERSION(STROMX_CVIMGPROC_VERSION_MAJOR, STROMX_CVIMGPROC_VERSION_MINOR, STROMX_CVIMGPROC_VERSION_PATCH);
        const std::string Laplacian::TYPE("Laplacian");
        
        Laplacian::Laplacian()
          : runtime::OperatorKernel(TYPE, PACKAGE, VERSION, setupInitParameters()),
            m_ddepth(0),
            m_delta(0.0),
            m_ksize(3),
            m_scale(1.0),
            m_dataFlow()
        {
        }
        
        const runtime::DataRef Laplacian::getParameter(unsigned int id) const
        {
            switch(id)
            {
            case DDEPTH:
                return m_ddepth;
            case DELTA:
                return m_delta;
            case KSIZE:
                return m_ksize;
            case SCALE:
                return m_scale;
            case DATA_FLOW:
                return m_dataFlow;
            default:
                throw runtime::WrongParameterId(id, *this);
            }
        }
        
        void Laplacian::setParameter(unsigned int id, const runtime::Data& value)
        {
            try
            {
                switch(id)
                {
                case DDEPTH:
                    {
                        const runtime::Enum & castedValue = runtime::data_cast<runtime::Enum>(value);
                        if(! castedValue.variant().isVariant(runtime::Variant::ENUM))
                        {
                            throw runtime::WrongParameterType(parameter(id), *this);
                        }
                        cvsupport::checkEnumValue(castedValue, m_ddepthParameter, *this);
                        m_ddepth = castedValue;
                    }
                    break;
                case DELTA:
                    {
                        const runtime::Float64 & castedValue = runtime::data_cast<runtime::Float64>(value);
                        if(! castedValue.variant().isVariant(runtime::Variant::FLOAT_64))
                        {
                            throw runtime::WrongParameterType(parameter(id), *this);
                        }
                        cvsupport::checkNumericValue(castedValue, m_deltaParameter, *this);
                        m_delta = castedValue;
                    }
                    break;
                case KSIZE:
                    {
                        const runtime::UInt32 & castedValue = runtime::data_cast<runtime::UInt32>(value);
                        if(! castedValue.variant().isVariant(runtime::Variant::UINT_32))
                        {
                            throw runtime::WrongParameterType(parameter(id), *this);
                        }
                        cvsupport::checkNumericValue(castedValue, m_ksizeParameter, *this);
                        if(int(castedValue) % 2 == 0)
                            throw runtime::WrongParameterValue(*m_ksizeParameter, *this, "Only odd values are allowed");
                        m_ksize = castedValue;
                    }
                    break;
                case SCALE:
                    {
                        const runtime::Float64 & castedValue = runtime::data_cast<runtime::Float64>(value);
                        if(! castedValue.variant().isVariant(runtime::Variant::FLOAT_64))
                        {
                            throw runtime::WrongParameterType(parameter(id), *this);
                        }
                        cvsupport::checkNumericValue(castedValue, m_scaleParameter, *this);
                        m_scale = castedValue;
                    }
                    break;
                case DATA_FLOW:
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
        
        const std::vector<const runtime::Parameter*> Laplacian::setupInitParameters()
        {
            std::vector<const runtime::Parameter*> parameters;
            
            m_dataFlowParameter = new runtime::EnumParameter(DATA_FLOW);
            m_dataFlowParameter->setAccessMode(runtime::Parameter::NONE_WRITE);
            m_dataFlowParameter->setTitle(L_("Data flow"));
            m_dataFlowParameter->add(runtime::EnumDescription(runtime::Enum(MANUAL), L_("Manual")));
            m_dataFlowParameter->add(runtime::EnumDescription(runtime::Enum(ALLOCATE), L_("Allocate")));
            parameters.push_back(m_dataFlowParameter);
            
            return parameters;
        }
        
        const std::vector<const runtime::Parameter*> Laplacian::setupParameters()
        {
            std::vector<const runtime::Parameter*> parameters;
            
            switch(int(m_dataFlow))
            {
            case(MANUAL):
                {
                    m_ddepthParameter = new runtime::EnumParameter(DDEPTH);
                    m_ddepthParameter->setAccessMode(runtime::Parameter::ACTIVATED_WRITE);
                    m_ddepthParameter->setTitle(L_("Destination depth"));
                    m_ddepthParameter->add(runtime::EnumDescription(runtime::Enum(SAME), L_("Same as input")));
                    m_ddepthParameter->add(runtime::EnumDescription(runtime::Enum(DEPTH_8_BIT), L_("8-bit")));
                    m_ddepthParameter->add(runtime::EnumDescription(runtime::Enum(DEPTH_16_BIT), L_("16-bit")));
                    parameters.push_back(m_ddepthParameter);
                    
                    m_ksizeParameter = new runtime::NumericParameter<runtime::UInt32>(KSIZE);
                    m_ksizeParameter->setAccessMode(runtime::Parameter::ACTIVATED_WRITE);
                    m_ksizeParameter->setTitle(L_("Kernel size"));
                    m_ksizeParameter->setMin(runtime::UInt32(1));
                    m_ksizeParameter->setStep(runtime::UInt32(2));
                    parameters.push_back(m_ksizeParameter);
                    
                    m_scaleParameter = new runtime::NumericParameter<runtime::Float64>(SCALE);
                    m_scaleParameter->setAccessMode(runtime::Parameter::ACTIVATED_WRITE);
                    m_scaleParameter->setTitle(L_("Scale"));
                    parameters.push_back(m_scaleParameter);
                    
                    m_deltaParameter = new runtime::NumericParameter<runtime::Float64>(DELTA);
                    m_deltaParameter->setAccessMode(runtime::Parameter::ACTIVATED_WRITE);
                    m_deltaParameter->setTitle(L_("Delta"));
                    parameters.push_back(m_deltaParameter);
                    
                }
                break;
            case(ALLOCATE):
                {
                    m_ddepthParameter = new runtime::EnumParameter(DDEPTH);
                    m_ddepthParameter->setAccessMode(runtime::Parameter::ACTIVATED_WRITE);
                    m_ddepthParameter->setTitle(L_("Destination depth"));
                    m_ddepthParameter->add(runtime::EnumDescription(runtime::Enum(SAME), L_("Same as input")));
                    m_ddepthParameter->add(runtime::EnumDescription(runtime::Enum(DEPTH_8_BIT), L_("8-bit")));
                    m_ddepthParameter->add(runtime::EnumDescription(runtime::Enum(DEPTH_16_BIT), L_("16-bit")));
                    parameters.push_back(m_ddepthParameter);
                    
                    m_ksizeParameter = new runtime::NumericParameter<runtime::UInt32>(KSIZE);
                    m_ksizeParameter->setAccessMode(runtime::Parameter::ACTIVATED_WRITE);
                    m_ksizeParameter->setTitle(L_("Kernel size"));
                    m_ksizeParameter->setMin(runtime::UInt32(1));
                    m_ksizeParameter->setStep(runtime::UInt32(2));
                    parameters.push_back(m_ksizeParameter);
                    
                    m_scaleParameter = new runtime::NumericParameter<runtime::Float64>(SCALE);
                    m_scaleParameter->setAccessMode(runtime::Parameter::ACTIVATED_WRITE);
                    m_scaleParameter->setTitle(L_("Scale"));
                    parameters.push_back(m_scaleParameter);
                    
                    m_deltaParameter = new runtime::NumericParameter<runtime::Float64>(DELTA);
                    m_deltaParameter->setAccessMode(runtime::Parameter::ACTIVATED_WRITE);
                    m_deltaParameter->setTitle(L_("Delta"));
                    parameters.push_back(m_deltaParameter);
                    
                }
                break;
            }
            
            return parameters;
        }
        
        const std::vector<const runtime::Description*> Laplacian::setupInputs()
        {
            std::vector<const runtime::Description*> inputs;
            
            switch(int(m_dataFlow))
            {
            case(MANUAL):
                {
                    m_srcDescription = new runtime::Description(SRC, runtime::Variant::IMAGE);
                    m_srcDescription->setTitle(L_("Source"));
                    inputs.push_back(m_srcDescription);
                    
                    m_dstDescription = new runtime::Description(DST, runtime::Variant::IMAGE);
                    m_dstDescription->setTitle(L_("Destination"));
                    inputs.push_back(m_dstDescription);
                    
                }
                break;
            case(ALLOCATE):
                {
                    m_srcDescription = new runtime::Description(SRC, runtime::Variant::IMAGE);
                    m_srcDescription->setTitle(L_("Source"));
                    inputs.push_back(m_srcDescription);
                    
                }
                break;
            }
            
            return inputs;
        }
        
        const std::vector<const runtime::Description*> Laplacian::setupOutputs()
        {
            std::vector<const runtime::Description*> outputs;
            
            switch(int(m_dataFlow))
            {
            case(MANUAL):
                {
                    runtime::Description* dst = new runtime::Description(DST, runtime::Variant::IMAGE);
                    dst->setTitle(L_("Destination"));
                    outputs.push_back(dst);
                    
                }
                break;
            case(ALLOCATE):
                {
                    runtime::Description* dst = new runtime::Description(DST, runtime::Variant::IMAGE);
                    dst->setTitle(L_("Destination"));
                    outputs.push_back(dst);
                    
                }
                break;
            }
            
            return outputs;
        }
        
        void Laplacian::initialize()
        {
            runtime::OperatorKernel::initialize(setupInputs(), setupOutputs(), setupParameters());
        }
        
        void Laplacian::execute(runtime::DataProvider & provider)
        {
            switch(int(m_dataFlow))
            {
            case(MANUAL):
                {
                    runtime::Id2DataPair srcInMapper(SRC);
                    runtime::Id2DataPair dstInMapper(DST);
                    
                    provider.receiveInputData(srcInMapper && dstInMapper);
                    
                    const runtime::Data* srcData = 0;
                    runtime::Data* dstData = 0;
                    
                    runtime::ReadAccess srcReadAccess;
                    runtime::DataContainer inContainer = dstInMapper.data();
                    runtime::WriteAccess writeAccess(inContainer);
                    dstData = &writeAccess.get();
                    
                    if(srcInMapper.data() == inContainer)
                    {
                        throw runtime::InputError(SRC, *this, "Can not operate in place.");
                    }
                    else
                    {
                        srcReadAccess = runtime::ReadAccess(srcInMapper.data());
                        srcData = &srcReadAccess.get();
                    }
                    
                    if(! srcData->variant().isVariant(m_srcDescription->variant()))
                    {
                        throw runtime::InputError(SRC, *this, "Wrong input data variant.");
                    }
                    if(! dstData->variant().isVariant(m_dstDescription->variant()))
                    {
                        throw runtime::InputError(DST, *this, "Wrong input data variant.");
                    }
                    
                    const runtime::Image* srcCastedData = runtime::data_cast<runtime::Image>(srcData);
                    runtime::Image * dstCastedData = runtime::data_cast<runtime::Image>(dstData);
                    
                    runtime::Image::PixelType pixelType = cvsupport::computeOutPixelType(convertDdepth(m_ddepth), srcCastedData->pixelType());
                    unsigned int stride = runtime::Image::pixelSize(pixelType) * srcCastedData->width();
                    dstCastedData->initializeImage(srcCastedData->width(), srcCastedData->height(), stride, dstCastedData->data(), pixelType);
                    
                    cv::Mat srcCvData = cvsupport::getOpenCvMat(*srcCastedData);
                    cv::Mat dstCvData = cvsupport::getOpenCvMat(*dstCastedData);
                    int ddepthCvData = convertDdepth(m_ddepth);
                    int ksizeCvData = int(m_ksize);
                    double scaleCvData = double(m_scale);
                    double deltaCvData = double(m_delta);
                    
                    cv::Laplacian(srcCvData, dstCvData, ddepthCvData, ksizeCvData, scaleCvData, deltaCvData);
                    
                    runtime::DataContainer dstOutContainer = inContainer;
                    runtime::Id2DataPair dstOutMapper(DST, dstOutContainer);
                    
                    provider.sendOutputData(dstOutMapper);
                }
                break;
            case(ALLOCATE):
                {
                    runtime::Id2DataPair srcInMapper(SRC);
                    
                    provider.receiveInputData(srcInMapper);
                    
                    const runtime::Data* srcData = 0;
                    
                    runtime::ReadAccess srcReadAccess;
                    
                    srcReadAccess = runtime::ReadAccess(srcInMapper.data());
                    srcData = &srcReadAccess.get();
                    
                    if(! srcData->variant().isVariant(m_srcDescription->variant()))
                    {
                        throw runtime::InputError(SRC, *this, "Wrong input data variant.");
                    }
                    
                    const runtime::Image* srcCastedData = runtime::data_cast<runtime::Image>(srcData);
                    
                    cv::Mat srcCvData = cvsupport::getOpenCvMat(*srcCastedData);
                    cv::Mat dstCvData;
                    int ddepthCvData = convertDdepth(m_ddepth);
                    int ksizeCvData = int(m_ksize);
                    double scaleCvData = double(m_scale);
                    double deltaCvData = double(m_delta);
                    
                    cv::Laplacian(srcCvData, dstCvData, ddepthCvData, ksizeCvData, scaleCvData, deltaCvData);
                    
                    runtime::Image* dstCastedData = new cvsupport::Image(dstCvData);
                    runtime::DataContainer dstOutContainer = runtime::DataContainer(dstCastedData);
                    runtime::Id2DataPair dstOutMapper(DST, dstOutContainer);
                    
                    runtime::Image::PixelType pixelType = cvsupport::computeOutPixelType(convertDdepth(m_ddepth), srcCastedData->pixelType());
                    unsigned int stride = runtime::Image::pixelSize(pixelType) * srcCastedData->width();
                    dstCastedData->initializeImage(dstCastedData->width(), dstCastedData->height(), stride, dstCastedData->data(), pixelType);
                    provider.sendOutputData(dstOutMapper);
                }
                break;
            }
        }
        
        int Laplacian::convertDdepth(const runtime::Enum & value)
        {
            switch(int(value))
            {
            case SAME:
                return -1;
            case DEPTH_8_BIT:
                return CV_8U;
            case DEPTH_16_BIT:
                return CV_16U;
            default:
                throw runtime::WrongParameterValue(parameter(DDEPTH), *this);
            }
        }
        
    } // cvimgproc
} // stromx

