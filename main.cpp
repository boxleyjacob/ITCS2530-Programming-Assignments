#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <limits>

int main()
{
    //  Constants 
    const double ELITE_TS_THRESHOLD = 0.600;  // True shooting % considered elite
    const double STARTER_MINUTES_MIN = 28.0;   // Min avg minutes for a starter
    const double HIGH_USAGE_POINTS = 20.0;   // Points per 100 considered high usage
    const double ELITE_NET_RATING = 5.0;    // Net rating considered elite
    const int    VETERAN_GAMES = 50;     // Games threshold for veteran status

    // Welcome Banner
    std::cout << "========================================\n";
    std::cout << "   Basketball Analytics Tracker v3.0   \n";
    std::cout << "   ITCS 2530 - Jacob Boxley            \n";
    std::cout << "========================================\n\n";

    // Menu 
    std::cout << "Please select an option:\n";
    std::cout << "  1 - Add Player Session\n";
    std::cout << "  2 - View Weekly Report\n";
    std::cout << "  3 - Get Player Recommendation\n";
    std::cout << "Enter choice (1-3): ";

    int menuChoice = 0;
    std::cin >> menuChoice;

    // Validate menu input
    if (std::cin.fail() || menuChoice < 1 || menuChoice > 3)
    {
        std::cout << "\nInvalid menu choice. Exiting program.\n";
        return 1;
    }

    switch (menuChoice)
    {
    case 1:
        std::cout << "\n[ Add Player Session Selected ]\n\n";
        break;
    case 2:
        std::cout << "\n[ View Weekly Report Selected ]\n\n";
        break;
    case 3:
        std::cout << "\n[ Player Recommendation Selected ]\n\n";
        break;
    }

    // User Input 

    // Player name (string with spaces)
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::string playerName = "";
    std::cout << "Enter player name: ";
    std::getline(std::cin, playerName);

    // Games played (int)
    int gamesPlayed = 0;
    std::cout << "Enter number of games played: ";
    std::cin >> gamesPlayed;

    while (std::cin.fail() || gamesPlayed <= 0)
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Enter a positive number of games: ";
        std::cin >> gamesPlayed;
    }

    // Minutes played (double)
    double minutesPlayed = 0.0;
    std::cout << "Enter total minutes played: ";
    std::cin >> minutesPlayed;

    while (std::cin.fail() || minutesPlayed <= 0.0)
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Enter positive minutes played: ";
        std::cin >> minutesPlayed;
    }

    // Points per 100 possessions (double)
    double pointsPer100 = 0.0;
    std::cout << "Enter points per 100 possessions: ";
    std::cin >> pointsPer100;

    while (std::cin.fail() || pointsPer100 < 0.0)
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Enter a non-negative value: ";
        std::cin >> pointsPer100;
    }

    // True shooting percentage (double)
    double trueShootingPct = 0.0;
    std::cout << "Enter true shooting percentage (0.0 - 1.0): ";
    std::cin >> trueShootingPct;

    while (std::cin.fail() || trueShootingPct < 0.0 || trueShootingPct > 1.0)
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Enter a value between 0.0 and 1.0: ";
        std::cin >> trueShootingPct;
    }

    // On/off court ratings (double)
    double onCourtRating = 0.0;
    std::cout << "Enter on-court net rating: ";
    std::cin >> onCourtRating;

    while (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Enter on-court net rating: ";
        std::cin >> onCourtRating;
    }

    double offCourtRating = 0.0;
    std::cout << "Enter off-court net rating: ";
    std::cin >> offCourtRating;

    while (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid input. Enter off-court net rating: ";
        std::cin >> offCourtRating;
    }

    // Derived Values
    double avgMinutesPerGame = minutesPlayed / gamesPlayed;
    double netRatingImpact = onCourtRating - offCourtRating;

    // if/else Block 1: Shooting & Minutes Assessment 
    // Compound condition: player shoots elite AND plays starter minutes
    std::string performanceLabel = "";
    if (trueShootingPct >= ELITE_TS_THRESHOLD && avgMinutesPerGame >= STARTER_MINUTES_MIN)
    {
        performanceLabel = "Elite Starter";
    }
    else if (trueShootingPct >= ELITE_TS_THRESHOLD && avgMinutesPerGame < STARTER_MINUTES_MIN)
    {
        performanceLabel = "Efficient Reserve";
    }
    else if (trueShootingPct < ELITE_TS_THRESHOLD && avgMinutesPerGame >= STARTER_MINUTES_MIN)
    {
        performanceLabel = "High-Volume Starter";
    }
    else
    {
        performanceLabel = "Developmental Player";
    }

    // ─── if/else Block 2: Impact & Usage Assessment ───────────────
    // Compound condition: high net rating impact AND high scoring load
    std::string impactLabel = "";
    if (netRatingImpact >= ELITE_NET_RATING && pointsPer100 >= HIGH_USAGE_POINTS)
    {
        impactLabel = "Franchise Cornerstone";
    }
    else if (netRatingImpact >= ELITE_NET_RATING && pointsPer100 < HIGH_USAGE_POINTS)
    {
        impactLabel = "Glue Guy / Two-Way Player";
    }
    else if (netRatingImpact < ELITE_NET_RATING && pointsPer100 >= HIGH_USAGE_POINTS)
    {
        impactLabel = "Volume Scorer";
    }
    else
    {
        impactLabel = "Role Player";
    }

    // ─── if/else Block 3: Veteran Status
    std::string experienceLabel = "";
    if (gamesPlayed >= VETERAN_GAMES && netRatingImpact > 0.0)
    {
        experienceLabel = "Veteran Contributor";
    }
    else if (gamesPlayed >= VETERAN_GAMES && netRatingImpact <= 0.0)
    {
        experienceLabel = "Veteran - Needs Improvement";
    }
    else
    {
        experienceLabel = "Still Building Experience";
    }

    // Console Output
    std::cout << "\n";
    std::cout << "========================================\n";
    std::cout << "        BASKETBALL ANALYTICS REPORT     \n";
    std::cout << "========================================\n";
    std::cout << std::left << std::setw(28) << "Player:" << playerName << "\n";
    std::cout << std::left << std::setw(28) << "Games Played:" << gamesPlayed << "\n";
    std::cout << std::left << std::setw(28) << "Minutes Played:" << minutesPlayed << "\n";
    std::cout << std::fixed << std::setprecision(2);
    std::cout << std::left << std::setw(28) << "Avg Min/Game:" << avgMinutesPerGame << "\n";
    std::cout << std::left << std::setw(28) << "Points/100 Poss:" << pointsPer100 << "\n";
    std::cout << std::left << std::setw(28) << "True Shooting %:" << trueShootingPct << "\n";
    std::cout << std::left << std::setw(28) << "On-Court Rating:" << onCourtRating << "\n";
    std::cout << std::left << std::setw(28) << "Off-Court Rating:" << offCourtRating << "\n";
    std::cout << std::left << std::setw(28) << "Net Rating Impact:" << netRatingImpact << "\n";
    std::cout << "----------------------------------------\n";
    std::cout << std::left << std::setw(28) << "Performance Type:" << performanceLabel << "\n";
    std::cout << std::left << std::setw(28) << "Impact Role:" << impactLabel << "\n";
    std::cout << std::left << std::setw(28) << "Experience Status:" << experienceLabel << "\n";
    std::cout << "========================================\n";

    // File Output
    std::ofstream reportFile("report.txt");

    if (!reportFile)
    {
        std::cout << "\nError: Could not open report.txt for writing.\n";
        return 1;
    }

    reportFile << "========================================\n";
    reportFile << "        BASKETBALL ANALYTICS REPORT     \n";
    reportFile << "========================================\n";
    reportFile << std::left << std::setw(28) << "Player:" << playerName << "\n";
    reportFile << std::left << std::setw(28) << "Games Played:" << gamesPlayed << "\n";
    reportFile << std::left << std::setw(28) << "Minutes Played:" << minutesPlayed << "\n";
    reportFile << std::fixed << std::setprecision(2);
    reportFile << std::left << std::setw(28) << "Avg Min/Game:" << avgMinutesPerGame << "\n";
    reportFile << std::left << std::setw(28) << "Points/100 Poss:" << pointsPer100 << "\n";
    reportFile << std::left << std::setw(28) << "True Shooting %:" << trueShootingPct << "\n";
    reportFile << std::left << std::setw(28) << "On-Court Rating:" << onCourtRating << "\n";
    reportFile << std::left << std::setw(28) << "Off-Court Rating:" << offCourtRating << "\n";
    reportFile << std::left << std::setw(28) << "Net Rating Impact:" << netRatingImpact << "\n";
    reportFile << "----------------------------------------\n";
    reportFile << std::left << std::setw(28) << "Performance Type:" << performanceLabel << "\n";
    reportFile << std::left << std::setw(28) << "Impact Role:" << impactLabel << "\n";
    reportFile << std::left << std::setw(28) << "Experience Status:" << experienceLabel << "\n";
    reportFile << "========================================\n";

    reportFile.close();

    std::cout << "\nReport saved to report.txt\n";
    std::cout << "\nThank you for using Basketball Analytics Tracker!\n";

    return 0;
}
