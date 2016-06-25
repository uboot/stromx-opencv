#ifndef STROMX_CVCALIB3D_SOLVEPNP_H
#define STROMX_CVCALIB3D_SOLVEPNP_H

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
        class STROMX_CVCALIB3D_API SolvePnP : public runtime::OperatorKernel
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
                OUTPUT_RVEC,
                OUTPUT_TVEC,
                PARAMETER_CAMERA_MATRIX,
                PARAMETER_DATA_FLOW,
                PARAMETER_DIST_COEFFS
            };
            SolvePnP();
            virtual OperatorKernel* clone() const { return new SolvePnP; }
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
            
            cvsupport::Matrix m_cameraMatrix;
            cvsupport::Matrix m_distCoeffs;
            runtime::Enum m_dataFlow;
            runtime::MatrixParameter* m_cameraMatrixParameter;
            runtime::MatrixParameter* m_distCoeffsParameter;
            runtime::Input* m_imagePointsDescription;
            runtime::Input* m_objectPointsDescription;
            runtime::Input* m_rvecDescription;
            runtime::Input* m_tvecDescription;
            runtime::EnumParameter* m_dataFlowParameter;
        };
    } // cvcalib3d
} // stromx

#endif // STROMX_CVCALIB3D_SOLVEPNP_H
