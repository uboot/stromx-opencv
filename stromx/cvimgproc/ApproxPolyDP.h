#ifndef STROMX_CVIMGPROC_APPROXPOLYDP_H
#define STROMX_CVIMGPROC_APPROXPOLYDP_H

#include "stromx/cvimgproc/Config.h"
#include <stromx/cvsupport/Matrix.h>
#include <stromx/runtime/Enum.h>
#include <stromx/runtime/EnumParameter.h>
#include <stromx/runtime/List.h>
#include <stromx/runtime/MatrixParameter.h>
#include <stromx/runtime/NumericParameter.h>
#include <stromx/runtime/OperatorException.h>
#include <stromx/runtime/OperatorKernel.h>
#include <stromx/runtime/Primitive.h>
#include <stromx/runtime/Variant.h>
#include <stromx/runtime/Visualization.h>

namespace stromx
{
    namespace cvimgproc
    {
        class STROMX_CVIMGPROC_API ApproxPolyDP : public runtime::OperatorKernel
        {
        public:
            enum DataFlowId
            {
                ALLOCATE
            };
            enum DataId
            {
                INPUT_CURVE,
                OUTPUT_OUT_CURVE,
                PARAMETER_CLOSED,
                PARAMETER_DATA_FLOW,
                PARAMETER_EPSILON
            };
            ApproxPolyDP();
            virtual OperatorKernel* clone() const { return new ApproxPolyDP; }
            virtual void setParameter(const unsigned int id, const runtime::Data& value);
            virtual const runtime::DataRef getParameter(const unsigned int id) const;
            void initialize();
            virtual void execute(runtime::DataProvider& provider);
            
        private:
            static const std::string PACKAGE;
            static const runtime::Version VERSION;
            static const std::string TYPE;
            
            const std::vector<const runtime::Parameter*> setupInitParameters();
            const std::vector<const runtime::Parameter*> setupParameters();
            const std::vector<const runtime::Input*> setupInputs();
            const std::vector<const runtime::Output*> setupOutputs();
            
            runtime::Bool m_closed;
            runtime::Float64 m_epsilon;
            runtime::Enum m_dataFlow;
            runtime::Parameter* m_closedParameter;
            runtime::Input* m_curveDescription;
            runtime::NumericParameter<runtime::Float64>* m_epsilonParameter;
            runtime::Input* m_outCurveDescription;
            runtime::EnumParameter* m_dataFlowParameter;
        };
    } // cvimgproc
} // stromx

#endif // STROMX_CVIMGPROC_APPROXPOLYDP_H
