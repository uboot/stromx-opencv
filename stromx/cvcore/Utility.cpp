#include "Utility.h"

#include <opencv2/core/core.hpp>

namespace stromx
{
    namespace cvcore
    {
        double mean(const cv::Mat & input)
        {
            cv::Scalar value = cv::mean(input);
            return value[0];
        }
        
        void merge(const cv::Mat & input1, const cv::Mat & input2, cv::Mat & dst)
        {
            std::vector<cv::Mat> mv(2);
            mv[0] = input1;
            mv[1] = input2;
            cv::merge(mv, dst);
            
        }
        
        double sum(const cv::Mat & input)
        {
            cv::Scalar value = cv::sum(input);
            return value[0];
        }
        
    }
}
