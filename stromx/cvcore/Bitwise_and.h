#ifndef STROMX_CVCORE_BITWISE_AND_H
#define STROMX_CVCORE_BITWISE_AND_H

#include "stromx/cvcore/Config.h"
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
    namespace cvcore
    {
        class STROMX_CVCORE_API Bitwise_and : public runtime::OperatorKernel
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
                INPUT_SRC_1,
                INPUT_SRC_2,
                OUTPUT_DST,
                PARAMETER_DATA_FLOW
            };
            Bitwise_and();
            virtual OperatorKernel* clone() const { return new Bitwise_and; }
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
            
            runtime::Enum m_dataFlow;
            runtime::Input* m_dstDescription;
            runtime::Input* m_src1Description;
            runtime::Input* m_src2Description;
            runtime::EnumParameter* m_dataFlowParameter;
        };
    } // cvcore
} // stromx

#endif // STROMX_CVCORE_BITWISE_AND_H
