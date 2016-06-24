#ifndef STROMX_CVIMGPROC_CORNERSUBPIX_H
#define STROMX_CVIMGPROC_CORNERSUBPIX_H

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
        class STROMX_CVIMGPROC_API CornerSubPix : public runtime::OperatorKernel
        {
        public:
            enum DataFlowId
            {
                IN_PLACE
            };
            enum DataId
            {
                INPUT_POINT_MATRIX,
                INPUT_SRC,
                OUTPUT_POINT_MATRIX,
                PARAMETER_DATA_FLOW,
                PARAMETER_WIN_SIZE_X,
                PARAMETER_WIN_SIZE_Y
            };
            CornerSubPix();
            virtual OperatorKernel* clone() const { return new CornerSubPix; }
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
            
            runtime::UInt32 m_winSizeX;
            runtime::UInt32 m_winSizeY;
            runtime::Enum m_dataFlow;
            runtime::Input* m_pointMatrixDescription;
            runtime::Input* m_srcDescription;
            runtime::NumericParameter<runtime::UInt32>* m_winSizeXParameter;
            runtime::NumericParameter<runtime::UInt32>* m_winSizeYParameter;
            runtime::EnumParameter* m_dataFlowParameter;
        };
    } // cvimgproc
} // stromx

#endif // STROMX_CVIMGPROC_CORNERSUBPIX_H
