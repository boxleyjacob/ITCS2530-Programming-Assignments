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

//PA6 fixed using namespace std twice error
using namespace std;

// ============================================================
// Week 05: Console color constants
// ============================================================
const int COLOR_DEFAULT = 7;   // White (standard)
const int COLOR_HEADER = 11;  // Cyan  (banners and section headers)
const int COLOR_LABEL = 14;  // Yellow (field labels)
const int COLOR_GOOD = 10;  // Green  (positive impact / success messages)
const int COLOR_BAD = 12;  // Red    (negative impact / error messages)
const int COLOR_NEUTRAL = 13;  // Magenta (neutral impact)

// ============================================================
// New PA7 Mach - refactoring storage arrays to a struct
// ============================================================
struct SessionStorage
{
    string storedName;
    int    storedGames;
    double storedPts100;
    double storedMinutes;
    double storedTS;
    double storedOnOff;
    string storedRole;
    string storedImpact;
    string storedExperience;
};

// ============================================================
// Week 05: setColor
// Purpose: Change the console text color.
// ============================================================
void setColor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

// ============================================================
// Week 05: displayBanner
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
// Week 05: displayMenu
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
// Week 05: getValidInt
// Purpose: Prompt for an int and loop until valid input >= min.
// ============================================================
//NEW PA7 Mach - Fixed buffer issue again.
int getValidInt(const string& prompt, int minVal)
{
    int value;

    cout << prompt;
    cin >> value;

    while (cin.fail() || value < minVal || cin.peek() != '\n')
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        setColor(COLOR_BAD);
        cout << "  [!] Invalid input. Enter a value >= "
            << minVal << ": ";
        setColor(COLOR_DEFAULT);

        cin >> value;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return value;
}

// ============================================================
// Week 05: getValidDouble
// Purpose: Prompt for a double and loop until value is in range.
// ============================================================
//NEW PA7 Mach - Fixed buffer issue
double getValidDouble(const string& prompt, double minVal, double maxVal)
{
    double value;

    cout << prompt;
    cin >> value;

    while (cin.fail() || value < minVal || value > maxVal || cin.peek() != '\n')
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        setColor(COLOR_BAD);
        cout << "  [!] Invalid input. Enter a value between "
            << minVal << " and " << maxVal << ": ";
        setColor(COLOR_DEFAULT);

        cin >> value;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return value;
}

// ============================================================
// Week 05: getValidString
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
// Week 05: computeStats
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
// Week 05: displayReport
// Purpose: Print the single-session analytics report to console.
// ============================================================
//NEW PA7 Mach - Refactored for struct
void displayReport(const SessionStorage& session,
    double avgMinutesPerGame,
    double onCourtRating,
    double offCourtRating,
    double scoringContribution)
{
    setColor(COLOR_HEADER);
    cout << "================================================" << endl;
    cout << "           Player Analytics Report              " << endl;
    cout << "================================================" << endl;
    setColor(COLOR_DEFAULT);

    cout << fixed << setprecision(1) << left;
    setColor(COLOR_LABEL);  cout << setw(32) << "Player Name:";
    setColor(COLOR_DEFAULT); cout << session.storedName << endl;

    setColor(COLOR_LABEL);  cout << setw(32) << "Games Played:";
    setColor(COLOR_DEFAULT); cout << session.storedGames << endl;

    setColor(COLOR_LABEL);  cout << setw(32) << "Minutes Played:";
    setColor(COLOR_DEFAULT); cout << session.storedMinutes << endl;

    setColor(COLOR_LABEL);  cout << setw(32) << "Avg Minutes Per Game:";
    setColor(COLOR_DEFAULT); cout << avgMinutesPerGame << endl;

    setColor(COLOR_LABEL);  cout << setw(32) << "Points Per 100 Possessions:";
    setColor(COLOR_DEFAULT); cout << session.storedPts100 << endl;

    setColor(COLOR_LABEL);  cout << setw(32) << "True Shooting %:";
    setColor(COLOR_DEFAULT); cout << session.storedTS << "%" << endl;

    setColor(COLOR_LABEL);  cout << setw(32) << "On-Court Rating:";
    setColor(COLOR_DEFAULT); cout << onCourtRating << endl;

    setColor(COLOR_LABEL);  cout << setw(32) << "Off-Court Rating:";
    setColor(COLOR_DEFAULT); cout << offCourtRating << endl;

    setColor(COLOR_LABEL);  cout << setw(32) << "On/Off Differential:";
    setColor(COLOR_DEFAULT); cout << session.storedOnOff << endl;

    setColor(COLOR_LABEL);  cout << setw(32) << "Scoring Contribution Index:";
    setColor(COLOR_DEFAULT); cout << scoringContribution << endl;

    cout << endl;
    setColor(COLOR_HEADER);
    cout << "------------------------------------------------" << endl;
    setColor(COLOR_LABEL);  cout << setw(32) << "Player Role:";
    setColor(COLOR_DEFAULT); cout << session.storedRole << endl;

    setColor(COLOR_LABEL);  cout << setw(32) << "Impact Classification:";
    setColor(COLOR_DEFAULT); cout << session.storedImpact << endl;

    setColor(COLOR_LABEL);  cout << setw(32) << "Experience Level:";
    setColor(COLOR_DEFAULT); cout << session.storedExperience << endl;

    setColor(COLOR_HEADER);
    cout << "------------------------------------------------" << endl;
    setColor(COLOR_DEFAULT);
    cout << endl;

    // Impact sentence with color
    // NEW PA7 Mach - Refactored for struct
    if (session.storedOnOff > 0)
    {
        setColor(COLOR_GOOD);
        cout << session.storedName
            << " has a POSITIVE impact: the team performs better with them on court." << endl;
    }
    else if (session.storedOnOff < 0)
    {
        setColor(COLOR_BAD);
        cout << session.storedName
            << " has a NEGATIVE impact: the team performs better when they sit." << endl;
    }
    else
    {
        setColor(COLOR_NEUTRAL);
        cout << session.storedName
            << " has a NEUTRAL impact on overall team performance." << endl;
    }

    setColor(COLOR_DEFAULT);
    cout << endl;
    setColor(COLOR_HEADER);
    cout << "================================================" << endl;
    setColor(COLOR_DEFAULT);
    cout << endl;
}

// ============================================================
// Week 05: saveReport
// Purpose: Write all stored sessions to report.txt.
// ============================================================

//NEW PA7 Mach - Refactoring for struct
void saveReport(const SessionStorage sessions[],
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

    //NEW PA7 Mach - refactored for struct
    for (int i = 0; i < sessionCount; i++)
    {
        reportFile << fixed << setprecision(1) << left
            << setw(20) << sessions[i].storedName
            << setw(8) << sessions[i].storedGames
            << setw(12) << sessions[i].storedPts100
            << setw(8) << sessions[i].storedTS
            << setw(10) << sessions[i].storedOnOff
            << setw(22) << sessions[i].storedRole
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

    //PA6 Mach - All Arrays recieve mulitipule input however stored minutes is not used yet.
    //NEW PA7 replaced arrays with new struct
    SessionStorage sessions[MAX_SESSIONS];
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

    // Week 05: call displayBanner function instead of inline code
    displayBanner();

    // LOOP 1: do-while — Main menu loop (carried from Week 04)
    do
    {
        // Week 05: call displayMenu function instead of inline code
        displayMenu();
        cin >> menuChoice;

        // LOOP 2: while — Menu input validation (carried from Week 04)
        //NEW PA7 Mach - Fixed buffer issue.
        while (cin.fail() || menuChoice < 1 || menuChoice > 4 || cin.peek() != '\n')
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            setColor(COLOR_BAD);
            cout << "  [!] Invalid choice. Please enter 1-4: ";
            setColor(COLOR_DEFAULT);

            cin >> menuChoice;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

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
            //PA6 Mach - This is array size validation.
            if (sessionCount >= MAX_SESSIONS)
            {
                setColor(COLOR_BAD);
                cout << "  [!] Session limit reached (" << MAX_SESSIONS << " max). View or exit." << endl;
                setColor(COLOR_DEFAULT);
                cout << endl;
                break;
            }

            // Week 05: use input functions instead of inline validation loops
            playerName = getValidString("Enter the player's name: ");
            gamesPlayed = getValidInt("Enter the number of games played this season: ", 1);
            pointsPer100 = getValidDouble("Enter their points per 100 possessions: ", 0.0, 200.0);
            minutesPlayed = getValidDouble("Enter their minutes played this season: ", 0.0, 3936.0);
            trueShootingPct = getValidDouble("Enter their true shooting percentage (e.g. 58.5): ", 0.0, 100.0);
            onCourtRating = getValidDouble("Enter the team's on-court rating with this player: ", -50.0, 200.0);
            offCourtRating = getValidDouble("Enter the team's off-court rating without this player: ", -50.0, 200.0);

            // Week 05: derived stats via computeStats function
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
                //PA6 Mach Refactoring Block 3 with an enum for assignment.
                //PA6 ENUM addition
                enum ExperienceLevel
                {
                    VETERAN_CONTRIBUTOR,
                    VETERAN_NEEDS_ROLE_ADJUSTMENT,
                    STILL_BUILDING_EXPERIENCE
                };

                //PA6 Mach String replacement
                ExperienceLevel experienceLabel;
                //PA6 Mach since I wrote the enum prior to functions being added the enum screwed up passed
                //values using this to fix it.
                string experienceText;

                //PA6 MAch Updated if statement for enum
                if (gamesPlayed >= VETERAN_GAMES && onOffDifferential > 0)
                    experienceLabel = VETERAN_CONTRIBUTOR;
                else if (gamesPlayed >= VETERAN_GAMES && onOffDifferential <= 0)
                    experienceLabel = VETERAN_NEEDS_ROLE_ADJUSTMENT;
                else
                    experienceLabel = STILL_BUILDING_EXPERIENCE;

                //PA6 Mach continuing to fix value passing for functions
                if (experienceLabel == VETERAN_CONTRIBUTOR)
                    experienceText = "Veteran Contributor";
                else if (experienceLabel == VETERAN_NEEDS_ROLE_ADJUSTMENT)
                    experienceText = "Veteran - Needs Role Adjustment";
                else
                    experienceText = "Still Building Experience";

                // Store session (carried from Week 04)
                //NEW PA7 Mach - Refactored for struct
                sessions[sessionCount].storedName = playerName;
                sessions[sessionCount].storedGames = gamesPlayed;
                sessions[sessionCount].storedPts100 = pointsPer100;
                sessions[sessionCount].storedMinutes = minutesPlayed;
                sessions[sessionCount].storedTS = trueShootingPct;
                sessions[sessionCount].storedOnOff = onOffDifferential;
                sessions[sessionCount].storedRole = roleLabel;
                sessions[sessionCount].storedImpact = impactLabel;
                sessions[sessionCount].storedExperience = experienceText;

                // Week 05: call displayReport function instead of inline output
                //NEW PA7 Mach - Refactored for struct
                displayReport(sessions[sessionCount],
                    avgMinutesPerGame,
                    onCourtRating,
                    offCourtRating,
                    scoringContribution);

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

            //NEW PA7 Mach - Refactored for struct
            for (int i = 0; i < sessionCount; i++)
            {
                cout << fixed << setprecision(1) << left
                    << setw(20) << sessions[i].storedName
                    << setw(8) << sessions[i].storedGames
                    << setw(12) << sessions[i].storedPts100
                    << setw(8) << sessions[i].storedTS
                    << setw(10) << sessions[i].storedOnOff
                    << setw(22) << sessions[i].storedRole
                    << endl;
            }

            cout << string(80, '-') << endl;
            cout << endl;

            //Week 05: call saveReport function instead of inline file writing
            //NEW PA7 updated call for struct
            saveReport(sessions, sessionCount);

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

            //NEW PA7 Mach - Refactored for struct
            for (int i = 0; i < sessionCount; i++)
            {
                cout << endl;
                setColor(COLOR_LABEL);  cout << "Player:     ";
                setColor(COLOR_DEFAULT); cout << sessions[i].storedName << endl;
                setColor(COLOR_LABEL);  cout << "Role:       ";
                setColor(COLOR_DEFAULT); cout << sessions[i].storedRole << endl;
                setColor(COLOR_LABEL);  cout << "Impact:     ";
                setColor(COLOR_DEFAULT); cout << sessions[i].storedImpact << endl;
                setColor(COLOR_LABEL);  cout << "Experience: ";
                setColor(COLOR_DEFAULT); cout << sessions[i].storedExperience << endl;
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