#ifndef STROMX_CVIMGPROC_FINDCONTOURS_H
#define STROMX_CVIMGPROC_FINDCONTOURS_H

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
        class STROMX_CVIMGPROC_API FindContours : public runtime::OperatorKernel
        {
        public:
            enum MethodId
            {
                CHAIN_APPROX_NONE,
                CHAIN_APPROX_SIMPLE,
                CHAIN_APPROX_TC89_L1,
                CHAIN_APPROX_TC89_KCOS
            };
            enum ModeId
            {
                RETR_EXTERNAL,
                RETR_LIST
            };
            enum DataFlowId
            {
                ALLOCATE
            };
            enum DataId
            {
                INPUT_SRC,
                OUTPUT_DST,
                PARAMETER_DATA_FLOW,
                PARAMETER_METHOD,
                PARAMETER_MODE
            };
            FindContours();
            virtual OperatorKernel* clone() const { return new FindContours; }
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
            
            int convertMethod(const runtime::Enum & value);
            int convertMode(const runtime::Enum & value);
            
            runtime::Enum m_method;
            runtime::Enum m_mode;
            runtime::Enum m_dataFlow;
            runtime::Input* m_dstDescription;
            runtime::EnumParameter* m_methodParameter;
            runtime::EnumParameter* m_modeParameter;
            runtime::Input* m_srcDescription;
            runtime::EnumParameter* m_dataFlowParameter;
        };
    } // cvimgproc
} // stromx

#endif // STROMX_CVIMGPROC_FINDCONTOURS_H
