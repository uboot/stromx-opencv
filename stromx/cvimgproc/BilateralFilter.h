#ifndef STROMX_CVIMGPROC_BILATERALFILTER_H
#define STROMX_CVIMGPROC_BILATERALFILTER_H

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
        class STROMX_CVIMGPROC_API BilateralFilter : public runtime::OperatorKernel
        {
        public:
            enum DataFlowId
            {
                MANUAL,
                ALLOCATE
            };
            enum DataId
            {
                INPUT_DST,
                INPUT_SRC,
                OUTPUT_DST,
                PARAMETER_D,
                PARAMETER_DATA_FLOW,
                PARAMETER_SIGMA_COLOR,
                PARAMETER_SIGMA_SPACE
            };
            BilateralFilter();
            virtual OperatorKernel* clone() const { return new BilateralFilter; }
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
            
            runtime::UInt32 m_d;
            runtime::Float64 m_sigmaColor;
            runtime::Float64 m_sigmaSpace;
            runtime::Enum m_dataFlow;
            runtime::NumericParameter<runtime::UInt32>* m_dParameter;
            runtime::Input* m_dstDescription;
            runtime::NumericParameter<runtime::Float64>* m_sigmaColorParameter;
            runtime::NumericParameter<runtime::Float64>* m_sigmaSpaceParameter;
            runtime::Input* m_srcDescription;
            runtime::EnumParameter* m_dataFlowParameter;
        };
    } // cvimgproc
} // stromx

#endif // STROMX_CVIMGPROC_BILATERALFILTER_H
