#include <vector>
#include <iostream>

using namespace std;

void init_zeros(unsigned int size,vector<vector<double>> & out){
    out.resize(size);
    for(unsigned int i=0;i < size;i++){
        out[i].resize(size);
        for(unsigned int j=0;j < size;j++){
            out[i][j] = 0.0;
        }
    }
}


void matrix_mult(vector<vector<double>> A, vector<vector<double>> B,vector<vector<double>> & out){ //solo para matrises validas
    unsigned long size_matrix_rows = A[0].size();
    unsigned long size_matrix_columns = A.size();

    out.resize(size_matrix_columns);

    for (unsigned long i=0;i < size_matrix_columns; i++) {
        out[i].resize(size_matrix_rows);
    }
    double sum = 0;
    for(unsigned long i=0; i < size_matrix_columns; i++){
        for(unsigned long j=0; j < size_matrix_rows; j++){
            sum = 0;
            for(unsigned long w=0; w < size_matrix_rows; w++){
                sum = sum + A[i][w]*B[w][j];
            }
            out[i][j] = sum;
        }
    }
}

void init_unitary(unsigned int size,vector<vector<double>> & out){
    out.resize(size);
    for(unsigned int i=0;i < size;i++){
        out[i].resize(size);
        for(unsigned int j=0;j < size;j++){
            if(i==j){
                out[i][j] = 1.0;
            }else{
                out[i][j] = 0.0;
            }
        }
    }
}

void matrix_pow(vector<vector<double>> A, int power,vector<vector<double>> & out){ //solo para matrises validas
    unsigned long size_matrix = A.size();

    vector<vector<double>> temp = A;
    vector<vector<double>> temp_next;

    if(power == 0){
        init_zeros(size_matrix,out);
        for (unsigned long i=0;i < size_matrix; i++) {
            out[i][i] = 1;
        }
    }else if(power == 1){
        out = A;
    }else{
        for(int i=1; i < power; i++){
            matrix_mult(temp,A,temp_next);
            temp = temp_next;
        }
        out = temp;
    }
}

void matrix_sum(vector<vector<double>> A, vector<vector<double>> B,vector<vector<double>> & out){ //solo para matrises validas
    unsigned long size_matrix_rows = A[0].size();
    unsigned long size_matrix_columns = A.size();
    out.resize(size_matrix_columns);

    for (unsigned long i=0;i < size_matrix_columns; i++) {
        out[i].resize(size_matrix_rows);
    }

    for(unsigned long i=0; i < size_matrix_columns; i++){
        for(unsigned long j=0; j < size_matrix_rows; j++){
            out[i][j] = A[i][j] + B[i][j];
        }
    }
}

void matrix_mult_scalar(vector<vector<double>> A, double scalar,vector<vector<double>> & out){ //solo para matrises validas
    unsigned long size_matrix_rows = A[0].size();
    unsigned long size_matrix_columns = A.size();
    out.resize(size_matrix_columns);

    for (unsigned long i=0;i < size_matrix_columns; i++) {
        out[i].resize(size_matrix_rows);
    }

    for(unsigned long i=0; i < size_matrix_columns; i++){
        for(unsigned long j=0; j < size_matrix_rows; j++){
            out[i][j] = A[i][j]*scalar;
        }
    }
}

void print_matrix(vector<vector<double>> A){
    unsigned long size_matrix_rows = A[0].size();
    unsigned long size_matrix_columns = A.size();
    cout << "-------------------------------------------" << endl;
    for(unsigned long i=0; i < size_matrix_columns; i++){
        for(unsigned long j=0; j < size_matrix_rows; j++){
            cout << A[i][j] << " ";
        }
        cout << endl;
    }
    cout << "-------------------------------------------" << endl;
}
