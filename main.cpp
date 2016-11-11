#include <iostream>
#include <vector>
#include <ctime>

unsigned long long findNextCollatz(unsigned long long n);
void fillCollatzSeq(unsigned long long n);
unsigned long long smartFill(unsigned long long n);
std::vector<unsigned long long> collatzSequence;
int chainTable[1000000];


//41.6 seconds for brute force
int main(){

	//Brute Force:
	/*std::clock_t start;
	start = std::clock();
	unsigned long long numWithLongestChain = 0;
	unsigned long long currMaxChain = 0;
	for (int i = 0; i < 1000000; i++){
		fillCollatzSeq(i);
		if (collatzSequence.size() > currMaxChain){
			currMaxChain = collatzSequence.size();
			numWithLongestChain = i;
		}
		collatzSequence.clear();
	}
	std::cout << "Number with longest chain: " << numWithLongestChain << std::endl;
	std::cout << "Time to run (Brute Force): " << (std::clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << std::endl;
*/
	//Using previous knowledge to reduce computations...
	std::clock_t start2;
	start2 = std::clock();
	chainTable[0] = 0;
	chainTable[1] = 1;
	unsigned long long numWithLongestChain = 0;
	unsigned long long currMaxChain = 0;

	for (int i = 0; i < 1000000; i++){
		unsigned long long currNum = smartFill(i);
		if (currNum > currMaxChain){
			currMaxChain = currNum;
			numWithLongestChain = i;
		}
	}

	std::cout << "Number with longest chain: " << numWithLongestChain << std::endl;
	std::cout << "Time to run (SmartFill): " << (std::clock() - start2) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << std::endl;
	system("PAUSE");
	return 0;
}


unsigned long long findNextCollatz(unsigned long long n){
	if (n % 2 == 0){
		return n / 2;
	}
	else{
		return 3 * n + 1;
	}
}

void fillCollatzSeq(unsigned long long n){
	unsigned long long currNum = n;
	while (currNum != 1 && currNum != 0){
		collatzSequence.push_back(currNum);
		currNum = findNextCollatz(currNum);
	}
	collatzSequence.push_back(currNum);
}

unsigned long long smartFill(unsigned long long n){
	unsigned long long currNum = n;
	unsigned long long numChains = 0;
	if (n == 1){
		return 1;
	}
	while (true && currNum > 0){
		if (currNum < n){
			numChains += chainTable[currNum];
			chainTable[n] = numChains;
			break;
		}
		currNum = findNextCollatz(currNum);
		numChains++;
	}
	return numChains;
}
