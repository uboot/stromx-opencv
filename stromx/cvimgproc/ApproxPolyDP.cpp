#include "stromx/cvimgproc/ApproxPolyDP.h"

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
        const std::string ApproxPolyDP::PACKAGE(STROMX_CVIMGPROC_PACKAGE_NAME);
        const runtime::Version ApproxPolyDP::VERSION(STROMX_CVIMGPROC_VERSION_MAJOR, STROMX_CVIMGPROC_VERSION_MINOR, STROMX_CVIMGPROC_VERSION_PATCH);
        const std::string ApproxPolyDP::TYPE("ApproxPolyDP");
        
        ApproxPolyDP::ApproxPolyDP()
          : runtime::OperatorKernel(TYPE, PACKAGE, VERSION, setupInitParameters()),
            m_closed(false),
            m_epsilon(10.0),
            m_dataFlow()
        {
        }
        
        const runtime::DataRef ApproxPolyDP::getParameter(unsigned int id) const
        {
            switch(id)
            {
            case PARAMETER_CLOSED:
                return m_closed;
            case PARAMETER_EPSILON:
                return m_epsilon;
            case PARAMETER_DATA_FLOW:
                return m_dataFlow;
            default:
                throw runtime::WrongParameterId(id, *this);
            }
        }
        
        void ApproxPolyDP::setParameter(unsigned int id, const runtime::Data& value)
        {
            try
            {
                switch(id)
                {
                case PARAMETER_CLOSED:
                    {
                        const runtime::Bool & castedValue = runtime::data_cast<runtime::Bool>(value);
                        if(! castedValue.variant().isVariant(runtime::Variant::BOOL))
                        {
                            throw runtime::WrongParameterType(parameter(id), *this);
                        }
                        m_closed = castedValue;
                    }
                    break;
                case PARAMETER_EPSILON:
                    {
                        const runtime::Float64 & castedValue = runtime::data_cast<runtime::Float64>(value);
                        if(! castedValue.variant().isVariant(runtime::Variant::FLOAT_64))
                        {
                            throw runtime::WrongParameterType(parameter(id), *this);
                        }
                        cvsupport::checkNumericValue(castedValue, m_epsilonParameter, *this);
                        m_epsilon = castedValue;
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
        
        const std::vector<const runtime::Parameter*> ApproxPolyDP::setupInitParameters()
        {
            std::vector<const runtime::Parameter*> parameters;
            
            return parameters;
        }
        
        const std::vector<const runtime::Parameter*> ApproxPolyDP::setupParameters()
        {
            std::vector<const runtime::Parameter*> parameters;
            
            switch(int(m_dataFlow))
            {
            case(ALLOCATE):
                {
                    m_epsilonParameter = new runtime::NumericParameter<runtime::Float64>(PARAMETER_EPSILON);
                    m_epsilonParameter->setAccessMode(runtime::Parameter::ACTIVATED_WRITE);
                    m_epsilonParameter->setTitle(L_("Maximal error in pixels"));
                    m_epsilonParameter->setMin(runtime::Float64(0.0));
                    parameters.push_back(m_epsilonParameter);
                    
                    m_closedParameter = new runtime::Parameter(PARAMETER_CLOSED, runtime::Variant::BOOL);
                    m_closedParameter->setAccessMode(runtime::Parameter::ACTIVATED_WRITE);
                    m_closedParameter->setTitle(L_("Curve is closed"));
                    parameters.push_back(m_closedParameter);
                    
                }
                break;
            }
            
            return parameters;
        }
        
        const std::vector<const runtime::Input*> ApproxPolyDP::setupInputs()
        {
            std::vector<const runtime::Input*> inputs;
            
            switch(int(m_dataFlow))
            {
            case(ALLOCATE):
                {
                    m_curveDescription = new runtime::Input(INPUT_CURVE, runtime::Variant::INT_32_MATRIX || runtime::Variant::FLOAT_32_MATRIX);
                    m_curveDescription->setTitle("Polygon");
                    m_curveDescription->setVisualization(runtime::Visualization::POLYGON || runtime::Visualization::POLYLINE);
                    m_curveDescription->setRows(0);
                    m_curveDescription->setCols(2);
                    inputs.push_back(m_curveDescription);
                    
                }
                break;
            }
            
            return inputs;
        }
        
        const std::vector<const runtime::Output*> ApproxPolyDP::setupOutputs()
        {
            std::vector<const runtime::Output*> outputs;
            
            switch(int(m_dataFlow))
            {
            case(ALLOCATE):
                {
                    runtime::Output* outCurve = new runtime::Output(OUTPUT_OUT_CURVE, runtime::Variant::INT_32_MATRIX || runtime::Variant::FLOAT_32_MATRIX);
                    outCurve->setTitle(L_("Polygon"));
                    outCurve->setVisualization(runtime::Visualization::POLYGON || runtime::Visualization::POLYLINE);
                    outCurve->setRows(0);
                    outCurve->setCols(2);
                    outputs.push_back(outCurve);
                    
                }
                break;
            }
            
            return outputs;
        }
        
        void ApproxPolyDP::initialize()
        {
            runtime::OperatorKernel::initialize(setupInputs(), setupOutputs(), setupParameters());
        }
        
        void ApproxPolyDP::execute(runtime::DataProvider & provider)
        {
            switch(int(m_dataFlow))
            {
            case(ALLOCATE):
                {
                    runtime::Id2DataPair curveInMapper(INPUT_CURVE);
                    
                    provider.receiveInputData(curveInMapper);
                    
                    const runtime::Data* curveData = 0;
                    
                    runtime::ReadAccess curveReadAccess;
                    
                    curveReadAccess = runtime::ReadAccess(curveInMapper.data());
                    curveData = &curveReadAccess.get();
                    
                    if(! curveData->variant().isVariant(m_curveDescription->variant()))
                    {
                        throw runtime::InputError(INPUT_CURVE, *this, "Wrong input data variant.");
                    }
                    
                    const runtime::Matrix* curveCastedData = runtime::data_cast<runtime::Matrix>(curveData);
                    cvsupport::checkMatrixValue(*curveCastedData, m_curveDescription, *this);
                    
                    cv::Mat curveCvData = cvsupport::getOpenCvMat(*curveCastedData, 2);
                    cv::Mat outCurveCvData;
                    double epsilonCvData = double(m_epsilon);
                    bool closedCvData = bool(m_closed);
                    
                    cv::approxPolyDP(curveCvData, outCurveCvData, epsilonCvData, closedCvData);
                    
                    runtime::Matrix* outCurveCastedData = new cvsupport::Matrix(outCurveCvData);
                    runtime::DataContainer outCurveOutContainer = runtime::DataContainer(outCurveCastedData);
                    runtime::Id2DataPair outCurveOutMapper(OUTPUT_OUT_CURVE, outCurveOutContainer);
                    
                    provider.sendOutputData(outCurveOutMapper);
                }
                break;
            }
        }
        
    } // cvimgproc
} // stromx

