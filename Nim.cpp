#include <iostream>
#include <stdio.h>
#include <ctime>
#include <cstdlib>
#include <string.h>
using namespace std;


const int  N_stones = 10;
unsigned max_number;
bool hard = false;



// Let's check the presence of stones
bool Check (int N, int * heaps) {
	int count = 0;
    for (int i = 0; i < N; i++) 
    	if (heaps[i] < 2) count++;
    if (count != N) return true;
    return false;
}

// Fill heaps
void Fill (int N, int * heaps) {
    for(int i = 0; i < N; i++)
        heaps[i] = rand() % N_stones + 1;
}

// Show the current state of the piles
void Show (int N, int * heaps) {
    cout<<"\nCurrent state:\n";
    for(int i = 0; i < N; i++)
        cout << heaps[i] << ' ';
}

// Find XOR of stones in heaps
int Find (int N, int * heaps) {
    int a = 0;
    for (int i = 0; i < N; i++){
        a = a ^ heaps[i];

    }
    return a;
}

// Show error
void Error (int num) {
	cout << "\nPlease, try again\n";
	string err[] = {
		"You can enter only 1, 2 or 3\n",
		"You can enter only 1 or 0\n",
		"The number of banches can be only more then 0\n",
		"We don't have such batch\n",
		"There are no heaps int the batch\n",
		"There are not enough heaps in the batch\n",
		"You can give only 2 or 4 heaps\n"
	};
	cout << err[num];
}

void Wrong (int N, int * heaps);

// Find Grandy 
int Find_Grundy (int ch){
	int ost = ch % 6;
	if (ost == 0 || ost == 1) return 0;
	else if (ost == 2 || ost == 3) return 1;
	else if (ost == 4 || ost == 5) return 2;
}

// XOR of the elements of an array consisting of Grandy numbers
bool Mas (int N, int * mas, int G, int i) {
	mas[i] = G;
	int a = Find (N, mas);
	if (a == 0) return true;
	else return false;
	
}

// The correct course of the computer
void Right (int N, int * heaps) {
    int i;
	int G;
	int * arr;
    arr = (int*) malloc (N * sizeof(int));
    for (i = 0; i < N; i++) {
    	arr[i] = Find_Grundy (heaps[i]);
	}
	int a = Find(N, arr);
	if (a != 0){
		for (i = 0; i < N; i++) {
			if(heaps[i] > 1) {
				int c = heaps[i] - 2;
				G = Find_Grundy(c);
				if (Mas(N, arr, G, i)){
					heaps[i] -= 2;
					cout << "\n I gave 2 from the " << i + 1 << " batch";
					break;
				}
			}
			if(heaps[i] > 3) {
				int c = heaps[i] - 4;
				G = Find_Grundy(c);
				if (Mas(N, arr, G, i)) {
					heaps[i] -= 4;
					cout << "\n I gave 4 from the " << i + 1 << " batch";
					break;
				}
			}
		}
	}
    else Wrong (N, heaps);
}

// Wrong course of the computer
void Wrong (int N, int * heaps) {
    int i;
	int G;
	int * arr;
    arr = (int*) malloc (N * sizeof(int));
    for (i = 0; i < N; i++) {
    	arr[i] = Find_Grundy(heaps[i]);
	}
	
	
		while (true) {
			int n = rand() % N;
			int k = rand() % 2;
			if(heaps[n] > 1 && k == 0) {
				int c = heaps[n] - 2;
				G = Find_Grundy(c);
				if (!Mas(N, arr, G, n)){
					heaps[n] -= 2;
					cout << "\n I gave 2 from the " << n + 1 << " batch";
					break;
				}
			}
			if(heaps[n] > 3 && k == 1) {
				int c = heaps[n] - 4;
				G = Find_Grundy(c);
				if (!Mas(N, arr, G, n)) {
					heaps[n] -= 4;
					cout << "\n I gave 4 from the " << n+1 << " batch";
					break;
				}
			}
		}
	
}

// Computer's Progress
void Comp (int N, int * heaps) {
    if (!hard) {
		if (rand() % max_number + 1 == 1) Right(N, heaps);
    	else Wrong(N, heaps);
    }
    else {
    	if (rand() % max_number + 1 != 1)  Right(N, heaps);
    	else Wrong(N, heaps);
	}
}



// Player's progress
void Human (int N, int * heaps){
	int k;
	int v;
	bool flag = true;
	while(true) {
		cout << "\n   Input the number of the batch:  ";
		cin >> k;
		if (k > 0 && k <= N && heaps[k-1] > 1) break;
		else if (k <= 0 || k > N) Error(3);
		else if (heaps[k - 1] <= 1) Error(5);
		else cout << "\nPlease, try again\n";
	}
	k--;
	while (true) {
		cout << "   Input the number of heaps:  ";
		cin >> v;
		if (v == 2 || v == 4 && heaps[k] >= v) break;
		else if (v != 2 && v != 4) Error(6);
		else if (v > heaps[k]) Error(5);
		else cout << "\nPlease, try again\n";
	}
	heaps[k] -= v;
}



void Defis () {
	cout << "\n-----------------------------------------------------------\n";
}

int main () {
    int n;
	int i;
	int l;
    srand(time(0));
    cout << "Do you want to play with computer or with some people? \n1 means computer, 0 means the human\n";
    cin >> n;
    
    bool flag = false;
	bool flag2 = true;
    while (!flag){
        if (n == 1){
            cout << "You will play with computer!";
            Defis();
            cout << "\nInput the difficulty of the level \n1 means easy, 2 means medium and 3 means hard\n";
            flag = true;
            cin >> l;
            while (flag2) {

                if (l == 1) {
                    cout << "The game will be easy\n";
                    max_number = 10;
                    flag2 = false;
                }
                else if (l == 2){
                    cout << "The game will be medium\n";
                    max_number = 2;
                    flag2 = false;
                }
                else if (l == 3){
                    cout << "The game will be hard\n";
                    max_number = 20;
                    flag2 = false;
                    hard = true;
                }
                else {
                    Error(0);
                    cin >> l;
                }
            }
		}
        else if (n == 0) {
            cout << "You will play with your friend\n";
            flag = true;
        }
        else if (n != 0 && n != 1){
            Error(1);
            cin >> n;
        }
    }
    Defis();
    int N;
	cout << "How many banches do you want?\n";
	while (true){
    cin >> N;
    if (N > 0) break;
    else Error(2);
    }
    int * heaps;
    heaps = (int*)malloc(N * sizeof(int));
    Defis();
    Fill(N, heaps);
    if (n == 1){
		char p_n[20];
		
		while (true) {
		cout << "Input your name: ";
		fflush(stdin);
		gets(p_n);
		if(strlen(p_n) != 0) break;
		else cout << "\nPlease, try again\n";
		}
		int prior;
		cout << "\n\n" << p_n << ", do you want to be the first? \n1 means yes, 0 - no:  ";
		cin >> prior;
		while (prior != 0 && prior != 1) {
			Error(1);
			cin >> prior;
		}
		if (prior == 0) {
			cout << "\nYou will play with the second number\n";
			while(Check(N, heaps)) {
        		Show(N, heaps);
        		Comp(N, heaps);
        		if (!Check(N, heaps)) {
					cout << "\n\n" << "The computer winned! It was really good game!";
					break;
				}
				Defis();
        		Show(N, heaps);
        		Human(N, heaps);
				if (!Check(N, heaps)) {
					cout << "\n\n" << p_n << " is winner! It was really good game, congratulate you!";
					break;
				}
				Defis();        
    		}
    	}
    	else if (prior == 1) {
    		cout << "\nYou will play with the first number\n";
    		while (Check(N, heaps)) {
        		Show(N, heaps);
        		Human(N, heaps);
				if (!Check(N, heaps)) {
					cout << "\n\n" << p_n << " is winner! It was really good game, congratulate you!";
					break;
				}
				Defis();
        		Show(N, heaps);
        		Comp(N, heaps);
        		if (!Check(N, heaps)) {
					cout << "\n\n" << "The computer winned! It was really good game!";
					break;
				}
				Defis();        
    		}
		}
	}
	else if (n == 0) {
		char p1[20];
		char p2[20];
		while(true) {
		cout << "\nThe first player, input your name: ";
		cin >> p1;
		fflush(stdin);
		if(strlen(p1) != 0) break;
		else cout << "\nPlease, try again\n";
		}
		while(true) {
		cout << "\nThe second player, input your name: ";
		cin >> p2;
		fflush(stdin);
		if(strlen(p2) != 0) break;
		else cout << "\nPlease, try again\n";
		}
		
		
		while (Check(N, heaps)) {		
			Show(N, heaps);
			cout << "\n\n" << p1 << ",\n";
			Human(N, heaps);
			if (!Check(N, heaps)) {
				cout << "\n\n" << p1 << " is winner! It was really good game, congratulate you!";
				break;
			}
			Defis();
			Show (N, heaps);
			cout << "\n\n" << p2 << ",\n";
			Human(N, heaps);
				if (!Check(N, heaps)) {
					cout << "\n\n" << p2 << " is winner! It was really good game, congratulate you!";
					break;	
				}
			Defis();
		}
	}
	system ("pause");
	return 0;
}
