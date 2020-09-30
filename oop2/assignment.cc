double mean(double *x, int N) { //would be better to find length of x using .sizeof()?
	double total{0};
	for(int i{0}; i < N; i++) {
		total += x[i];
	}
	return total/N;
}

double stdev(double *x, int N) {
	double total{0};
	for(int i{0}; i < N; i++) {
		total += (x[i]-mean(x,N))*(x[i]-mean(x,N));
	}
	return sqrt(total/(N-1));
}

int main() {
	cout << "Enter file name..." << endl;
	string name; cin >> name;
	ifstream file(name);
	int lines{0};
	if(!file.good()){
		cerr << "Error. File could not be opened or may not exist." << endl;
	} else {
		while(!file.eof()){
			string line; file >> line;
			if(isdigit(line[0])){
				lines++;
			}
		}
		
		file.clear();
		file.seekg(0,file.beg);
		double *array = new double[lines];
		int i{0};
		int errors{1};
		while(!file.eof()){
			double line; file >> line;
			if(file.fail()) {
				cout << errors << " line(s) ignored."  << endl;
				errors++;
				file.clear(); file.ignore(10000, '\n'); // skips to next new line (assumes line shorter than 10000 characters)
			} else {
				array[i] = line;
				i++;
			}
		}
		file.close();
		
		cout << "The mean is " << setprecision(6) <<  mean(array,lines) << endl;
		cout << "The standard deviation is " << setprecision(4) << stdev(array,lines) << endl;
		delete[] array;
	}
		
	return 0;
}
