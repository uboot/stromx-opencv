#include "stromx/cvimgproc/FitEllipse.h"

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
        const std::string FitEllipse::PACKAGE(STROMX_CVIMGPROC_PACKAGE_NAME);
        const runtime::Version FitEllipse::VERSION(STROMX_CVIMGPROC_VERSION_MAJOR, STROMX_CVIMGPROC_VERSION_MINOR, STROMX_CVIMGPROC_VERSION_PATCH);
        const std::string FitEllipse::TYPE("FitEllipse");
        
        FitEllipse::FitEllipse()
          : runtime::OperatorKernel(TYPE, PACKAGE, VERSION, setupInitParameters()),
            m_dataFlow()
        {
        }
        
        const runtime::DataRef FitEllipse::getParameter(unsigned int id) const
        {
            switch(id)
            {
            case PARAMETER_DATA_FLOW:
                return m_dataFlow;
            default:
                throw runtime::WrongParameterId(id, *this);
            }
        }
        
        void FitEllipse::setParameter(unsigned int id, const runtime::Data& value)
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
        
        const std::vector<const runtime::Parameter*> FitEllipse::setupInitParameters()
        {
            std::vector<const runtime::Parameter*> parameters;
            
            return parameters;
        }
        
        const std::vector<const runtime::Parameter*> FitEllipse::setupParameters()
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
        
        const std::vector<const runtime::Input*> FitEllipse::setupInputs()
        {
            std::vector<const runtime::Input*> inputs;
            
            switch(int(m_dataFlow))
            {
            case(ALLOCATE):
                {
                    m_pointsDescription = new runtime::Input(INPUT_POINTS, runtime::Variant::INT_32_MATRIX || runtime::Variant::FLOAT_32_MATRIX);
                    m_pointsDescription->setTitle("Point set");
                    m_pointsDescription->setVisualization(runtime::Visualization::POINT);
                    m_pointsDescription->setRows(0);
                    m_pointsDescription->setCols(2);
                    inputs.push_back(m_pointsDescription);
                    
                }
                break;
            }
            
            return inputs;
        }
        
        const std::vector<const runtime::Output*> FitEllipse::setupOutputs()
        {
            std::vector<const runtime::Output*> outputs;
            
            switch(int(m_dataFlow))
            {
            case(ALLOCATE):
                {
                    runtime::Output* ellipse = new runtime::Output(OUTPUT_ELLIPSE, runtime::Variant::FLOAT_32_MATRIX);
                    ellipse->setTitle(L_("Bounding box"));
                    ellipse->setVisualization(runtime::Visualization::ELLIPSE);
                    ellipse->setRows(1);
                    ellipse->setCols(5);
                    outputs.push_back(ellipse);
                    
                }
                break;
            }
            
            return outputs;
        }
        
        void FitEllipse::initialize()
        {
            runtime::OperatorKernel::initialize(setupInputs(), setupOutputs(), setupParameters());
        }
        
        void FitEllipse::execute(runtime::DataProvider & provider)
        {
            switch(int(m_dataFlow))
            {
            case(ALLOCATE):
                {
                    runtime::Id2DataPair pointsInMapper(INPUT_POINTS);
                    
                    provider.receiveInputData(pointsInMapper);
                    
                    const runtime::Data* pointsData = 0;
                    
                    runtime::ReadAccess pointsReadAccess;
                    
                    pointsReadAccess = runtime::ReadAccess(pointsInMapper.data());
                    pointsData = &pointsReadAccess.get();
                    
                    if(! pointsData->variant().isVariant(m_pointsDescription->variant()))
                    {
                        throw runtime::InputError(INPUT_POINTS, *this, "Wrong input data variant.");
                    }
                    
                    const runtime::Matrix* pointsCastedData = runtime::data_cast<runtime::Matrix>(pointsData);
                    cvsupport::checkMatrixValue(*pointsCastedData, m_pointsDescription, *this);
                    
                    cv::Mat pointsCvData = cvsupport::getOpenCvMat(*pointsCastedData, 2);
                    cv::RotatedRect ellipseCvData;
                    
                    ellipseCvData = cv::fitEllipse(pointsCvData);
                    
                    runtime::Matrix* ellipseCastedData = new cvsupport::Matrix(ellipseCvData);
                    runtime::DataContainer ellipseOutContainer = runtime::DataContainer(ellipseCastedData);
                    runtime::Id2DataPair ellipseOutMapper(OUTPUT_ELLIPSE, ellipseOutContainer);
                    
                    provider.sendOutputData(ellipseOutMapper);
                }
                break;
            }
        }
        
    } // cvimgproc
} // stromx

