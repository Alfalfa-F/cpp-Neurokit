#include <iostream>
#include <stdio.h>
#include "signal_filter.h"
#include <Eigen/Dense>
#include <Iir.h>
Eigen::MatrixXd filter_elgendi(Eigen::MatrixXd signal){

// 原scipy使用的滤波器
return signal;
}

Eigen::MatrixXd filter_nabian2018(Eigen::MatrixXd signal){
    //原scipy使用的滤波器
    return signal;
}


Eigen::MatrixXd filter_SOS(Eigen::MatrixXd signal, int sampling_rate){
    // const double[][6] SOS = getSOS()
  
    length = signal.cols(); //拿到signal的大小
    
    const double SOS[][6];   //未确定SOS的大小
    const int nSOS = sizeof(SOS) / sizeof(SOS[0]);
    try {
        Iir::Custom::SOSCascade<nSOS> cust(SOS);;
    }
    catch (const std::exception& e) {
        std::cerr << "Wrong parameters" << std::endl;
        return;
    }
  double filter_signal[length];  //创建过滤后的信号array
  double* signal_array= signal.data();
    
    //过滤signal array
    for (int i = 0; i < length; i++)
	{
		filter_signal[i] = cust.filter(signal_array[i]);
    
	}
  
  Eigen::Map<Eigen::MatrixXd> res(filter_signal,1,length) //从array还原回MatrixXd

return res;
}
