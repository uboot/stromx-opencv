#include "stromx/cvcore/Bitwise_and.h"

#include "stromx/cvcore/Locale.h"
#include "stromx/cvcore/Utility.h"
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
#include <opencv2/core/core.hpp>

namespace stromx
{
    namespace cvcore
    {
        const std::string Bitwise_and::PACKAGE(STROMX_CVCORE_PACKAGE_NAME);
        const runtime::Version Bitwise_and::VERSION(STROMX_CVCORE_VERSION_MAJOR, STROMX_CVCORE_VERSION_MINOR, STROMX_CVCORE_VERSION_PATCH);
        const std::string Bitwise_and::TYPE("Bitwise_and");
        
        Bitwise_and::Bitwise_and()
          : runtime::OperatorKernel(TYPE, PACKAGE, VERSION, setupInitParameters()),
            m_dataFlow()
        {
        }
        
        const runtime::DataRef Bitwise_and::getParameter(unsigned int id) const
        {
            switch(id)
            {
            case PARAMETER_DATA_FLOW:
                return m_dataFlow;
            default:
                throw runtime::WrongParameterId(id, *this);
            }
        }
        
        void Bitwise_and::setParameter(unsigned int id, const runtime::Data& value)
        {
            try
            {
                switch(id)
                {
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
        
        const std::vector<const runtime::Parameter*> Bitwise_and::setupInitParameters()
        {
            std::vector<const runtime::Parameter*> parameters;
            
            m_dataFlowParameter = new runtime::EnumParameter(PARAMETER_DATA_FLOW);
            m_dataFlowParameter->setAccessMode(runtime::Parameter::NONE_WRITE);
            m_dataFlowParameter->setTitle(L_("Data flow"));
            m_dataFlowParameter->add(runtime::EnumDescription(runtime::Enum(MANUAL), L_("Manual")));
            m_dataFlowParameter->add(runtime::EnumDescription(runtime::Enum(ALLOCATE), L_("Allocate")));
            parameters.push_back(m_dataFlowParameter);
            
            return parameters;
        }
        
        const std::vector<const runtime::Parameter*> Bitwise_and::setupParameters()
        {
            std::vector<const runtime::Parameter*> parameters;
            
            switch(int(m_dataFlow))
            {
            case(MANUAL):
                {
                }
                break;
            case(ALLOCATE):
                {
                }
                break;
            }
            
            return parameters;
        }
        
        const std::vector<const runtime::Input*> Bitwise_and::setupInputs()
        {
            std::vector<const runtime::Input*> inputs;
            
            switch(int(m_dataFlow))
            {
            case(MANUAL):
                {
                    m_src1Description = new runtime::Input(INPUT_SRC_1, runtime::Variant::IMAGE);
                    m_src1Description->setTitle(L_("Source 1"));
                    inputs.push_back(m_src1Description);
                    
                    m_src2Description = new runtime::Input(INPUT_SRC_2, runtime::Variant::IMAGE);
                    m_src2Description->setTitle(L_("Source 2"));
                    inputs.push_back(m_src2Description);
                    
                    m_dstDescription = new runtime::Input(INPUT_DST, runtime::Variant::IMAGE);
                    m_dstDescription->setTitle(L_("Destination"));
                    inputs.push_back(m_dstDescription);
                    
                }
                break;
            case(ALLOCATE):
                {
                    m_src1Description = new runtime::Input(INPUT_SRC_1, runtime::Variant::IMAGE);
                    m_src1Description->setTitle(L_("Source 1"));
                    inputs.push_back(m_src1Description);
                    
                    m_src2Description = new runtime::Input(INPUT_SRC_2, runtime::Variant::IMAGE);
                    m_src2Description->setTitle(L_("Source 2"));
                    inputs.push_back(m_src2Description);
                    
                }
                break;
            }
            
            return inputs;
        }
        
        const std::vector<const runtime::Output*> Bitwise_and::setupOutputs()
        {
            std::vector<const runtime::Output*> outputs;
            
            switch(int(m_dataFlow))
            {
            case(MANUAL):
                {
                    runtime::Output* dst = new runtime::Output(OUTPUT_DST, runtime::Variant::IMAGE);
                    dst->setTitle(L_("Destination"));
                    outputs.push_back(dst);
                    
                }
                break;
            case(ALLOCATE):
                {
                    runtime::Output* dst = new runtime::Output(OUTPUT_DST, runtime::Variant::IMAGE);
                    dst->setTitle(L_("Destination"));
                    outputs.push_back(dst);
                    
                }
                break;
            }
            
            return outputs;
        }
        
        void Bitwise_and::initialize()
        {
            runtime::OperatorKernel::initialize(setupInputs(), setupOutputs(), setupParameters());
        }
        
        void Bitwise_and::execute(runtime::DataProvider & provider)
        {
            switch(int(m_dataFlow))
            {
            case(MANUAL):
                {
                    runtime::Id2DataPair src1InMapper(INPUT_SRC_1);
                    runtime::Id2DataPair src2InMapper(INPUT_SRC_2);
                    runtime::Id2DataPair dstInMapper(INPUT_DST);
                    
                    provider.receiveInputData(src1InMapper && src2InMapper && dstInMapper);
                    
                    const runtime::Data* src1Data = 0;
                    const runtime::Data* src2Data = 0;
                    runtime::Data* dstData = 0;
                    
                    runtime::ReadAccess src1ReadAccess;
                    runtime::ReadAccess src2ReadAccess;
                    runtime::DataContainer inContainer = dstInMapper.data();
                    runtime::WriteAccess writeAccess(inContainer);
                    dstData = &writeAccess.get();
                    
                    if(src1InMapper.data() == inContainer)
                    {
                        throw runtime::InputError(INPUT_SRC_1, *this, "Can not operate in place.");
                    }
                    else
                    {
                        src1ReadAccess = runtime::ReadAccess(src1InMapper.data());
                        src1Data = &src1ReadAccess.get();
                    }
                    
                    if(src2InMapper.data() == inContainer)
                    {
                        throw runtime::InputError(INPUT_SRC_2, *this, "Can not operate in place.");
                    }
                    else
                    {
                        src2ReadAccess = runtime::ReadAccess(src2InMapper.data());
                        src2Data = &src2ReadAccess.get();
                    }
                    
                    if(! src1Data->variant().isVariant(m_src1Description->variant()))
                    {
                        throw runtime::InputError(INPUT_SRC_1, *this, "Wrong input data variant.");
                    }
                    if(! src2Data->variant().isVariant(m_src2Description->variant()))
                    {
                        throw runtime::InputError(INPUT_SRC_2, *this, "Wrong input data variant.");
                    }
                    if(! dstData->variant().isVariant(m_dstDescription->variant()))
                    {
                        throw runtime::InputError(INPUT_DST, *this, "Wrong input data variant.");
                    }
                    
                    const runtime::Image* src1CastedData = runtime::data_cast<runtime::Image>(src1Data);
                    const runtime::Image* src2CastedData = runtime::data_cast<runtime::Image>(src2Data);
                    runtime::Image * dstCastedData = runtime::data_cast<runtime::Image>(dstData);
                    
                    if((src1CastedData->rows() != src2CastedData->rows()) || (src1CastedData->cols() != src2CastedData->cols()))
                        throw runtime::InputError(INPUT_SRC_1, *this, "Input images must have the same size.");
                        
                    if(src1CastedData->numChannels() != src2CastedData->numChannels())
                        throw runtime::InputError(INPUT_SRC_1, *this, "Input images must have the same number of channels.");
                        
                    if(src1CastedData->depth() != src2CastedData->depth())
                        throw runtime::InputError(INPUT_SRC_1, *this, "Input images must have the same depth if the destination depth is not explicitely given.");
                    
                    dstCastedData->initializeImage(src1CastedData->width(), src1CastedData->height(), src1CastedData->stride(), dstCastedData->data(), src1CastedData->pixelType());
                    
                    cv::Mat src1CvData = cvsupport::getOpenCvMat(*src1CastedData);
                    cv::Mat src2CvData = cvsupport::getOpenCvMat(*src2CastedData);
                    cv::Mat dstCvData = cvsupport::getOpenCvMat(*dstCastedData);
                    
                    cv::bitwise_and(src1CvData, src2CvData, dstCvData);
                    
                    runtime::DataContainer dstOutContainer = inContainer;
                    runtime::Id2DataPair dstOutMapper(OUTPUT_DST, dstOutContainer);
                    
                    provider.sendOutputData(dstOutMapper);
                }
                break;
            case(ALLOCATE):
                {
                    runtime::Id2DataPair src1InMapper(INPUT_SRC_1);
                    runtime::Id2DataPair src2InMapper(INPUT_SRC_2);
                    
                    provider.receiveInputData(src1InMapper && src2InMapper);
                    
                    const runtime::Data* src1Data = 0;
                    const runtime::Data* src2Data = 0;
                    
                    runtime::ReadAccess src1ReadAccess;
                    runtime::ReadAccess src2ReadAccess;
                    
                    src1ReadAccess = runtime::ReadAccess(src1InMapper.data());
                    src1Data = &src1ReadAccess.get();
                    src2ReadAccess = runtime::ReadAccess(src2InMapper.data());
                    src2Data = &src2ReadAccess.get();
                    
                    if(! src1Data->variant().isVariant(m_src1Description->variant()))
                    {
                        throw runtime::InputError(INPUT_SRC_1, *this, "Wrong input data variant.");
                    }
                    if(! src2Data->variant().isVariant(m_src2Description->variant()))
                    {
                        throw runtime::InputError(INPUT_SRC_2, *this, "Wrong input data variant.");
                    }
                    
                    const runtime::Image* src1CastedData = runtime::data_cast<runtime::Image>(src1Data);
                    const runtime::Image* src2CastedData = runtime::data_cast<runtime::Image>(src2Data);
                    
                    if((src1CastedData->rows() != src2CastedData->rows()) || (src1CastedData->cols() != src2CastedData->cols()))
                        throw runtime::InputError(INPUT_SRC_1, *this, "Input images must have the same size.");
                        
                    if(src1CastedData->numChannels() != src2CastedData->numChannels())
                        throw runtime::InputError(INPUT_SRC_1, *this, "Input images must have the same number of channels.");
                        
                    if(src1CastedData->depth() != src2CastedData->depth())
                        throw runtime::InputError(INPUT_SRC_1, *this, "Input images must have the same depth if the destination depth is not explicitely given.");
                    
                    cv::Mat src1CvData = cvsupport::getOpenCvMat(*src1CastedData);
                    cv::Mat src2CvData = cvsupport::getOpenCvMat(*src2CastedData);
                    cv::Mat dstCvData;
                    
                    cv::bitwise_and(src1CvData, src2CvData, dstCvData);
                    
                    runtime::Image* dstCastedData = new cvsupport::Image(dstCvData);
                    runtime::DataContainer dstOutContainer = runtime::DataContainer(dstCastedData);
                    runtime::Id2DataPair dstOutMapper(OUTPUT_DST, dstOutContainer);
                    
                    dstCastedData->initializeImage(dstCastedData->width(), dstCastedData->height(), dstCastedData->stride(), dstCastedData->data(), src1CastedData->pixelType());
                    provider.sendOutputData(dstOutMapper);
                }
                break;
            }
        }
        
    } // cvcore
} // stromx

