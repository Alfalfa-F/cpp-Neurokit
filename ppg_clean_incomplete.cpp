using namespace std;
#include <vector>
#include <iostream>
#include <Eigen/Dense>
#include "signal_filter.cpp"

Eigen::MatrixXd _ppg_clean_missing(Eigen::MatrixXd ppg_signal);



Eigen::MatrixXd ppg_clean(Eigen::MatrixXd ppg_signal, int sampling_rate =1000, std::string method="elgendi"){

// 未处理心跳 heart_rate= None
    int n = ppg_signal.array().isNaN().sum();
        if(n > 0){
            std::cerr <<  "There are " << n << " missing data points in your signal."
                    " Filling missing values by using the forward filling method." << std::endl;
            ppg_signal = _ppg_clean_missing(ppg_signal);
        };
        // 统一大小写
        int len = method.length();
        for(int i = 0; i < len; i++){
            method[i] = tolower(method[i]);
        }

        if(method == "elgendi"){
            ppg_signal = _ppg_clean_elgendi(ppg_signal, sampling_rate);
        }
        else if(method == "nabian2018"){
            ppg_signal = _ppg_clean_nabian2018(ppg_signal, sampling_rate);
        }
        else if(method == "None"){
            ppg_signal = _ppg_clean_SOS(ppg_signal, sampling_rate);
        }
    return ppg_signal;
}

Eigen::MatrixXd _ppg_clean_missing(Eigen::MatrixXd ppg_signal){
int r = ppg_signal.cols();// 经过as_vector的处理，ppg_signal 应该已经变成一个一维的数组了
for(int i = 0; i < r; i++ ){
    if(i >= 1 && std::isnan(ppg_signal(0,i))){
        ppg_signal(0,i) = ppg_signal(0,i-1);//原python的方法也不能保证第一个值为NaN的时候进行填充
};}
return ppg_signal;
}


Eigen::MatrixXd _ppg_clean_elgendi(Eigen::MatrixXd ppg_signal, int sampling_rate){

Eigen::MatrixXd res = filter_elgendi(ppg_signal);
return res;
}

Eigen::MatrixXd _ppg_clean_nabian2018(Eigen::MatrixXd ppg_signal, int sampling_rate){

    Eigen::MatrixXd res = filter_nabian2018(ppg_signal);
return res;

}

Eigen::MatrixXd _ppg_clean_SOS(Eigen::MatrixXd ppg_signal, int sampling_rate){

    Eigen::MatrixXd res = filter_SOS(ppg_signal);
    return res;

}
