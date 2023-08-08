#include <iostream>
#include <Eigen/Dense>

class PPG_FindPeaks {
public:
    Eigen::VectorXi findPeaks(const Eigen::MatrixXd& signal, bool show = false) {
        int N = signal.cols(); // 使用 cols() 获取signal的长度
        int L = static_cast<int>(std::ceil(N / 2.0) - 1);

        Eigen::MatrixXd x = signal.rowwise() - signal.colwise().mean(); // Detrend

        Eigen::MatrixXd m_max(L, N);
        Eigen::MatrixXd m_min(L, N);
        m_max.setZero();
        m_min.setZero();

        for (int k = 1; k < L; ++k) {
            for (int i = k + 2; i < N - k + 1; ++i) {
                if (x(i - 1) > x(i - k - 1) && x(i - 1) > x(i + k - 1)) {
                    m_max(k - 1, i - 1) = 1.0;
                }
                if (x(i - 1) < x(i - k - 1) && x(i - 1) < x(i + k - 1)) {
                    m_min(k - 1, i - 1) = 1.0;
                }
            }
        }

        Eigen::VectorXi gamma_max = m_max.rowwise().sum();
        Eigen::VectorXi gamma_min = m_min.rowwise().sum();

        int lambda_max = gamma_max.argmax();
        int lambda_min = gamma_min.argmax();

        m_max.conservativeResize(lambda_max + 1, Eigen::NoChange);
        m_min.conservativeResize(lambda_min + 1, Eigen::NoChange);

        Eigen::VectorXi m_max_sum = (m_max.array() == 0).rowwise().count();
        Eigen::VectorXi m_min_sum = (m_min.array() == 0).rowwise().count();

        Eigen::VectorXi peaks;
        for (int i = 0; i < N; ++i) {
            if (m_max_sum(i) == 0) {
                peaks.conservativeResize(peaks.size() + 1);
                peaks(peaks.size() - 1) = i;
            }
        }

        return peaks;
    }
};
