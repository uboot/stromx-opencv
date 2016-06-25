#ifndef STROMX_CVIMGPROC_LAPLACIAN_H
#define STROMX_CVIMGPROC_LAPLACIAN_H

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
        class STROMX_CVIMGPROC_API Laplacian : public runtime::OperatorKernel
        {
        public:
            enum DdepthId
            {
                SAME,
                DEPTH_8_BIT,
                DEPTH_16_BIT
            };
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
                PARAMETER_DATA_FLOW,
                PARAMETER_DDEPTH,
                PARAMETER_DELTA,
                PARAMETER_KSIZE,
                PARAMETER_SCALE
            };
            Laplacian();
            virtual OperatorKernel* clone() const { return new Laplacian; }
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
            
            int convertDdepth(const runtime::Enum & value);
            
            runtime::Enum m_ddepth;
            runtime::Float64 m_delta;
            runtime::UInt32 m_ksize;
            runtime::Float64 m_scale;
            runtime::Enum m_dataFlow;
            runtime::EnumParameter* m_ddepthParameter;
            runtime::NumericParameter<runtime::Float64>* m_deltaParameter;
            runtime::Input* m_dstDescription;
            runtime::NumericParameter<runtime::UInt32>* m_ksizeParameter;
            runtime::NumericParameter<runtime::Float64>* m_scaleParameter;
            runtime::Input* m_srcDescription;
            runtime::EnumParameter* m_dataFlowParameter;
        };
    } // cvimgproc
} // stromx

#endif // STROMX_CVIMGPROC_LAPLACIAN_H
