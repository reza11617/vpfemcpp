#pragma once
#include <iostream>
#include <fstream>
#include <cassert>
#include <cmath>
#include <Eigen/Dense>
#include <Eigen/Sparse>
#include <memory>
#include "Instrumentation.hpp"


typedef Eigen::Vector<long double, Eigen::Dynamic> VectorXld;
typedef Eigen::Matrix<long double, Eigen::Dynamic, Eigen::Dynamic> MatrixXld;
