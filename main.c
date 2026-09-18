#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PATIENTS 100
#define TOTAL_WARDS 4
#define TOTAL_SPECIALTIES 4
#define BEDS_PER_WARD 20

int totalPatients = 0;

int bedOccupancy[TOTAL_WARDS][BEDS_PER_WARD];
int assignedBeds[MAX_PATIENTS];

char patientNames[MAX_PATIENTS][50];
int patientIDs[MAX_PATIENTS];
int patientAges[MAX_PATIENTS];

int urgencyLevels[MAX_PATIENTS];
int specialties[MAX_PATIENTS];
int assignedWards[MAX_PATIENTS];

int admissionDays[MAX_PATIENTS];

float finalBills[MAX_PATIENTS];
float waitingTimes[MAX_PATIENTS];
float emergencySurcharges[MAX_PATIENTS];
float wardCosts[MAX_PATIENTS];
float grossTotals[MAX_PATIENTS];
float discounts[MAX_PATIENTS];
float finalPayableAmounts[MAX_PATIENTS];

char specialtyNames[TOTAL_SPECIALTIES][30];
float consultationFees[TOTAL_SPECIALTIES];
int specialtyTimes[TOTAL_SPECIALTIES];
int dailyPatientCaps[TOTAL_SPECIALTIES];
int specialtyQueueCounts[TOTAL_SPECIALTIES] = {0};

char wardNames[TOTAL_WARDS][30];
float wardDailyRates[TOTAL_WARDS];
int wardCapacities[TOTAL_WARDS];

void displayTitle();
void displayMenu();

void initializeBeds();
void initializeSpecialties();
void initializeWards();

void registerPatient();
void viewPatients();
void searchPatient();
void viewBedStatus();

int assignBed(int wardID);

float calculateEmergencySurcharge(float baseFee, int urgencyLevel);
float calculateWardCost(int wardID, int admissionDays);
float calculateGrossTotal(float baseFee,
                          float emergencySurcharge,
                          float wardCost);
float calculateAgeDiscount(float grossTotal, int age);
float calculateFinalPayable(float grossTotal, float discount);

void displayPatientBill(int patientIndex);
void displayPatientsByPriority();
void generatePerformanceReport();

int main(){
        int choice ;
        initializeBeds();
        initializeSpecialties();
        initializeWards();

        do
     {
        displayTitle();
        displayMenu();

        scanf("%d",&choice);

        switch(choice)
    {
    case 1:
        registerPatient();
        break;

    case 2:
        viewPatients();
        break;

    case 3:
        searchPatient();
        break;

    case 4:
        viewBedStatus();
        break;

    case 5:
        displayPatientsByPriority();
        break;

    case 6:
        generatePerformanceReport();
        break;

    case 7:
        printf("\nThank you for using Smart Hospital Admission System.\n");
        break;

    default:
        printf("\nInvalid Choice! Please try again.\n");
    } } while(choice != 7);


        return 0 ;
                  }
   void displayTitle()
 {
    printf("===========================================\n");
    printf(" SMART HOSPITAL ADMISSION SYSTEM\n");
    printf("-------------------------------------------\n");
 }
   void displayMenu()
  {
    printf("1. Register Patient\n");
    printf("2. View Patients\n");
    printf("3. Search Patient\n");
    printf("4. View Bed Status\n");
    printf("5. View Patients by Priority\n");
    printf("6. Generate Performance Reports\n");
    printf("7. Exit\n");

    printf("\nEnter your choice: ");
  }

  void initializeBeds()
   {
    for(int i = 0; i < TOTAL_WARDS; i++)
    {
        for(int j = 0; j < BEDS_PER_WARD; j++)
        {
            bedOccupancy[i][j] = 0;
        }
    }
   }

   int assignBed(int wardID)
   {
    int wardIndex = wardID - 1;

    for(int i = 0; i < wardCapacities[wardIndex]; i++)
     {
        if(bedOccupancy[wardIndex][i] == 0)
        {
            bedOccupancy[wardIndex][i] = 1;
            return i + 1;
        }
     }

    return -1;
    }

  void initializeSpecialties()
  {
    strcpy(specialtyNames[0], "General Practice");
    consultationFees[0] = 1500.00;
    specialtyTimes[0] = 15;
    dailyPatientCaps[0] = 30;

    strcpy(specialtyNames[1], "Paediatrics");
    consultationFees[1] = 2500.00;
    specialtyTimes[1] = 20;
    dailyPatientCaps[1] = 20;

    strcpy(specialtyNames[2], "Cardiology");
    consultationFees[2] = 4500.00;
    specialtyTimes[2] = 30;
    dailyPatientCaps[2] = 12;

    strcpy(specialtyNames[3], "Neurology");
    consultationFees[3] = 5000.00;
    specialtyTimes[3] = 30;
    dailyPatientCaps[3] = 10;
  }

   void initializeWards()
  {
    strcpy(wardNames[0], "General Ward");
    wardDailyRates[0] = 3000.00;
    wardCapacities[0] = 20;

    strcpy(wardNames[1], "Paediatric Ward");
    wardDailyRates[1] = 6000.00;
    wardCapacities[1] = 10;

    strcpy(wardNames[2], "Surgical Ward");
    wardDailyRates[2] = 12000.00;
    wardCapacities[2] = 10;

    strcpy(wardNames[3], "ICU");
    wardDailyRates[3] = 25000.00;
    wardCapacities[3] = 5;
  }

  void registerPatient()
  {
      if (totalPatients >= MAX_PATIENTS)
      {
          printf("\nHospital is full! Cannot register more patients.\n");
          return ;
      }
       patientIDs[totalPatients] = 1001 + totalPatients;

       printf("Enter Patient Name : ");
       scanf(" %49[^\n]", patientNames[totalPatients]);

       printf("Enter Patient Age : ");
       scanf("%d", &patientAges[totalPatients]);

       do
     {
        printf("\nEnter Urgency Level:\n");
        printf("1. Normal\n");
        printf("2. Urgent\n");
        printf("3. Critical\n");
        printf("Enter your choice (1-3): ");

        scanf("%d", &urgencyLevels[totalPatients]);

      if(urgencyLevels[totalPatients] < 1 ||
         urgencyLevels[totalPatients] > 3)
      {
         printf("Invalid urgency level! Please enter 1-3.\n");
       }

      } while(urgencyLevels[totalPatients] < 1 ||
         urgencyLevels[totalPatients] > 3);

        printf("\nAvailable Specialties:\n");

        for(int i = 0; i < TOTAL_SPECIALTIES; i++)
        {
          printf("%d. %s - LKR %.2f\n",
                    i + 1,
                  specialtyNames[i],
                  consultationFees[i]);
          }

        do
          {
            printf("Enter Specialty ID (1-4): ");
            scanf("%d", &specialties[totalPatients]);

           if(specialties[totalPatients] < 1 ||
              specialties[totalPatients] > TOTAL_SPECIALTIES)
           {
                printf("Invalid Specialty ID! Please enter 1-4.\n");
            }

        } while(specialties[totalPatients] < 1 ||
                specialties[totalPatients] > TOTAL_SPECIALTIES);

        int specialtyIndex = specialties[totalPatients] - 1;

         if(specialtyQueueCounts[specialtyIndex] >= dailyPatientCaps[specialtyIndex])
          {
             printf("\nDaily patient capacity reached for %s.\n",
             specialtyNames[specialtyIndex]);

                      return;
           }

           waitingTimes[totalPatients] =
           specialtyQueueCounts[specialtyIndex] *
           specialtyTimes[specialtyIndex];

           specialtyQueueCounts[specialtyIndex]++;

          emergencySurcharges[totalPatients] =
          calculateEmergencySurcharge(
          consultationFees[specialtyIndex],
          urgencyLevels[totalPatients] );

     int admitted;

           printf("\nIs the patient admitted to a ward? (1-Yes, 0-No): ");
           scanf("%d", &admitted);

     if(admitted == 1)
        {
         do
           {
            printf("Enter Ward ID (1-4): ");
            scanf("%d", &assignedWards[totalPatients]);

           if(assignedWards[totalPatients] < 1 ||
              assignedWards[totalPatients] > TOTAL_WARDS)
         {
            printf("Invalid Ward ID! Please enter 1-4.\n");
           }

      } while(assignedWards[totalPatients] < 1 ||
              assignedWards[totalPatients] > TOTAL_WARDS);


     do
       {
        printf("Enter Number of Days Admitted: ");
        scanf("%d", &admissionDays[totalPatients]);

        if(admissionDays[totalPatients] <= 0)
         {
            printf("Invalid number of days! Please enter a positive value.\n");
         }

       } while(admissionDays[totalPatients] <= 0);


        assignedBeds[totalPatients] =
        assignBed(assignedWards[totalPatients]);

    if(assignedBeds[totalPatients] == -1)
     {
        printf("No available bed in this ward.\n");
        assignedBeds[totalPatients] = 0;
      }

       wardCosts[totalPatients] =
            calculateWardCost(
            assignedWards[totalPatients],
            admissionDays[totalPatients]);

        }
   else
    {
      assignedWards[totalPatients] = 0;
      admissionDays[totalPatients] = 0;
      assignedBeds[totalPatients] = 0;
      wardCosts[totalPatients] = 0.0;
     }

     grossTotals[totalPatients] =
        calculateGrossTotal(
        consultationFees[specialtyIndex],
        emergencySurcharges[totalPatients],
        wardCosts[totalPatients] ) ;

     discounts[totalPatients] =
        calculateAgeDiscount(
        grossTotals[totalPatients],
        patientAges[totalPatients] );

     finalPayableAmounts[totalPatients] =
        calculateFinalPayable(
        grossTotals[totalPatients],
        discounts[totalPatients] );

         printf("\nPatient Registered Successfully!\n");
         printf("Estimated Waiting Time: %.2f minutes\n",
                  waitingTimes[totalPatients]);
         printf("Emergency Surcharge: LKR %.2f\n",
                 emergencySurcharges[totalPatients]);
         printf("Ward Stay Cost: LKR %.2f\n",
                  wardCosts[totalPatients]);
         printf("Gross Total: LKR %.2f\n", grossTotals[totalPatients]);

         printf("Age Subsidy Discount: LKR %.2f\n",
                 discounts[totalPatients]);
         printf("Final Payable Amount: LKR %.2f\n",
                finalPayableAmounts[totalPatients]);

            displayPatientBill(totalPatients);

         totalPatients++;
   }

   void viewPatients()
 {
    if (totalPatients == 0)
    {
        printf("\nNo patients registered yet.\n");
        return;
    }

    printf("\n===== Patient List =====\n");

    for (int i = 0; i < totalPatients; i++)
    {
       printf("\nPatient ID   : %d", patientIDs[i]);
       printf("\nPatient Name : %s", patientNames[i]);
       printf("\nPatient Age  : %d", patientAges[i]);

       printf("\nUrgency Level : ");

       if (urgencyLevels[i] == 1)
         {
          printf("Level 1 (Normal)");
          }
      else if (urgencyLevels[i] == 2)
        {
          printf("Level 2 (Urgent)");
         }
       else
        {
         printf("Level 3 (Critical)");
         }

      printf("\nAssigned Bed : %d\n", assignedBeds[i]);
     }
   }
   void displayPatientsByPriority()
 {
    if(totalPatients == 0)
    {
        printf("\nNo patients registered yet.\n");
        return;
    }

    int priorityOrder[MAX_PATIENTS];

    // Store original patient indices
    for(int i = 0; i < totalPatients; i++)
    {
        priorityOrder[i] = i;
    }

    // Bubble Sort by urgency level (3 -> 2 -> 1)
    for(int i = 0; i < totalPatients - 1; i++)
    {
        for(int j = 0; j < totalPatients - i - 1; j++)
        {
            if(urgencyLevels[priorityOrder[j]] <
               urgencyLevels[priorityOrder[j + 1]])
            {
                int temp = priorityOrder[j];
                priorityOrder[j] = priorityOrder[j + 1];
                priorityOrder[j + 1] = temp;
            }
        }
    }

    printf("\n===== PATIENT PRIORITY LIST =====\n");

    for(int i = 0; i < totalPatients; i++)
    {
        int index = priorityOrder[i];

        printf("\nPriority %d\n", i + 1);
        printf("Patient ID   : PAT-%d\n", patientIDs[index]);
        printf("Patient Name : %s\n", patientNames[index]);
        printf("Urgency Level: %d\n", urgencyLevels[index]);
    }
 }
  void searchPatient()
 {
    int searchID;
    int found = 0;

    printf("\nEnter Patient ID to search : ");
    scanf("%d", &searchID);

    for(int i = 0; i < totalPatients; i++)
    {
        if(patientIDs[i] == searchID)
        {
            printf("\nPatient Found!\n");

             printf("\nPatient ID   : %d", patientIDs[i]);
             printf("\nPatient Name : %s", patientNames[i]);
             printf("\nPatient Age  : %d", patientAges[i]);
             printf("\nUrgency Level : ");

           if (urgencyLevels[i] == 1)
            {
                printf("Level 1 (Normal)");
             }
           else if (urgencyLevels[i] == 2)
           {
                printf("Level 2 (Urgent)");
             }
           else
           {
               printf("Level 3 (Critical)");
            }
             printf("\nAssigned Bed : %d\n", assignedBeds[i]);

            found = 1;
            break;
        }
    }

    if(found == 0)
    {
        printf("\nPatient not found!\n");
    }
 }

 void viewBedStatus()
  {
    printf("\n===== Bed Status =====\n");

    for(int i = 0; i < TOTAL_WARDS; i++)
    {
        printf("\nWard %d - %s\n", i + 1, wardNames[i]);

        for(int j = 0; j < wardCapacities[i]; j++)
        {
            printf("Bed %d : ", j + 1);

            if(bedOccupancy[i][j] == 0)
            {
                printf("Available\n");
            }
            else
            {
                printf("Occupied\n");
            }
        }
    }
  }

  float calculateEmergencySurcharge(float baseFee, int urgencyLevel)
  {
     if(urgencyLevel == 2)
       {
         return baseFee * 0.20;
         }
    else if(urgencyLevel == 3)
      {
         return baseFee * 0.50;
        }
    else
     {
        return 0.0;
     }
   }

   float calculateWardCost(int wardID, int admissionDays)
   {
     if(wardID == 0 || admissionDays == 0)
     {
        return 0.0;
      }

        return admissionDays * wardDailyRates[wardID - 1];
     }

     float calculateGrossTotal(float baseFee,
                          float emergencySurcharge,
                          float wardCost)
         {
           return baseFee + emergencySurcharge + wardCost;
              }

    float calculateAgeDiscount(float grossTotal, int age)
   {
      if(age < 5 || age > 65)
       {
        return grossTotal * 0.15;
         }
     else
      {
        return 0.0;
        }
    }

    float calculateFinalPayable(float grossTotal, float discount)
      {
        return grossTotal - discount;
      }

      void displayPatientBill(int patientIndex)
 {
    int specialtyIndex = specialties[patientIndex] - 1;

    printf("\n====================================================\n");
    printf("       SMART HOSPITAL ADMISSION & BILL\n");
    printf("====================================================\n");

    printf("\nPatient ID : PAT-%d\n", patientIDs[patientIndex]);
    printf("Patient Name : %s\n", patientNames[patientIndex]);
    printf("Age : %d Years", patientAges[patientIndex]);

    if(patientAges[patientIndex] < 5 ||
       patientAges[patientIndex] > 65)
    {
        printf(" (15%% Subsidy Eligible)\n");
    }
    else
    {
        printf("\n");
    }

    printf("Specialty : %s\n",
           specialtyNames[specialtyIndex]);

    if(assignedWards[patientIndex] != 0)
    {
        printf("Assigned Ward : %s (Bed #%02d)\n",
               wardNames[assignedWards[patientIndex] - 1],
               assignedBeds[patientIndex]);
    }
    else
    {
        printf("Assigned Ward : Outpatient / OPD\n");
    }

    printf("Urgency Level : ");

    if(urgencyLevels[patientIndex] == 1)
    {
        printf("Level 1 (Normal)\n");
    }
    else if(urgencyLevels[patientIndex] == 2)
    {
        printf("Level 2 (Urgent)\n");
    }
    else
    {
        printf("Level 3 (Critical)\n");
    }

    printf("----------------------------------------------------\n");

    printf("Base Consultation Fee : LKR %.2f\n",
           consultationFees[specialtyIndex]);

    printf("Emergency Surcharge : LKR %.2f\n",
           emergencySurcharges[patientIndex]);

    printf("Ward Stay Cost : LKR %.2f\n",
           wardCosts[patientIndex]);

    printf("----------------------------------------------------\n");

    printf("Gross Total Bill : LKR %.2f\n",
           grossTotals[patientIndex]);

    printf("Age Subsidy Discount : LKR -%.2f\n",
           discounts[patientIndex]);

    printf("----------------------------------------------------\n");

    printf("Final Payable Amount : LKR %.2f\n",
           finalPayableAmounts[patientIndex]);

    printf("Estimated Waiting Time : %.2f minutes\n",
           waitingTimes[patientIndex]);

    printf("====================================================\n");
 }

 void generatePerformanceReport()
 {
    int normalCount = 0;
    int urgentCount = 0;
    int criticalCount = 0;

    float totalRevenue = 0.0;
    float totalDiscounts = 0.0;

    for(int i = 0; i < totalPatients; i++)
    {
        if(urgencyLevels[i] == 1)
        {
            normalCount++;
        }
        else if(urgencyLevels[i] == 2)
        {
            urgentCount++;
        }
        else if(urgencyLevels[i] == 3)
        {
            criticalCount++;
        }
         totalRevenue += finalPayableAmounts[i];
         totalDiscounts += discounts[i];
     }
    printf("\nTotal Revenue Earned : LKR %.2f\n", totalRevenue);
    printf("Total Discounts Granted : LKR %.2f\n", totalDiscounts);

    printf("\n========================================\n");
    printf("       PERFORMANCE REPORT\n");
    printf("========================================\n");

    printf("\nTotal Patients Registered : %d\n", totalPatients);

    printf("\nPatients by Urgency Level:\n");
    printf("Level 3 (Critical) : %d\n", criticalCount);
    printf("Level 2 (Urgent)   : %d\n", urgentCount);
    printf("Level 1 (Normal)   : %d\n", normalCount);

    printf("========================================\n");

    printf("\nBed Occupancy Percentage:\n");

    for(int i = 0; i < TOTAL_WARDS; i++)
    {
       int occupiedBeds = 0;

      for(int j = 0; j < wardCapacities[i]; j++)
         {
            if(bedOccupancy[i][j] == 1)
           {
                occupiedBeds++;
             }
          }

    float occupancyPercentage =
                                ((float)occupiedBeds / wardCapacities[i]) * 100;

          printf("%s : %d/%d beds occupied (%.2f%%)\n",
           wardNames[i],
           occupiedBeds,
           wardCapacities[i],
           occupancyPercentage);
       }
    int highestPatientIndex = 0;

     if(totalPatients > 0)
      {
         for(int i = 1; i < totalPatients; i++)
           {
             if(finalPayableAmounts[i] >
                  finalPayableAmounts[highestPatientIndex])
             {
                   highestPatientIndex = i;
              }
           }

      printf("\nHighest-Paying Patient:\n");
      printf("Patient ID   : PAT-%d\n",
           patientIDs[highestPatientIndex]);
      printf("Patient Name : %s\n",
           patientNames[highestPatientIndex]);
      printf("Total Bill   : LKR %.2f\n",
              finalPayableAmounts[highestPatientIndex]);
     }
  }

