	cout << "word = " << word << endl;
	
	cout << "Enter a phrase... ";
	string phrase; getline(cin,phrase);
	cout << "phrase = " << phrase << endl;
	
	if(word == phrase) {
		cout << "These are the same" << endl;
	} else {
		cout << "These are different" << endl;
	}
	
	cout << "joined = " << word + phrase << endl;
	word += phrase;
	cout << "appended = " << word << endl;
	for(int i{1}; i <= phrase.length(); i++) {
		if(phrase[i] != ' ') {
			cout << phrase.substr(0,i) << endl;
		}
	}

	string fileType{".txt"};
	ostringstream ofss; //open a stream to 'load' strings on to
	ofss << "FileData" << fileType; //load onto it
	string outputFilename{ofss.str()}; //extract string from the stream
	cout << outputFilename << endl;
	ofss.str(""); //clear ofss content
	
        string str{"you know that nobody does it like this"};
        string key{"nobody"};
        size_t start{str.rfind(key)}; //position of last occurence of "nobody" in str (the first char), returns string::npos if no match is found, we don't use int as string::npos can be very large, size_t is largest possible
        //cout << start << endl;
        //cout << string::npos << endl;
        if(start != string::npos) {
		str.replace(start,key.length(),"everybody");
        }
        cout << str << endl;
	
	int size{5};
	double arr[size];
	for (int i{0}; i < size; i++) {
		arr[i] = i;
	}
	vector<vector<double>> vec;
	for(int i{0}; i < size; i++) {
		vector<double> temp;
		for(int j{0}; j < size; j++) {
			temp.push_back(arr[j]);
		}
		vec.push_back(temp);
	}
	
	for(int i{0}; i < vec.size(); i++) {
		for(int j{0}; j < vec.size(); j++) {
			cout << vec[i][j] << endl;
		}
	}

	vector<int> vec2 = {3,2,5,4,1};
	vector<int>::iterator ptr; //a pointer
	
	for(ptr = vec2.begin(); ptr < vec2.end(); ptr++) {//NOT declaring ptr here
		cout << *ptr << endl;
	}
	
	sort(vec2.begin(),vec2.end());
	reverse(vec2.begin(),vec2.end());
	for(ptr = vec2.begin(); ptr < vec2.end(); ptr++) {
		cout << *ptr << endl;
	}
	
	return 0;
}
