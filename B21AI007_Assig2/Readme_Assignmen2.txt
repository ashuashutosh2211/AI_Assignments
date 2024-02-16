TA Assignment System

This Python program is designed to automate the allocation of Teaching Assistants (TAs) to courses based on student preferences, course capacities, and other constraints.

Table of Contents
- Prerequisites
- Getting Started
  - Installation
  - Data Preparation
- Usage
- Algorithm Overview
- Results


Prerequisites

Before you get started, make sure you have the following:
- Python 3.x
- pandas library
- matplotlib library for visualizations

Getting Started

Installation

Use google colab or jupyter notebook or any othre preferred tool to run and use .ipynb file

Data Preparation

1. Prepare your data files:
   - Create two CSV files: data.csv and courses.csv.
   - data.csv should contain TA applications, including their preferences, programs, and grades.
   - courses.csv should contain course information, including course names, capacities, and offered for which programs.

2. Edit the Python script to customize any parameters:
   - You can adjust the TA-to-credit ratio (ta_per_credit_per_student) based on your specific requirements.
   - Ensure that the seniority levels are correctly defined in the seniority dictionary.

Usage

Run the program using Python:
python <file_name>.py (B21AI007_Assignment2.py)

The program will attempt to allocate TAs to courses based on the defined constraints and preferences. The results will be displayed, including the allocation and various statistics.

Algorithm Overview

The program uses a backtracking search algorithm to find an optimal TA allocation based on the following constraints:
- constraints for TAs.
- Seniority-based preferences.
- Course capacity constraints.

Results

The program will display the allocation results, preference distributions, and program distributions. It will also generate CSV files for allocated and unallocated TAs for further analysis.

