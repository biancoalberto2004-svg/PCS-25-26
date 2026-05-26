#include <iostream>
#include <Eigen/Dense>
#include "gradiente_coniugato.hpp"

void print_result(const risultato_gc& result, const Eigen::VectorXd& x_ex, const unsigned int it_max, const double res_tol) {
	
	Eigen::VectorXd x = result.sol;
	unsigned int it = result.it;
	double res_rel = result.res_rel;
	bool conv = result.conv;
	
	// Se il vettore restituito non ha la stessa dimensione della soluzione esatta
	// significa che c'è stato un errore a monte (caso 3)
	if (x.size() != x_ex.size()) {
		std::cout << "Stampa annullata: dimensioni non compatibili per calcolare l'errore.\n";
		return;
	}
	
	const auto err_rel = (x_ex.norm() == 0.0) ? (x - x_ex).norm() :
										  (x - x_ex).norm() / x_ex.norm();

	std::cout.precision(4);
	std::cout<< "Convergenza: " << conv << '\n';
	std::cout<< std::scientific<< "it"<< "/"<< "it_max"<< '\n';
	std::cout<< std::scientific<< it<< "/"<< it_max<< '\n';
	std::cout<< std::scientific<< "res"<< "/"<< "res_tol"<< '\n';
	std::cout<< std::scientific<< res_rel<< "/"<< res_tol<< '\n';
	std::cout<< std::scientific<< "err_rel"<< '\n';
	std::cout<< std::scientific<< err_rel<< '\n';
	//std::cout<< std::scientific<< "Soluzione: "<< '\n';
	//std::cout<< std::scientific<< x << '\n';

}

int main() {
	
    const double tol = 1.0e-15;
	const unsigned int it_max = 500;
	const double res_tol = 1.0e-12;
	
	// Caso 1: matrice ben condizionata
	
	std::cout << "\nCaso 1: \n";
	const int n1= 200;
	Eigen::MatrixXd B1 = Eigen::MatrixXd::Random(n1, n1);

	if (abs(B1.determinant()) < tol)
		return -1;

	Eigen::MatrixXd A1 = B1.transpose() * B1;
	Eigen::VectorXd x_ex1 = Eigen::VectorXd::Ones(n1);

	Eigen::VectorXd b1 = A1 * x_ex1;
	Eigen::VectorXd x0_1 = Eigen::VectorXd::Zero(n1);
	
	risultato_gc result1 = gradiente_coniugato(A1, b1, x0_1, it_max, res_tol);
	
	print_result(result1, x_ex1, it_max, res_tol);
	
	
	// Caso 2: matrice mal condizionata: matrice di Hilbert
	
	std::cout << "\nCaso 2: \n";
	const int n2=100;
	Eigen::MatrixXd H(n2, n2);
    
	for (int i = 0; i < n2; ++i) {
        for (int j = 0; j < n2; ++j) {
            H(i, j) = 1.0 / (i + j + 1.0);
        }
    }
	
	Eigen::VectorXd x_ex2 = Eigen::VectorXd::Ones(n2);
	Eigen::VectorXd b2 = H * x_ex2;
	Eigen::VectorXd x0_2 = Eigen::VectorXd::Zero(n2);
	
	risultato_gc result2 = gradiente_coniugato(H, b2, x0_2, it_max, res_tol);
	
	print_result(result2, x_ex2, it_max, res_tol);
	
	// Caso 3: dimensioni errate
	
	std::cout << "\nCaso 3: \n";
	const int n3 = 5;
	Eigen::MatrixXd B3 = Eigen::MatrixXd::Random(n3, n3);

	if (abs(B3.determinant()) < tol)
		return -1;

	Eigen::MatrixXd A3 = B3.transpose() * B3;
	Eigen::VectorXd x_ex3 = Eigen::VectorXd::Ones(n3);

	Eigen::VectorXd b3 = A3 * x_ex3;
	Eigen::VectorXd x0_3 = Eigen::VectorXd::Zero(n3+1);	

	risultato_gc result3 = gradiente_coniugato(A3, b3, x0_3, it_max, res_tol);
	
	print_result(result3, x_ex3, it_max, res_tol);
}