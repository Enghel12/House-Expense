#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Define the maximum number of elements in the map
#define MAX_MAP_SIZE 100

//this function clears the buffer by deleting the characters that could not be stored by scanf_s
void clearInputBuffer() {
    int c = 0;

    /*getting chars from the buffer using getchar command and storing them to the c
    if the character is equal to '\n' it means that we reached the end of the buffer*/
    while(c = getchar() != '\n' && c != EOF) {}
}

//this function checks if the user tried to store characters to an integer
int checkIntegerInput() {
    int currentInput = 0;
    bool inputStored = false;
    
    //if the input did not store successfully, execute this loop again
    while (!inputStored) {
    
        //if the input return is not 1, the user tried to enter characters
        if (scanf_s("%d", &currentInput) != 1) {
            system("cls");
            printf("Error, you cannot store characters to an integer, try again\n");
            currentInput = 0;
            clearInputBuffer(); //clearing the buffer
        }
        else {
            system("cls");
            inputStored = true;
        }
        
    }
  
    return currentInput;
}

void convertStringToInt(const char* wattString, int* firstVal, int* secondVal) {
    bool firstFinished = false;
    
    //traversing the string that our pointer is pointing to
    for (int i = 0; i < strlen(wattString); i++) {

        //if the current charatcer from string is a digit, convert it to an int and store it
        if (!firstFinished && wattString[i] >= '0' && wattString[i] <= '9') {
            *firstVal = *firstVal * 10 + (wattString[i] - '0');
        }
        else if (firstFinished && wattString[i] >= '0' && wattString[i] <= '9') {
            *secondVal = *secondVal * 10 + (wattString[i] - '0');
        }
        
        //if we finished storing the first value from our string, now we will store the next
        if (wattString[i] == '-')
            firstFinished = true;
    }
}

//this is the blueprint for the first map
struct map1 {
    char key[20] = "";
    int val = 0;
};

//and here is the second map
struct map2 {
    char key[20] = "";
    char val[20] = "";
};

//creating two arrays of type map1 and 2 with a maximum size of 100 elements
map1 deviceOccurences[MAX_MAP_SIZE];
map2 deviceConsumption[MAX_MAP_SIZE];

//this function initializez our maps
void initializeMap1() {
    for (int i = 0; i < MAX_MAP_SIZE; i++)
        deviceOccurences[i].key[0] = '\0';
}
void initializeMap2() {
    for (int i = 0; i < MAX_MAP_SIZE; i++)
        deviceConsumption[i].key[0] = '\0';
}

//these functions are used to insert two values to our custom maps
void insertPairToMap1(const char* getDeviceName, int occurences) {
    for (int i = 0; i < MAX_MAP_SIZE; i++) {
        if (deviceOccurences[i].key[0] == '\0') {
            //here we store to our first map each device that the user has
            strncpy(deviceOccurences[i].key, getDeviceName, sizeof(deviceOccurences[i].key)-1);

            //and here we store to our map how many times each device appears
            deviceOccurences[i].val = occurences;
            return;
        }
    }
}
void insertPairToMap2(const char* getDeviceName, const char* getDeviceConsumption) {
    for (int i = 0; i < MAX_MAP_SIZE; i++) {
        if (deviceConsumption[i].key[0] == '\0') {
            //here we give values to the keys and values of our second map
            strncpy(deviceConsumption[i].key, getDeviceName, sizeof(deviceConsumption[i].key) - 1);
            strncpy(deviceConsumption[i].val, getDeviceConsumption, sizeof(deviceConsumption[i].key) - 1);
            return;
        }
    }
}

struct electricity {
    int hourlyConsumption = 0;
    int dailyConsumption = 0;
    int monthlyConsumption = 0;

    int dailyMoneySpent = 0;
    int monthlyMoneySpent = 0;

    //here is an array of const char pointers which contains all the available electronic devices
    const char* availableElectronicDevices[5][10] = {
        "Refrigerators","Ovens","Dishwashers","Washing Machines","Hair Dryers","Coffee Makers","Toasters",
        "Vaccum Cleaners","Irons","TVs","Computers","Monitors","GameConsoles",
        "Lightning Bulbs","Desk lamps",
        "Air Conditioners","Electronic heaters","Ceiling Fans",
        "Phone Chargers","Laptop Chargers","Tablet Chargers"
    };

    //this function prints the content of all the files that contain info about electricity
    void printFiles(char fileName[20], int rowsNum) {
        FILE* openCurrentFile = fopen(fileName, "r");
        char lines[100] = "";
        int currentRow = 0;
        
        while (currentRow < rowsNum) {
            fgets(lines, 100, openCurrentFile);
            printf("%s\n", lines);
            currentRow++;
        }
        fclose(openCurrentFile);
    }

    void firstFile() {
        char fileName[20] = "ElectricityInfo.txt";
        int rowsNumber = 8;
        
        //calling this function to print to the console the content of the First File
        printFiles(fileName, rowsNumber);
        int user_choice = checkIntegerInput();
        system("cls");

    }

    /*this function will store the user input to two maps, first map for device occurences
    second mao for the consumption in wats of each electronic device*/
    void storeUserInput() {
        int deviceNumber = 0;
        char wattConsumption[20];
        char newDeviceName[20];

        //initializing our maps
        initializeMap1();
        initializeMap2();
        char fileName[] = "infoAboutUserInput.txt";
        int rowsNumber = 9;
        printFiles(fileName, rowsNumber);
        
        int user_input = checkIntegerInput();
        system("cls");


        /*Traversing our array and storing the user input to the maps*/
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 10; j++) {
                if (availableElectronicDevices[i][j] != NULL) {
                    printf("Enter how many %s you have:\n", availableElectronicDevices[i][j]);
                    deviceNumber = checkIntegerInput();

                    //here we insert to the first map a pair
                    insertPairToMap1(availableElectronicDevices[i][j], deviceNumber);
                    system("cls");
                    clearInputBuffer();

                    //if the user does not have a device, skip this if statement
                    if (deviceNumber != 0) {
                        printf("What is the consumption in wats:\n");
                        fgets(wattConsumption, sizeof(wattConsumption), stdin);
                        insertPairToMap2(availableElectronicDevices[i][j], wattConsumption);
                        system("cls");
                    }
                    else {
                        strcpy(wattConsumption, "0\n");
                        insertPairToMap2(availableElectronicDevices[i][j], wattConsumption);
                    }

                }
            }
        }

        //here we let the user store any other device that he posesses
        printf("Everything is stored successfully\n");
        printf("Would you like to add any other device that was not on the list? 1.Yes 2.No \n");
        user_input = checkIntegerInput();
        system("cls");
        int countNewDevices = 0;

        if (user_input == 1) {
            
            printf("First you need to enter the device name\n");
            printf("For example, if you have a jacuzzi that consumes electricity\n");
            printf("Just type:jacuzzi\n");

            //in this for loop we add new elements to our maps
            for (int i = 21; i < MAX_MAP_SIZE; i++) {
                clearInputBuffer();

                //obtaining the new device's name and storing it to newDeviceName
                printf("Enter your new device here: \n");
                fgets(newDeviceName, 20, stdin);
                system("cls");
                countNewDevices++;
              
                //here we store the occurences of that device to deviceNumber
                printf("Now enter how many %s you have: ", newDeviceName);
                deviceNumber = checkIntegerInput();
                system("cls");
                clearInputBuffer();
                //adding to our first map the new device and its occurences
                insertPairToMap1(newDeviceName, deviceNumber);

                //here we store the consumption in wats of that device to wattConsumption
                printf("And the consumption in wats of that device: \n");
                fgets(wattConsumption, sizeof(wattConsumption), stdin);
               
                //now we store to the second map that new device and its consumption in wats
                insertPairToMap2(newDeviceName, wattConsumption);
                system("cls");
                printf("Device stored!\n");

                printf("Add another device ? 1.Yes 2.No\n");
                user_input = checkIntegerInput();
                if (user_input == 2)
                    break;
            }
            
        }
        char map1Value[10];

        FILE* storeMaps = fopen("userDevicesAndConsumptionHere.txt", "w");
        //here we store the first map to our file which contains all the user's devices
        for (int i = 0; i < 21 + countNewDevices; i++) {

            //using fprintf to write to a file
            fprintf(storeMaps, "\n");
            fprintf(storeMaps, deviceOccurences[i].key);
            fprintf(storeMaps, ":");

            //converting the value(integer) from the first map to a string
            sprintf(map1Value, "%d", deviceOccurences[i].val);
            fprintf(storeMaps, map1Value);
        }
        fprintf(storeMaps, "\n\nAnd Consumption: \n");

        //storing the second map which contains the consumption in wats of each device
        for (int j = 0; j < 21 + countNewDevices; j++) {
            fprintf(storeMaps, "\n");
            fprintf(storeMaps, deviceConsumption[j].key);
            fprintf(storeMaps, ":");
            fprintf(storeMaps, deviceConsumption[j].val);
        }

        calculateConsumption(countNewDevices);
    }

    //this function calculates which devices consume the most electricity
    void calculateTopFive(struct map2 consumption[MAX_MAP_SIZE], int countNewDevices) {
        
        int sum1 = 0, sum2 = 0;
        int firstVal = 0, secondVal = 0;

        /*using selection sort to traverse our map and sort in the electronic devices
        in ascending order, based on the consumption in wats of each device*/
        for (int i = 0; i < 21 + countNewDevices-1; i++) {
            int currentIndex = i;
            for (int nextIndex = i + 1; nextIndex < 21 + countNewDevices; nextIndex++) {

                //calling this function to convert character digits to integers
                convertStringToInt(consumption[currentIndex].val, &firstVal, &secondVal);
                
                //storing here the consumption in wats(highest value) of the first element of map
                sum1 = firstVal + secondVal;
                firstVal = 0, secondVal = 0;

                convertStringToInt(consumption[nextIndex].val, &firstVal, &secondVal);

                //and here the consumption in wats(highest value) of the second element of map
                sum2 = firstVal + secondVal;
                firstVal = 0, secondVal = 0;

                /*if we find a new element in map which has a higher consumption in wats
                store the index of that element here*/
                if (sum1 < sum2)
                    currentIndex = nextIndex;        
            }
            char key[20];
            char value[20];

            //swaping the elements of our map(their keys and values)
            strcpy(key, consumption[currentIndex].key);
            strcpy(value, consumption[currentIndex].val);
            strcpy(consumption[currentIndex].key, consumption[i].key);
            strcpy(consumption[currentIndex].val, consumption[i].val);
            strcpy(consumption[i].key, key);
            strcpy(consumption[i].val, value);
        }
        
        printf("Here are the top 5 devices that consume the most electricity in your house:\n");
        //printing the first 5 elements that have the most consumption in wats
        for (int i = 0; i < 5; i++)
            printf("%s: %s\n", consumption[i].key, consumption[i].val);
        
        printf("If you want to save money, you need to focus on these 5 devices and start ");
        printf("using them less\n");
        printf("Press anything to continue: \n");
        int user_input = checkIntegerInput();
        system("cls");
    }

    //and this funcion calculates how much money the user spends in a day and a month
    void calculateMoney() {

        //calculating the costs based on this formula: 1kw = 0,60 lei
        dailyMoneySpent = (dailyConsumption / 1000) * 0.60;
        monthlyMoneySpent = dailyMoneySpent * 30;

        printf("Here is how much money you spent on electricity in a day: \n");
        printf("%d lei\n", dailyMoneySpent);
        printf("And in a month: \n");
        printf("%d lei", monthlyMoneySpent);

        printf("Press anything to continue: \n");
        int user_input = checkIntegerInput();
        system("cls");
        printf("Thank you for using house expenses! \n");
    }

    //this function calculates the total consumption of all of the user's electronic devices
    void calculateConsumption(int countNewDevices) {
        system("cls");
        
        char fileName[] = "printAllPowerCases.txt";
        int rowsNumber = 18;
        int averageVal = 0;
        printFiles(fileName, rowsNumber);
        int user_choice = checkIntegerInput();
        system("cls");

        //if the user picked a wrong number, execute this while loop
        while (user_choice > 3 || user_choice < 1) {
            printf("Wrong choice! Enter again or press 0 close the program\n");
            clearInputBuffer();
            user_choice = checkIntegerInput();

            //if the user entered 0, close the program
            if (user_choice == 0)
                exit(0);


        }
        int firstWattValue = 0, secondWattValue = 0;

        for (int i = 0; i < 21 + countNewDevices; i++) {
            
            //here we calculate the average, worst and best case for the power consumption
            switch (user_choice) {
            case 1:
                convertStringToInt(deviceConsumption[i].val, &firstWattValue, &secondWattValue);
                //getting the average of the two watt values
                averageVal = (firstWattValue + secondWattValue) / 2;

                //storing the total consumption(during an hour) of all electronic devices to this variable
                hourlyConsumption += deviceOccurences[i].val * averageVal;

                //reinitializing our variables
                firstWattValue = 0, secondWattValue = 0;

                break;

            case 2:
                convertStringToInt(deviceConsumption[i].val, &firstWattValue, &secondWattValue);
                hourlyConsumption += deviceOccurences[i].val * secondWattValue;
                firstWattValue = 0, secondWattValue = 0;
                break;

            case 3:
                convertStringToInt(deviceConsumption[i].val, &firstWattValue, &secondWattValue);
                hourlyConsumption += deviceOccurences[i].val * firstWattValue;
                firstWattValue = 0, secondWattValue = 0;
                break;
            default: break;
            }
        }

        //calculating the total consumption in a day and a month
        dailyConsumption = hourlyConsumption * 24;
        monthlyConsumption = dailyConsumption * 30;

        printf("Total electricity consumption in wats in:  \n");
        printf("An hour:%d  \n", hourlyConsumption);
        printf("A day:%d  \n", dailyConsumption);
        printf("A month:%d  \n", monthlyConsumption);

        printf("Total electricity consumption in kilowwats in:  \n");
        float hourlyConsumptionFloat = 0;
        float dailyConsumptionFloat = 0;
        float monthlyConsumptionFloat = 0;

        hourlyConsumptionFloat = hourlyConsumption;
        dailyConsumptionFloat = dailyConsumption;
        monthlyConsumptionFloat = monthlyConsumption;

        //converting the consumption in wats to kilowats
        hourlyConsumptionFloat = hourlyConsumptionFloat / 1000;
        dailyConsumptionFloat = dailyConsumptionFloat / 1000;
        monthlyConsumptionFloat = monthlyConsumptionFloat / 1000;

        printf("An hour:%f  \n", hourlyConsumptionFloat);
        printf("A day:%f \n", dailyConsumptionFloat);
        printf("A month:%f  \n", monthlyConsumptionFloat);

        printf("Press any number to see the list with all of your electronic devices: \n");
        user_choice = checkIntegerInput();

        printf("\n\nHere are all the devices of your house and their consumption: \n");
        
        //printing all of the user's deivces to the console by accessing our map again
        for (int i = 0; i < 21 + countNewDevices; i++)
            printf("%s : %s\n", deviceConsumption[i].key, deviceConsumption[i].val);
        
        printf("All these devices were included when you calculated the total consumption\n");

        printf("Press any number to continue: \n");
        user_choice = checkIntegerInput();

        //printing the top 5 devices that consume the most electricity
        calculateTopFive(deviceConsumption, countNewDevices);

        //using this func to print how much money the user spends in a day and a month on electricity
        calculateMoney();

    }
    
};
struct water {

    //here are the variables that will be used to calculate the water consumption
    int dailyWaterConsumption = 0, monthlyWaterConsumption = 0;
    double moneySpentInADay = 0, moneySpentInAMonth = 0;
    char highestUtilityConsumption[20];

    //1.Variables for bathroom
    int showerNumber = 0, showerLength = 0, flowRate = 0, bathsPerMonth = 0, bathFillUpTime = 0;
    int toiletFlushes = 0, toiletLitersUsed = 0, faucetUses = 0, faucetTime = 0;
    int washByHand = 0, waterTimeForDishes = 0, dishWasherUsedInADay = 0;
    int laundryLoadsInADay = 0;

    //in this array of pointers, we store the addreses of all the variables that we will use
    int* storeUserChoices[20] = {
        &showerNumber, &showerLength, &flowRate, &bathsPerMonth, &bathFillUpTime,
        &toiletFlushes, &toiletLitersUsed, &faucetUses, &faucetTime, &washByHand,
        &waterTimeForDishes, &dishWasherUsedInADay
    };

    //more information regarding the water consumption
    void moreWaterInfo() {
        printf("Welcome to water section\n\n");
        printf("Here you see the following: \n\n");
        printf("1.How much water you consume in your house in : a day, a month\n\n");
        printf("2.What is the house utility that consumes the most water\n\n");
        printf("3.How much money you spend on water in a day and a month\n\n");
        printf("Press 1 to begin or 0 to exit\n\n");

        int user_input = checkIntegerInput();
        system("cls");

        if (user_input == 0)
            exit(0);

        if (user_input != 1) {
            printf("Wrong input, try again later!\n");
            exit(0);
        }
    }

    //this function calculates the money spent on water in a day and a month
    void calculateMoneySpent(int dailyConsumption) {
        /*using cubic meters to calculate the consumption, 1 cubic meter = 1000 liters
        the price of a cubic meter is around 5 lei*/

        //converting an integer to double in c using type casting
        double newDailyConsumption = (double)(dailyConsumption);

        //converting the liters to cubic meters
        double cubicMetersDaily = newDailyConsumption / 1000;
        double cubicMetersMonthly = 0;

        //multiplying the cubic meters with 8 because 1 cb costs 5 lei
        moneySpentInADay = cubicMetersDaily * 8;
        moneySpentInAMonth = moneySpentInADay * 30;

        //printing the values
        printf("Money spent in a day: %g lei\n", moneySpentInADay);
        printf("Money spent in a month: %g lei", moneySpentInAMonth);

        FILE* accessWaterConsumptionFile = fopen("StoreWaterConsumption.txt", "a");

        //using fseek to reach the end of our file
        fseek(accessWaterConsumptionFile, 0, SEEK_END);

        //after reaching the end of file, we move down two more rows
        fprintf(accessWaterConsumptionFile, "\n\n");
        
        char moneySpentInADayString[20];
        char moneySpentInAMonthString[20];

        //converting from int to string using sprintf and storing to a file using fprintf
        sprintf(moneySpentInADayString, "%f", moneySpentInADay);
        fprintf(accessWaterConsumptionFile, "Total money spent in a day: ");
        fprintf(accessWaterConsumptionFile, moneySpentInADayString);
        fprintf(accessWaterConsumptionFile, "\n");

        sprintf(moneySpentInAMonthString, "%f", moneySpentInAMonth);
        fprintf(accessWaterConsumptionFile, "Total money spent in a month: ");
        fprintf(accessWaterConsumptionFile, moneySpentInAMonthString);

        fclose(accessWaterConsumptionFile);
    }


    void calculateWaterConsumption() {

        FILE* printMessages = fopen("PrintWaterQuestions.txt", "r");
        int rows = 1;
        int position = -1;
        char firstLine[200] = "", secondLine[200] = "";
        int* storeAnswers = nullptr;

        while (rows < 28) {
            //if the row is odd, it will be stored in the firstLine variable
            if (rows % 2 != 0)
                fgets(firstLine, 100, printMessages);
            else {

                fgets(secondLine, 100, printMessages);  //if not, store it to the second one

                printf("%s", firstLine); //and print each pair of two rows
                printf("%s", secondLine);

                int user_choice = 0;
                if (rows != 10) {
                    position++;
                }
                user_choice = checkIntegerInput(); //here we take user input

                //using this pointer to store the user choices to the variables of our array
                storeAnswers = storeUserChoices[position];

                //if my pointer points to nothing valid, exit the while loop
                if (storeAnswers == nullptr) {
                    //storing the user input to the las tvariables of array directly
                    dishWasherUsedInADay = user_choice;
                    break;
                }
                if(rows != 10)
                *storeAnswers = user_choice;
                clearInputBuffer(); //clearing buffer
            }
            rows++; //keep updating rows at each iteration

        }
        system("cls");
        //including one more question regarding the laundry
        printf("How many loads of laundry are done in a day? \n");
        int user_choice = checkIntegerInput();

        //storing the user input to the last variable that we need
        laundryLoadsInADay = user_choice;

        printf("All answers are stored successfully! 1.Continue 2.Exit program\n");
        user_choice = checkIntegerInput();
        system("cls");

        //if user input is not 1, stop the program from executting
        if (user_choice == 2) {
            printf("Exitting..\n");
            exit(0);
        }
        else if(user_choice != 1) {
            printf("Wrong choice, try again later!\n");
            exit(0);
        }
        system("cls");
        int totalShowerConsumptionDaily = 0,  totalToiletConsumptionDaily = 0;
        int totalFaucetConsumptionDaily = 0, totalWaterUsedForDishesDaily = 0, totalLaundryConsumptionDaily = 0;

        /*1. We calculate what is the total water consumption of each house utility
        in liters in a day and a month*/

        //for shower
        if (flowRate == 1) {
            int consumptionOfJustAShower = showerLength * 9; //assuming 9 liters for one minute
            totalShowerConsumptionDaily = showerNumber * consumptionOfJustAShower;
        }
        else if (flowRate == 2) {
            
            //if flowrate is 2 we calculate the consumption based on an old shower model
            int consumptionOfJustAShower = showerLength * 20; //assuming 20 liters for one minute
            totalShowerConsumptionDaily = showerNumber * consumptionOfJustAShower;
        }

        //calculating the consumption of a single bath
        int consumptionOfASingleBath = bathFillUpTime * 9;  //9 litters in a minute
        
        /*if the user does not take baths, then this variable: bathsPerMonth is 0 meaning
        that the consumptionOfASingleBath is also 0 liters*/
        if (bathsPerMonth == 0)
            consumptionOfASingleBath = 0;

        //calculating how much water is used throughout a month for baths
        int totalBathConsumptionMonthly = consumptionOfASingleBath * bathsPerMonth;
        
        //for toilet
        totalToiletConsumptionDaily = toiletFlushes * toiletLitersUsed;

        //for faucet
        int consumptionOfAFaucetUse = faucetTime * 5; //assuming a faucet consumes 5 liters
        totalFaucetConsumptionDaily = consumptionOfAFaucetUse * faucetUses;


        //for dishes: if the user washes the dishes by hand, calculate like this
        if (washByHand == 1) {
            totalWaterUsedForDishesDaily = waterTimeForDishes * 6; //assuming 6 liters in a minute
        }
        else if (washByHand == 2) {
            //calculate like this if the user uses the dishwasher instead
            totalWaterUsedForDishesDaily = dishWasherUsedInADay * 15; //asuming 15 liters per use
        }
        
        
        //for laundry
        totalLaundryConsumptionDaily = laundryLoadsInADay * 75; //assuming 75 liters per load

        //2.calculating the total water used in a day and in a month

        //adding the consumption of each utility to the total
        dailyWaterConsumption = totalShowerConsumptionDaily + totalToiletConsumptionDaily +
            totalFaucetConsumptionDaily + totalWaterUsedForDishesDaily +
            totalLaundryConsumptionDaily; //we don't include the water that the bath consumes

        monthlyWaterConsumption = 30 * dailyWaterConsumption;

        //here we include the water used by baths to get the total water consumption in a month
        monthlyWaterConsumption += totalBathConsumptionMonthly;

        printf("Water used in a day in liters: %d\n\n", dailyWaterConsumption);
        printf("Water used in a month in liters: %d\n\n", monthlyWaterConsumption);
        printf("Water used by each house utility in a day: \n\n");
        
        //storing the consumption of each utility to another array
        int totalConsumptionArray[5] = {
            totalShowerConsumptionDaily, totalToiletConsumptionDaily,
            totalFaucetConsumptionDaily, totalWaterUsedForDishesDaily,
            totalLaundryConsumptionDaily
        };

        //creating an array of const char pointers that point to c strings
        const char* utilityName[5] = {
            "Shower consumption: ", "Toilet: ", "Faucet: ",
            "Dishes: ", "Laundry: "
        };


        //creating a new file to store the data to it
        FILE* accessFile = fopen("StoreWaterConsumption.txt", "w");
        

        //using fprintf to write to our file and sprintf to convers an integer to a string
        char firstConsumption[20], secondConsumption[20];
        fprintf(accessFile, "Total Water Consumption in a day: ");
        sprintf(firstConsumption, "%d", dailyWaterConsumption);
        fprintf(accessFile, firstConsumption);
        fprintf(accessFile, "\n");

        fprintf(accessFile, "Total Water Consumption in a month: ");
        sprintf(secondConsumption, "%d", monthlyWaterConsumption);
        fprintf(accessFile, secondConsumption);
        fprintf(accessFile, "\n");
        fprintf(accessFile, "\n");
        fprintf(accessFile, "Individual consume: \n");
        fprintf(accessFile, "\n");

        int currPosition=0;
        int highestConsumptionUtility=0;

        //printing the strings form UtilityName and the total consumption of each utility
        for (int i = 0; i < 5; i++) {
            
            //finding where in array is stored the utility that uses the most water in a day
            if (highestConsumptionUtility < totalConsumptionArray[i]) {
                highestConsumptionUtility = totalConsumptionArray[i];
                currPosition = i;  //getting its pos
            }

            //printing to the console the water consumption of each utility
            printf("%s %d liters/day\n\n", utilityName[i], totalConsumptionArray[i]);

            char temp[20];
            //using type casting to convert an integer to a string
            sprintf(temp, "%d", totalConsumptionArray[i]);

            //using printf to write to a file, and add at each line two strings
            fprintf(accessFile, utilityName[i]);
            fprintf(accessFile, temp);
            fprintf(accessFile, "\n");
        }
        fclose(accessFile);

        printf("Press anything to continue: \n");
        user_choice = checkIntegerInput();

        calculateMoneySpent(dailyWaterConsumption);

        printf("\nPress any number to continue: \n");
        int new_user_choice = checkIntegerInput();
        system("cls");
        
        //printing the utility that consumes the most water
        printf("Here is the utility that cosumes the most water in a month: \n");


        /*if the utility that consumes most water in a month manages to consume even more 
        water than the consumption of baths in a month, then print that utility*/
        if (totalConsumptionArray[currPosition] * 30 > totalBathConsumptionMonthly)
            printf("%s : %d liters\n\n", utilityName[currPosition], highestConsumptionUtility);
        else
            printf("Baths: %d liters\n\n", totalBathConsumptionMonthly);
            //if not, print the water that is consumed by baths

        printf("If you want to save more money, you should limit the use of this utility\n");
        printf("Press any number to exit: \n");
        int last_user_input = checkIntegerInput();
        system("cls");

        printf("Thank you for using house expenses! \n");
        exit(0);
    }

};

//this function explains to the user what the program does
void explainProgram() {

    //opening a file(notepad) by using a file pointer
    FILE* openCurrentFile = fopen("printFirstMessages.txt", "r");
    char documentLine[70] = "";
    int documentRows = 0;

    printf("                                        =========================\n");
    printf("                                        WELCOME TO HOUSE EXPENSES\n");
    printf("                                        =========================\n\n\n\n\n");
 
    while (documentRows < 7) {
        fgets(documentLine, 70, openCurrentFile);
        printf("%s\n", documentLine);  //here we print each line of the notepad
        documentRows++;
    }

    //closing the file
    fclose(openCurrentFile);
    printf("Your choice:\n");
}

//this function is used to select the user's desired utility based on the input
void selectUtility(int* user_choice) {
    //here we initialize 3 objects of our structs
    electricity e;
    water w;

    switch (*user_choice) {
    case 1:
        e.firstFile();
        e.storeUserInput();
        break;
    case 2:
        w.moreWaterInfo();
        w.calculateWaterConsumption();
        break;
        
    default:
        printf("Wrong choice, try again later! \n");
        break;
    }
}

int main()
{

    explainProgram();
    int user_choice = checkIntegerInput();
    selectUtility(&user_choice);
    
    
    return 0;
}
