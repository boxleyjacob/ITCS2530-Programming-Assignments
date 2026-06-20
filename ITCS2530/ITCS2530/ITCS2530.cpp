// ============================================================
// Week 04 Programming Assignment - Jacob Boxley
// ITCS 2530 - C++ Programming
// Building on Week 03: Added repetition (loops).
//   - do-while: keeps the menu running until user exits
//   - while:    input validation loops (replaces single if checks)
//   - for:      displays all recorded sessions in the report
// ============================================================

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <limits>
using namespace std;

int main()
{
    //  Constants (carried from Week 03)
    const double ELITE_TS_PCT = 58.0;   // True shooting % considered elite
    const double STARTER_MINUTES = 28.0;   // Avg min/game to be considered a starter
    const double HIGH_USAGE_POINTS = 20.0;   // Points per 100 considered high scoring load
    const double POSITIVE_IMPACT = 5.0;    // On/off differential for strong positive impact
    const int    VETERAN_GAMES = 50;     // Games threshold for veteran status
    const int    MAX_SESSIONS = 5;      // Max player sessions we can store (for arrays)
    const int    MENU_EXIT = 4;      // Menu option that exits the program

    // Session storage arrays (new for Week 04 — needed for for loop) ──
    // These hold data across multiple sessions so we can display them all at once
    string storedName[MAX_SESSIONS];
    int    storedGames[MAX_SESSIONS];
    double storedPts100[MAX_SESSIONS];
    double storedMinutes[MAX_SESSIONS];
    double storedTS[MAX_SESSIONS];
    double storedOnOff[MAX_SESSIONS];
    string storedRole[MAX_SESSIONS];
    string storedImpact[MAX_SESSIONS];
    string storedExperience[MAX_SESSIONS];
    int    sessionCount = 0;   // Tracks how many sessions have been entered

    // Variables (carried from Week 03) 
    string playerName;
    int    gamesPlayed;
    int    menuChoice;
    double pointsPer100;
    double minutesPlayed;
    double trueShootingPct;
    double onCourtRating;
    double offCourtRating;

    // Welcome Banner (carried from Week 03) 
    cout << "================================================" << endl;
    cout << "       Welcome to Basketball Analytics Pro      " << endl;
    cout << "       Your Advanced Player Evaluation Tool     " << endl;
    cout << "================================================" << endl;
    cout << endl;
    cout << "This program analyzes a player's performance" << endl;
    cout << "using advanced basketball statistics." << endl;
    cout << endl;

    // ════════════════════════════════════════════════════════════
    // LOOP 1: do-while — Main menu loop
    // Purpose: Keep the program running until the user selects Exit.
    
    do
    {
        // Display menu options
        cout << "What would you like to do?" << endl;
        cout << "  1 - Add Player Session" << endl;
        cout << "  2 - View Session Report" << endl;
        cout << "  3 - Get Player Recommendation" << endl;
        cout << "  4 - Exit" << endl;
        cout << endl;
        cout << "Enter your choice (1-4): ";
        cin >> menuChoice;

       
        // LOOP 2: while — Menu input validation
        // Purpose: Keep re-prompting if the user enters something
        // invalid. 
        while (cin.fail() || menuChoice < 1 || menuChoice > 4)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "  [!] Invalid choice. Please enter 1-4: ";
            cin >> menuChoice;
        }

        cout << endl;

        // Switch on menu choice 
        switch (menuChoice)
        {

            
            // CASE 1: Add Player Session
            
        case 1:

            cout << "[ Mode: Add Player Session ]" << endl;
            cout << endl;

            if (sessionCount >= MAX_SESSIONS)
            {
                cout << "  [!] Session limit reached (" << MAX_SESSIONS << " max). View or exit." << endl;
                cout << endl;
                break;
            }

            
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Enter the player's name: ";
            getline(cin, playerName);

            // while: validate gamesPlayed 
            cout << "Enter the number of games played this season: ";
            cin >> gamesPlayed;
            while (cin.fail() || gamesPlayed <= 0)
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "  [!] Invalid input. Enter a positive number of games: ";
                cin >> gamesPlayed;
            }

            //  while: validate pointsPer100
            cout << "Enter their points per 100 possessions: ";
            cin >> pointsPer100;
            while (cin.fail() || pointsPer100 < 0)
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "  [!] Invalid input. Enter 0 or greater: ";
                cin >> pointsPer100;
            }

            //  while: validate minutesPlayed 
            cout << "Enter their minutes played this season: ";
            cin >> minutesPlayed;
            while (cin.fail() || minutesPlayed < 0)
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "  [!] Invalid input. Enter 0 or greater: ";
                cin >> minutesPlayed;
            }

            // while: validate trueShootingPct 
            cout << "Enter their true shooting percentage (e.g. 58.5): ";
            cin >> trueShootingPct;
            while (cin.fail() || trueShootingPct < 0 || trueShootingPct > 100)
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "  [!] Invalid input. Enter a value between 0 and 100: ";
                cin >> trueShootingPct;
            }

            // while: validate onCourtRating 
            cout << "Enter the team's on-court rating with this player: ";
            cin >> onCourtRating;
            while (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "  [!] Invalid input. Enter a numeric rating: ";
                cin >> onCourtRating;
            }

            // while: validate offCourtRating
            cout << "Enter the team's off-court rating without this player: ";
            cin >> offCourtRating;
            while (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "  [!] Invalid input. Enter a numeric rating: ";
                cin >> offCourtRating;
            }

            // Derived stats (carried from Week 03) 
            {
                double onOffDifferential = onCourtRating - offCourtRating;
                double scoringContribution = (minutesPlayed / 48.0) * (pointsPer100 / 100.0) * 100.0;
                double avgMinutesPerGame = minutesPlayed / gamesPlayed;

                // if/else Block 1: Role classification 
                // Compound condition: TS% AND avg minutes per game
                string roleLabel = "";
                if (trueShootingPct >= ELITE_TS_PCT && avgMinutesPerGame >= STARTER_MINUTES)
                    roleLabel = "Elite Starter";
                else if (trueShootingPct >= ELITE_TS_PCT && avgMinutesPerGame < STARTER_MINUTES)
                    roleLabel = "Efficient Reserve";
                else if (trueShootingPct < ELITE_TS_PCT && avgMinutesPerGame >= STARTER_MINUTES)
                    roleLabel = "High-Volume Starter";
                else
                    roleLabel = "Developmental Player";

                // if/else Block 2: Impact classification 
                // Compound condition: on/off differential AND points per 100
                string impactLabel = "";
                if (onOffDifferential >= POSITIVE_IMPACT && pointsPer100 >= HIGH_USAGE_POINTS)
                    impactLabel = "Franchise Cornerstone";
                else if (onOffDifferential >= POSITIVE_IMPACT && pointsPer100 < HIGH_USAGE_POINTS)
                    impactLabel = "Two-Way Glue Guy";
                else if (onOffDifferential < POSITIVE_IMPACT && pointsPer100 >= HIGH_USAGE_POINTS)
                    impactLabel = "Volume Scorer";
                else
                    impactLabel = "Role Player";

                // if/else Block 3: Experience assessment 
                // Compound condition: games played AND on/off differential
                string experienceLabel = "";
                if (gamesPlayed >= VETERAN_GAMES && onOffDifferential > 0)
                    experienceLabel = "Veteran Contributor";
                else if (gamesPlayed >= VETERAN_GAMES && onOffDifferential <= 0)
                    experienceLabel = "Veteran - Needs Role Adjustment";
                else
                    experienceLabel = "Still Building Experience";

                // Console output for this session
                cout << endl;
                cout << "================================================" << endl;
                cout << "           Player Analytics Report              " << endl;
                cout << "================================================" << endl;
                cout << fixed << setprecision(1) << left;
                cout << setw(32) << "Player Name:" << playerName << endl;
                cout << setw(32) << "Games Played:" << gamesPlayed << endl;
                cout << setw(32) << "Minutes Played:" << minutesPlayed << endl;
                cout << setw(32) << "Avg Minutes Per Game:" << avgMinutesPerGame << endl;
                cout << setw(32) << "Points Per 100 Possessions:" << pointsPer100 << endl;
                cout << setw(32) << "True Shooting %:" << trueShootingPct << "%" << endl;
                cout << setw(32) << "On-Court Rating:" << onCourtRating << endl;
                cout << setw(32) << "Off-Court Rating:" << offCourtRating << endl;
                cout << setw(32) << "On/Off Differential:" << onOffDifferential << endl;
                cout << setw(32) << "Scoring Contribution Index:" << scoringContribution << endl;
                cout << endl;
                cout << "------------------------------------------------" << endl;
                cout << setw(32) << "Player Role:" << roleLabel << endl;
                cout << setw(32) << "Impact Classification:" << impactLabel << endl;
                cout << setw(32) << "Experience Level:" << experienceLabel << endl;
                cout << "------------------------------------------------" << endl;
                cout << endl;

                if (onOffDifferential > 0)
                    cout << playerName << " has a POSITIVE impact: the team performs better with them on court." << endl;
                else if (onOffDifferential < 0)
                    cout << playerName << " has a NEGATIVE impact: the team performs better when they sit." << endl;
                else
                    cout << playerName << " has a NEUTRAL impact on overall team performance." << endl;

                cout << endl;
                cout << "================================================" << endl;
                cout << endl;

                // Store session data for the report (Case 2) 
                storedName[sessionCount] = playerName;
                storedGames[sessionCount] = gamesPlayed;
                storedPts100[sessionCount] = pointsPer100;
                storedMinutes[sessionCount] = minutesPlayed;
                storedTS[sessionCount] = trueShootingPct;
                storedOnOff[sessionCount] = onOffDifferential;
                storedRole[sessionCount] = roleLabel;
                storedImpact[sessionCount] = impactLabel;
                storedExperience[sessionCount] = experienceLabel;
                sessionCount++;

                cout << "  [+] Session saved! (" << sessionCount << "/" << MAX_SESSIONS << " slots used)" << endl;
                cout << endl;
            }
            break;

            // 
            // CASE 2: View Session Report
            //
            // LOOP 3: for — Iterates over all stored sessions
            // Purpose: Display every saved player in a formatted table.
            
            
        case 2:

            cout << "[ Mode: View Session Report ]" << endl;
            cout << endl;

            if (sessionCount == 0)
            {
                cout << "  [!] No sessions recorded yet. Add a session first." << endl;
                cout << endl;
                break;
            }

            // Console table 
            cout << "=================================================" << endl;
            cout << "           All Sessions - Summary Report          " << endl;
            cout << "=================================================" << endl;
            cout << left
                << setw(20) << "Player"
                << setw(8) << "Games"
                << setw(12) << "Pts/100"
                << setw(8) << "TS%"
                << setw(10) << "On/Off"
                << setw(22) << "Role"
                << endl;
            cout << string(80, '-') << endl;

            // for loop: i starts at 0, runs once per stored session
            for (int i = 0; i < sessionCount; i++)
            {
                cout << fixed << setprecision(1) << left
                    << setw(20) << storedName[i]
                    << setw(8) << storedGames[i]
                    << setw(12) << storedPts100[i]
                    << setw(8) << storedTS[i]
                    << setw(10) << storedOnOff[i]
                    << setw(22) << storedRole[i]
                    << endl;
            }

            cout << string(80, '-') << endl;
            cout << endl;

            // Write same report to report.txt 
            {
                ofstream reportFile("report.txt");

                reportFile << "=================================================" << endl;
                reportFile << "           All Sessions - Summary Report          " << endl;
                reportFile << "           ITCS 2530 | Jacob Boxley               " << endl;
                reportFile << "=================================================" << endl;
                reportFile << left
                    << setw(20) << "Player"
                    << setw(8) << "Games"
                    << setw(12) << "Pts/100"
                    << setw(8) << "TS%"
                    << setw(10) << "On/Off"
                    << setw(22) << "Role"
                    << endl;
                reportFile << string(80, '-') << endl;

                // Same for loop written to file
                for (int i = 0; i < sessionCount; i++)
                {
                    reportFile << fixed << setprecision(1) << left
                        << setw(20) << storedName[i]
                        << setw(8) << storedGames[i]
                        << setw(12) << storedPts100[i]
                        << setw(8) << storedTS[i]
                        << setw(10) << storedOnOff[i]
                        << setw(22) << storedRole[i]
                        << endl;
                }

                reportFile << string(80, '-') << endl;
                reportFile.close();
                cout << "  Report saved to report.txt" << endl;
                cout << endl;
            }
            break;

            // ────────────────────────────────────────────────────────
            // CASE 3: Get Player Recommendation (carried from Week 03)
            // ────────────────────────────────────────────────────────
        case 3:

            cout << "[ Mode: Get Player Recommendation ]" << endl;
            cout << endl;

            if (sessionCount == 0)
            {
                cout << "  [!] No sessions recorded yet. Add a session first." << endl;
                cout << endl;
                break;
            }

            cout << "=================================================" << endl;
            cout << "           Player Recommendations                 " << endl;
            cout << "=================================================" << endl;

            for (int i = 0; i < sessionCount; i++)
            {
                cout << endl;
                cout << "Player:     " << storedName[i] << endl;
                cout << "Role:       " << storedRole[i] << endl;
                cout << "Impact:     " << storedImpact[i] << endl;
                cout << "Experience: " << storedExperience[i] << endl;
                cout << "------------------------------------------------" << endl;
            }

            cout << endl;
            break;

            // ────────────────────────────────────────────────────────
            // CASE 4: Exit
            // ────────────────────────────────────────────────────────
        case 4:
            cout << "Thanks for using Basketball Analytics Pro. Good game!" << endl;
            cout << endl;
            break;

        } // end switch

    } while (menuChoice != MENU_EXIT);   // LOOP 1 ends — exit when user picks 4

    return 0;

} // end main