#ifndef STROMX_CVIMGPROC_ERODE_H
#define STROMX_CVIMGPROC_ERODE_H

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
        class STROMX_CVIMGPROC_API Erode : public runtime::OperatorKernel
        {
        public:
            enum ShapeId
            {
                MORPH_RECT,
                MORPH_ELLIPSE,
                MORPH_CROSS
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
                PARAMETER_ITERATIONS,
                PARAMETER_KSIZEX,
                PARAMETER_KSIZEY,
                PARAMETER_SHAPE
            };
            Erode();
            virtual OperatorKernel* clone() const { return new Erode; }
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
            
            int convertShape(const runtime::Enum & value);
            
            runtime::UInt32 m_iterations;
            runtime::UInt32 m_ksizex;
            runtime::UInt32 m_ksizey;
            runtime::Enum m_shape;
            runtime::Enum m_dataFlow;
            runtime::Input* m_dstDescription;
            runtime::NumericParameter<runtime::UInt32>* m_iterationsParameter;
            runtime::NumericParameter<runtime::UInt32>* m_ksizexParameter;
            runtime::NumericParameter<runtime::UInt32>* m_ksizeyParameter;
            runtime::EnumParameter* m_shapeParameter;
            runtime::Input* m_srcDescription;
            runtime::EnumParameter* m_dataFlowParameter;
        };
    } // cvimgproc
} // stromx

#endif // STROMX_CVIMGPROC_ERODE_H
