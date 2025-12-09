#include <iostream>
using namespace std;

const int EPISODES_CAPACITY = 20;
const int SHOWS_CAPACITY = 20;

struct Show {
    string name;
    string genre;
    string network;
    int seasons;
    int start_year, end_year;
    int episodes_each_season[EPISODES_CAPACITY];
    int most_episodes = 0, least_episodes = 100;
    int most_episodes_season, least_episodes_season;
    int total_episodes;
    double avg_episodes_per_season;
};

struct Filter_Criteria {
    int min_start_year;
    int min_num_seasons;
    string network;
    string genre;
};

int menu();
void display_separator();
//populate and display one show struct
void populate_one_show_struct(istream& fin, Show& s);
void display_one_show_struct(const Show& s);
//analysis single function
void least_most_episode_season(Show& s); 
//populate and display shows array
void populate_shows_array(istream& fin, Show s[], int& num_shows);
void display_shows_array(const Show s[], int num_shows);
//sorting functions
int sort_menu();
bool sort_condition(const Show s[], const Show& temp, int sort_mode, int j);
void sort_shows_array(Show s[], int num_shows, int sort_mode);
void display_sort_mode(int sort_mode);
//search function
int search_shows_array(const Show s[], int num_shows, const string& target);
//filter functions
int criteria_menu();
Filter_Criteria collect_criteria(int criteria_mode);
bool criteria_condition(const Filter_Criteria& c, const Show& s, int criteria_mode);
void filter_shows_array(const Show s[], int num_shows, const Filter_Criteria& c, int criteria_mode);
//analysis multiple functions
void oldest_show(const Show s[], int num_shows, int& pos);
void newest_show(const Show s[], int num_shows, int& pos);
//remove function
void remove_show(Show s[], int& num_shows, string target_show, int pos);







