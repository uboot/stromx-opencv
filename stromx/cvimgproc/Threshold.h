#ifndef STROMX_CVIMGPROC_THRESHOLD_H
#define STROMX_CVIMGPROC_THRESHOLD_H

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
        class STROMX_CVIMGPROC_API Threshold : public runtime::OperatorKernel
        {
        public:
            enum ThresholdTypeId
            {
                THRESH_BINARY,
                THRESH_BINARY_INV,
                THRESH_TRUNC,
                THRESH_TOZERO,
                THRESH_TOZERO_INV
            };
            enum DataFlowId
            {
                MANUAL,
                ALLOCATE,
                IN_PLACE
            };
            enum DataId
            {
                INPUT_DST,
                INPUT_SRC,
                OUTPUT_DST,
                OUTPUT_SRC,
                PARAMETER_DATA_FLOW,
                PARAMETER_MAXVAL,
                PARAMETER_THRESHOLD,
                PARAMETER_THRESHOLD_TYPE
            };
            Threshold();
            virtual OperatorKernel* clone() const { return new Threshold; }
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
            
            int convertThresholdType(const runtime::Enum & value);
            
            runtime::Float64 m_maxval;
            runtime::Float64 m_threshold;
            runtime::Enum m_thresholdType;
            runtime::Enum m_dataFlow;
            runtime::Input* m_dstDescription;
            runtime::NumericParameter<runtime::Float64>* m_maxvalParameter;
            runtime::Input* m_srcDescription;
            runtime::NumericParameter<runtime::Float64>* m_thresholdParameter;
            runtime::EnumParameter* m_thresholdTypeParameter;
            runtime::EnumParameter* m_dataFlowParameter;
        };
    } // cvimgproc
} // stromx

#endif // STROMX_CVIMGPROC_THRESHOLD_H
