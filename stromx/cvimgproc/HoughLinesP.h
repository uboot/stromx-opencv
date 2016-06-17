#ifndef STROMX_CVIMGPROC_HOUGHLINESP_H
#define STROMX_CVIMGPROC_HOUGHLINESP_H

#include "stromx/cvimgproc/Config.h"
#include <stromx/cvsupport/Matrix.h>
#include <stromx/runtime/Enum.h>
#include <stromx/runtime/EnumParameter.h>
#include <stromx/runtime/List.h>
#include <stromx/runtime/MatrixDescription.h>
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
        class STROMX_CVIMGPROC_API HoughLinesP : public runtime::OperatorKernel
        {
        public:
            enum DataFlowId
            {
                ALLOCATE
            };
            enum DataId
            {
                INPUT_SRC,
                OUTPUT_DST,
                PARAMETER_DATA_FLOW,
                PARAMETER_MAX_LINE_GAP,
                PARAMETER_MIN_LINE_LENGTH,
                PARAMETER_RHO,
                PARAMETER_THETA,
                PARAMETER_THRESHOLD
            };
            HoughLinesP();
            virtual OperatorKernel* clone() const { return new HoughLinesP; }
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
            const std::vector<const runtime::Description*> setupInputs();
            const std::vector<const runtime::Description*> setupOutputs();
            
            runtime::Float64 m_maxLineGap;
            runtime::Float64 m_minLineLength;
            runtime::Float64 m_rho;
            runtime::Float64 m_theta;
            runtime::UInt32 m_threshold;
            runtime::Enum m_dataFlow;
            runtime::MatrixDescription* m_dstDescription;
            runtime::NumericParameter<runtime::Float64>* m_maxLineGapParameter;
            runtime::NumericParameter<runtime::Float64>* m_minLineLengthParameter;
            runtime::NumericParameter<runtime::Float64>* m_rhoParameter;
            runtime::Description* m_srcDescription;
            runtime::NumericParameter<runtime::Float64>* m_thetaParameter;
            runtime::NumericParameter<runtime::UInt32>* m_thresholdParameter;
            runtime::EnumParameter* m_dataFlowParameter;
        };
    } // cvimgproc
} // stromx

#endif // STROMX_CVIMGPROC_HOUGHLINESP_H
