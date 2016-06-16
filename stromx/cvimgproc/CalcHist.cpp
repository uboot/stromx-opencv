#include "stromx/cvimgproc/CalcHist.h"

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
        const std::string CalcHist::PACKAGE(STROMX_CVIMGPROC_PACKAGE_NAME);
        const runtime::Version CalcHist::VERSION(STROMX_CVIMGPROC_VERSION_MAJOR, STROMX_CVIMGPROC_VERSION_MINOR, STROMX_CVIMGPROC_VERSION_PATCH);
        const std::string CalcHist::TYPE("CalcHist");
        
        CalcHist::CalcHist()
          : runtime::OperatorKernel(TYPE, PACKAGE, VERSION, setupInitParameters()),
            m_histMax(256),
            m_histMin(0),
            m_histSize(16),
            m_dataFlow()
        {
        }
        
        const runtime::DataRef CalcHist::getParameter(unsigned int id) const
        {
            switch(id)
            {
            case PARAMETER_HIST_MAX:
                return m_histMax;
            case PARAMETER_HIST_MIN:
                return m_histMin;
            case PARAMETER_HIST_SIZE:
                return m_histSize;
            case PARAMETER_DATA_FLOW:
                return m_dataFlow;
            default:
                throw runtime::WrongParameterId(id, *this);
            }
        }
        
        void CalcHist::setParameter(unsigned int id, const runtime::Data& value)
        {
            try
            {
                switch(id)
                {
                case PARAMETER_HIST_MAX:
                    {
                        const runtime::Float32 & castedValue = runtime::data_cast<runtime::Float32>(value);
                        if(! castedValue.variant().isVariant(runtime::Variant::FLOAT_32))
                        {
                            throw runtime::WrongParameterType(parameter(id), *this);
                        }
                        cvsupport::checkNumericValue(castedValue, m_histMaxParameter, *this);
                        m_histMax = castedValue;
                    }
                    break;
                case PARAMETER_HIST_MIN:
                    {
                        const runtime::Float32 & castedValue = runtime::data_cast<runtime::Float32>(value);
                        if(! castedValue.variant().isVariant(runtime::Variant::FLOAT_32))
                        {
                            throw runtime::WrongParameterType(parameter(id), *this);
                        }
                        cvsupport::checkNumericValue(castedValue, m_histMinParameter, *this);
                        m_histMin = castedValue;
                    }
                    break;
                case PARAMETER_HIST_SIZE:
                    {
                        const runtime::UInt32 & castedValue = runtime::data_cast<runtime::UInt32>(value);
                        if(! castedValue.variant().isVariant(runtime::Variant::UINT_32))
                        {
                            throw runtime::WrongParameterType(parameter(id), *this);
                        }
                        cvsupport::checkNumericValue(castedValue, m_histSizeParameter, *this);
                        m_histSize = castedValue;
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
        
        const std::vector<const runtime::Parameter*> CalcHist::setupInitParameters()
        {
            std::vector<const runtime::Parameter*> parameters;
            
            return parameters;
        }
        
        const std::vector<const runtime::Parameter*> CalcHist::setupParameters()
        {
            std::vector<const runtime::Parameter*> parameters;
            
            switch(int(m_dataFlow))
            {
            case(ALLOCATE):
                {
                    m_histMinParameter = new runtime::NumericParameter<runtime::Float32>(PARAMETER_HIST_MIN);
                    m_histMinParameter->setAccessMode(runtime::Parameter::ACTIVATED_WRITE);
                    m_histMinParameter->setTitle(L_("Minimum"));
                    parameters.push_back(m_histMinParameter);
                    
                    m_histMaxParameter = new runtime::NumericParameter<runtime::Float32>(PARAMETER_HIST_MAX);
                    m_histMaxParameter->setAccessMode(runtime::Parameter::ACTIVATED_WRITE);
                    m_histMaxParameter->setTitle(L_("Maximum"));
                    parameters.push_back(m_histMaxParameter);
                    
                    m_histSizeParameter = new runtime::NumericParameter<runtime::UInt32>(PARAMETER_HIST_SIZE);
                    m_histSizeParameter->setAccessMode(runtime::Parameter::ACTIVATED_WRITE);
                    m_histSizeParameter->setTitle(L_("Number of bins"));
                    parameters.push_back(m_histSizeParameter);
                    
                }
                break;
            }
            
            return parameters;
        }
        
        const std::vector<const runtime::Description*> CalcHist::setupInputs()
        {
            std::vector<const runtime::Description*> inputs;
            
            switch(int(m_dataFlow))
            {
            case(ALLOCATE):
                {
                    m_srcDescription = new runtime::Description(INPUT_SRC, runtime::Variant::MONO_IMAGE);
                    m_srcDescription->setTitle(L_("Source"));
                    inputs.push_back(m_srcDescription);
                    
                }
                break;
            }
            
            return inputs;
        }
        
        const std::vector<const runtime::Description*> CalcHist::setupOutputs()
        {
            std::vector<const runtime::Description*> outputs;
            
            switch(int(m_dataFlow))
            {
            case(ALLOCATE):
                {
                    runtime::Description* dst = new runtime::Description(OUTPUT_DST, runtime::Variant::MATRIX);
                    dst->setTitle(L_("Destination"));
                    dst->setVisualization(runtime::Visualization::HISTOGRAM);
                    outputs.push_back(dst);
                    
                }
                break;
            }
            
            return outputs;
        }
        
        void CalcHist::initialize()
        {
            runtime::OperatorKernel::initialize(setupInputs(), setupOutputs(), setupParameters());
        }
        
        void CalcHist::execute(runtime::DataProvider & provider)
        {
            switch(int(m_dataFlow))
            {
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
                    float histMinCvData = float(m_histMin);
                    float histMaxCvData = float(m_histMax);
                    int histSizeCvData = int(m_histSize);
                    
                    calcHist(srcCvData, dstCvData, histMinCvData, histMaxCvData, histSizeCvData);
                    
                    runtime::Matrix* dstCastedData = new cvsupport::Matrix(dstCvData);
                    runtime::DataContainer dstOutContainer = runtime::DataContainer(dstCastedData);
                    runtime::Id2DataPair dstOutMapper(OUTPUT_DST, dstOutContainer);
                    
                    provider.sendOutputData(dstOutMapper);
                }
                break;
            }
        }
        
    } // cvimgproc
} // stromx

