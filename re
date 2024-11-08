# Entity Matching System

This repository contains a solution for entity matching, focusing on name matching. The solution leverages a Random Forest model combined with various name similarity measures to accurately label name pairs as matches or non-matches. 

## Features
- **Multiple Approaches**: Three approaches for entity matching, including rule-based and machine learning methods.
- **Pre-trained Model**: A pre-trained Random Forest model (`pkl_file_random_forest.pkl`) is included for quick execution.
- **Excel Input/Output**: Accepts input in Excel format and generates an output file with similarity scores and match labels.

## Prerequisites
- **Python 3.x**
- Required Python libraries:
  - `pandas` for data manipulation
  - `scikit-learn` for machine learning
  - `joblib` for loading the model
  - `openpyxl` for reading and writing Excel files

If you haven't installed the necessary libraries, install them by running:
```bash
pip install pandas scikit-learn joblib openpyxl
File Structure
Ensure that your project directory has the following structure:

bash
Copy code
entity_matching_system/
├── all_approaches.py              # File 1: code implementing all three approaches
├── final_approach.py              # File 2: code for generating the .pkl file
├── pkl_file_random_forest.pkl     # File 3: pre-trained model file
├── pie_entity_matching_solution.py # File 4: testing script
├── input_data.xlsx                # Input Excel file with names for matching
Steps to Run the Code
1. Clone the Repository
Clone this repository to your local machine. In your terminal or command prompt, run:

bash
Copy code
git clone [GitHub Link Here]
cd entity_matching_system
2. Install Dependencies
Ensure that you have the necessary libraries installed. You can install them by running:

bash
Copy code
pip install pandas scikit-learn joblib openpyxl
3. Prepare the Input File (Excel)
Create an Excel file named input_data.xlsx with two columns: name1 and name2. These columns should contain the names you want to compare for matching. Place this file in the project directory.

Example of input data (Excel format):
Name 1	Name 2
John Smith	Jon Smith
Alice Lee	Alyce Lee
Mike Tyler	Jon Smith
4. Modify the Input File Path (if needed)
In pie_entity_matching_solution.py, make sure the input_file variable is correctly pointing to your input Excel file:

python
Copy code
input_file = 'input_data.xlsx'
5. Run the Testing Script
After setting up the input file, run the testing script to perform entity matching. Use the following command:

bash
Copy code
python pie_entity_matching_solution.py
The script will:

Load the pre-trained Random Forest model from pkl_file_random_forest.pkl.
Load the input Excel file containing the name pairs.
Perform the name matching to generate similarity scores and labels.
Save the results in a new Excel file named output_predictions.xlsx.
6. Output File
After running the script, you will find output_predictions.xlsx in the project directory. It contains the following columns:

Name 1	Name 2	Similarity Score	Label
John Smith	Jon Smith	0.98	1
Alice Lee	Alyce Lee	0.94	1
Mike Tyler	Jon Smith	0.17	0
Similarity Score: A numerical value representing the similarity between name1 and name2.
Label: A binary label indicating whether the names match (1 for match, 0 for no match).
