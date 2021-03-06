#ifndef STROMX_CVIMGPROC_GAUSSIANBLUR_H
#define STROMX_CVIMGPROC_GAUSSIANBLUR_H

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
        class STROMX_CVIMGPROC_API GaussianBlur : public runtime::OperatorKernel
        {
        public:
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
                PARAMETER_KSIZEX,
                PARAMETER_KSIZEY,
                PARAMETER_SIGMA_X,
                PARAMETER_SIGMA_Y
            };
            GaussianBlur();
            virtual OperatorKernel* clone() const { return new GaussianBlur; }
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
            
            runtime::UInt32 m_ksizex;
            runtime::UInt32 m_ksizey;
            runtime::Float64 m_sigmaX;
            runtime::Float64 m_sigmaY;
            runtime::Enum m_dataFlow;
            runtime::Input* m_dstDescription;
            runtime::NumericParameter<runtime::UInt32>* m_ksizexParameter;
            runtime::NumericParameter<runtime::UInt32>* m_ksizeyParameter;
            runtime::NumericParameter<runtime::Float64>* m_sigmaXParameter;
            runtime::NumericParameter<runtime::Float64>* m_sigmaYParameter;
            runtime::Input* m_srcDescription;
            runtime::EnumParameter* m_dataFlowParameter;
        };
    } // cvimgproc
} // stromx

#endif // STROMX_CVIMGPROC_GAUSSIANBLUR_H
