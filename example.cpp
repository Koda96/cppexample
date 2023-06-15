#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <cstdlib>
#include <cstdio>
using namespace std;
using namespace std::chrono;

const vector<string> letters = {
    "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"
};

void generateLetterCombinations(vector<int>& keypad, const string& currentCombination, vector<string>& combinations) {
    // Caso base: si se han procesado todas las teclas
    if (keypad.empty()) {
        combinations.push_back(currentCombination);
        return;
    }

    // Obtener el número de la primera tecla en el vector y eliminarlo
    int digit = keypad[0];
    keypad.erase(keypad.begin());

    // Obtener las letras correspondientes al número actual
    string lettersForDigit = letters[digit];

    // Generar combinaciones para las letras del número actual
    for (char letter : lettersForDigit) {
        string newCombination = currentCombination + letter;
        generateLetterCombinations(keypad, newCombination, combinations);
    }

    // Restaurar el número procesado para el siguiente bucle recursivo
    keypad.insert(keypad.begin(), digit);
}

// Función para generar combinaciones de letras a partir de los dígitos del teclado
vector<string> getLetterCombinationsRecursive(const vector<int>& keypad) {
	
    vector<string> combinations;
    string currentCombination;
    vector<int> keypadCopy = keypad;
    generateLetterCombinations(keypadCopy, currentCombination, combinations);
    auto stop = high_resolution_clock::now();
    
    return combinations;
}

vector<string> getLetterCombinationsIterative(const vector<int>& keypad) {
    vector<string> combinations;

    combinations.push_back("");

    for (int digit : keypad) {
        vector<string> newCombinations;

        string lettersForDigit = letters[digit];

        for (char letter : lettersForDigit) {
            for (string combination : combinations) {
                newCombinations.push_back(combination + letter);
            }
        }

        combinations = newCombinations;
    }

    return combinations;
}

int main() {
	std::ios_base::sync_with_stdio(false);
	int combos, metodo;
	char ch = ',';
	vector<int> keypad ;
	vector<string> combinations;
	
	vector<string> letters = {
        "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"
    };
    
    for (string pos : letters){
    	int c;
    	c++;
    	if (c > 2)
    		cout << c-1 << "-->" << pos << endl;
	}
	
	cout << "Que combinaciones hacer? " << endl;
	cin >> combos;
	
	while (combos%10!=0){
		keypad.insert(keypad.begin(), combos%10);
		combos /= 10;
	}
	
	cout << "Que metodo usar?\n1.Iterativo\n2.Recursivo" << endl;
	cin >> metodo;
	
	auto start = high_resolution_clock::now();
	switch (metodo){
		case 1:
			combinations = getLetterCombinationsIterative(keypad);
			break;
		case 2:
			combinations = getLetterCombinationsRecursive(keypad);
			break;
	}
	auto stop = high_resolution_clock::now();
    
	int c = 1;
	auto start2 = high_resolution_clock::now();
    for (string combination : combinations) {
    	int len = combination.length();
    	for ( int i = len ; i > 1 ; i--){
    		combination.insert(i-1,",");
		}
		cout << c++ << ". " << "{" << combination << "}" << " ";
    }
    cout << "\n";
    auto stop2 = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    auto duration2 = duration_cast<milliseconds>(stop2 - start2);
    cout << "Tiempo que tardo la funcion: " << duration.count() << " ms." << endl;
    cout << "Tiempo que tardo mostrar: " << duration2.count() << " ms." << endl;

    return 0;
}
