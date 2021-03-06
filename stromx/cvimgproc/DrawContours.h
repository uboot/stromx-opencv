#ifndef STROMX_CVIMGPROC_DRAWCONTOURS_H
#define STROMX_CVIMGPROC_DRAWCONTOURS_H

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
        class STROMX_CVIMGPROC_API DrawContours : public runtime::OperatorKernel
        {
        public:
            enum DataFlowId
            {
                IN_PLACE
            };
            enum DataId
            {
                INPUT_CONTOURS,
                INPUT_IMG,
                OUTPUT_IMG,
                PARAMETER_CH_1,
                PARAMETER_CH_2,
                PARAMETER_CH_3,
                PARAMETER_DATA_FLOW,
                PARAMETER_THICKNESS
            };
            DrawContours();
            virtual OperatorKernel* clone() const { return new DrawContours; }
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
            
            runtime::UInt8 m_ch1;
            runtime::UInt8 m_ch2;
            runtime::UInt8 m_ch3;
            runtime::Int32 m_thickness;
            runtime::Enum m_dataFlow;
            runtime::NumericParameter<runtime::UInt8>* m_ch1Parameter;
            runtime::NumericParameter<runtime::UInt8>* m_ch2Parameter;
            runtime::NumericParameter<runtime::UInt8>* m_ch3Parameter;
            runtime::Input* m_contoursDescription;
            runtime::Input* m_imgDescription;
            runtime::NumericParameter<runtime::Int32>* m_thicknessParameter;
            runtime::EnumParameter* m_dataFlowParameter;
        };
    } // cvimgproc
} // stromx

#endif // STROMX_CVIMGPROC_DRAWCONTOURS_H
