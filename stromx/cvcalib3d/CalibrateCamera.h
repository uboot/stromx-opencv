#ifndef STROMX_CVCALIB3D_CALIBRATECAMERA_H
#define STROMX_CVCALIB3D_CALIBRATECAMERA_H

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
        class STROMX_CVCALIB3D_API CalibrateCamera : public runtime::OperatorKernel
        {
        public:
            enum DataFlowId
            {
                ALLOCATE
            };
            enum DataId
            {
                INPUT_IMAGE_POINTS,
                INPUT_OBJECT_POINTS,
                OUTPUT_CAMERA_MATRIX,
                OUTPUT_DIST_COEFFS,
                PARAMETER_DATA_FLOW,
                PARAMETER_IMAGE_SIZE_X,
                PARAMETER_IMAGE_SIZE_Y
            };
            CalibrateCamera();
            virtual OperatorKernel* clone() const { return new CalibrateCamera; }
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
            
            runtime::UInt32 m_imageSizeX;
            runtime::UInt32 m_imageSizeY;
            runtime::Enum m_dataFlow;
            runtime::Input* m_cameraMatrixDescription;
            runtime::Input* m_distCoeffsDescription;
            runtime::Input* m_imagePointsDescription;
            runtime::NumericParameter<runtime::UInt32>* m_imageSizeXParameter;
            runtime::NumericParameter<runtime::UInt32>* m_imageSizeYParameter;
            runtime::Input* m_objectPointsDescription;
            runtime::EnumParameter* m_dataFlowParameter;
        };
    } // cvcalib3d
} // stromx

#endif // STROMX_CVCALIB3D_CALIBRATECAMERA_H
