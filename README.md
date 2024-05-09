Inventory Control User Manual

Introduction
The Inventory Control program is designed to help users manage a vehicle inventory. It provides the functionality to add new vehicles, delete existing vehicles, view the current inventory, and save changes to “inventory.csv”

Installation
To use Inventory Control, please follow these instructions.
1.	Compile the program using a C++ compiler such as Visual Studio.
2.	Run the executable. (Make sure “inventory.csv” is in the same directory as the executable)
3.	Follow the on-screen instructions.

Menu Options
The Inventory Control program offers the following menu options:
1.	Add Vehicle: This option allows you to add a new vehicle to the inventory. You will be prompted to enter the Stock Number, Year, Make, Model, and VIN (Vehicle Identification Number) of the vehicle.

2.	Delete Vehicle: Use this option to delete an existing vehicle from the inventory. Enter the Stock Number of the vehicle you wish to remove.

3.	View Inventory: Selecting this option will display the current inventory of vehicles.

4.	Save and Exit: Choose this option to save the inventory and exit the program.

Input Validation
To ensure that vehicles are entered properly, the Inventory Control Program provides input validation.
•	Stock Number: Must be an unique integer. The program will prompt you to enter a different stock number if the one provided is already in use.

•	Year: It must be an four-digit integer between 1900 and 2030.

•	VIN(Vehicle Identification Number): Must be an unique string of exactly 17 characters. If it is not the correct length or is already used, you will be asked to enter a different VIN.

Exiting the Program
Please select 4 in the Menu to save the inventory and exit the program.

Notes
This program uses a simple .csv file to store Inventory Data across multiple sessions.  “inventory.csv” must be in the same directory as the executable.

Summary
The Inventory Control program provides a powerful yet user-friendly to solution to managing your vehicle inventory. By following the instructions and guidelines in this manual, you will be able to add, delete, and view vehicles in your inventory!
Thank you for choosing Inventory Control!
