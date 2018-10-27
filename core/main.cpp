#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <math.h>
#include "./factorial.cpp"
#include "./matrix.cpp"

using namespace std;


void pi_n(vector<vector<double>> init_vector,vector<vector<double>> p_matrix,int n, vector<vector<double>> & output){
    vector<vector<double>> temp = init_vector;

    for(int i = 0; i < n; i++){
        matrix_mult(temp,p_matrix,temp);
    }
    output = temp;
}

double p_n(int n, double time, double lambda){
    double e = 2.7182818284590452353602874;
    double lambda_time = (lambda*time);
    double p_previous = pow(e,-(lambda_time));
    double p = p_previous;
    for(int i = 0; i < n; i++){
        p = (lambda_time/n)*p_previous;
        p_previous = p;
    }
    return p;
}

int main(int argc, char *argv[])
{
    double tmp_target = atof(argv[1]);
    string chain = argv[2];
    string continuous_flag = argv[3];
    double delta_t = 0;
    string q_matrix_flag;
    string p_matrix_flag;
    double lambda = 0;
    int target;
    double e = 2.7182818284590452353602874;
    double final_check = 0;

    if (continuous_flag == "true"){
        delta_t = atof(argv[4]);
        target = int(tmp_target/delta_t);
        q_matrix_flag = argv[5];
        p_matrix_flag = argv[6];
    }else{
        target = int(tmp_target);
    }
    ifstream inFile;
    inFile.open(chain);

    if (!inFile) {
        cerr << "Unable to open file datafile.txt";
        exit(1);   // call system to stop
    }
//temp variables
    vector<double> temp;
    string line;
    string number;
    int counter = 0;
//permanent variables
    unsigned int number_of_states = 0;
    bool init_flag = false;
    vector<double> init_vector;
    vector<vector<double>> init_vector_matrix;
    vector<vector<double>> matrix; // matrix[llegada][salida] = prob

//--------------init block----------------
//-------------matrix creation--------------
    counter = 0;
    while (getline(inFile,line)) {
        if(counter == 0){
            number_of_states = stoi(line);
            counter++;
        }else if(counter == 1){
            istringstream iss(line);
            while (getline(iss,number,' ')) {
                init_vector.push_back(stod(number));

            }
            init_vector_matrix.resize(1);
            init_vector_matrix[0].resize(number_of_states);
            for(unsigned int i = 0; i < number_of_states; i++){
                init_vector_matrix[0][i] = init_vector[i];
            }
            counter++;
        }else if(counter == 2){
            //initialization of matrix
            if(init_flag == false){
                matrix.resize(number_of_states);
                for(unsigned int i=0;i < number_of_states;i++){
                    matrix[i].resize(number_of_states);
                    for(unsigned int j=0;j < number_of_states;j++){
                        matrix[i][j] = 0.0;
                    }
                }
                init_flag = true;
                continue;
            }
            //filling the matrix
            istringstream iss(line);
            temp.clear();
            while (getline(iss,number,' ')) {
                temp.push_back(stod(number));
            }
            if(continuous_flag == "true"){
                if(q_matrix_flag=="true"){
                    matrix[(unsigned int)temp[0]][(unsigned int)temp[1]] = temp[2];
                }else if(p_matrix_flag=="true"){
                    matrix[(unsigned int)temp[0]][(unsigned int)temp[1]] = temp[2];
                }else{
                    matrix[(unsigned int)temp[0]][(unsigned int)temp[1]] = delta_t*temp[2];
                }
            }else{
                matrix[(unsigned int)temp[0]][(unsigned int)temp[1]] = temp[2];
            }
        }
    }
    inFile.close();
    double sum = 0;
    if(continuous_flag == "true"){ // populate the middle if its continuos
        for(unsigned int i = 0;i < number_of_states;i++){//trabel the diagonal
            sum = 0;
            for(unsigned int j = 0;j < number_of_states;j++){//travel de rows
                sum = sum + matrix[i][j];
            }
            if(q_matrix_flag=="true"){
                matrix[i][i] = -sum;
            }else if(p_matrix_flag=="true"){
                matrix[i][i] = sum;
            }else{
                matrix[i][i] = 1 - sum;
            }
        }
    }
    vector<vector<double>> unitary_matrix;
    if(p_matrix_flag=="true"){
        //-------lambda calculation-----------
        for(unsigned int i = 0; i < number_of_states ; i++){
            for(unsigned int j = 0; j < number_of_states ; j++){
                if(lambda < matrix[i][j]){
                    lambda = matrix[i][j];
                }
            }
        }
        matrix_mult_scalar(matrix,1.0/lambda,matrix);
        for(unsigned int i = 0; i < number_of_states ; i++){
            matrix[i][i] = -matrix[i][i];
        }
        init_unitary(number_of_states,unitary_matrix);
        matrix_sum(matrix,unitary_matrix,matrix);
    }
//-----------execution block---------------

    vector<double> actual;
    vector<double> previous = init_vector;

    //------variables for Q matrix calculous (and P matrix jeje)-----
    double time = 0;
    double fact;
    vector<vector<double>> q_sum;
    init_zeros(number_of_states,q_sum);
    vector<vector<double>> q_matrix_1 = matrix;
    vector<vector<double>> q_matrix_2;
    vector<vector<double>> q_matrix_out;

    //exclusibe P
    double temp_number;

    //-------------------------------
    ofstream output("./result.txt");
    if(output.is_open()){
        for(unsigned int i=0;i<number_of_states;i++){ //save init vector
            if(i == number_of_states-1){
                output << init_vector[i] << "\n" ;
            }else{
                output << init_vector[i] << " ";
            }
        }
        for(int x=0;x < target;x++){//iteraciones hasta "n"
            actual.clear();
            init_zeros(number_of_states,q_sum);
            init_zeros(number_of_states,q_matrix_1);
            init_zeros(number_of_states,q_matrix_2);
            for(unsigned int j=0;j < number_of_states;j++){ //inicializacion vector actual
                actual.push_back(0.0);
            }

            //ecuacion aproximada cyka
            if(q_matrix_flag=="true"){
                time = x*delta_t + delta_t;

                //sum
                for ( int n=0;n<10;n++) {
                    matrix_mult_scalar(matrix,time,q_matrix_2);
                    matrix_pow(q_matrix_2,n,q_matrix_1);
                    fact = factorial(n);
                    matrix_mult_scalar(q_matrix_1,1.0/fact,q_matrix_2);
                    matrix_sum(q_matrix_2,q_sum,q_sum);
                }
                matrix_mult(init_vector_matrix,q_sum,q_matrix_out);

                for(unsigned int index=0; index < number_of_states ; index++){
                    actual[index] = q_matrix_out[0][index];
                }

            }else if(p_matrix_flag=="true"){
                time = x*delta_t + delta_t;
                temp_number = 0;

                for ( int n=0;n<10;n++) {
                    temp_number = p_n(n,time,lambda);
                    pi_n(init_vector_matrix,matrix,n,q_matrix_1);
                    matrix_mult_scalar(q_matrix_1,temp_number,q_matrix_2);
                    matrix_sum(q_matrix_2,q_sum,q_sum);
                }
                for(unsigned int index=0; index < number_of_states ; index++){
                    actual[index] = q_sum[0][index];
                }
            }else{//calculo de forma en apuntes
                for(unsigned int j=0;j < number_of_states;j++){
                    for(unsigned int i=0;i < number_of_states;i++){
                        actual[j] = actual[j] + previous[i] * matrix[i][j];
                    }
                }
                previous = actual;
            }

            //sum igual 1
            final_check = 0;
            for(unsigned int i=0;i<number_of_states;i++){
                final_check = final_check + actual[i];
            }
            cout << final_check << endl;

            //----------print/save result-------------
            for(unsigned int i=0;i<number_of_states;i++){
                if(x == target-1){
                    if(i == number_of_states-1){
                        output << actual[i] ;
                    }else{
                        output << actual[i] << " ";
                    }
                }else{
                    if(i == number_of_states-1){
                        output << actual[i] << "\n" ;
                    }else{
                        output << actual[i] << " ";
                    }
                }
            }
        }
    }
    output.close();
    return 0;
}
