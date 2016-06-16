#include "stromx/cvimgproc/MorphologyEx.h"

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
        const std::string MorphologyEx::PACKAGE(STROMX_CVIMGPROC_PACKAGE_NAME);
        const runtime::Version MorphologyEx::VERSION(STROMX_CVIMGPROC_VERSION_MAJOR, STROMX_CVIMGPROC_VERSION_MINOR, STROMX_CVIMGPROC_VERSION_PATCH);
        const std::string MorphologyEx::TYPE("MorphologyEx");
        
        MorphologyEx::MorphologyEx()
          : runtime::OperatorKernel(TYPE, PACKAGE, VERSION, setupInitParameters()),
            m_iterations(1),
            m_ksizex(3),
            m_ksizey(3),
            m_op(1),
            m_shape(0),
            m_dataFlow()
        {
        }
        
        const runtime::DataRef MorphologyEx::getParameter(unsigned int id) const
        {
            switch(id)
            {
            case PARAMETER_ITERATIONS:
                return m_iterations;
            case PARAMETER_KSIZEX:
                return m_ksizex;
            case PARAMETER_KSIZEY:
                return m_ksizey;
            case PARAMETER_OP:
                return m_op;
            case PARAMETER_SHAPE:
                return m_shape;
            case PARAMETER_DATA_FLOW:
                return m_dataFlow;
            default:
                throw runtime::WrongParameterId(id, *this);
            }
        }
        
        void MorphologyEx::setParameter(unsigned int id, const runtime::Data& value)
        {
            try
            {
                switch(id)
                {
                case PARAMETER_ITERATIONS:
                    {
                        const runtime::UInt32 & castedValue = runtime::data_cast<runtime::UInt32>(value);
                        if(! castedValue.variant().isVariant(runtime::Variant::UINT_32))
                        {
                            throw runtime::WrongParameterType(parameter(id), *this);
                        }
                        cvsupport::checkNumericValue(castedValue, m_iterationsParameter, *this);
                        m_iterations = castedValue;
                    }
                    break;
                case PARAMETER_KSIZEX:
                    {
                        const runtime::UInt32 & castedValue = runtime::data_cast<runtime::UInt32>(value);
                        if(! castedValue.variant().isVariant(runtime::Variant::UINT_32))
                        {
                            throw runtime::WrongParameterType(parameter(id), *this);
                        }
                        cvsupport::checkNumericValue(castedValue, m_ksizexParameter, *this);
                        m_ksizex = castedValue;
                    }
                    break;
                case PARAMETER_KSIZEY:
                    {
                        const runtime::UInt32 & castedValue = runtime::data_cast<runtime::UInt32>(value);
                        if(! castedValue.variant().isVariant(runtime::Variant::UINT_32))
                        {
                            throw runtime::WrongParameterType(parameter(id), *this);
                        }
                        cvsupport::checkNumericValue(castedValue, m_ksizeyParameter, *this);
                        m_ksizey = castedValue;
                    }
                    break;
                case PARAMETER_OP:
                    {
                        const runtime::Enum & castedValue = runtime::data_cast<runtime::Enum>(value);
                        if(! castedValue.variant().isVariant(runtime::Variant::ENUM))
                        {
                            throw runtime::WrongParameterType(parameter(id), *this);
                        }
                        cvsupport::checkEnumValue(castedValue, m_opParameter, *this);
                        m_op = castedValue;
                    }
                    break;
                case PARAMETER_SHAPE:
                    {
                        const runtime::Enum & castedValue = runtime::data_cast<runtime::Enum>(value);
                        if(! castedValue.variant().isVariant(runtime::Variant::ENUM))
                        {
                            throw runtime::WrongParameterType(parameter(id), *this);
                        }
                        cvsupport::checkEnumValue(castedValue, m_shapeParameter, *this);
                        m_shape = castedValue;
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
        
        const std::vector<const runtime::Parameter*> MorphologyEx::setupInitParameters()
        {
            std::vector<const runtime::Parameter*> parameters;
            
            m_dataFlowParameter = new runtime::EnumParameter(PARAMETER_DATA_FLOW);
            m_dataFlowParameter->setAccessMode(runtime::Parameter::NONE_WRITE);
            m_dataFlowParameter->setTitle(L_("Data flow"));
            m_dataFlowParameter->add(runtime::EnumDescription(runtime::Enum(MANUAL), L_("Manual")));
            m_dataFlowParameter->add(runtime::EnumDescription(runtime::Enum(ALLOCATE), L_("Allocate")));
            m_dataFlowParameter->add(runtime::EnumDescription(runtime::Enum(IN_PLACE), L_("In place")));
            parameters.push_back(m_dataFlowParameter);
            
            return parameters;
        }
        
        const std::vector<const runtime::Parameter*> MorphologyEx::setupParameters()
        {
            std::vector<const runtime::Parameter*> parameters;
            
            switch(int(m_dataFlow))
            {
            case(MANUAL):
                {
                    m_opParameter = new runtime::EnumParameter(PARAMETER_OP);
                    m_opParameter->setAccessMode(runtime::Parameter::ACTIVATED_WRITE);
                    m_opParameter->setTitle(L_("Operation"));
                    m_opParameter->add(runtime::EnumDescription(runtime::Enum(MORPH_OPEN), L_("Open")));
                    m_opParameter->add(runtime::EnumDescription(runtime::Enum(MORPH_CLOSE), L_("Close")));
                    m_opParameter->add(runtime::EnumDescription(runtime::Enum(MORPH_GRADIENT), L_("Gradient")));
                    m_opParameter->add(runtime::EnumDescription(runtime::Enum(MORPH_TOPHAT), L_("Tophat")));
                    m_opParameter->add(runtime::EnumDescription(runtime::Enum(MORPH_BLACKHAT), L_("Blackhat")));
                    parameters.push_back(m_opParameter);
                    
                    m_ksizexParameter = new runtime::NumericParameter<runtime::UInt32>(PARAMETER_KSIZEX);
                    m_ksizexParameter->setAccessMode(runtime::Parameter::ACTIVATED_WRITE);
                    m_ksizexParameter->setTitle(L_("Kernel size X"));
                    m_ksizexParameter->setMin(runtime::UInt32(1));
                    parameters.push_back(m_ksizexParameter);
                    
                    m_ksizeyParameter = new runtime::NumericParameter<runtime::UInt32>(PARAMETER_KSIZEY);
                    m_ksizeyParameter->setAccessMode(runtime::Parameter::ACTIVATED_WRITE);
                    m_ksizeyParameter->setTitle(L_("Kernel size Y"));
                    m_ksizeyParameter->setMin(runtime::UInt32(1));
                    parameters.push_back(m_ksizeyParameter);
                    
                    m_shapeParameter = new runtime::EnumParameter(PARAMETER_SHAPE);
                    m_shapeParameter->setAccessMode(runtime::Parameter::ACTIVATED_WRITE);
                    m_shapeParameter->setTitle(L_("Kernel shape"));
                    m_shapeParameter->add(runtime::EnumDescription(runtime::Enum(MORPH_RECT), L_("Rectangle")));
                    m_shapeParameter->add(runtime::EnumDescription(runtime::Enum(MORPH_ELLIPSE), L_("Ellipse")));
                    m_shapeParameter->add(runtime::EnumDescription(runtime::Enum(MORPH_CROSS), L_("Cross")));
                    parameters.push_back(m_shapeParameter);
                    
                    m_iterationsParameter = new runtime::NumericParameter<runtime::UInt32>(PARAMETER_ITERATIONS);
                    m_iterationsParameter->setAccessMode(runtime::Parameter::ACTIVATED_WRITE);
                    m_iterationsParameter->setTitle(L_("Number of iterations"));
                    m_iterationsParameter->setMin(runtime::UInt32(1));
                    parameters.push_back(m_iterationsParameter);
                    
                }
                break;
            case(ALLOCATE):
                {
                    m_opParameter = new runtime::EnumParameter(PARAMETER_OP);
                    m_opParameter->setAccessMode(runtime::Parameter::ACTIVATED_WRITE);
                    m_opParameter->setTitle(L_("Operation"));
                    m_opParameter->add(runtime::EnumDescription(runtime::Enum(MORPH_OPEN), L_("Open")));
                    m_opParameter->add(runtime::EnumDescription(runtime::Enum(MORPH_CLOSE), L_("Close")));
                    m_opParameter->add(runtime::EnumDescription(runtime::Enum(MORPH_GRADIENT), L_("Gradient")));
                    m_opParameter->add(runtime::EnumDescription(runtime::Enum(MORPH_TOPHAT), L_("Tophat")));
                    m_opParameter->add(runtime::EnumDescription(runtime::Enum(MORPH_BLACKHAT), L_("Blackhat")));
                    parameters.push_back(m_opParameter);
                    
                    m_ksizexParameter = new runtime::NumericParameter<runtime::UInt32>(PARAMETER_KSIZEX);
                    m_ksizexParameter->setAccessMode(runtime::Parameter::ACTIVATED_WRITE);
                    m_ksizexParameter->setTitle(L_("Kernel size X"));
                    m_ksizexParameter->setMin(runtime::UInt32(1));
                    parameters.push_back(m_ksizexParameter);
                    
                    m_ksizeyParameter = new runtime::NumericParameter<runtime::UInt32>(PARAMETER_KSIZEY);
                    m_ksizeyParameter->setAccessMode(runtime::Parameter::ACTIVATED_WRITE);
                    m_ksizeyParameter->setTitle(L_("Kernel size Y"));
                    m_ksizeyParameter->setMin(runtime::UInt32(1));
                    parameters.push_back(m_ksizeyParameter);
                    
                    m_shapeParameter = new runtime::EnumParameter(PARAMETER_SHAPE);
                    m_shapeParameter->setAccessMode(runtime::Parameter::ACTIVATED_WRITE);
                    m_shapeParameter->setTitle(L_("Kernel shape"));
                    m_shapeParameter->add(runtime::EnumDescription(runtime::Enum(MORPH_RECT), L_("Rectangle")));
                    m_shapeParameter->add(runtime::EnumDescription(runtime::Enum(MORPH_ELLIPSE), L_("Ellipse")));
                    m_shapeParameter->add(runtime::EnumDescription(runtime::Enum(MORPH_CROSS), L_("Cross")));
                    parameters.push_back(m_shapeParameter);
                    
                    m_iterationsParameter = new runtime::NumericParameter<runtime::UInt32>(PARAMETER_ITERATIONS);
                    m_iterationsParameter->setAccessMode(runtime::Parameter::ACTIVATED_WRITE);
                    m_iterationsParameter->setTitle(L_("Number of iterations"));
                    m_iterationsParameter->setMin(runtime::UInt32(1));
                    parameters.push_back(m_iterationsParameter);
                    
                }
                break;
            case(IN_PLACE):
                {
                    m_opParameter = new runtime::EnumParameter(PARAMETER_OP);
                    m_opParameter->setAccessMode(runtime::Parameter::ACTIVATED_WRITE);
                    m_opParameter->setTitle(L_("Operation"));
                    m_opParameter->add(runtime::EnumDescription(runtime::Enum(MORPH_OPEN), L_("Open")));
                    m_opParameter->add(runtime::EnumDescription(runtime::Enum(MORPH_CLOSE), L_("Close")));
                    m_opParameter->add(runtime::EnumDescription(runtime::Enum(MORPH_GRADIENT), L_("Gradient")));
                    m_opParameter->add(runtime::EnumDescription(runtime::Enum(MORPH_TOPHAT), L_("Tophat")));
                    m_opParameter->add(runtime::EnumDescription(runtime::Enum(MORPH_BLACKHAT), L_("Blackhat")));
                    parameters.push_back(m_opParameter);
                    
                    m_ksizexParameter = new runtime::NumericParameter<runtime::UInt32>(PARAMETER_KSIZEX);
                    m_ksizexParameter->setAccessMode(runtime::Parameter::ACTIVATED_WRITE);
                    m_ksizexParameter->setTitle(L_("Kernel size X"));
                    m_ksizexParameter->setMin(runtime::UInt32(1));
                    parameters.push_back(m_ksizexParameter);
                    
                    m_ksizeyParameter = new runtime::NumericParameter<runtime::UInt32>(PARAMETER_KSIZEY);
                    m_ksizeyParameter->setAccessMode(runtime::Parameter::ACTIVATED_WRITE);
                    m_ksizeyParameter->setTitle(L_("Kernel size Y"));
                    m_ksizeyParameter->setMin(runtime::UInt32(1));
                    parameters.push_back(m_ksizeyParameter);
                    
                    m_shapeParameter = new runtime::EnumParameter(PARAMETER_SHAPE);
                    m_shapeParameter->setAccessMode(runtime::Parameter::ACTIVATED_WRITE);
                    m_shapeParameter->setTitle(L_("Kernel shape"));
                    m_shapeParameter->add(runtime::EnumDescription(runtime::Enum(MORPH_RECT), L_("Rectangle")));
                    m_shapeParameter->add(runtime::EnumDescription(runtime::Enum(MORPH_ELLIPSE), L_("Ellipse")));
                    m_shapeParameter->add(runtime::EnumDescription(runtime::Enum(MORPH_CROSS), L_("Cross")));
                    parameters.push_back(m_shapeParameter);
                    
                    m_iterationsParameter = new runtime::NumericParameter<runtime::UInt32>(PARAMETER_ITERATIONS);
                    m_iterationsParameter->setAccessMode(runtime::Parameter::ACTIVATED_WRITE);
                    m_iterationsParameter->setTitle(L_("Number of iterations"));
                    m_iterationsParameter->setMin(runtime::UInt32(1));
                    parameters.push_back(m_iterationsParameter);
                    
                }
                break;
            }
            
            return parameters;
        }
        
        const std::vector<const runtime::Description*> MorphologyEx::setupInputs()
        {
            std::vector<const runtime::Description*> inputs;
            
            switch(int(m_dataFlow))
            {
            case(MANUAL):
                {
                    m_srcDescription = new runtime::Description(INPUT_SRC, runtime::Variant::IMAGE);
                    m_srcDescription->setTitle(L_("Source"));
                    inputs.push_back(m_srcDescription);
                    
                    m_dstDescription = new runtime::Description(INPUT_DST, runtime::Variant::IMAGE);
                    m_dstDescription->setTitle(L_("Destination"));
                    inputs.push_back(m_dstDescription);
                    
                }
                break;
            case(ALLOCATE):
                {
                    m_srcDescription = new runtime::Description(INPUT_SRC, runtime::Variant::IMAGE);
                    m_srcDescription->setTitle(L_("Source"));
                    inputs.push_back(m_srcDescription);
                    
                }
                break;
            case(IN_PLACE):
                {
                    m_srcDescription = new runtime::Description(INPUT_SRC, runtime::Variant::IMAGE);
                    m_srcDescription->setTitle(L_("Source"));
                    inputs.push_back(m_srcDescription);
                    
                }
                break;
            }
            
            return inputs;
        }
        
        const std::vector<const runtime::Description*> MorphologyEx::setupOutputs()
        {
            std::vector<const runtime::Description*> outputs;
            
            switch(int(m_dataFlow))
            {
            case(MANUAL):
                {
                    runtime::Description* dst = new runtime::Description(OUTPUT_DST, runtime::Variant::IMAGE);
                    dst->setTitle(L_("Destination"));
                    outputs.push_back(dst);
                    
                }
                break;
            case(ALLOCATE):
                {
                    runtime::Description* dst = new runtime::Description(OUTPUT_DST, runtime::Variant::IMAGE);
                    dst->setTitle(L_("Destination"));
                    outputs.push_back(dst);
                    
                }
                break;
            case(IN_PLACE):
                {
                    runtime::Description* src = new runtime::Description(OUTPUT_SRC, runtime::Variant::IMAGE);
                    src->setTitle(L_("Source"));
                    outputs.push_back(src);
                    
                }
                break;
            }
            
            return outputs;
        }
        
        void MorphologyEx::initialize()
        {
            runtime::OperatorKernel::initialize(setupInputs(), setupOutputs(), setupParameters());
        }
        
        void MorphologyEx::execute(runtime::DataProvider & provider)
        {
            switch(int(m_dataFlow))
            {
            case(MANUAL):
                {
                    runtime::Id2DataPair srcInMapper(INPUT_SRC);
                    runtime::Id2DataPair dstInMapper(INPUT_DST);
                    
                    provider.receiveInputData(srcInMapper && dstInMapper);
                    
                    const runtime::Data* srcData = 0;
                    runtime::Data* dstData = 0;
                    
                    runtime::ReadAccess srcReadAccess;
                    runtime::DataContainer inContainer = dstInMapper.data();
                    runtime::WriteAccess writeAccess(inContainer);
                    dstData = &writeAccess.get();
                    
                    if(srcInMapper.data() == inContainer)
                    {
                        srcData = &writeAccess.get();
                    }
                    else
                    {
                        srcReadAccess = runtime::ReadAccess(srcInMapper.data());
                        srcData = &srcReadAccess.get();
                    }
                    
                    if(! srcData->variant().isVariant(m_srcDescription->variant()))
                    {
                        throw runtime::InputError(INPUT_SRC, *this, "Wrong input data variant.");
                    }
                    if(! dstData->variant().isVariant(m_dstDescription->variant()))
                    {
                        throw runtime::InputError(INPUT_DST, *this, "Wrong input data variant.");
                    }
                    
                    const runtime::Image* srcCastedData = runtime::data_cast<runtime::Image>(srcData);
                    runtime::Image * dstCastedData = runtime::data_cast<runtime::Image>(dstData);
                    
                    dstCastedData->initializeImage(srcCastedData->width(), srcCastedData->height(), srcCastedData->stride(), dstCastedData->data(), srcCastedData->pixelType());
                    
                    cv::Mat srcCvData = cvsupport::getOpenCvMat(*srcCastedData);
                    cv::Mat dstCvData = cvsupport::getOpenCvMat(*dstCastedData);
                    int opCvData = convertOp(m_op);
                    int ksizexCvData = int(m_ksizex);
                    int ksizeyCvData = int(m_ksizey);
                    int shapeCvData = convertShape(m_shape);
                    int iterationsCvData = int(m_iterations);
                    
                    cv::morphologyEx(srcCvData, dstCvData, opCvData, getStructuringElement(shapeCvData, cv::Size(ksizexCvData, ksizeyCvData)), cv::Point(-1, -1), iterationsCvData);
                    
                    runtime::DataContainer dstOutContainer = inContainer;
                    runtime::Id2DataPair dstOutMapper(OUTPUT_DST, dstOutContainer);
                    
                    provider.sendOutputData(dstOutMapper);
                }
                break;
            case(ALLOCATE):
                {
                    runtime::Id2DataPair srcInMapper(INPUT_SRC);
                    
                    provider.receiveInputData(srcInMapper);
                    
                    const runtime::Data* srcData = 0;
                    
                    runtime::ReadAccess srcReadAccess;
                    
                    srcReadAccess = runtime::ReadAccess(srcInMapper.data());
                    srcData = &srcReadAccess.get();
                    
                    if(! srcData->variant().isVariant(m_srcDescription->variant()))
                    {
                        throw runtime::InputError(INPUT_SRC, *this, "Wrong input data variant.");
                    }
                    
                    const runtime::Image* srcCastedData = runtime::data_cast<runtime::Image>(srcData);
                    
                    cv::Mat srcCvData = cvsupport::getOpenCvMat(*srcCastedData);
                    cv::Mat dstCvData;
                    int opCvData = convertOp(m_op);
                    int ksizexCvData = int(m_ksizex);
                    int ksizeyCvData = int(m_ksizey);
                    int shapeCvData = convertShape(m_shape);
                    int iterationsCvData = int(m_iterations);
                    
                    cv::morphologyEx(srcCvData, dstCvData, opCvData, getStructuringElement(shapeCvData, cv::Size(ksizexCvData, ksizeyCvData)), cv::Point(-1, -1), iterationsCvData);
                    
                    runtime::Image* dstCastedData = new cvsupport::Image(dstCvData);
                    runtime::DataContainer dstOutContainer = runtime::DataContainer(dstCastedData);
                    runtime::Id2DataPair dstOutMapper(OUTPUT_DST, dstOutContainer);
                    
                    dstCastedData->initializeImage(dstCastedData->width(), dstCastedData->height(), dstCastedData->stride(), dstCastedData->data(), srcCastedData->pixelType());
                    provider.sendOutputData(dstOutMapper);
                }
                break;
            case(IN_PLACE):
                {
                    runtime::Id2DataPair srcInMapper(INPUT_SRC);
                    
                    provider.receiveInputData(srcInMapper);
                    
                    runtime::Data* srcData = 0;
                    
                    runtime::DataContainer inContainer = srcInMapper.data();
                    runtime::WriteAccess writeAccess(inContainer);
                    srcData = &writeAccess.get();
                    
                    if(! srcData->variant().isVariant(m_srcDescription->variant()))
                    {
                        throw runtime::InputError(INPUT_SRC, *this, "Wrong input data variant.");
                    }
                    
                    runtime::Image * srcCastedData = runtime::data_cast<runtime::Image>(srcData);
                    
                    cv::Mat srcCvData = cvsupport::getOpenCvMat(*srcCastedData);
                    cv::Mat dstCvData = srcCvData;
                    int opCvData = convertOp(m_op);
                    int ksizexCvData = int(m_ksizex);
                    int ksizeyCvData = int(m_ksizey);
                    int shapeCvData = convertShape(m_shape);
                    int iterationsCvData = int(m_iterations);
                    
                    cv::morphologyEx(srcCvData, dstCvData, opCvData, getStructuringElement(shapeCvData, cv::Size(ksizexCvData, ksizeyCvData)), cv::Point(-1, -1), iterationsCvData);
                    
                    runtime::DataContainer srcOutContainer = inContainer;
                    runtime::Id2DataPair srcOutMapper(OUTPUT_SRC, srcOutContainer);
                    
                    provider.sendOutputData(srcOutMapper);
                }
                break;
            }
        }
        
        int MorphologyEx::convertOp(const runtime::Enum & value)
        {
            switch(int(value))
            {
            case MORPH_OPEN:
                return cv::MORPH_OPEN;
            case MORPH_CLOSE:
                return cv::MORPH_CLOSE;
            case MORPH_GRADIENT:
                return cv::MORPH_GRADIENT;
            case MORPH_TOPHAT:
                return cv::MORPH_TOPHAT;
            case MORPH_BLACKHAT:
                return cv::MORPH_BLACKHAT;
            default:
                throw runtime::WrongParameterValue(parameter(PARAMETER_OP), *this);
            }
        }
        
        int MorphologyEx::convertShape(const runtime::Enum & value)
        {
            switch(int(value))
            {
            case MORPH_RECT:
                return cv::MORPH_RECT;
            case MORPH_ELLIPSE:
                return cv::MORPH_ELLIPSE;
            case MORPH_CROSS:
                return cv::MORPH_CROSS;
            default:
                throw runtime::WrongParameterValue(parameter(PARAMETER_SHAPE), *this);
            }
        }
        
    } // cvimgproc
} // stromx

