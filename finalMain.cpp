#include <iostream>
#include <fstream>
#include "finalLibrary.h"
#include <iomanip>
using namespace std;

int const CAPACITY = 20;

int main() {
	//declare objects, variables
	//Show current_show;
	string sources;
	string file_name;
	//shows array and its size
	Show shows[CAPACITY];
	int num_shows = 0;

	cout << "This program helps you learn about TV shows.\n";
	cout << "Please enter the file name that you would like to process: ";
	cin >> file_name;
	ifstream fin;  //create input file stream object
	fin.open(file_name); //open the file
	while(!fin.is_open()) {
		cout << "ERROR: Failed to open the file.\n";
		cout << "Please enter the file name that you would like to process: ";
		cin >> file_name;
		fin.open(file_name);
	}
	cout << endl;

	//tests for project proposal
    /*
	getline(fin, sources, '*');
	fin.ignore();
	populate_one_show_struct(fin, current_show);
	display_one_show_struct(current_show);
    populate_one_show_struct(fin, current_show);
	display_one_show_struct(current_show);
	*/
	getline(fin, sources, '*');
	fin.ignore(); //discard trailing endline
	populate_shows_array(fin, shows, num_shows);
	fin.close();
	int choice;
	do {
		choice = menu();
		cin.ignore();
		switch(choice) {
    		case 1: {
    			cout << "You have chosen to display the TV Shows Overview:\n\n";
    			display_shows_array(shows, num_shows);
    			break;
    		}
    		case 2: {
    			string show_input;
    			int pos;
    			cout << "You have chosen to search for a specific show.\n";
    			cout << "Enter the show name that you would like to search for: ";
    			getline(cin, show_input);
    			pos = search_shows_array(shows, num_shows, show_input);
    			//cout << endl << "Position: " << pos << endl;
    			if(pos == -1) {
    				cout << "\nCould not find \"" << show_input << "\" in the list of shows.\n\n";
    			} else {
    				cout << endl;
    				display_separator();
    				display_one_show_struct(shows[pos]);
    				display_separator();
    				cout << endl;
    			}
    			break;
    		}
    		case 3: {
    			cout << "You have chosen to sort the list of shows.\n";
    			int sort_mode = sort_menu(); //will only return 1, 2, 3, or 4
    			cin.ignore();
    			display_sort_mode(sort_mode);
    			sort_shows_array(shows, num_shows, sort_mode);
    			display_shows_array(shows, num_shows);
    			break;
    		}
    		case 4: {
    		    string show_input;
    			int pos;
    			cout << "You have chosen to display the seasons with the most and least episodes of a given show.\n";
    			cout << "Enter the name of the show that you are interested in: ";
    			getline(cin, show_input);
    			pos = search_shows_array(shows, num_shows, show_input);
    			//cout << endl << "Position: " << pos << endl;
    			if(pos == -1) {
    				cout << "\nCould not find \"" << show_input << "\" in the list of shows.\n\n";
    			} else {
    				cout << endl;
    				display_separator();
    				display_one_show_struct(shows[pos]);
    				cout << "Season with the most episodes: season " << shows[pos].most_episodes_season;
        			cout << ", with " << shows[pos].most_episodes << " episodes.\n";
        			cout << "Season with the least episodes: season " << shows[pos].least_episodes_season;
        			cout << ", with " << shows[pos].least_episodes << " episodes.\n";
        			display_separator();
        			cout << endl;
    			}
    		    break;
    		}
    		case 5: {
    		    string show_input;
    			int pos;
    			cout << "You have chosen to display the average episodes per season of a given show.\n";
    			cout << "Enter the name of the show that you are interested in: ";
    			getline(cin, show_input);
    			pos = search_shows_array(shows, num_shows, show_input);
    			//cout << endl << "Position: " << pos << endl;
    			if(pos == -1) {
    				cout << "\nCould not find \"" << show_input << "\" in the list of shows.\n\n";
    			} else {
    				cout << endl;
    				display_separator();
    				display_one_show_struct(shows[pos]);
    				cout << fixed << setprecision(2);
    				cout << "Average episodes per season of " << shows[pos].name << ": ";
    				cout << shows[pos].avg_episodes_per_season << endl;
        			display_separator();
        			cout << endl;
    			}
    		    break;
    		}
    		case 6: {
    		    cout << "You have chosen to display only shows of a given criteria.\n";
    		    int criteria_mode = criteria_menu();
    		    cin.ignore();
    		    Filter_Criteria criteria_input = collect_criteria(criteria_mode);
    		    filter_shows_array(shows, num_shows, criteria_input, criteria_mode);
    		    break;
    		}
    		case 7: {
    		    int pos;
    		    cout << "You have chosen to display the oldest and newest shows by start date.\n\n";
    		    cout << "OLDEST SHOW:\n";
    		    oldest_show(shows, num_shows, pos);
    		    display_separator();
    		    display_one_show_struct(shows[pos]);
    		    display_separator();
    		    cout << "NEWEST SHOW:\n";
    		    newest_show(shows, num_shows, pos);
    		    display_separator();
    		    display_one_show_struct(shows[pos]);
    		    display_separator();
    		    cout << endl;
    		    break;
    		}
    		case 8: {
    		    string show_input;
    		    int pos;
    		    cout << "You have chosen to remove a show from the list.\n";
            	cout << "Enter the name of the show you would like to remove: ";
            	getline(cin, show_input);
            	pos = search_shows_array(shows, num_shows, show_input);
            	cout << endl;
            	if(pos == -1) {
            	    cout << "Could not find \"" << show_input << "\" in the list of shows.\n\n";
            	} else {
        		    remove_show(shows, num_shows, show_input, pos);
        		    cout << "Here is the updated list of shows:\n";
    		        display_shows_array(shows, num_shows);
    		    }
    		    break;
    		}
		} //end of switch
	}
	while(choice != 9);
	cout << "Thank you for using the program.\n";
	fin.close();
	return 0;
}


