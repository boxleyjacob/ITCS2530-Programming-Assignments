// ============================================================
// Week 05 Programming Assignment - Jacob Boxley
// ITCS 2530 - C++ Programming
// Building on Week 04: Added user-defined functions and console color.
//   - Functions: displayBanner, displayMenu, getValidInt,
//                getValidDouble, getValidString, computeStats,
//                displayReport, saveReport, setColor
//   - Console color: Windows SetConsoleTextAttribute
// ============================================================

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <limits>
#define NOMINMAX
#include <windows.h>
using namespace std;using namespace std;

// ============================================================
// NEW Week 05: Console color constants
// ============================================================
const int COLOR_DEFAULT = 7;   // White (standard)
const int COLOR_HEADER = 11;  // Cyan  (banners and section headers)
const int COLOR_LABEL = 14;  // Yellow (field labels)
const int COLOR_GOOD = 10;  // Green  (positive impact / success messages)
const int COLOR_BAD = 12;  // Red    (negative impact / error messages)
const int COLOR_NEUTRAL = 13;  // Magenta (neutral impact)

// ============================================================
// NEW Week 05: setColor
// Purpose: Change the console text color.
// ============================================================
void setColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// ============================================================
// NEW Week 05: displayBanner
// Purpose: Print the welcome banner (moved out of main).
// ============================================================
void displayBanner()
{
    setColor(COLOR_HEADER);
    cout << "================================================" << endl;
    cout << "       Welcome to Basketball Analytics Pro      " << endl;
    cout << "       Your Advanced Player Evaluation Tool     " << endl;
    cout << "================================================" << endl;
    setColor(COLOR_DEFAULT);
    cout << endl;
    cout << "This program analyzes a player's performance" << endl;
    cout << "using advanced basketball statistics." << endl;
    cout << endl;
}

// ============================================================
// NEW Week 05: displayMenu
// Purpose: Print the main menu options (moved out of main).
// ============================================================
void displayMenu()
{
    setColor(COLOR_HEADER);
    cout << "What would you like to do?" << endl;
    setColor(COLOR_DEFAULT);
    cout << "  1 - Add Player Session" << endl;
    cout << "  2 - View Session Report" << endl;
    cout << "  3 - Get Player Recommendation" << endl;
    cout << "  4 - Exit" << endl;
    cout << endl;
    cout << "Enter your choice (1-4): ";
}

// ============================================================
// NEW Week 05: getValidInt
// Purpose: Prompt for an int and loop until valid input >= min.
// ============================================================
int getValidInt(const string& prompt, int minVal)
{
    int value;
    cout << prompt;
    cin >> value;
    while (cin.fail() || value < minVal)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        setColor(COLOR_BAD);
        cout << "  [!] Invalid input. Enter a value >= " << minVal << ": ";
        setColor(COLOR_DEFAULT);
        cin >> value;
    }
    return value;
}

// ============================================================
// NEW Week 05: getValidDouble
// Purpose: Prompt for a double and loop until value is in range.
// ============================================================
double getValidDouble(const string& prompt, double minVal, double maxVal)
{
    double value;
    cout << prompt;
    cin >> value;
    while (cin.fail() || value < minVal || value > maxVal)
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        setColor(COLOR_BAD);
        cout << "  [!] Invalid input. Enter a value between "
            << minVal << " and " << maxVal << ": ";
        setColor(COLOR_DEFAULT);
        cin >> value;
    }
    return value;
}

// ============================================================
// NEW Week 05: getValidString
// Purpose: Read a full line (with spaces) and ensure it's not empty.
// ============================================================
string getValidString(const string& prompt)
{
    string value;
    cout << prompt;
    getline(cin, value);
    while (value.empty())
    {
        setColor(COLOR_BAD);
        cout << "  [!] Name cannot be empty. Try again: ";
        setColor(COLOR_DEFAULT);
        getline(cin, value);
    }
    return value;
}

// ============================================================
// NEW Week 05: computeStats (struct-free version using references)
// Purpose: Calculate derived stats from raw inputs.
//          Uses output parameters (passed by reference) so we
//          stay within Chapter 1-6 concepts (no structs/classes).
// ============================================================
void computeStats(int gamesPlayed, double minutesPlayed,
    double pointsPer100, double onCourtRating,
    double offCourtRating,
    double& onOffDifferential,
    double& avgMinutesPerGame,
    double& scoringContribution)
{
    onOffDifferential = onCourtRating - offCourtRating;
    avgMinutesPerGame = minutesPlayed / gamesPlayed;
    scoringContribution = (minutesPlayed / 48.0) * (pointsPer100 / 100.0) * 100.0;
}

// ============================================================
// NEW Week 05: displayReport
// Purpose: Print the single-session analytics report to console.
// ============================================================
void displayReport(const string& playerName, int gamesPlayed,
    double minutesPlayed, double avgMinutesPerGame,
    double pointsPer100, double trueShootingPct,
    double onCourtRating, double offCourtRating,
    double onOffDifferential, double scoringContribution,
    const string& roleLabel, const string& impactLabel,
    const string& experienceLabel)
{
    setColor(COLOR_HEADER);
    cout << "================================================" << endl;
    cout << "           Player Analytics Report              " << endl;
    cout << "================================================" << endl;
    setColor(COLOR_DEFAULT);

    cout << fixed << setprecision(1) << left;
    setColor(COLOR_LABEL);  cout << setw(32) << "Player Name:";
    setColor(COLOR_DEFAULT); cout << playerName << endl;

    setColor(COLOR_LABEL);  cout << setw(32) << "Games Played:";
    setColor(COLOR_DEFAULT); cout << gamesPlayed << endl;

    setColor(COLOR_LABEL);  cout << setw(32) << "Minutes Played:";
    setColor(COLOR_DEFAULT); cout << minutesPlayed << endl;

    setColor(COLOR_LABEL);  cout << setw(32) << "Avg Minutes Per Game:";
    setColor(COLOR_DEFAULT); cout << avgMinutesPerGame << endl;

    setColor(COLOR_LABEL);  cout << setw(32) << "Points Per 100 Possessions:";
    setColor(COLOR_DEFAULT); cout << pointsPer100 << endl;

    setColor(COLOR_LABEL);  cout << setw(32) << "True Shooting %:";
    setColor(COLOR_DEFAULT); cout << trueShootingPct << "%" << endl;

    setColor(COLOR_LABEL);  cout << setw(32) << "On-Court Rating:";
    setColor(COLOR_DEFAULT); cout << onCourtRating << endl;

    setColor(COLOR_LABEL);  cout << setw(32) << "Off-Court Rating:";
    setColor(COLOR_DEFAULT); cout << offCourtRating << endl;

    setColor(COLOR_LABEL);  cout << setw(32) << "On/Off Differential:";
    setColor(COLOR_DEFAULT); cout << onOffDifferential << endl;

    setColor(COLOR_LABEL);  cout << setw(32) << "Scoring Contribution Index:";
    setColor(COLOR_DEFAULT); cout << scoringContribution << endl;

    cout << endl;
    setColor(COLOR_HEADER);
    cout << "------------------------------------------------" << endl;
    setColor(COLOR_LABEL);  cout << setw(32) << "Player Role:";
    setColor(COLOR_DEFAULT); cout << roleLabel << endl;

    setColor(COLOR_LABEL);  cout << setw(32) << "Impact Classification:";
    setColor(COLOR_DEFAULT); cout << impactLabel << endl;

    setColor(COLOR_LABEL);  cout << setw(32) << "Experience Level:";
    setColor(COLOR_DEFAULT); cout << experienceLabel << endl;

    setColor(COLOR_HEADER);
    cout << "------------------------------------------------" << endl;
    setColor(COLOR_DEFAULT);
    cout << endl;

    // Impact sentence with color
    if (onOffDifferential > 0)
    {
        setColor(COLOR_GOOD);
        cout << playerName << " has a POSITIVE impact: the team performs better with them on court." << endl;
    }
    else if (onOffDifferential < 0)
    {
        setColor(COLOR_BAD);
        cout << playerName << " has a NEGATIVE impact: the team performs better when they sit." << endl;
    }
    else
    {
        setColor(COLOR_NEUTRAL);
        cout << playerName << " has a NEUTRAL impact on overall team performance." << endl;
    }

    setColor(COLOR_DEFAULT);
    cout << endl;
    setColor(COLOR_HEADER);
    cout << "================================================" << endl;
    setColor(COLOR_DEFAULT);
    cout << endl;
}

// ============================================================
// NEW Week 05: saveReport
// Purpose: Write all stored sessions to report.txt.
// ============================================================
void saveReport(const string storedName[], const int storedGames[],
    const double storedPts100[], const double storedTS[],
    const double storedOnOff[], const string storedRole[],
    int sessionCount)
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
}

// ============================================================
// main
// ============================================================
int main()
{
    // Constants (carried from Week 03/04)
    const double ELITE_TS_PCT = 58.0;
    const double STARTER_MINUTES = 28.0;
    const double HIGH_USAGE_POINTS = 20.0;
    const double POSITIVE_IMPACT = 5.0;
    const int    VETERAN_GAMES = 50;
    const int    MAX_SESSIONS = 5;
    const int    MENU_EXIT = 4;

    // Session storage arrays (carried from Week 04)
    string storedName[MAX_SESSIONS];
    int    storedGames[MAX_SESSIONS];
    double storedPts100[MAX_SESSIONS];
    double storedMinutes[MAX_SESSIONS];
    double storedTS[MAX_SESSIONS];
    double storedOnOff[MAX_SESSIONS];
    string storedRole[MAX_SESSIONS];
    string storedImpact[MAX_SESSIONS];
    string storedExperience[MAX_SESSIONS];
    int    sessionCount = 0;

    // Variables
    string playerName;
    int    gamesPlayed;
    int    menuChoice;
    double pointsPer100;
    double minutesPlayed;
    double trueShootingPct;
    double onCourtRating;
    double offCourtRating;

    // NEW Week 05: call displayBanner function instead of inline code
    displayBanner();

    // LOOP 1: do-while — Main menu loop (carried from Week 04)
    do
    {
        // NEW Week 05: call displayMenu function instead of inline code
        displayMenu();
        cin >> menuChoice;

        // LOOP 2: while — Menu input validation (carried from Week 04)
        while (cin.fail() || menuChoice < 1 || menuChoice > 4)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            setColor(COLOR_BAD);
            cout << "  [!] Invalid choice. Please enter 1-4: ";
            setColor(COLOR_DEFAULT);
            cin >> menuChoice;
        }

        cout << endl;

        switch (menuChoice)
        {

            // --------------------------------------------------------
            // CASE 1: Add Player Session
            // --------------------------------------------------------
        case 1:

            setColor(COLOR_HEADER);
            cout << "[ Mode: Add Player Session ]" << endl;
            setColor(COLOR_DEFAULT);
            cout << endl;

            if (sessionCount >= MAX_SESSIONS)
            {
                setColor(COLOR_BAD);
                cout << "  [!] Session limit reached (" << MAX_SESSIONS << " max). View or exit." << endl;
                setColor(COLOR_DEFAULT);
                cout << endl;
                break;
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            // NEW Week 05: use input functions instead of inline validation loops
            playerName = getValidString("Enter the player's name: ");
            gamesPlayed = getValidInt("Enter the number of games played this season: ", 1);
            pointsPer100 = getValidDouble("Enter their points per 100 possessions: ", 0.0, 200.0);
            minutesPlayed = getValidDouble("Enter their minutes played this season: ", 0.0, 3936.0);
            trueShootingPct = getValidDouble("Enter their true shooting percentage (e.g. 58.5): ", 0.0, 100.0);
            onCourtRating = getValidDouble("Enter the team's on-court rating with this player: ", -50.0, 200.0);
            offCourtRating = getValidDouble("Enter the team's off-court rating without this player: ", -50.0, 200.0);

            // NEW Week 05: derived stats via computeStats function
            {
                double onOffDifferential, avgMinutesPerGame, scoringContribution;
                computeStats(gamesPlayed, minutesPlayed, pointsPer100,
                    onCourtRating, offCourtRating,
                    onOffDifferential, avgMinutesPerGame, scoringContribution);

                // if/else Block 1: Role classification (carried from Week 03/04)
                string roleLabel = "";
                if (trueShootingPct >= ELITE_TS_PCT && avgMinutesPerGame >= STARTER_MINUTES)
                    roleLabel = "Elite Starter";
                else if (trueShootingPct >= ELITE_TS_PCT && avgMinutesPerGame < STARTER_MINUTES)
                    roleLabel = "Efficient Reserve";
                else if (trueShootingPct < ELITE_TS_PCT && avgMinutesPerGame >= STARTER_MINUTES)
                    roleLabel = "High-Volume Starter";
                else
                    roleLabel = "Developmental Player";

                // if/else Block 2: Impact classification (carried from Week 03/04)
                string impactLabel = "";
                if (onOffDifferential >= POSITIVE_IMPACT && pointsPer100 >= HIGH_USAGE_POINTS)
                    impactLabel = "Franchise Cornerstone";
                else if (onOffDifferential >= POSITIVE_IMPACT && pointsPer100 < HIGH_USAGE_POINTS)
                    impactLabel = "Two-Way Glue Guy";
                else if (onOffDifferential < POSITIVE_IMPACT && pointsPer100 >= HIGH_USAGE_POINTS)
                    impactLabel = "Volume Scorer";
                else
                    impactLabel = "Role Player";

                // if/else Block 3: Experience assessment (carried from Week 03/04)
                string experienceLabel = "";
                if (gamesPlayed >= VETERAN_GAMES && onOffDifferential > 0)
                    experienceLabel = "Veteran Contributor";
                else if (gamesPlayed >= VETERAN_GAMES && onOffDifferential <= 0)
                    experienceLabel = "Veteran - Needs Role Adjustment";
                else
                    experienceLabel = "Still Building Experience";

                // NEW Week 05: call displayReport function instead of inline output
                displayReport(playerName, gamesPlayed, minutesPlayed,
                    avgMinutesPerGame, pointsPer100, trueShootingPct,
                    onCourtRating, offCourtRating,
                    onOffDifferential, scoringContribution,
                    roleLabel, impactLabel, experienceLabel);

                // Store session (carried from Week 04)
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

                setColor(COLOR_GOOD);
                cout << "  [+] Session saved! (" << sessionCount << "/" << MAX_SESSIONS << " slots used)" << endl;
                setColor(COLOR_DEFAULT);
                cout << endl;
            }
            break;

            // --------------------------------------------------------
            // CASE 2: View Session Report
            // LOOP 3: for — iterates over all stored sessions (Week 04)
            // --------------------------------------------------------
        case 2:

            setColor(COLOR_HEADER);
            cout << "[ Mode: View Session Report ]" << endl;
            setColor(COLOR_DEFAULT);
            cout << endl;

            if (sessionCount == 0)
            {
                setColor(COLOR_BAD);
                cout << "  [!] No sessions recorded yet. Add a session first." << endl;
                setColor(COLOR_DEFAULT);
                cout << endl;
                break;
            }

            // Console table (carried from Week 04)
            setColor(COLOR_HEADER);
            cout << "=================================================" << endl;
            cout << "           All Sessions - Summary Report          " << endl;
            cout << "=================================================" << endl;
            setColor(COLOR_LABEL);
            cout << left
                << setw(20) << "Player"
                << setw(8) << "Games"
                << setw(12) << "Pts/100"
                << setw(8) << "TS%"
                << setw(10) << "On/Off"
                << setw(22) << "Role"
                << endl;
            setColor(COLOR_DEFAULT);
            cout << string(80, '-') << endl;

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

            // NEW Week 05: call saveReport function instead of inline file writing
            saveReport(storedName, storedGames, storedPts100, storedTS,
                storedOnOff, storedRole, sessionCount);

            setColor(COLOR_GOOD);
            cout << "  Report saved to report.txt" << endl;
            setColor(COLOR_DEFAULT);
            cout << endl;
            break;

            // --------------------------------------------------------
            // CASE 3: Get Player Recommendation (carried from Week 03/04)
            // --------------------------------------------------------
        case 3:

            setColor(COLOR_HEADER);
            cout << "[ Mode: Get Player Recommendation ]" << endl;
            setColor(COLOR_DEFAULT);
            cout << endl;

            if (sessionCount == 0)
            {
                setColor(COLOR_BAD);
                cout << "  [!] No sessions recorded yet. Add a session first." << endl;
                setColor(COLOR_DEFAULT);
                cout << endl;
                break;
            }

            setColor(COLOR_HEADER);
            cout << "=================================================" << endl;
            cout << "           Player Recommendations                 " << endl;
            cout << "=================================================" << endl;
            setColor(COLOR_DEFAULT);

            for (int i = 0; i < sessionCount; i++)
            {
                cout << endl;
                setColor(COLOR_LABEL);  cout << "Player:     ";
                setColor(COLOR_DEFAULT); cout << storedName[i] << endl;
                setColor(COLOR_LABEL);  cout << "Role:       ";
                setColor(COLOR_DEFAULT); cout << storedRole[i] << endl;
                setColor(COLOR_LABEL);  cout << "Impact:     ";
                setColor(COLOR_DEFAULT); cout << storedImpact[i] << endl;
                setColor(COLOR_LABEL);  cout << "Experience: ";
                setColor(COLOR_DEFAULT); cout << storedExperience[i] << endl;
                cout << "------------------------------------------------" << endl;
            }

            cout << endl;
            break;

            // --------------------------------------------------------
            // CASE 4: Exit
            // --------------------------------------------------------
        case 4:
            setColor(COLOR_GOOD);
            cout << "Thanks for using Basketball Analytics Pro. Good game!" << endl;
            setColor(COLOR_DEFAULT);
            cout << endl;
            break;

        } // end switch

    } while (menuChoice != MENU_EXIT); // LOOP 1 ends

    return 0;

} // end main