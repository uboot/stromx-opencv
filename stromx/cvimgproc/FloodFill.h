#ifndef STROMX_CVIMGPROC_FLOODFILL_H
#define STROMX_CVIMGPROC_FLOODFILL_H

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
        class STROMX_CVIMGPROC_API FloodFill : public runtime::OperatorKernel
        {
        public:
            enum DataFlowId
            {
                IN_PLACE
            };
            enum DataId
            {
                INPUT_SRC,
                OUTPUT_SRC,
                PARAMETER_DATA_FLOW,
                PARAMETER_NEW_VAL,
                PARAMETER_SEED_POINT_X,
                PARAMETER_SEED_POINT_Y
            };
            FloodFill();
            virtual OperatorKernel* clone() const { return new FloodFill; }
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
            
            runtime::Float64 m_newVal;
            runtime::UInt32 m_seedPointX;
            runtime::UInt32 m_seedPointY;
            runtime::Enum m_dataFlow;
            runtime::NumericParameter<runtime::Float64>* m_newValParameter;
            runtime::NumericParameter<runtime::UInt32>* m_seedPointXParameter;
            runtime::NumericParameter<runtime::UInt32>* m_seedPointYParameter;
            runtime::Input* m_srcDescription;
            runtime::EnumParameter* m_dataFlowParameter;
        };
    } // cvimgproc
} // stromx

#endif // STROMX_CVIMGPROC_FLOODFILL_H
