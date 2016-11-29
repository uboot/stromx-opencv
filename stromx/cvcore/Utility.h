#ifndef STROMX_CVCORE_UTILITY_H
#define STROMX_CVCORE_UTILITY_H

#include <opencv2/core/core.hpp>

namespace stromx
{
    namespace cvcore
    {
        double mean(const cv::Mat & input);
        
        void merge(const cv::Mat & input1, const cv::Mat & input2, cv::Mat & dst);
        
        double sum(const cv::Mat & input);
        
    }
}
#endif // STROMX_CVCORE_UTILITY_H
