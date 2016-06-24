#include "stromx/cvcore/Mean.h"

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
        const std::string Mean::PACKAGE(STROMX_CVCORE_PACKAGE_NAME);
        const runtime::Version Mean::VERSION(STROMX_CVCORE_VERSION_MAJOR, STROMX_CVCORE_VERSION_MINOR, STROMX_CVCORE_VERSION_PATCH);
        const std::string Mean::TYPE("Mean");
        
        Mean::Mean()
          : runtime::OperatorKernel(TYPE, PACKAGE, VERSION, setupInitParameters()),
            m_dataFlow()
        {
        }
        
        const runtime::DataRef Mean::getParameter(unsigned int id) const
        {
            switch(id)
            {
            case PARAMETER_DATA_FLOW:
                return m_dataFlow;
            default:
                throw runtime::WrongParameterId(id, *this);
            }
        }
        
        void Mean::setParameter(unsigned int id, const runtime::Data& value)
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
        
        const std::vector<const runtime::Parameter*> Mean::setupInitParameters()
        {
            std::vector<const runtime::Parameter*> parameters;
            
            return parameters;
        }
        
        const std::vector<const runtime::Parameter*> Mean::setupParameters()
        {
            std::vector<const runtime::Parameter*> parameters;
            
            switch(int(m_dataFlow))
            {
            case(ALLOCATE):
                {
                }
                break;
            }
            
            return parameters;
        }
        
        const std::vector<const runtime::Input*> Mean::setupInputs()
        {
            std::vector<const runtime::Input*> inputs;
            
            switch(int(m_dataFlow))
            {
            case(ALLOCATE):
                {
                    m_srcDescription = new runtime::Input(INPUT_SRC, runtime::Variant::MATRIX);
                    m_srcDescription->setTitle(L_("Source"));
                    inputs.push_back(m_srcDescription);
                    
                }
                break;
            }
            
            return inputs;
        }
        
        const std::vector<const runtime::Output*> Mean::setupOutputs()
        {
            std::vector<const runtime::Output*> outputs;
            
            switch(int(m_dataFlow))
            {
            case(ALLOCATE):
                {
                    runtime::Output* value = new runtime::Output(OUTPUT_VALUE, runtime::Variant::FLOAT_64);
                    value->setTitle(L_("Value"));
                    outputs.push_back(value);
                    
                }
                break;
            }
            
            return outputs;
        }
        
        void Mean::initialize()
        {
            runtime::OperatorKernel::initialize(setupInputs(), setupOutputs(), setupParameters());
        }
        
        void Mean::execute(runtime::DataProvider & provider)
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
                    
                    const runtime::Matrix* srcCastedData = runtime::data_cast<runtime::Matrix>(srcData);
                    
                    cv::Mat srcCvData = cvsupport::getOpenCvMat(*srcCastedData);
                    double valueCvData;
                    
                    valueCvData = mean(srcCvData);
                    
                    runtime::Float64* valueCastedData = new runtime::Float64(valueCvData);
                    runtime::DataContainer valueOutContainer = runtime::DataContainer(valueCastedData);
                    runtime::Id2DataPair valueOutMapper(OUTPUT_VALUE, valueOutContainer);
                    
                    provider.sendOutputData(valueOutMapper);
                }
                break;
            }
        }
        
    } // cvcore
} // stromx

