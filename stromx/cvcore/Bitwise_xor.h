#ifndef STROMX_CVCORE_BITWISE_XOR_H
#define STROMX_CVCORE_BITWISE_XOR_H

#include "stromx/cvcore/Config.h"
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
    namespace cvcore
    {
        class STROMX_CVCORE_API Bitwise_xor : public runtime::OperatorKernel
        {
        public:
            enum DataFlowId
            {
                MANUAL,
                ALLOCATE
            };
            enum ConnectorId
            {
                DST,
                SRC_2,
                SRC_1
            };
            enum ParameterId
            {
                DATA_FLOW
            };
            Bitwise_xor();
            virtual OperatorKernel* clone() const { return new Bitwise_xor; }
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
            
            runtime::Enum m_dataFlow;
            runtime::Description* m_dstDescription;
            runtime::Description* m_src1Description;
            runtime::Description* m_src2Description;
            runtime::EnumParameter* m_dataFlowParameter;
        };
    } // cvcore
} // stromx

#endif // STROMX_CVCORE_BITWISE_XOR_H
