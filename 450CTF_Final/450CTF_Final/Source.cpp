#include <stdlib.h>
#include <stdio.h>
#include <random>
#include <iostream>
#include <string.h>
#include <string>
#include <math.h>
#include <signal.h>
//#include <unistd.h>
using namespace std;

int key1;
int key2;
int key3;
int key4;
int key5;
int val;
bool flag;

void stage1() { // stage 1
	int answer = 12345;
	printf("First guess?\n");
	string input;
	cin >> input;
	if (input.length() >= 5 && input.length() < 10) {
		key1 = stoi(input);
		if (key1 == answer) return;
		for (int i = 3, count = 0; i < key1/2; i += 10, count++) {
			val = i;
			if (key1 % i == 0 && key1 % 5 != 0) return;
		}
		key1 = 0;
	}
	else return;
}

void stage2() { // 3
	string answer = "letMeInPlease";
	string answer2 = "letMeInPRETTYPlease";
	int x = 0;
	string input;
	for (int i = 0; i < 4; i++) rand();
	int section = rand() % 4;
	printf("Oh nice! That one worked too. Keep it up!\nGunna need another key here: ");
	cin >> input;
	if (input == answer2) {
		key3 = key2 * val;
		return;
	}
	else if (input.length() >= 5) {
		key3 = stoi(input);
		switch (section) {
		case 0:
			for (int i = key3, count = 0; i > 20 && count < input.length(); i -= x, count++) {
				x *= 10;
				x += atoi(input.substr(count,1).c_str());
				if (x == key1 || x == key2) {
					return;
				}
			}
			val++;
		case 1:
			for (int i = 2; i < sqrt(key3) && input.length() <= 10; i++) {
				if (key3 % i == 0) break;
				if (key3 % (i + 2) == key3 % i) {
					val++;
					return;
				}
			}
			key2 = 0;
			return;
		case 2:
			key2 *= val;
			return;
		case 3:
			srand(key3);
			key2 -= 2;
			printf("We need to redo that level...\n\n");
			val++;
			stage2();
			key2++;
			return;
		}
	}
	key2 = 0;
}

void stage3() { // 2
	if (key1) {
		string input = to_string(key1);
		if (input.length() < 5) input = "0000" + input;
		key1 = stoi(input.substr(3) + input.substr(0, 3));
		key1 = key1 - stoi(input.substr(3, 4) + input.substr(2, 1));
		printf("Hmmm... Seems to have worked...\nNext guess?\n");
		cin >> input;
		key2 += stoi(input);
		if (key2 - 17 < key1 && key2 < 200000) {
			key1 = key1 - 2 * key2;
			key2 = 0;
			return;
		}
		else if (key2++ == (key2*2)-key2) {
			if (key2 == key1) return;
			else key2--;
			string tupni = "";
			for (int i = input.length() - 1; i >= 0; i--) {
				tupni += input[i];
				if (i > 0 && input[i] == input[i - 1]) break;
			}
			int keyr = atoi(tupni.c_str());
			for (int i = 0, j = 1, k = input.length(); k < 8, i < k && j < 10; i += 2, j += 2) {
				if ((int)(keyr / pow(10, i)) % 2 && (int)(keyr / pow(10, j)) && ((int)key1 / (int)(keyr / pow(10, j)) % 3) + 1 != 2) key2++;
				else {
					key2 = 0;
					break;
				}
			}
			srand(key2);
			return stage2();
		}
	}
	else return;
	stage2();
}

bool stage5() { // 4
	if (key2 > 0) {
		string input;
		//struct sigaction sa;
		printf("Welp... You're still going so it must all be good\n");
		printf("Input-> ");
		cin >> input;
		for (int i = 0; i < stoi(input); i+=10) key4 += i;
		//sa.sa_handler = handler;
		//sigemptyset(&sa.sa_mask);
		//sa.sa_flags = 0;
		//sigaction(SIGALRM, &sa, NULL);
		//alarm(5);
		if (key4 < 20000 || to_string(key4).length() > 10) return false;
		printf("Darn. Wonder what went wrong. Better luck next time!\n");
		//if (scanf("%d", &key5) > 0) alarm(0);
		//else return false;
		cin >> input;
		if (input.length() < 5 || input.length() > 10) exit(0);
		key4 += stoi(input);
		srand(stoi(input));
		return true;
	}
	else return false;
}

bool stage4() { // 5
	if (stage5()) {
		string input;
		val -= 3; 
		for (int i = 2; i < val; i++) if (val % i == 0) return false;
		printf("Ok ok. Seems I didn't fool you. This should be the last level...\n");
		if ((key3 * key2 * key1) % val == 0) return false;
		if ((key3 + key2 + key1) % val == 0) return false;
		if (key1 == 44670) return false;
		for (int i = 0; i < 42; i++) rand();
		if ((key3 % rand() - key2 % rand() + key1 % rand() - (2 * rand()) % key4) % val == 0) {
			//sleep(4);
			printf("I hope you didn't find this flag by mistake...\n Nice job! You found Flag 3!!\n");
			exit(0);
		}
		if (key4 - key3 > key2 + key1) return false;
		
		printf("Input: ");
		cin >> input;
		if (input.length() < 5) return false;
		key5 = stoi(input.substr(3) + input.substr(0, 3));
		key5 = key1 - key5 - stoi(input.substr(3, 4) + input.substr(2, 1));

		if (key1 - (key2 - key3) > 0) {
			if (key5 > 200 && key5 < 40000000 && key5 >= key4) {
				int temp;
				printf("What's your first key value now?\n");
				cin >> temp;
				flag = true;
				return temp == key1;
			}
		}
		else if (key4 + key5 < key1 * 200) {
			if ((((int) (key5 / pow(10, 4))+6) % key1) + key1 == ((int)(key2 / pow(10, 5)))) {
				int temp;
				printf("What's your first key value now?\n");
				cin >> temp;
				flag = false;
				return temp == key5;
			}
		}
	}
	return false;
}

void order() {
	stage1();
	srand(key1);
	stage3();
	if (stage4()) {
		printf("You did it! You found Flag ");
		if (flag) printf("one");
		else printf("two");
		printf("! Can you find any other solutions? \n");
	}
	else printf("Darn. Wonder what went wrong. Better luck next time!\n");
}

int main() {
	printf("Welcome to my capture the flag!\nApologies for any visually induced nausea\n");
	order();
}