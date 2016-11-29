#ifndef STROMX_CVCALIB3D_STEREOCALIBRATE_H
#define STROMX_CVCALIB3D_STEREOCALIBRATE_H

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
        class STROMX_CVCALIB3D_API StereoCalibrate : public runtime::OperatorKernel
        {
        public:
            enum DataFlowId
            {
                EXTRINSICS,
                INTRINSICS
            };
            enum DataId
            {
                INPUT_IMAGE_POINTS_1,
                INPUT_IMAGE_POINTS_2,
                INPUT_OBJECT_POINTS,
                OUTPUT_CAMERA_MATRIX_1_ARG,
                OUTPUT_CAMERA_MATRIX_2_ARG,
                OUTPUT_DIST_COEFFS_1_ARG,
                OUTPUT_DIST_COEFFS_2_ARG,
                OUTPUT_RVEC,
                OUTPUT_TVEC,
                PARAMETER_CAMERA_MATRIX_1,
                PARAMETER_CAMERA_MATRIX_2,
                PARAMETER_DATA_FLOW,
                PARAMETER_DIST_COEFFS_1,
                PARAMETER_DIST_COEFFS_2,
                PARAMETER_IMAGE_SIZE_X,
                PARAMETER_IMAGE_SIZE_Y
            };
            StereoCalibrate();
            virtual OperatorKernel* clone() const { return new StereoCalibrate; }
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
            
            cvsupport::Matrix m_cameraMatrix1;
            cvsupport::Matrix m_cameraMatrix2;
            cvsupport::Matrix m_distCoeffs1;
            cvsupport::Matrix m_distCoeffs2;
            runtime::UInt32 m_imageSizeX;
            runtime::UInt32 m_imageSizeY;
            runtime::Enum m_dataFlow;
            runtime::MatrixParameter* m_cameraMatrix1Parameter;
            runtime::Input* m_cameraMatrix1ArgDescription;
            runtime::MatrixParameter* m_cameraMatrix2Parameter;
            runtime::Input* m_cameraMatrix2ArgDescription;
            runtime::MatrixParameter* m_distCoeffs1Parameter;
            runtime::Input* m_distCoeffs1ArgDescription;
            runtime::MatrixParameter* m_distCoeffs2Parameter;
            runtime::Input* m_distCoeffs2ArgDescription;
            runtime::Input* m_imagePoints1Description;
            runtime::Input* m_imagePoints2Description;
            runtime::NumericParameter<runtime::UInt32>* m_imageSizeXParameter;
            runtime::NumericParameter<runtime::UInt32>* m_imageSizeYParameter;
            runtime::Input* m_objectPointsDescription;
            runtime::Input* m_rvecDescription;
            runtime::Input* m_tvecDescription;
            runtime::EnumParameter* m_dataFlowParameter;
        };
    } // cvcalib3d
} // stromx

#endif // STROMX_CVCALIB3D_STEREOCALIBRATE_H
