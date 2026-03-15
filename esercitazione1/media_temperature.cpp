#include <fstream>
#include <iostream> 

int main(int argc, const char *argv[]) {
	if (argc != 2) {
		std::cerr << "Errore: Fornire un nome file \n";
		return 1;
	}
	std::string filename = argv[1];
	std::ifstream ifs(filename);
	if (ifs.is_open()) {
		std::string location;
		double temp1,temp2,temp3,temp4;
		while (ifs >> location >> temp1 >> temp2 >> temp3 >> temp4) {
			double avg_temp = (temp1+temp2+temp3+temp4)/4;
			std::cout << location << " " << avg_temp << "\n";
		}
	}
	else {
		std::cerr << "Errore nella lettura del file \n";
		return 1;
	}
	return 0;
}