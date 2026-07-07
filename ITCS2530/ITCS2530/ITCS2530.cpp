// ============================================================
// Week 08 Programming Assignment - Chris Mach
// ITCS 2530 - C++ Programming
// Adding classes to the program
//
// ============================================================

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <limits>
#define NOMINMAX
#include <windows.h>

using namespace std;

// ============================================================
//  NEW PA8 Mach - struct moved for class use
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
// NEW PA8 Mach - Addition of classes
// ============================================================
class StatisticsCalculator
{

	// ============================================================
	// Week 05: computeStats
	// Purpose: Calculate derived stats from raw inputs.
	//          Uses output parameters (passed by reference) so we
	//          stay within Chapter 1-6 concepts (no structs/classes).
	// ============================================================
public:
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
};

// ============================================================
// NEW PA8 Mach - Addition of classes
// ============================================================
class ReportManager
{
private:
	// ============================================================
	// Week 05: Console color constants
	// ============================================================
	const int COLOR_DEFAULT = 7;   // White (standard)
	const int COLOR_HEADER = 11;  // Cyan  (banners and section headers)
	const int COLOR_LABEL = 14;  // Yellow (field labels)
	const int COLOR_GOOD = 10;  // Green  (positive impact / success messages)
	const int COLOR_BAD = 12;  // Red    (negative impact / error messages)
	const int COLOR_NEUTRAL = 13;  // Magenta (neutral impact)

public:
	// ============================================================
	// Week 05: setColor
	// Purpose: Change the console text color.
	// ============================================================
	void setColor(int color)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	}

	//NEW PA8 Mach - Public Color Helper functions
	void setHeaderColor()
	{
		setColor(COLOR_HEADER);
	}

	void setDefaultColor()
	{
		setColor(COLOR_DEFAULT);
	}

	void setLabelColor()
	{
		setColor(COLOR_LABEL);
	}

	void setGoodColor()
	{
		setColor(COLOR_GOOD);
	}

	void setBadColor()
	{
		setColor(COLOR_BAD);
	}

	void setNeutralColor()
	{
		setColor(COLOR_NEUTRAL);
	}

	// ============================================================
	// Week 05: displayReport
	// Purpose: Print the single-session analytics report to console.
	// ============================================================
	// PA7 Mach - Refactored for struct
	void displayReport(const SessionStorage& session,
		double avgMinutesPerGame,
		double onCourtRating,
		double offCourtRating,
		double scoringContribution)
	{
		setHeaderColor();
		cout << "================================================" << endl;
		cout << "           Player Analytics Report              " << endl;
		cout << "================================================" << endl;
		setDefaultColor();

		cout << fixed << setprecision(1) << left;
		setLabelColor();  cout << setw(32) << "Player Name:";
		setDefaultColor(); cout << session.storedName << endl;

		setLabelColor();  cout << setw(32) << "Games Played:";
		setDefaultColor(); cout << session.storedGames << endl;

		setLabelColor();  cout << setw(32) << "Minutes Played:";
		setDefaultColor(); cout << session.storedMinutes << endl;

		setLabelColor();  cout << setw(32) << "Avg Minutes Per Game:";
		setDefaultColor(); cout << avgMinutesPerGame << endl;

		setLabelColor();  cout << setw(32) << "Points Per 100 Possessions:";
		setDefaultColor(); cout << session.storedPts100 << endl;

		setLabelColor();  cout << setw(32) << "True Shooting %:";
		setDefaultColor(); cout << session.storedTS << "%" << endl;

		setLabelColor();  cout << setw(32) << "On-Court Rating:";
		setDefaultColor(); cout << onCourtRating << endl;

		setLabelColor();  cout << setw(32) << "Off-Court Rating:";
		setDefaultColor(); cout << offCourtRating << endl;

		setLabelColor();  cout << setw(32) << "On/Off Differential:";
		setDefaultColor(); cout << session.storedOnOff << endl;

		setLabelColor();  cout << setw(32) << "Scoring Contribution Index:";
		setDefaultColor(); cout << scoringContribution << endl;

		cout << endl;
		setHeaderColor();
		cout << "------------------------------------------------" << endl;
		setLabelColor();  cout << setw(32) << "Player Role:";
		setDefaultColor(); cout << session.storedRole << endl;

		setLabelColor();  cout << setw(32) << "Impact Classification:";
		setDefaultColor(); cout << session.storedImpact << endl;

		setLabelColor();  cout << setw(32) << "Experience Level:";
		setDefaultColor(); cout << session.storedExperience << endl;

		setHeaderColor();
		cout << "------------------------------------------------" << endl;
		setDefaultColor();
		cout << endl;

		// Impact sentence with color
		// PA7 Mach - Refactored for struct
		if (session.storedOnOff > 0)
		{
			setGoodColor();
			cout << session.storedName
				<< " has a POSITIVE impact: the team performs better with them on court." << endl;
		}
		else if (session.storedOnOff < 0)
		{
			setBadColor();
			cout << session.storedName
				<< " has a NEGATIVE impact: the team performs better when they sit." << endl;
		}
		else
		{
			setNeutralColor();
			cout << session.storedName
				<< " has a NEUTRAL impact on overall team performance." << endl;
		}

		setDefaultColor();
		cout << endl;
		setHeaderColor();
		cout << "================================================" << endl;
		setDefaultColor();
		cout << endl;

	}

	// ============================================================
	// Week 05: saveReport
	// Purpose: Write all stored sessions to report.txt.
	// ============================================================

	// PA7 Mach - Refactoring for struct
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

		// PA7 Mach - refactored for struct
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
	// Week 05: displayBanner
	// Purpose: Print the welcome banner (moved out of main).
	// ============================================================
	void displayBanner()
	{
		setHeaderColor();
		cout << "================================================" << endl;
		cout << "       Welcome to Basketball Analytics Pro      " << endl;
		cout << "       Your Advanced Player Evaluation Tool     " << endl;
		cout << "================================================" << endl;
		setDefaultColor();
		cout << endl;
		cout << "This program analyzes a player's performance" << endl;
		cout << "using advanced basketball statistics." << endl;
		cout << endl;
	}
};

// ============================================================
// NEW PA8 Mach - Addition of classes
// ============================================================
class BasketballManager
{
private:
	// Constants (carried from Week 03/04)
	// NEW PA8 - moved to make global during refactor for classes may move local later.
	// NEw After Refactor moved to the manager
	static constexpr double ELITE_TS_PCT = 58.0;
	static constexpr double STARTER_MINUTES = 28.0;
	static constexpr double HIGH_USAGE_POINTS = 20.0;
	static constexpr double POSITIVE_IMPACT = 5.0;
	static constexpr int    VETERAN_GAMES = 50;
	static constexpr int    MAX_SESSIONS = 5;

	SessionStorage sessions[MAX_SESSIONS];
	int sessionCount;
	StatisticsCalculator calculator;
	ReportManager reports;

public:
	BasketballManager()
	{
		sessionCount = 0;
	}
	//NEW PA8 Mach - adding this to the manager to call the display.
	void displayBanner()
	{
		reports.displayBanner();
	}

	// ============================================================
	// Week 05: getValidInt
	// Purpose: Prompt for an int and loop until valid input >= min.
	// ============================================================
	// PA7 Mach - Fixed buffer issue again.
	int getValidInt(const string& prompt, int minVal)
	{
		int value;

		cout << prompt;
		cin >> value;

		while (cin.fail() || value < minVal || cin.peek() != '\n')
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			reports.setBadColor();
			cout << "  [!] Invalid input. Enter a value >= "
				<< minVal << ": ";
			reports.setDefaultColor();

			cin >> value;
		}

		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return value;
	}

	// ============================================================
	// Week 05: getValidDouble
	// Purpose: Prompt for a double and loop until value is in range.
	// ============================================================
	// PA7 Mach - Fixed buffer issue
	double getValidDouble(const string& prompt, double minVal, double maxVal)
	{
		double value;

		cout << prompt;
		cin >> value;

		while (cin.fail() || value < minVal || value > maxVal || cin.peek() != '\n')
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			reports.setBadColor();
			cout << "  [!] Invalid input. Enter a value between "
				<< minVal << " and " << maxVal << ": ";
			reports.setDefaultColor();

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
			reports.setBadColor();
			cout << "  [!] Name cannot be empty. Try again: ";
			reports.setDefaultColor();
			getline(cin, value);
		}
		return value;
	}

	void displayMenu()
	{
		reports.setHeaderColor();
		cout << "What would you like to do?" << endl;
		reports.setDefaultColor();
		cout << "  1 - Add Player Session" << endl;
		cout << "  2 - View Session Report" << endl;
		cout << "  3 - Get Player Recommendation" << endl;
		cout << "  4 - Exit" << endl;
		cout << endl;
		cout << "Enter your choice (1-4): ";
	}

	void addSession()
	{
		// Variables
		string playerName;
		int    gamesPlayed;
		double pointsPer100;
		double minutesPlayed;
		double trueShootingPct;
		double onCourtRating;
		double offCourtRating;

		reports.setHeaderColor();
		cout << "[ Mode: Add Player Session ]" << endl;
		reports.setDefaultColor();
		cout << endl;
		//PA6 Mach - This is array size validation.
		if (sessionCount >= MAX_SESSIONS)
		{
			reports.setBadColor();
			cout << "  [!] Session limit reached (" << MAX_SESSIONS << " max). View or exit." << endl;
			reports.setDefaultColor();
			cout << endl;
			return;
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
			calculator.computeStats(gamesPlayed, minutesPlayed, pointsPer100,
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
			// PA7 Mach - Refactored for struct
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
			// PA7 Mach - Refactored for struct
			reports.displayReport(sessions[sessionCount],
				avgMinutesPerGame,
				onCourtRating,
				offCourtRating,
				scoringContribution);

			sessionCount++;

			reports.setGoodColor();
			cout << "  [+] Session saved! (" << sessionCount << "/" << MAX_SESSIONS << " slots used)" << endl;
			reports.setDefaultColor();
			cout << endl;
		}
	}

	void viewSession()
	{
		reports.setHeaderColor();
		cout << "[ Mode: View Session Report ]" << endl;
		reports.setDefaultColor();
		cout << endl;

		if (sessionCount == 0)
		{
			reports.setBadColor();
			cout << "  [!] No sessions recorded yet. Add a session first." << endl;
			reports.setDefaultColor();
			cout << endl;
			return;
		}

		// Console table (carried from Week 04)
		reports.setHeaderColor();
		cout << "=================================================" << endl;
		cout << "           All Sessions - Summary Report          " << endl;
		cout << "=================================================" << endl;
		reports.setLabelColor();
		cout << left
			<< setw(20) << "Player"
			<< setw(8) << "Games"
			<< setw(12) << "Pts/100"
			<< setw(8) << "TS%"
			<< setw(10) << "On/Off"
			<< setw(22) << "Role"
			<< endl;
		reports.setDefaultColor();
		cout << string(80, '-') << endl;

		// PA7 Mach - Refactored for struct
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

		// Week 05: call saveReport function instead of inline file writing
		// PA7 updated call for struct
		reports.saveReport(sessions, sessionCount);

		reports.setGoodColor();
		cout << "  Report saved to report.txt" << endl;
		reports.setDefaultColor();
		cout << endl;
	}

	void showRecommendations()
	{
		reports.setHeaderColor();
		cout << "[ Mode: Get Player Recommendation ]" << endl;
		reports.setDefaultColor();
		cout << endl;

		if (sessionCount == 0)
		{
			reports.setBadColor();
			cout << "  [!] No sessions recorded yet. Add a session first." << endl;
			reports.setDefaultColor();
			cout << endl;
			return;
		}

		reports.setHeaderColor();
		cout << "=================================================" << endl;
		cout << "           Player Recommendations                 " << endl;
		cout << "=================================================" << endl;
		reports.setDefaultColor();

		// PA7 Mach - Refactored for struct
		for (int i = 0; i < sessionCount; i++)
		{
			cout << endl;
			reports.setLabelColor();  cout << "Player:     ";
			reports.setDefaultColor(); cout << sessions[i].storedName << endl;
			reports.setLabelColor();  cout << "Role:       ";
			reports.setDefaultColor(); cout << sessions[i].storedRole << endl;
			reports.setLabelColor();  cout << "Impact:     ";
			reports.setDefaultColor(); cout << sessions[i].storedImpact << endl;
			reports.setLabelColor();  cout << "Experience: ";
			reports.setDefaultColor(); cout << sessions[i].storedExperience << endl;
			cout << "------------------------------------------------" << endl;
		}

		cout << endl;
	}

	//NEW PA8 Mach - Adding some color control here to access it from main
	void setBadColor()
	{
		reports.setBadColor();
	}

	void setDefaultColor()
	{
		reports.setDefaultColor();
	}

	void setGoodColor()
	{
		reports.setGoodColor();
	}
};

// ============================================================
// main
// ============================================================
int main()
{
	const int    MENU_EXIT = 4;
	int    menuChoice;

	BasketballManager manager;
	manager.displayBanner();

	// LOOP 1: do-while — Main menu loop (carried from Week 04)
	do
	{
		// Week 05: call displayMenu function instead of inline code
		manager.displayMenu();
		cin >> menuChoice;

		// LOOP 2: while — Menu input validation (carried from Week 04)
		// PA7 Mach - Fixed buffer issue.
		while (cin.fail() || menuChoice < 1 || menuChoice > 4 || cin.peek() != '\n')
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			manager.setBadColor();
			cout << "  [!] Invalid choice. Please enter 1-4: ";
			manager.setDefaultColor();

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

			manager.addSession();

			break;

			// --------------------------------------------------------
			// CASE 2: View Session Report
			// LOOP 3: for — iterates over all stored sessions (Week 04)
			// --------------------------------------------------------
		case 2:

			manager.viewSession();

			break;

			// --------------------------------------------------------
			// CASE 3: Get Player Recommendation (carried from Week 03/04)
			// --------------------------------------------------------
		case 3:

			manager.showRecommendations();

			break;

			// --------------------------------------------------------
			// CASE 4: Exit
			// --------------------------------------------------------
		case 4:
			manager.setGoodColor();
			cout << "Thanks for using Basketball Analytics Pro. Good game!" << endl;
			manager.setDefaultColor();
			cout << endl;
			break;

		} // end switch

	} while (menuChoice != MENU_EXIT); // LOOP 1 ends

	return 0;

} // end main