#ifndef STROMX_CVCALIB3D_GENERATEPATTERN_H
#define STROMX_CVCALIB3D_GENERATEPATTERN_H

#include "stromx/cvcalib3d/Config.h"
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
    namespace cvcalib3d
    {
        class STROMX_CVCALIB3D_API GeneratePattern : public runtime::OperatorKernel
        {
        public:
            enum DataFlowId
            {
                ALLOCATE
            };
            enum DataId
            {
                OUTPUT_CORNERS,
                PARAMETER_DATA_FLOW,
                PARAMETER_PATTERN_SIZE_X,
                PARAMETER_PATTERN_SIZE_Y,
                PARAMETER_SQUARE_SIZE
            };
            GeneratePattern();
            virtual OperatorKernel* clone() const { return new GeneratePattern; }
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
            
            runtime::UInt32 m_patternSizeX;
            runtime::UInt32 m_patternSizeY;
            runtime::Float32 m_squareSize;
            runtime::Enum m_dataFlow;
            runtime::Input* m_cornersDescription;
            runtime::NumericParameter<runtime::UInt32>* m_patternSizeXParameter;
            runtime::NumericParameter<runtime::UInt32>* m_patternSizeYParameter;
            runtime::NumericParameter<runtime::Float32>* m_squareSizeParameter;
            runtime::EnumParameter* m_dataFlowParameter;
        };
    } // cvcalib3d
} // stromx

#endif // STROMX_CVCALIB3D_GENERATEPATTERN_H
