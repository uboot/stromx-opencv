#ifndef STROMX_CVIMGPROC_DISTANCETRANSFORM_H
#define STROMX_CVIMGPROC_DISTANCETRANSFORM_H

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
        class STROMX_CVIMGPROC_API DistanceTransform : public runtime::OperatorKernel
        {
        public:
            enum DistanceTypeId
            {
                DIST_L1,
                DIST_L2,
                DIST_C
            };
            enum MaskSizeId
            {
                SIZE_3,
                SIZE_5,
                SIZE_PRECISE
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
                PARAMETER_DISTANCE_TYPE,
                PARAMETER_MASK_SIZE
            };
            DistanceTransform();
            virtual OperatorKernel* clone() const { return new DistanceTransform; }
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
            
            int convertDistanceType(const runtime::Enum & value);
            int convertMaskSize(const runtime::Enum & value);
            
            runtime::Enum m_distanceType;
            runtime::Enum m_maskSize;
            runtime::Enum m_dataFlow;
            runtime::EnumParameter* m_distanceTypeParameter;
            runtime::Input* m_dstDescription;
            runtime::EnumParameter* m_maskSizeParameter;
            runtime::Input* m_srcDescription;
            runtime::EnumParameter* m_dataFlowParameter;
        };
    } // cvimgproc
} // stromx

#endif // STROMX_CVIMGPROC_DISTANCETRANSFORM_H
