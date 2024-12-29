#include <iostream>

int points = 0;
int calculatedDays;
int seasonDuration = 0;
int monthDays[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
bool februaryChecked = 0;
int startMonth, startDay, endMonth, endDay;
int loginStreak, loginPoints;
int easyTasks, mediumTasks, specialTasks, challenges, challengesPoints;
int easyTaskTime, mediumTaskTime, specialTaskTime, challengeTime;
int easyTasksTotalTime, mediumTasksTotalTime, specialTasksTotalTime, challengesTotalTime;
int taskChangeDays, taskChanged, taskChangeSL = 0, taskChangeGE = 0;
int battlePass;
int purchasedLevels, allPurchasedLevels;
int goldenEaglesSpendOnBattlePass = 0, goldenEaglesSpendOnLevels = 0;
int again;


void line() {
	std::cout << "- - - - - - - - - - - - - - - - - - - -\n";
}

int inputCheck(int min, int max) {
	int tempInput;
	while (!(std::cin >> tempInput) || min > tempInput || tempInput > max) {
		std::cin.clear();
		while (std::cin.get() != '\n') {
			continue;
		}
		std::cout << "Enter a number in range (" << min << "-" << max << "): ";
	}
	return tempInput;
}

int inputMonthCheck(int x) {
	int tempInput2;
	while (!(std::cin >> tempInput2) || tempInput2 == x) {
		std::cin.clear();
		while (std::cin.get() != '\n') {
			continue;
		}
		std::cout << "Enter the season end month correctly: ";
	}
	return tempInput2;
}

void welcome() {
	std::cout << "Welcome to the War Thunder battle pass console planner!\n";
	std::cout << "Version: 1.0\n";
	std::cout << "Creator: KAT_Editor\n";
	line();
}

void daysCalculation() {
	std::cout << "SEASON DURATION\n";
	std::cout << "Do you know the duration of the season in days? (0 - No, 1 - Yes): ";
	calculatedDays = inputCheck(0, 1);
	if (calculatedDays == 1) {
		std::cout << "Enter the season duration (77-92): ";
		seasonDuration = inputCheck(77, 92);
	}
	else {
		std::cout << "1 - January,   2 - February, 3 - March,     4 - April,\n";
		std::cout << "5 - May,       6 - June,     7 - July,      8 - August,\n";
		std::cout << "9 - September, 10- October,  11- November,  12- December\n";
		std::cout << "Enter the season start month (1-12): ";
		startMonth = inputCheck(1, 12);
		if (startMonth == 2) {
			std::cout << "Does this February have 28 or 29 days?: ";
			februaryChecked = 1;
			monthDays[1] = inputCheck(28, 29);
		}
		std::cout << "Enter the season start day (1-" << monthDays[startMonth - 1] << "): ";
		startDay = inputCheck(1, monthDays[startMonth - 1]);
		std::cout << "Enter the season end month (1-12): ";
		endMonth = inputMonthCheck(startMonth);
		if (februaryChecked == 0 && (startMonth == 1 || endMonth == 2 || (endMonth >= 2 && startMonth <= 12 && startMonth > endMonth))) {
			std::cout << "Does season February have 28 or 29 days?: ";
			monthDays[1] = inputCheck(28, 29);
		}
		std::cout << "Enter the season end day (1-" << monthDays[endMonth-1] << "): ";
		endDay = inputCheck(1, monthDays[endMonth - 1]);
		if (startMonth < endMonth) {
			for (int i = (startMonth - 1); i < (endMonth); i++) {
				seasonDuration += monthDays[i];
			}
		}
		else {
			for (int i = (startMonth - 1); i < 12; i++) {
				seasonDuration += monthDays[i];
			}
			for (int i = 0; i < (endMonth); i++) {
				seasonDuration += monthDays[i];
			}
		}
		seasonDuration = seasonDuration - (startDay - 1) - monthDays[endMonth - 1] + endDay - 1;
		std::cout << "Season duration = " << seasonDuration << " days\n";
		if (seasonDuration < 77 || seasonDuration > 92) {
			std::cout << "WARNING! The duration of the season is not within (77-92)\n";
		}
	}
	line();
}

void loginStreakCalculation() {
	std::cout << "LOGIN STREAK\n";
	std::cout << "Streak | Points\n";
	std::cout << "1-21   | 1\n";
	std::cout << "22-42  | 2\n";
	std::cout << "43-63  | 3\n";
	std::cout << "64-77  | 4\n";
	std::cout << "78-92  | 5\n";
	std::cout << "How many days in a row do you plan to login during the current season? (1-" << seasonDuration << "): ";
	loginStreak = inputCheck(1, seasonDuration);
	if (loginStreak < 22) {
		points = loginStreak;
	}
	else if (loginStreak < 43) {
		points = 21 + ((loginStreak - 21) * 2);
	}
	else if (loginStreak < 64) {
		points = 21 + 42 + ((loginStreak - 42) * 3);
	}
	else if (loginStreak < 78) {
		points = 21 + 42 + 63 + ((loginStreak - 63) * 4);
	}
	else {
		points = 21 + 42 + 63 + 56 + ((loginStreak - 77) * 5);
	}
	loginPoints = points;
	std::cout << "Points gain = " << points << std::endl;
	line();
}

void easyTasksCalculation() {
	std::cout << "EASY TASKS (x*2)\n";
	std::cout << "How many easy tasks do you plan to complete? (0-" << loginStreak << "): ";
	easyTasks = inputCheck(0, loginStreak);
	if (easyTasks > 0) {
		points += easyTasks * 2;
		std::cout << "How much minutes on average do you plan to spend on an easy task? (1-720): ";
		easyTaskTime = inputCheck(1, 720);
		easyTasksTotalTime = easyTasks * easyTaskTime;
		std::cout << "Points gain = " << easyTasks * 2 << ", points total = " << points << ", time spend = " << easyTasksTotalTime / 60 << " hours " << easyTasksTotalTime % 60 << " minutes\n";
	}
	line();
}

void mediumTasksCalculation() {
	std::cout << "MEDIUM TASKS (x*3)\n";
	if (easyTasks > 0) {
		std::cout << "How many medium tasks do you plan to complete? (0-" << easyTasks << "): ";
		mediumTasks = inputCheck(0, easyTasks);
		if (mediumTasks > 0) {
			points += mediumTasks * 3;
			std::cout << "How much minutes on average do you plan to spend on a medium task? (1-720): ";
			mediumTaskTime = inputCheck(1, 720);
			mediumTasksTotalTime = mediumTasks * mediumTaskTime;
			std::cout << "Points gain = " << mediumTasks * 3 << ", points total = " << points << ", time spend = " << mediumTasksTotalTime / 60 << " hours " << mediumTasksTotalTime % 60 << " minutes\n";
		}
	}
	else {
		std::cout << "To complete a medium task, you need to complete an easy task\n";
	}
	line();
}

void specialTasksCalculation() {
	std::cout << "SPECIAL TASKS (x*5)\n";
	if (mediumTasks > 0) {
		std::cout << "How many special tasks do you plan to complete? (0-" << mediumTasks << "): ";
		specialTasks = inputCheck(0, mediumTasks);
		if (specialTasks > 0) {
			points += specialTasks * 5;
			std::cout << "How many extra minutes (after previous tasks) on average do you plan to spend on a special task? (0-1440): ";
			specialTaskTime = inputCheck(0, 1440);
			specialTasksTotalTime = specialTasks * specialTaskTime;
			std::cout << "Points gain = " << specialTasks * 5 << ", points total = " << points << ", time spend = " << specialTasksTotalTime / 60 << " hours " << specialTasksTotalTime % 60 << " minutes\n";
		}
	}
	else {
		std::cout << "To complete a special task, you need to complete an medium task\n";
	}
	line();
}

void changeTaksCalculation() {
	std::cout << "TASK CHANGE\n";
	std::cout << "Changes | Price\n";
	std::cout << "1       | 1000 Silver Lions\n";
	std::cout << "2       | 5000 Silver Lions\n";
	std::cout << "3-5     | 10000 Silver Lions\n";
	std::cout << "6-7     | 50000 Silver Lions\n";
	std::cout << "8       | 5 Golden Eagles\n";
	std::cout << ">9      | 10 Golden Eeagles\n";
	std::cout << "How many days do you plan to change tasks? (0-" << loginStreak << "): ";
	taskChangeDays = inputCheck(0, loginStreak);
	if (taskChangeDays > 0) {
		std::cout << "How many times per day on average do you plan to change tasks? (1-20): ";
		taskChanged = inputCheck(1, 20);
		if (taskChanged == 1) {
			taskChangeSL = 1000 * taskChangeDays;
		}
		else if (taskChanged == 2) {
			taskChangeSL = (1000 + 5000) * taskChangeDays;
		}
		else if (taskChanged < 6) {
			taskChangeSL = (1000 + 5000 + (taskChanged - 2) * 10000) * taskChangeDays;
		}
		else if (taskChanged < 8) {
			taskChangeSL = (1000 + 5000 + 30000 + (taskChanged - 5) * 50000) * taskChangeDays;
		}
		else {
			taskChangeSL = (1000 + 5000 + 30000 + 100000) * taskChangeDays;
		}
		if (taskChanged == 8) {
			taskChangeGE = 5 * taskChangeDays;
		}
		else if (taskChanged > 8) {
			taskChangeGE = (5 + (taskChanged - 8) * 10) * taskChangeDays;
		}
		std::cout << "Silver Lions spend = " << taskChangeSL << ", Golden Eagles spend = " << taskChangeGE << std::endl;
	}
	line();
}

void challengesTasksCalculation() {
	std::cout << "CHALLENGES (x * 30, +45 if you finished all 14)\n";
	std::cout << "How many challenges do you plan to complete? (0-14): ";
	challenges = inputCheck(0, 14);
	if (challenges > 0) {
		challengesPoints += challenges * 30;
		if (challenges == 14) {
			challengesPoints += 45;
		}
		points += challengesPoints;
		std::cout << "How many extra minutes (after previous tasks) on average do you plan to spend on a challenge? (0-1440): ";
		challengeTime = inputCheck(0, 1440);
		challengesTotalTime = challenges * challengeTime;
		std::cout << "Points gain = " << challengesPoints << ", points total = " << points << ", time spend = " << challengesTotalTime / 60 << " hours " << challengesTotalTime % 60 << " minutes\n";
	}
	line();
}

void battlePassCheck() {
	std::cout << "BATTLE PASS\n";
	std::cout << "Battle pass = 2000 Golden Eagles, Improved Battle Pass (+15 levels) = 2500 Golden Eagles\n";
	allPurchasedLevels = 0;
	std::cout << "Do you planning to buy a Battle Pass? (0 - No, 1 - Yes, 2 - Improved Battle Pass): ";
	battlePass = inputCheck(0, 2);
	if (battlePass > 0) {
		goldenEaglesSpendOnBattlePass += 2000;
		if (battlePass == 2) {
			goldenEaglesSpendOnBattlePass += 500;
			points += 150;
			allPurchasedLevels = 15;
		}
		std::cout << "Points gain = " << (battlePass / 2 * 150) << ", points total = " << points << ", Golden Eagles spend = " << goldenEaglesSpendOnBattlePass << std::endl;
	}
	line();
}

void levelsPurchase () {
	std::cout << "PURCHASING LEVELS\n";
	std::cout << "Purchased levels | Level cost\n";
	std::cout << "1-15             | 75\n";
	std::cout << "16-25            | 125\n";
	std::cout << "26-35            | 175\n";
	std::cout << ">36              | 250\n";
	std::cout << "(including levels from an improved Battle Pass)\n";
	if (battlePass == 0) {
		std::cout << "You cant buy levels without a Battle Pass\n";
	}
	else {
		std::cout << "How many levels do you plan to buy? (0-200): ";
		purchasedLevels = inputCheck(0, 200);
		points += purchasedLevels * 10;
		allPurchasedLevels += purchasedLevels;
		if (allPurchasedLevels < 16) {
			goldenEaglesSpendOnLevels = allPurchasedLevels * 75;
		}
		else if (allPurchasedLevels < 26) {
			goldenEaglesSpendOnLevels = (15 * 75) + ((loginStreak - 15) * 125);
		}
		else if (allPurchasedLevels < 36) {
			goldenEaglesSpendOnLevels = (15 * 75) + (10 * 125) + ((loginStreak - 25) * 175);
		}
		else {
			goldenEaglesSpendOnLevels = (15 * 75) + (10 * 125) + (10 * 175) + ((allPurchasedLevels - 35) * 250);
		}
		if (battlePass == 2) {
			goldenEaglesSpendOnLevels -= (15 * 75);
		}
		std::cout << "Points gain = " << purchasedLevels * 10 << ", points total = " << points << ", Golden Eagles spend = " << goldenEaglesSpendOnLevels << std::endl;
	}
	line();
}

void results () {
	std::cout << "FINAL RESULTS\n";
	std::cout << std::endl;
	std::cout << "Sorce                | Points gain\n";
	std::cout << "Logins               | " << loginPoints << std::endl;
	std::cout << "Easy tasks           | " << easyTasks * 2 << std::endl;
	std::cout << "Medium tasks         | " << mediumTasks * 3 << std::endl;
	std::cout << "Special tasks        | " << specialTasks * 5 << std::endl;
	std::cout << "Challenges           | " << challengesPoints << std::endl;
	std::cout << "Improved Battle Pass | " << (battlePass / 2 * 150) << std::endl;
	std::cout << "Purchased levels     | " << purchasedLevels * 10 << std::endl;
	std::cout << "TOTAL POINTS = " << points << " (" << points / 10 << " Battle Pass level)\n";
	std::cout << std::endl;
	std::cout << "Sorce                | Time spend\n";
	std::cout << "Easy tasks           | " << easyTasksTotalTime / 60 << " hours " << easyTasksTotalTime % 60 << " minutes\n";
	std::cout << "Medium tasks         | " << mediumTasksTotalTime / 60 << " hours " << mediumTasksTotalTime  % 60 << " minutes\n";
	std::cout << "Special tasks        | " << specialTasksTotalTime / 60 << " hours " << specialTasksTotalTime % 60 << " minutes\n";
	std::cout << "Challenges           | " << challengesTotalTime / 60 << " hours " << challengesTotalTime % 60 << " minutes\n";
	std::cout << "TOTAL TIME = " << (easyTasksTotalTime + mediumTasksTotalTime + specialTasksTotalTime + challengesTotalTime) / 60 << " hours " << (easyTaskTime + mediumTaskTime + specialTaskTime + challengeTime) % 60 << " minutes\n";
	std::cout << std::endl;
	std::cout << "Sorce                | Currency spend\n";
	std::cout << "Task change          | " << taskChangeSL << " Silver Lions, " << taskChangeGE << " Golden Eagles\n";
	std::cout << "Battle Pass          | " << goldenEaglesSpendOnBattlePass << " Golden Eagles\n";
	std::cout << "Purchased levels     | " << goldenEaglesSpendOnLevels << " Golden Eagles \n";
	std::cout << "TOTAL CURRENCY SPEND = " << taskChangeSL << " Silver Lions, " << goldenEaglesSpendOnLevels + goldenEaglesSpendOnBattlePass + taskChangeGE << " Golden Eagles\n";
	line();
}

int main() {
	welcome();
	daysCalculation();
	while (1) {
		loginStreakCalculation();
		easyTasksCalculation();
		mediumTasksCalculation();
		specialTasksCalculation();
		changeTaksCalculation();
		challengesTasksCalculation();
		battlePassCheck();
		levelsPurchase();
		results();
		std::cout << "Calculate again? (0 - No, 1 - Yes): ";
		again = inputCheck(0, 1);
		if (again == 0) {
			break;
		}
		points = 0;
		taskChangeSL = 0;
		taskChangeGE = 0;
		goldenEaglesSpendOnBattlePass = 0;
		goldenEaglesSpendOnLevels = 0;
		line();
	}
}