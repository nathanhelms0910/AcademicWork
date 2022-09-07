#include <iostream>


using namespace std;

int inverse[26] = {0, 1, 0, 9, 0, 21, 0, 15, 0, 3, 0, 19, 0, 0, 0, 7, 0, 23, 0, 11, 0, 5, 17, 0, 25};

bool CheckTAOINSHR(string input) {
  int count_t = 0, count_a = 0, count_o = 0, count_i = 0, count_n = 0, count_s = 0, count_h = 0, count_r = 0;
  int length = input.length();
  for(int i = 0; i < length; ++i) {
	switch(input.at(i)) {
	  case 't':
		count_t++;
		break;
	  case 'a':
		count_a++;
		break;
	  case 'o':
		count_o++;
		break;
	  case 'i':
		count_i++;
		break;
	  case 'n':
		count_n++;
		break;
	  case 's':
		count_s++;
		break;
	  case 'h':
		count_h++;
		break;
	  case 'r':
		count_r++;
		break;
	}
  }
  if(count_t == 0 || count_t*100 < 3*length || count_t*100 > 12*length) {
	return false;
  }
  else if(count_a == 0 || count_a*100 < 3*length || count_a*100 > 12*length) {
	return false;
  }
  else if(count_o == 0 || count_o*100 < 3*length || count_o*100 > 12*length) {
	return false;
  }
  else if(count_i == 0 || count_i*100 < 3*length || count_i*100 > 12*length) {
	return false;
  }
  else if(count_n == 0 || count_n*100 < 3*length || count_n*100 > 12*length) {
	return false;
  }
  else if(count_s == 0 || count_s*100 < 3*length || count_s*100 > 12*length) {
	return false;
  }
  else if(count_h == 0 || count_h*100 < 3*length || count_h*100 > 12*length) {
	return false;
  }
  else if(count_r == 0 || count_r*100 < 3*length || count_r*100 > 12*length) {
	return false;
  }
  else {
	return true;
  }
}



bool CheckE(string input) {
  int count_e = 0;
  int length = input.length();
  for(int i = 0; i < length; ++i) {
	if(input.at(i) == 'e') {
	  count_e++;
	}
  }
  if(count_e*100 >= 8*length) {
	return true;
  }
  return false;
}

char affine(int a, int b, char input) {
  if(input < 'A' || input > 'Z') {
	return input;
  }
  char ciphertext;
  char plaintext;
  ciphertext = input - 'A';
  plaintext = (inverse[a] * (ciphertext + (26 - b))) % 26;
  plaintext = plaintext + 'a';
  return plaintext;
}


void decrypt(string input) {
  for(int a = 0; a < 26; ++a) {
	if(inverse[a] == 0) {
	  continue;
	}
	for(int b = 0; b < 26; ++b) {
	  string guess = "";
	  for(int i = 0; i < input.length(); ++i) {		
		guess += affine(a, b, input[i]);
	  }
	  if(CheckE(guess) && CheckTAOINSHR(guess)) {
		cout << guess << endl;
	  }

	}
  }


}


int main() {
  string input;
  while(getline(cin, input)) {
	decrypt(input);
  }

}
