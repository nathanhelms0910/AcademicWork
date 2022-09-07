#include <aspell.h>
#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

void check_matches(AspellSpeller* spell_checker, string guess) {
  vector<string> matches;
  string match;
  char newChar;

  //Start from 1 since shifting by 0 isn't very interesting
  for(int i = 0; i < 25; ++i) {
	match = "";
	//Using a shift cipher, encrypt "guess" with key "i"
	/*for(int j = 0; j < guess.length(); ++j) {
	  newChar = guess.at(j) - 'a';
	  newChar += i;
	  newChar %= 26;
	  newChar += 'A';
	  match += newChar;
	}*/

	//Using an affine cipher, encrypt "guess" with key "(i,j)"
	for(int j = 0; j < 25; ++j) {
	  for(int k = 0; k < guess.length(); ++k) {
		newChar = (i * ((guess.at(k) - 'a')) + j;
		newChar %= 26;
		newChar += 'A';
		match += newChar;
	  }
	}
	if(aspell_speller_check(spell_checker, match.c_str(), match.length())) {
	  matches.push_back(match);
	}
  }

  if(matches.size() > 0) {
	cout << "Matches for " << guess << ":";
	for(int i = 0; i < matches.size(); ++i) {
	  cout << " " << matches[i];
	}
	cout << endl;
  }
}

void do_search(AspellSpeller* spell_checker, int length) {
  string guess;
  string end;
  int is_a_word;
  guess = "";
  end = "";

  for(int i = 0; i < length; ++i) {
	guess += 'a';
	end += 'z';
  }
  while(guess != end) {
	is_a_word = aspell_speller_check(spell_checker, guess.c_str(), length);
	if(is_a_word) {
	  check_matches(spell_checker, guess);
	}
	for(int i = guess.length() - 1; i >= 0; --i) {
	  if(guess.at(i) != 'z') {
		++guess[i];
		break;
	  }
	  else {
		guess[i] = 'a';
	  }
	}
  }
}

int main(int argc, char* argv[]) {
  AspellConfig *spell_config;
  AspellCanHaveError *possible_error;
  AspellSpeller *spell_checker;

  spell_config = new_aspell_config();
  aspell_config_replace(spell_config, "lang", "en_US");

  possible_error = new_aspell_speller(spell_config);
  if(aspell_error_number(possible_error) != 0) {
	cerr << aspell_error_message(possible_error) << endl;
	exit(EXIT_FAILURE);
  }
  spell_checker = to_aspell_speller(possible_error);
  do_search(spell_checker, 5);



  delete_aspell_speller(spell_checker);
  delete_aspell_config(spell_config);
}
