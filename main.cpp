// Week 01 Programming Assignment - Jacob Boxley
// ITCS 2530 - C++ Programming
// This program collects basketball analytics data from the user and displays a summary
 
#include <iostream>
#include <string>
using namespace std;
 
int main()
{
    // Declare variables to store user input
    string playerName;
    double pointsPer100;
    double minutesPlayed;
    double trueShootingPct;
    double onCourtRating;
    double offCourtRating;
 
    // Display a welcome header
    cout << "========================================" << endl;
    cout << "   Basketball Analytics Evaluator" << endl;
    cout << "========================================" << endl;
    cout << endl;
 
    // Prompt the user for player information
    cout << "Enter the player's name: ";
    getline(cin, playerName);
 
    cout << "Enter their points per 100 possessions: ";
    cin >> pointsPer100;
 
    cout << "Enter their minutes played this season: ";
    cin >> minutesPlayed;
 
    cout << "Enter their true shooting percentage (e.g. 58.5): ";
    cin >> trueShootingPct;
 
    cout << "Enter the team's on-court rating with this player: ";
    cin >> onCourtRating;
 
    cout << "Enter the team's off-court rating without this player: ";
    cin >> offCourtRating;
 
    
    double onOffDifferential = onCourtRating - offCourtRating;
 
    
    double scoringContribution = (minutesPlayed / 48.0) * (pointsPer100 / 100.0) * 100;
 
    
    cout << endl;
    cout << "========================================" << endl;
    cout << "   Player Analytics Report" << endl;
    cout << "========================================" << endl;
    cout << endl;
    cout << playerName << " has posted " << pointsPer100 << " points per 100 possessions this season" << endl;
    cout << "with a true shooting percentage of " << trueShootingPct << "%, logging " << minutesPlayed << " minutes." << endl;
    cout << endl;
    cout << "When " << playerName << " is on the court, the team rates at " << onCourtRating << "." << endl;
    cout << "When they sit, that number drops to " << offCourtRating << "." << endl;
    
    cout << "That is an on/off differential of " << onOffDifferential << " points." << endl;
    cout << "A positive differential means the team performs better with " << playerName << " on the court." << endl;
    cout << "A negative differential means the team performs better when " << playerName << " sits." << endl;
 
    cout << endl;
    cout << "Estimated scoring contribution index: " << scoringContribution << endl;
    cout << endl;
    cout << "========================================" << endl;
 
    return 0;