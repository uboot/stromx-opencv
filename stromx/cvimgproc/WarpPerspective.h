#ifndef STROMX_CVIMGPROC_WARPPERSPECTIVE_H
#define STROMX_CVIMGPROC_WARPPERSPECTIVE_H

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
        class STROMX_CVIMGPROC_API WarpPerspective : public runtime::OperatorKernel
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
                PARAMETER_AFFINE_M,
                PARAMETER_DATA_FLOW,
                PARAMETER_DSIZEX,
                PARAMETER_DSIZEY
            };
            WarpPerspective();
            virtual OperatorKernel* clone() const { return new WarpPerspective; }
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
            
            cvsupport::Matrix m_affineM;
            runtime::UInt32 m_dsizex;
            runtime::UInt32 m_dsizey;
            runtime::Enum m_dataFlow;
            runtime::MatrixParameter* m_affineMParameter;
            runtime::NumericParameter<runtime::UInt32>* m_dsizexParameter;
            runtime::NumericParameter<runtime::UInt32>* m_dsizeyParameter;
            runtime::Input* m_dstDescription;
            runtime::Input* m_srcDescription;
            runtime::EnumParameter* m_dataFlowParameter;
        };
    } // cvimgproc
} // stromx

#endif // STROMX_CVIMGPROC_WARPPERSPECTIVE_H
