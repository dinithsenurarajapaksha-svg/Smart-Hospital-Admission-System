# Smart Hospital Admission System

A modular, menu-driven hospital patient and resource allocation system developed in the C programming language for the CSC 1012 Introduction to Computer Programming assignment.

## Features

- Register hospital patients
- Automatically generate unique patient IDs
- Validate numeric user inputs
- Select medical specialties
- Calculate estimated waiting times
- Assign available beds to patients
- Track bed occupancy using a 2D array
- Calculate emergency surcharges
- Calculate ward admission costs
- Apply age-based subsidy discounts
- Generate detailed patient bills
- Search patients by patient ID
- Display patients in emergency-priority order
- Generate hospital performance reports
- Save permanent patient billing records
- Save and load bed occupancy across program runs

## Medical Specialties

| ID | Specialty | Base Fee | Average Time | Daily Capacity |
|---|---|---:|---:|---:|
| 1 | General Practice | LKR 1,500 | 15 minutes | 30 |
| 2 | Paediatrics | LKR 2,500 | 20 minutes | 20 |
| 3 | Cardiology | LKR 4,500 | 30 minutes | 12 |
| 4 | Neurology | LKR 5,000 | 30 minutes | 10 |

## Hospital Wards

| ID | Ward | Daily Rate | Capacity |
|---|---|---:|---:|
| 1 | General Ward | LKR 3,000 | 20 |
| 2 | Paediatric Ward | LKR 6,000 | 10 |
| 3 | Surgical Ward | LKR 12,000 | 10 |
| 4 | ICU | LKR 25,000 | 5 |

## Billing Calculations

The final bill includes:

- Base consultation fee
- Emergency surcharge
- Ward stay cost
- Age subsidy discount

Patients below 5 years or above 65 years receive a 15% discount on the gross bill.

## File Handling

The system uses:

- `patient_records.txt` to append permanent patient billing records
- `beds_status.txt` to save and load bed occupancy information

These files are created automatically when the program runs.

## Technologies and Concepts

- C programming
- Parallel arrays
- One-dimensional and two-dimensional arrays
- Functions
- Loops and conditional statements
- String handling
- Bubble sort
- Linear search
- File handling
- Input validation

## How to Run

1. Download or clone this repository.
2. Open the project in Code::Blocks or another C IDE.
3. Compile `main.c`.
4. Run the program.
5. Select an option from the main menu.

## Repository

[Smart Hospital Admission System](https://github.com/dinithsenurarajapaksha-svg/Smart-Hospital-Admission-System)

## Author

Dinith Senura Rajapaksha
