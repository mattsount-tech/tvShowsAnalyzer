#include <iostream>
#include <fstream>
#include "finalLibrary.h"
#include <iomanip>
using namespace std;


int menu() {
	string choice_input;
	int choice;
	//display the menu
	cout << "Here are the options:\n";
	cout << "\t1 - Display TV Shows Overview\n";
	cout << "\t2 - Search for a specific show\n";
	cout << "\t3 - Sort the list of shows\n";
	cout << "\t4 - Display the seasons with the most and least episodes of a given show\n";
	cout << "\t5 - Display the average episodes per season of a given shows\n";
	cout << "\t6 - Display only shows of a given criteria\n";
	cout << "\t7 - Display the oldest and newest shows by start date\n";
	cout << "\t8 - Remove a show from the list of shows\n";
	cout << "\t9 - Exit the program\n";
	//prompt user to select valid option
	cout << "Enter your option (1 - 9): ";
	cin >> choice_input;
	cout << endl;
	while(!(choice_input == "1" || choice_input == "2" || choice_input == "3" || choice_input == "4" || choice_input == "5" || choice_input == "6" || choice_input == "7" || choice_input == "8" || choice_input == "9")) {
		cout << "\"" << choice_input << "\" is not a proper option.\n\n";
		cout << "Enter your option (1 - 9): ";
		cin >> choice_input;
		cout << endl;
	}
	choice = stoi(choice_input);
	return choice;
}

void display_separator() {
    for(int i = 0; i < 108; i++) {
		cout << "=";
	}
	cout << endl;
}

//populate and display one show struct
//================================================================================
void populate_one_show_struct(istream& fin, Show& s) {
	getline(fin, s.name, ',');
	getline(fin, s.network, ',');
	getline(fin, s.genre, ',');
	fin >> s.seasons;
	fin.ignore(); //discard comma
	fin >> s.start_year;
	fin.ignore(); //discard comma
	fin >> s.end_year;
	fin.ignore(); //discard endline

	s.total_episodes = 0;
	//extract episodes in each season into array
	for(int i = 0; i < s.seasons; i++) {
		fin >> s.episodes_each_season[i];
		s.total_episodes += s.episodes_each_season[i];
		//cout << shows[i].episodes_each_season[j] << " ";
	}
	fin.ignore(); //discard endline
	s.avg_episodes_per_season = double(s.total_episodes) / s.seasons;
	least_most_episode_season(s);
	/*
	cout << "*" << s.name << "*" << endl;
	cout << "*" << s.network << "*" << endl;
	cout << "*" << s.genre << "*" << endl;
	cout << "*" << s.seasons << "*" << endl;
	cout << "*" << s.start_year << "*" << endl;
	cout << "*" << s.end_year << "*" << endl;
	*/
}

void display_one_show_struct(const Show& s) {
	cout << fixed << setprecision(2);
	cout << "TV-SHOW: " << s.name << " | ";
	cout << "GENRE: " << s.genre << " | ";
	cout << "ORIGINAL NETWORK: " << s.network << " | ";
	cout << "SEASONS: " << s.seasons << " | ";
	cout << "RUN: " << s.start_year << " - " << s.end_year;
	cout << endl;
	//display seasons and number of episodes each season
	cout << left << setw(9) << "SEASON:" << " | ";
	for(int i = 0; i < s.seasons; i++) {
		cout << left << setw(2) << i + 1 << " | ";
	}
	cout << endl;
	cout << left << setw(9) << "EPISODES:" << " | ";
	for(int i = 0; i < s.seasons; i++) {
		cout << left << setw(2) << s.episodes_each_season[i] << " | ";
	}
	cout << endl;
}

void least_most_episode_season(Show& s) {
	//determine season with most episodes
	s.most_episodes = 0;
	for(int j = 0; j < s.seasons; j++) {
		if(s.episodes_each_season[j] > s.most_episodes) {
			s.most_episodes = s.episodes_each_season[j];
			s.most_episodes_season = j + 1;
		}
	}
	s.least_episodes = 1000;
	//determine season with least episodes
	for(int j = 0; j < s.seasons; j++) {
		if(s.episodes_each_season[j] < s.least_episodes) {
			s.least_episodes = s.episodes_each_season[j];
			s.least_episodes_season = j + 1;
		}
	}
	/*
	cout << "The season for " << s.name << " with the most episodes has ";
	cout << s.most_episodes << " episodes and is season " << s.most_episodes_season;
	cout << endl;
	cout << "The season for " << s.name << " with the least episodes has ";
	cout << s.least_episodes << " episodes and is season " << s.least_episodes_season;
	cout << endl << endl;
	*/

}

//populate and display shows array
//====================================================================================

void populate_shows_array(istream& fin, Show s[], int& num_shows) {
	for(int i = 0; !fin.eof(); i++) {
		populate_one_show_struct(fin, s[i]);
		num_shows++;
		/*
		display_one_show_struct(s[i]);
		cout << endl << num_shows << endl;
		*/
	}
}

void display_shows_array(const Show s[], int num_shows) {
    display_separator();
	cout << left << setw(30) << "TV-SHOW";
	cout << setw(20) << "GENRE";
	cout << setw(20) << "ORIGINAL NETWORK";
	cout << setw(10) << "SEASONS";
	cout << setw(17) << "TOTAL EPISODES";
	cout << setw(10) << "RUN";
	cout << endl;
    display_separator();
	for(int i = 0; i < num_shows; i++) {
		cout << left << setw(30) << s[i].name;
		cout << setw(20) << s[i].genre;
		cout << setw(20) << s[i].network;
		cout << setw(10) << s[i].seasons;
		cout << setw(17) << s[i].total_episodes;
		cout << s[i].start_year << " - " << s[i].end_year;
		cout << endl;
	}
	display_separator();
	cout << endl;
}

//sorting shows array functions
//====================================================================================

void sort_shows_array(Show s[], int num_shows, int sort_mode) {
    //insertion sort
	for(int i = 1; i < num_shows; i++) { 
		Show temp = s[i];
		int j = i - 1;

		while(j >= 0 && sort_condition(s, temp, sort_mode, j)) {
			s[j + 1] = s[j];
			j--;
		}
		s[j + 1] = temp;
	}
}
//generalize while loop condition into one function in order to sort multiple ways
bool sort_condition(const Show s[], const Show& temp, int sort_mode, int j) {
	switch(sort_mode) {
    	case 1: //sort alphabetically
    		return s[j].name > temp.name;
    		break;
    	case 2: //sort by earliest release date
    		return s[j].start_year > temp.start_year;
    		break;
    	case 3: //sort by least seasons
    		return s[j].seasons > temp.seasons;
    		break;
    	case 4: //sort by least total episodes
    		return s[j].total_episodes > temp.total_episodes;
    		break;
    	default:
    		return false;
	}
}

int sort_menu() {
	string sort_mode_input;
	int sort_mode;
	//display the menu
	cout << "How would you like to sort the Shows list?\n";
	cout << "\t1 - Alphabetically\n";
	cout << "\t2 - By earliest release year\n";
	cout << "\t3 - By least seasons\n";
	cout << "\t4 - By least total episodes\n";
	//prompt user to select valid option
	cout << "Enter your option (1 - 4): ";
	cin >> sort_mode_input;
	cout << endl;
	while(!(sort_mode_input == "1" || sort_mode_input == "2" || sort_mode_input == "3" || sort_mode_input == "4")) {
		cout << "\"" << sort_mode_input << "\" is not a proper option.\n\n";
		cout << "Enter your option (1 - 4): ";
		cin >> sort_mode_input;
		cout << endl;
	}
	sort_mode = stoi(sort_mode_input);
	return sort_mode;
}

void display_sort_mode(int sort_mode) {
	switch(sort_mode) {
    	case 1:
    		cout << "Here is the list of shows sorted alphabetically:\n";
    		break;
    	case 2:
    		cout << "Here is the list of shows sorted by earliest release year:\n";
    		break;
    	case 3:
    		cout << "Here is the list of shows sorted by least seasons:\n";
    		break;
    	case 4:
    		cout << "Here is the list of shows sorted by least total episodes:\n";
    		break;
	}
}

//search function
//==============================================================================

int search_shows_array(const Show s[], int num_shows, const string& target) {
	for(int i = 0; i < num_shows; i++) {
		if(s[i].name == target) {
			return i;
		}
	}
	return -1; //will happen if target is not found in array
}

//filter functions
//==============================================================================
int criteria_menu() {
	string criteria_mode_input;
	int criteria_mode;
	//display the menu
	cout << "What criteria would you like to display shows under?\n";
	cout << "\t1 - Network\n";
	cout << "\t2 - Genre\n";
	cout << "\t3 - Minimum number of seasons\n";
	cout << "\t4 - Minimum start year\n";
	//prompt user to select valid option
	cout << "Enter your option (1 - 4): ";
	cin >> criteria_mode_input;
	cout << endl;
	while(!(criteria_mode_input == "1" || criteria_mode_input == "2" || criteria_mode_input == "3" || criteria_mode_input == "4")) {
		cout << "\"" << criteria_mode_input << "\" is not a proper option.\n\n";
		cout << "Enter your option (1 - 4): ";
		cin >> criteria_mode_input;
		cout << endl;
	}
	criteria_mode = stoi(criteria_mode_input);
	return criteria_mode;
}

Filter_Criteria collect_criteria(int criteria_mode) {
    Filter_Criteria input;
	switch(criteria_mode) {
    	case 1:
    		cout << "Enter the network: ";
    		getline(cin, input.network);
    		break;
    	case 2:
    		cout << "Enter the genre: ";
    		getline(cin, input.genre);
    		break;
    	case 3:
    		cout << "Enter the minimum number of seasons: ";
    		cin >> input.min_num_seasons;
    		break;
    	case 4:
    		cout << "Enter the minimum start year: ";
    		cin >> input.min_start_year;
    		break;
	}
	cout << endl;
	return input;
}
//generalize filter condition into one function so user can filter by multiple criteria
bool criteria_condition(const Filter_Criteria& c, const Show& s, int criteria_mode) {
	switch(criteria_mode) {
    	case 1: //network
    		return s.network == c.network;
    		break;
    	case 2: //genre
    		return s.genre == c.genre;
    		break;
    	case 3: //min seasons
    		return s.seasons >= c.min_num_seasons;
    		break;
    	case 4: //min start year
    		return s.start_year >= c.min_start_year;
    		break;
    	default: 
    	    cout << "ERROR: Invalid criteria mode" << endl;
    	    return false;
    	    break;
	}
}

void filter_shows_array(const Show s[], int num_shows, const Filter_Criteria& c, int criteria_mode) {
    bool found = false;
    //check if any shows match criteria
    for(int i = 0; i < num_shows && found == false; i++) {
        if(criteria_condition(c, s[i], criteria_mode)) {
            found = true;
        }
    }
    if(found == false) {
        cout << "Could not find any shows matching the given criteria.\n\n";
    } else {
        switch(criteria_mode) {
        	case 1: //network
        		cout << "Displaying shows whose network is " << c.network << ":\n";
        		break;
        	case 2: //genre
        		cout << "Displaying shows whose genre is " << c.genre << ":\n";
        		break;
        	case 3: //min seasons
        	    cout << "Displaying shows with at least " << c.min_num_seasons << " seasons:\n";
        		break;
        	case 4: //min start year
        		cout << "Displaying shows released in " << c.min_start_year << " or later:\n";
        		break;
    	}
    	//display shows based on filter
    	display_separator();
        for(int i = 0; i < num_shows; i++) {
            if(criteria_condition(c, s[i], criteria_mode)) {
                display_one_show_struct(s[i]);
            }
        }
        display_separator();
        cout << endl;
    }
}

//analysis multiple functions
//==============================================================================
void oldest_show(const Show s[], int num_shows, int& pos) {
    int oldest_year = 3000;
    pos = -1;
    for(int i = 0; i < num_shows; i++) {
        if(s[i].start_year < oldest_year) {
            oldest_year = s[i].start_year;
            pos = i;
        }
    }
}

void newest_show(const Show s[], int num_shows, int& pos) {
    int newest_year = 0;
    pos = -1;
    for(int i = 0; i < num_shows; i++) {
        if(s[i].start_year > newest_year) {
            newest_year = s[i].start_year;
            pos = i;
        }
    }
}

//remove function
//================================================================================
void remove_show(Show s[], int& num_shows, string target_show, int pos) {
    for(int i = pos; i < num_shows - 1; i++) {
    	s[i] = s[i + 1]; 
    }
    num_shows--;
}














