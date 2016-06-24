#ifndef STROMX_CVIMGPROC_RESIZE_H
#define STROMX_CVIMGPROC_RESIZE_H

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
        class STROMX_CVIMGPROC_API Resize : public runtime::OperatorKernel
        {
        public:
            enum InterpolationId
            {
                INTER_NEAREST,
                INTER_LINEAR
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
                PARAMETER_DSIZEX,
                PARAMETER_DSIZEY,
                PARAMETER_FX,
                PARAMETER_FY,
                PARAMETER_INTERPOLATION
            };
            Resize();
            virtual OperatorKernel* clone() const { return new Resize; }
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
            
            int convertInterpolation(const runtime::Enum & value);
            
            runtime::UInt32 m_dsizex;
            runtime::UInt32 m_dsizey;
            runtime::Float64 m_fx;
            runtime::Float64 m_fy;
            runtime::Enum m_interpolation;
            runtime::Enum m_dataFlow;
            runtime::NumericParameter<runtime::UInt32>* m_dsizexParameter;
            runtime::NumericParameter<runtime::UInt32>* m_dsizeyParameter;
            runtime::Input* m_dstDescription;
            runtime::NumericParameter<runtime::Float64>* m_fxParameter;
            runtime::NumericParameter<runtime::Float64>* m_fyParameter;
            runtime::EnumParameter* m_interpolationParameter;
            runtime::Input* m_srcDescription;
            runtime::EnumParameter* m_dataFlowParameter;
        };
    } // cvimgproc
} // stromx

#endif // STROMX_CVIMGPROC_RESIZE_H
