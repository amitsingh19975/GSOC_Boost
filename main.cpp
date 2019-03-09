#include "include/matrix_v3/matrix.hpp"
#include "include/matrix_v3/dynamic_engine.hpp"
#include "include/matrix_v3/static_engine.hpp"
#include "test/matrix_test_v3_dynamic.hpp"
#include "test/matrix_test_v3_dynamic_sparse.hpp"
#include "test/matrix_test_v3_static.hpp"
#include <algorithm>
#include <cassert>
#include <chrono>
#include <complex>

using namespace sm_v3;

int main(){
    // smatrix_test::testIntAssign();
    // smatrix_test::testIntCompare();
    // smatrix_test::testIntAdd();
    // smatrix_test::testIntAddAssign();
    // smatrix_test::testIntSub();
    // smatrix_test::testIntSubAssign();
    // smatrix_test::testIntMul();
    // smatrix_test::testIntMulAssign();
    // smatrix_test::testComplexAssign();
    // smatrix_test::testComplexCompare();
    // smatrix_test::testComplexAdd();
    // smatrix_test::testComplexSub();
    // smatrix_test::testComplexSubAssign();
    // smatrix_test::testComplexAddAssign();
    // smatrix_test::testComplexMul();
    // smatrix_test::testComplexMulAssign();
    // smatrix_test::testIntAssign();
    
    // dynamic_matrix_test::testIntCompare();
    // dynamic_matrix_test::testIntAdd();
    // dynamic_matrix_test::testIntAddAssign();
    // dynamic_matrix_test::testIntSub();
    // dynamic_matrix_test::testIntSubAssign();
    // dynamic_matrix_test::testIntMul();
    // dynamic_matrix_test::testIntMulAssign();
    // dynamic_matrix_test::testComplexAssign();
    // dynamic_matrix_test::testComplexCompare();
    // dynamic_matrix_test::testComplexAdd();
    // dynamic_matrix_test::testComplexSub();
    // dynamic_matrix_test::testComplexSubAssign();
    // dynamic_matrix_test::testComplexAddAssign();
    // dynamic_matrix_test::testComplexMul();
    // dynamic_matrix_test::testComplexMulAssign();
    
    dynamic_sparse_matrix_test::testIntCompare();
    dynamic_sparse_matrix_test::testIntAdd();
    dynamic_sparse_matrix_test::testIntAddAssign();
    dynamic_sparse_matrix_test::testIntSub();
    dynamic_sparse_matrix_test::testIntSubAssign();
    dynamic_sparse_matrix_test::testIntMul();
    dynamic_sparse_matrix_test::testIntMulAssign();
    dynamic_sparse_matrix_test::testComplexAssign();
    dynamic_sparse_matrix_test::testComplexCompare();
    dynamic_sparse_matrix_test::testComplexAdd();
    dynamic_sparse_matrix_test::testComplexSub();
    dynamic_sparse_matrix_test::testComplexSubAssign();
    dynamic_sparse_matrix_test::testComplexAddAssign();
    dynamic_sparse_matrix_test::testComplexMul();
    dynamic_sparse_matrix_test::testComplexMulAssign();
    // std::vector<int> m ={10,0,0,0,0,8,0,6,0,0,3,0,0,0,0,2}; 
    return 0;
}