#include<iostream>
#include<Eigen/Dense>
#include "D:\\NeuroKit\\iir1-1.9.4\\Iir.h"
#include "D:\\NeuroKit\\iir1-1.9.4\\iir\\Custom.h"


class PPGFilter{
    private:
        Eigen::MatrixXd data;
    
    public:
    
    PPGFilter(){}

    PPGFilter(Eigen::MatrixXd signal){
        data = signal;
        int n = signal.array().isNaN().sum();
        if(n > 0){
            std::cerr <<  "There are " << n << " missing data points in your signal."
                    " Filling missing values by using the forward filling method." << std::endl;
            data = ppg_clean_missing(signal);
        };
    }
    
    
    template <int nSOS>
        Eigen::MatrixXd SOSFilter(const double (&SOS_Parameter)[nSOS][6]){
            int length = data.cols();    //拿到signal的大小
        
        // const int nSOS = sizeof(SOS_Parameter) / sizeof(SOS_Parameter[0]);
        try {
            Iir::Custom::SOSCascade<nSOS> cust(SOS_Parameter);

             double filter_signal[length];    //创建过滤后的信号array
             double *signal_array= data.data(); //过滤signal array
            for (int i = 0; i < length; i++)
	        {
		        filter_signal[i] = cust.filter(signal_array[i]);
	        }
  
            Eigen::Map<Eigen::MatrixXd> res(filter_signal,1,length);    //从array还原回MatrixXd
            return res;
        }

        catch (const std::exception& e) {
            std::cerr << "Wrong parameters" << std::endl;
            return Eigen::MatrixXd();
        }
    }

    Eigen::MatrixXd PPGCleanMissing(Eigen::MatrixXd ppg_signal){
        int r = ppg_signal.cols();// 经过as_vector的处理，ppg_signal 应该已经变成一个一维的数组了
        for(int i = 0; i < r; i++ ){
            if(i >= 1 && std::isnan(ppg_signal(0,i))){
                ppg_signal(0,i) = ppg_signal(0,i-1);  //原python的方法也不能保证第一个值为NaN的时候进行填充
            };
        }
        return ppg_signal;
    }
};
