# Electrical Load Monitoring and Billing System

A simple C++ console project for registering electrical appliances, viewing their daily energy usage, searching appliances, and calculating electricity bills.

## Features

- Register appliances
- View all registered appliances
- Search for an appliance by name
- Show daily energy summary
- Calculate electricity bill
- Save appliance records to a file
- Load saved appliance records when the program starts
- Save billing summary to a file

## Files Used

- `main.cpp` - main source code
- `appliances.txt` - stores registered appliance data
- `billing_summary.txt` - stores the latest billing summary

## Appliance Data Format

Each appliance is stored in this format:

```text
ApplianceName,PowerInWatts,HoursPerDay
```

Example:

```text
Fan,75,10
Television,120,5
Fridge,150,24
```

## How the Program Works

### Register Appliance

The user enters:

- appliance name
- power rating in watts
- usage hours per day

The appliance is added to the list and saved to `appliances.txt`.

### View Appliances

Displays all registered appliances with:

- name
- power rating
- hours used per day

### Search Appliance

Allows the user to search for an appliance by name.

### Energy Summary

Shows the daily energy used by each appliance in `kWh/day` and the total daily energy usage.

### Calculate Electricity Bill

The user enters the cost per `kWh`.

Formula:

```text
Bill = Total Energy × Cost per kWh
```

Energy formula:

```text
Energy (kWh/day) = (Power in Watts × Hours per Day) / 1000
```

The result is displayed and also saved to `billing_summary.txt`.

## Sample Menu

```text
1. Register appliance
2. View appliances
3. Search appliance
4. Energy summary
5. Calculate electricity bill
0. Exit
```

## How to Compile

```bash
g++ main.cpp -o load_monitor
```

## How to Run

```bash
./load_monitor
```

On Windows:

```bash
load_monitor.exe
```

## Requirements

- C++ compiler
- Terminal or command prompt

## Purpose of the Project

This project helps in learning:

- structs in C++
- vectors
- functions
- file handling
- input and output
- simple billing calculations
